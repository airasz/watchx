// Created by:  Airasz
// board esp8266: 1MB/256KBFS, 80mhzCPU, 25MhZcrystalFreq
//  methode: usb or software serial

#include <SPI.h>
#define FS_NO_GLOBALS
#include <FS.h>
#include <SoftwareSerial.h>
// #include <Tone32.h>
#include "note.h"
// #include "pitches.h"
#include "watchx.h"
#include <TimeLib.h>

// #define SS_DISABLE 0x1062 // black

#define SS_DISABLE 0 // black

int tmpNOTE = 110;
// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)

// For 1.44" and 1.8" TFT with ST7735 use

#include "res.h"
float p = 3.1415926;

bool updateSecondhand = false;
String rssmsg[300];
String siteonread;
bool noanim = false;
bool animation = true;

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 0
uint16 analogClockProps[8] = {0, 0, 0, 0, 0, 0, 0, 0};
String nsb15 = "NotoSansBold15";
String sui14 = "SegoeUI-14";
String sfpt_r14 = "SFProText-Regular-14";
String sfpt_r16 = "SFProText-Regular-16";
String sfpt_r18 = "SFProText-Regular-18";
String sfpd_r20 = "SFProDisplay-Regular-20";
String sfpd_r24 = "SFProDisplay-Regular-24";
String sfpd_r28 = "SFProDisplay-Regular-28";

String scores = "";
String homescore = "";
String awayscore = "";
String hometeam = "";
String awayteam = "";
String matchtime = "";
int ihscore = 0; // home score in integer
int iascore = 0; // away score in integer

const struct site_t
{
  char *title;
  char *url;
  char *contentsToDisplay;
} sites[] = {
    {"bananab", "http://192.168.10.232/radio/oradio.php?cmd=status", "title"},
    {"bananay", "http://192.168.1.152/radio/oradio.php?cmd=status", "title"},
    {"orangeb", "http://192.168.10.200/radio/oradio.php?cmd=status", "title"},
    {"orangey", "http://192.168.1.120/radio/oradio.php?cmd=status", "title"}};
char *url = "http://192.168.10.232/radio/oradio.php?cmd=status";
String sdata;

// SoftwareSerial serial(21, 19);

long prevmill2 = 0;
long prevmill3 = 0;
int angka = 0;
bool blinking = false;
int nblinking = 6;
bool blinkstate = false;
int blinkval = 255;
int countblink = 22;
int blinkduration = 9; // by point (1=9)
int endmatch = 0;
int startblink = 0;
int endblink = 0;
#define usbbaud 115200
int dmode = 10;
void setup(void)
{
  Serial.begin(115200);
  // serial.begin(96050);
  // tone(BUZZER_PIN, tmpNOTE);
  // noTone(BUZZER_PIN);
  Serial.print("Hello! ST77xx TFT Test");
  // pinMode(25, OUTPUT);

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS initialisation failed!");
    while (1)
      yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nInitialisation done.");

  // digitalWrite(25, HIGH);
  // Use this initializer (uncomment) if you're using a 1.44" TFT
  // tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 0.96" 180x60 TFT
  // tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  // Use this initializer (uncomment) if you're using a 1.54" 240x240 TFT
  // tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels

  Serial.println("Initialized");

  uint16_t time = millis();
  // tft.fillScreen(TFT_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
  //  testdrawtext(usbbaud, TFT_WHITE);
  //  testdrawtext("USB serial screen fo pi-radio, baud = 115200\nWaiting for incoming signal...", TFT_WHITE);
  delay(1000);
  delay(200);
  noTone(BUZZER_PIN);

  WiFi.begin("ASUS", "air46664");
  // printtextcs(0, 0, "Connecting to WiFi...", TFT_WHITE, 16);
  while (WiFi.status() != WL_CONNECTED)
  {
    /* code */

    Serial.print(".");
    delay(200);
  }

  syncTime();
  // ledcSetup(BUZZER_CHANNEL, 1000, 8);        // Configure PWM
  // ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL); // Attach the pin to the PWM channel
}

void syncTime()
{
  if (Ping.ping(remote_host))
  {
    Serial.println("has internet");
    timeClient.begin();
    timeClient.setTimeOffset(3600 * 7);
    timeClient.update();
    // setSyncProvider(timeClient.getEpochTime());
    // setTime(int hr, int min, int sec, int dy, int mnth, int yr)
    Serial.println("has internet, sync device with internet time");
    setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
            timeClient.getDate(), timeClient.getMonth(), timeClient.getYear());
  }
  else
  {
    Serial.println("ping failed");
  }
}
long prevmill = 0;
String oldsdata;
int tryrequest = 0;
bool foundRadio = false;
String data;
char c;
int toScreenSleep = 0;
int maxWait = 20;
String olddata = "";
int clockFace = 3, oldClockFace = 0;
int oldss = 0;
void loop()
{

  // while (serial.available() > 0)
  // {
  //   delay(10);
  //   c = serial.read();
  //   data += c;
  // }
  while (Serial.available() > 0)
  {
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length() > 0)
  {
    // if (!data.startsWith("#"))
    //   // proccesData(data);
    //   else
    //       // proccesCMD(data.substring(1));
    //       data = "";
  }
  if (millis() > prevmill + 2000)
  {
    // Serial.printf("hijr : %s \n", nowHijr());
    Serial.printf("day : %d month : %dyear : %d \n", day(), month(), year());
    Serial.print("hijriah = ");
    Serial.println(nowHijr());
    if (second() == 10)
    {
      // Serial.println("analog clock");
      if (oldss != second())
      {
        oldss = second();
        if (minute() % 5 == 0 && second() < 4)
        {
          clockFace = random(5);
        }
        // drawClockFace();
      }
      // analogClock(0);
    }
    toScreenSleep++;
    // if (toScreenSleep > 10)
    // {
    //   testdrawtext("waiting for incoming data", COLOR_MEDIUM[random(10)]);
    // }
    // else
    // Serial.printf("maxwait = %d", maxWait);
    if (toScreenSleep > maxWait)
    {
      toScreenSleep = 0;
      // testdrawtext("waiting for incoming data", COLOR_MEDIUM[random(12)]);
      // printWordWrap("waiting for incoming data", COLOR_MEDIUM[random(12)]);
    }
    prevmill = millis();
  }
  beepnblink(); // beepnblink.ino
} // end loop
int displaylivescore = 0;