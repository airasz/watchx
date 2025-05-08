// Created by:  Airasz
// board esp8266: 1MB/256KBFS, 80mhzCPU, 25MhZcrystalFreq
//  methode: usb or software serial
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <SPI.h>
// #define FS_NO_GLOBALS
#include <SoftwareSerial.h>
// #include <Tone32.h>
// #include "pitches.h"
// #include "fonts.h"

// #include "Free_Fonts.h"
#include "watchx.h"
#include <TimeLib.h>

// #define SS_DISABLE 0x1062 // black

#define SS_DISABLE 0 // black

#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>
#include <Fonts/FreeMono24pt7b.h>

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include <Fonts/FreeMonoOblique9pt7b.h>
#include <Fonts/FreeMonoOblique12pt7b.h>
#include <Fonts/FreeMonoOblique18pt7b.h>
#include <Fonts/FreeMonoOblique24pt7b.h>

#include <Fonts/FreeMonoBoldOblique9pt7b.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>
#include <Fonts/FreeMonoBoldOblique24pt7b.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include <Fonts/FreeSansOblique9pt7b.h>
#include <Fonts/FreeSansOblique12pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Fonts/FreeSansOblique24pt7b.h>

#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>

#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerif24pt7b.h>

#include <Fonts/FreeSerifItalic9pt7b.h>
#include <Fonts/FreeSerifItalic12pt7b.h>
#include <Fonts/FreeSerifItalic18pt7b.h>
#include <Fonts/FreeSerifItalic24pt7b.h>

#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>

#include <Fonts/FreeSerifBoldItalic9pt7b.h>
#include <Fonts/FreeSerifBoldItalic12pt7b.h>
#include <Fonts/FreeSerifBoldItalic18pt7b.h>
#include <Fonts/FreeSerifBoldItalic24pt7b.h>

// #define TT1 &TomThumb

#define FM9 &FreeMono9pt7b
#define FM12 &FreeMono12pt7b
#define FM18 &FreeMono18pt7b
#define FM24 &FreeMono24pt7b

#define FMB9 &FreeMonoBold9pt7b
#define FMB12 &FreeMonoBold12pt7b
#define FMB18 &FreeMonoBold18pt7b
#define FMB24 &FreeMonoBold24pt7b
#define FMBO12 &FreeMonoBoldOblique12pt7b
#define FMBO18 &FreeMonoBoldOblique18pt7b
#define FMBO24 &FreeMonoBoldOblique24pt7b

#define FSS9 &FreeSans9pt7b
#define FSS12 &FreeSans12pt7b
#define FSS18 &FreeSans18pt7b
#define FSS24 &FreeSans24pt7b

#define FSSB9 &FreeSansBold9pt7b
#define FSSB12 &FreeSansBold12pt7b
#define FSSB18 &FreeSansBold18pt7b
#define FSSB24 &FreeSansBold24pt7b

#define FSSO9 &FreeSansOblique9pt7b
#define FSSO12 &FreeSansOblique12pt7b
#define FSSO18 &FreeSansOblique18pt7b
#define FSSO24 &FreeSansOblique24pt7b

#define FSSBO9 &FreeSansBoldOblique9pt7b
#define FSSBO12 &FreeSansBoldOblique12pt7b
#define FSSBO18 &FreeSansBoldOblique18pt7b
#define FSSBO24 &FreeSansBoldOblique24pt7b

#define FS9 &FreeSerif9pt7b
#define FS12 &FreeSerif12pt7b
#define FS18 &FreeSerif18pt7b
#define FS24 &FreeSerif24pt7b

#define FSI9 &FreeSerifItalic9pt7b
#define FSI12 &FreeSerifItalic12pt7b
#define FSI19 &FreeSerifItalic18pt7b
#define FSI24 &FreeSerifItalic24pt7b

#define FSB9 &FreeSerifBold9pt7b
#define FSB12 &FreeSerifBold12pt7b
#define FSB18 &FreeSerifBold18pt7b
#define FSB24 &FreeSerifBold24pt7b

#define FSBI9 &FreeSerifBoldItalic9pt7b
#define FSBI12 &FreeSerifBoldItalic12pt7b
#define FSBI18 &FreeSerifBoldItalic18pt7b
#define FSBI24 &FreeSerifBoldItalic24pt7b

#define FF0 NULL // ff0 reserved for GLCD
#define FF1 &FreeMono9pt7b
#define FF2 &FreeMono12pt7b
#define FF3 &FreeMono18pt7b
#define FF4 &FreeMono24pt7b

#define FF5 &FreeMonoBold9pt7b
#define FF6 &FreeMonoBold12pt7b
#define FF7 &FreeMonoBold18pt7b
#define FF8 &FreeMonoBold24pt7b

#define FF9 &FreeMonoOblique9pt7b
#define FF10 &FreeMonoOblique12pt7b
#define FF11 &FreeMonoOblique18pt7b
#define FF12 &FreeMonoOblique24pt7b

#define FF13 &FreeMonoBoldOblique9pt7b
#define FF14 &FreeMonoBoldOblique12pt7b
#define FF15 &FreeMonoBoldOblique18pt7b
#define FF16 &FreeMonoBoldOblique24pt7b

#define FF17 &FreeSans9pt7b
#define FF18 &FreeSans12pt7b
#define FF19 &FreeSans18pt7b
#define FF20 &FreeSans24pt7b

#define FF21 &FreeSansBold9pt7b
#define FF22 &FreeSansBold12pt7b
#define FF23 &FreeSansBold18pt7b
#define FF24 &FreeSansBold24pt7b

#define FF25 &FreeSansOblique9pt7b
#define FF26 &FreeSansOblique12pt7b
#define FF27 &FreeSansOblique18pt7b
#define FF28 &FreeSansOblique24pt7b

#define FF29 &FreeSansBoldOblique9pt7b
#define FF30 &FreeSansBoldOblique12pt7b
#define FF31 &FreeSansBoldOblique18pt7b
#define FF32 &FreeSansBoldOblique24pt7b

#define FF33 &FreeSerif9pt7b
#define FF34 &FreeSerif12pt7b
#define FF35 &FreeSerif18pt7b
#define FF36 &FreeSerif24pt7b

#define FF37 &FreeSerifItalic9pt7b
#define FF38 &FreeSerifItalic12pt7b
#define FF39 &FreeSerifItalic18pt7b
#define FF40 &FreeSerifItalic24pt7b

#define FF41 &FreeSerifBold9pt7b
#define FF42 &FreeSerifBold12pt7b
#define FF43 &FreeSerifBold18pt7b
#define FF44 &FreeSerifBold24pt7b

#define FF45 &FreeSerifBoldItalic9pt7b
#define FF46 &FreeSerifBoldItalic12pt7b
#define FF47 &FreeSerifBoldItalic18pt7b
#define FF48 &FreeSerifBoldItalic24pt7b

// #include <Fonts/FreeMono9pt7b.h>
// #include <Fonts/FreeMono12pt7b.h>
// #include <Fonts/FreeMono18pt7b.h>
// #include <Fonts/FreeMono24pt7b.h>

// // #include <Fonts/FreeMonoBold9pt7b.h>
// #include <Fonts/FreeMonoBold12pt7b.h>
// #include <Fonts/FreeMonoBold18pt7b.h>
// #include <Fonts/FreeMonoBold24pt7b.h>

// #include <Fonts/FreeMonoOblique9pt7b.h>
// #include <Fonts/FreeMonoOblique12pt7b.h>
// #include <Fonts/FreeMonoOblique18pt7b.h>
// #include <Fonts/FreeMonoOblique24pt7b.h>

// #include <Fonts/FreeMonoBoldOblique9pt7b.h>
// #include <Fonts/FreeMonoBoldOblique12pt7b.h>
// #include <Fonts/FreeMonoBoldOblique18pt7b.h>
// #include <Fonts/FreeMonoBoldOblique24pt7b.h>

// // #include <Fonts/FreeSans9pt7b.h>
// #include <Fonts/FreeSans12pt7b.h>
// #include <Fonts/FreeSans18pt7b.h>
// #include <Fonts/FreeSans24pt7b.h>

// #include <Fonts/FreeSansBold9pt7b.h>
// #include <Fonts/FreeSansBold12pt7b.h>
// #include <Fonts/FreeSansBold18pt7b.h>
// #include <Fonts/FreeSansBold24pt7b.h>

// #include <Fonts/FreeSansOblique9pt7b.h>
// #include <Fonts/FreeSansOblique12pt7b.h>
// #include <Fonts/FreeSansOblique18pt7b.h>
// #include <Fonts/FreeSansOblique24pt7b.h>

// #include <Fonts/FreeSansBoldOblique9pt7b.h>
// #include <Fonts/FreeSansBoldOblique12pt7b.h>
// #include <Fonts/FreeSansBoldOblique18pt7b.h>
// #include <Fonts/FreeSansBoldOblique24pt7b.h>

// #include <Fonts/FreeSerif9pt7b.h>
// #include <Fonts/FreeSerif12pt7b.h>
// #include <Fonts/FreeSerif18pt7b.h>
// #include <Fonts/FreeSerif24pt7b.h>

// #include <Fonts/FreeSerifItalic9pt7b.h>
// #include <Fonts/FreeSerifItalic12pt7b.h>
// #include <Fonts/FreeSerifItalic18pt7b.h>
// #include <Fonts/FreeSerifItalic24pt7b.h>

// #include <Fonts/FreeSerifBold9pt7b.h>
// #include <Fonts/FreeSerifBold12pt7b.h>
// #include <Fonts/FreeSerifBold18pt7b.h>
// #include <Fonts/FreeSerifBold24pt7b.h>

// #include <Fonts/FreeSerifBoldItalic9pt7b.h>
// #include <Fonts/FreeSerifBoldItalic12pt7b.h>
// #include <Fonts/FreeSerifBoldItalic18pt7b.h>
// #include <Fonts/FreeSerifBoldItalic24pt7b.h>

// #define FF0 NULL // ff0 reserved for GLCD
// #include <Fonts/FreeMono9pt7b.h>
// String pasaranWuku = Dino[day()];

// #include <Fonts/FreeMonoBold9pt7b.h>
// #include <Fonts/FreeMonoBold12pt7b.h>
// #include <Fonts/FreeMonoBold18pt7b.h>
// #include <Fonts/FreeMonoBold24pt7b.h>

// #include <Fonts/FreeMonoOblique9pt7b.h>
// #include <Fonts/FreeMonoOblique12pt7b.h>
// #include <Fonts/FreeMonoOblique18pt7b.h>
// #include <Fonts/FreeMonoOblique24pt7b.h>

// #include <Fonts/FreeMonoBoldOblique9pt7b.h>
// #include <Fonts/FreeMonoBoldOblique12pt7b.h>
// #include <Fonts/FreeMonoBoldOblique18pt7b.h>
// #include <Fonts/FreeMonoBoldOblique24pt7b.h>

// #include <Fonts/FreeSans9pt7b.h>
// #include <Fonts/FreeSans12pt7b.h>
// #include <Fonts/FreeSans18pt7b.h>
// #include <Fonts/FreeSans24pt7b.h>

// #include <Fonts/FreeSansBold9pt7b.h>
// #include <Fonts/FreeSansBold12pt7b.h>
// #include <Fonts/FreeSansBold18pt7b.h>
// #include <Fonts/FreeSansBold24pt7b.h>

// #include <Fonts/FreeSansOblique9pt7b.h>
// #include <Fonts/FreeSansOblique12pt7b.h>
// #include <Fonts/FreeSansOblique18pt7b.h>
// #include <Fonts/FreeSansOblique24pt7b.h>

// #include <Fonts/FreeSansBoldOblique9pt7b.h>
// #include <Fonts/FreeSansBoldOblique12pt7b.h>
// #include <Fonts/FreeSansBoldOblique18pt7b.h>
// #include <Fonts/FreeSansBoldOblique24pt7b.h>

// #include <Fonts/FreeSerif9pt7b.h>
// #include <Fonts/FreeSerif12pt7b.h>
// #include <Fonts/FreeSerif18pt7b.h>
// #include <Fonts/FreeSerif24pt7b.h>

// #include <Fonts/FreeSerifItalic9pt7b.h>
// #include <Fonts/FreeSerifItalic12pt7b.h>
// #include <Fonts/FreeSerifItalic18pt7b.h>
// #include <Fonts/FreeSerifItalic24pt7b.h>

// #include <Fonts/FreeSerifBold9pt7b.h>
// #include <Fonts/FreeSerifBold12pt7b.h>
// #include <Fonts/FreeSerifBold18pt7b.h>
// #include <Fonts/FreeSerifBold24pt7b.h>

// #include <Fonts/FreeSerifBoldItalic9pt7b.h>
// #include <Fonts/FreeSerifBoldItalic12pt7b.h>
// #include <Fonts/FreeSerifBoldItalic18pt7b.h>
// #include <Fonts/FreeSerifBoldItalic24pt7b.h>

// #include <Fonts/FreeMonoBold9pt7b.h>
// #include <Fonts/FreeSans9pt7b.h>
// #include <Fonts/FreeMonoBold12pt7b.h>
// #include <Fonts/FreeMonoBold18pt7b.h>
// #include <Fonts/FreeMonoBold24pt7b.h>
#include <FS.h>

File dbFile;
// ESP32 CS(SS)=5,SCL(SCK)=18,SDA(MOSI)=23,BUSY=15,RES(RST)=2,DC=0

// 1.54'' EPD Module
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ 5, /*DC=*/17, /*RES=*/4, /*BUSY=*/15)); // GDEH0154D67 200x200, SSD1681

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

uint16_t analogClockProps[8] = {0, 0, 0, 0, 0, 0, 0, 0};
String nsb15 = "NotoSansBold15";
String sui14 = "SegoeUI-14";
String sfpt_r14 = "SFProText-Regular-14";
String sfpt_r16 = "SFProText-Regular-16";
String sfpt_r18 = "SFProText-Regular-18";
String sfpd_r20 = "SFProDisplay-Regular-20";
String sfpd_r24 = "SFProDisplay-Regular-24";
String sfpd_r28 = "SFProDisplay-Regular-28";

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
// String prev_psa
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
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  display.init(115200, true, 50, false);

  if (display.epd2.hasFastPartialUpdate)
  {
    // showPartialUpdate();
    delay(1000);
  }
  // display.hibernate();

  pinMode(2, OUTPUT);
  if (!SPIFFS.begin(true))
  {
    Serial.println(F("An Error has occurred while mounting SPIFFS"));
  }
  // else
  // {
  //   startScreen(true, "success mount SPIFFS");
  // }
  // large block of text
  // // tft.fillScreen(TFT_BLACK);
  // testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", TFT_WHITE);
  // printText("USB serial screen fo pi-radio, baud = 115200\nWaiting for incoming signal...");
  //  testdrawtext(usbbaud, TFT_WHITE);
  //  testdrawtext("USB serial screen fo pi-radio, baud = 115200\nWaiting for incoming signal...", TFT_WHITE);
  delay(1000);
  // digitalWrite(25, LOW);
  // // tft.fillScreen(TFT_BLACK);
  printText("waiting for incoming data");
  delay(200);

  WiFi.begin("ASUS", "air46664");
  // printtextcs(0, 0, "Connecting to WiFi...", TFT_WHITE, 16);
  while (WiFi.status() != WL_CONNECTED)
  {
    /* code */

    Serial.print(".");
    delay(200);
  }
  digitalWrite(2, LOW);
  syncTime();
  // tft.fillScreen(TFT_BLACK);
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
    Serial.printf("weekday : %d \n", timeClient.getDay()); // hari kesekian tiap minggu
    Serial.printf("day  : %d \n", timeClient.getDay());
    imnt = timeClient.getMonth(), iday = timeClient.getDate();
    Serial.printf("mnt : %d | day %d\n", imnt, iday);
    printClock();
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
int clockFace = 1, oldClockFace = 0;
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
    if (!data.startsWith("#"))
      proccesData(data);
    else
      proccesCMD(data.substring(1));
    data = "";
  }
  if (millis() > prevmill + 1000)
  {
    if (second() == 1)
      drawClockFace();
    else if (second() == 2)
      display.hibernate();
    if (dmode == 10)
    {
      // Serial.println("analog clock");
      if (oldss != second())
      {
        oldss = second();
        if (minute() % 10 == 0 && second() < 4)
        {
          // clockFace = random(5);
          // tft.fillScreen(TFT_BLACK);
        }
        // analogClock(0);
        // digitalClock(1);
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
  beepnblink();     // beepnblink.ino
  blinkingtopray(); // beepnblink.ino
} // end loop
void fixClock()
{
  if (timeClient.getYear() == 1970)
  {
    timeClient.update();
    setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
            timeClient.getDate(), timeClient.getMonth(), timeClient.getYear());
    imnt = timeClient.getMonth(), iday = timeClient.getDate();
  }
  else
  {

    WiFi.mode(WIFI_OFF);
    // setCpuFrequencyMhz(20);
  }
}
int displaylivescore = 0;
void proccesCMD(String data)
{
  if (data.length() > 4)
  {

    //    Serial.println(data);
    // tb_display_print_String(data.c_str(), 20);
    toScreenSleep = 0;
    // if (data.length() > 10)
    //   maxWait = data.length() / 10
    // else
    maxWait = (data.length() > 18) ? data.length() / 6 : 40;
    // // tft.printf("maxwait = %d\n", maxWait);
    if (data.startsWith("rotation"))
    {
      int sr = data.substring(9).toInt();
      // printWordWrap("rotated", COLOR_MEDIUM[random(12)]);
      data = "";
      return;
    }
    else if (data.startsWith("resetscreen"))
    {
      // tft.fillScreen(TFT_BLACK);
      data = "";
      return;
    }
    else if (data.startsWith("setnote"))
    {
      // tft.fillScreen(TFT_BLACK);
      data = data.substring(8);
      // data.replace("\n", "");
      // data.replace("\r", "");
      // data.replace("\0", "");
      for (int i = 0; i < sizeof(notes) / sizeof(struct Note); i++)
      {
        // Serial.printf("note : -%s- -%s-\n", data, notes[i].name);

        if (data.startsWith(notes[i].name))
        {
          // tone(BUZZER_PIN, notes[i].note, 500, BUZZER_CHANNEL);
          // ledcWriteTone(BUZZER_CHANNEL, notes[i].note);

          tmpNOTE = notes[i].frequency;
          nblinking = 1;
          blinking = true;
          blinkduration = 9;
          startblink = 2;
          endblink = 8;
          angka = 0;
          countblink = 0;
          Serial.println("start beeping " + notes[i].name);
          data = "";
          prevmill2 = millis();
          // printWordWrap("note set to " + notes[i].name, COLOR_MEDIUM[random(12)]);
          break;
        }
      }

      // printWordWrap(data.substring(7), COLOR_MEDIUM[random(12)]);
    }

    else if (data.startsWith("blink"))
    {
      nblinking = data.substring(6).toInt();
      blinking = true;
      blinkduration = 9;
      startblink = 9;
      endblink = 10;
      countblink = 0;
      angka = 7;
      Serial.println("startblinking");
      data = "";
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("clockface"))
    {
      int idata = data.substring(10).toInt();
      if (idata < 5)
      {
        if (idata != clockFace)
        {

          // tft.fillScreen(TFT_BLACK);
          clockFace = idata;
          nblinking = 1;
          blinking = true;
          blinkduration = 9;
          startblink = 9;
          endblink = 10;
          countblink = 0;
          angka = 7;
          Serial.println("startblinking");
        }
      }
      data = "";
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("shakeface"))
    {

      // tft.fillScreen(TFT_BLACK);
      clockFace = random(5);
      nblinking = 1;
      blinking = true;
      blinkduration = 9;
      startblink = 9;
      endblink = 10;
      countblink = 0;
      angka = 7;
      Serial.println("startblinking");
      data = "";
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("settime"))
    {
      int h = data.substring(8, 10).toInt();
      int m = data.substring(11, 13).toInt();
      int s = data.substring(14, 16).toInt();
      updateSecondhand = false;
      nblinking = 1;
      blinking = true;
      blinkduration = 9;
      startblink = 9;
      endblink = 10;
      countblink = 0;
      angka = 7;
      Serial.println("startblinking");
      setTime(h, m, s, timeClient.getDate(), timeClient.getMonth(), timeClient.getYear());
      data = "";
      // setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
      //             timeClient.getDay(), timeClient.getMonth(), timeClient.getYear());
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("setdate"))
    {
      int d = data.substring(8, 10).toInt();
      int m = data.substring(11, 13).toInt();
      int y = data.substring(14, 18).toInt();
      updateSecondhand = false;
      nblinking = 1;
      blinking = true;
      blinkduration = 9;
      startblink = 9;
      endblink = 10;
      countblink = 0;
      angka = 7;
      Serial.println("startblinking");
      // setTime(h, m, s, 2, 7, 2021);
      setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
              d, m, y);
      data = "";
      // setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
      //             timeClient.getDay(), timeClient.getMonth(), timeClient.getYear());
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("longbeep"))
    {
      nblinking = 1;
      blinking = true;
      blinkduration = 9;
      startblink = 2;
      endblink = 8;
      angka = 0;
      countblink = 0;
      Serial.println("start beeping");
      data = "";
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("endmatch"))
    {
      nblinking = 2;
      blinking = true;
      blinkduration = 19;
      endmatch = 1;
      startblink = 9;
      endblink = 10;
      angka = 7;
      countblink = 0;
      Serial.println("start beeping");
      data = "";
      prevmill2 = millis();
      return;
    }
    else if (data.startsWith("animation"))
    {
      animation = !animation;
      nblinking = 1;
      blinking = true;
      blinkduration = 9;
      startblink = 9;
      endblink = 10;
      countblink = 0;
      angka = 7;
      Serial.println("startblinking");
      data = "";
      prevmill2 = millis();
      Serial.printf("animation  : %s \n", (animation) ? "true" : "false");
      // tft.fillScreen(TFT_BLACK);
      // tft.printf("animation  : %s \n", (animation) ? "true" : "false");
      data = "";
      return;
    }
    else if (data.startsWith("dmode"))
    {
      if (data == "dmode")
      {
        // tft.fillScreen(TFT_BLACK);
        // tft.printf("dmode=%d\n0 livescore\n1 typing mode\n2 statis mode", dmode);

        return;
      }
      else
      {
        int dmod = data.substring(6).toInt();
      https: // www.goal.com/en/match/al-naft-vs-duhok/VxL4dxAH-wWwdSVLTwcV6
        if (dmod == 10 && dmode != 10)
          // tft.fillScreen(TFT_BLACK);
          if (dmod < 3 || dmod == 10)
            dmode = dmod;
        // Serial.println("startblinking");
        // tft.setCursor(0, 0);
        // // tft.setTextSize(2);
        Serial.printf("change display mode to : %d \n", dmode);
        // tft.fillScreen(TFT_BLACK);
        // tft.printf("dmode=%d\n0 livescore\n1 typing mode\n2 statis mode", dmode);
        // // tft.setTextSize(1);
        data = "";
        return;
      }
    }

    data = "";
  }
}

void proccesData(String data)
{
  if (data.length() > 4)
  {
    if (data.startsWith("noanim"))
    {
      noanim = true;
      data = data.substring(6);
    }
    toScreenSleep = 0;
    maxWait = (data.length() > 18) ? data.length() / 6 : 40;
    // // tft.printf("maxwait = %d\n", maxWait);
    if (data.startsWith("testnum"))
    {

      int sr = data.substring(7).toInt();
      // tft.fillScreen(TFT_BLACK);
      // testDTSegment(sr);
      data = "";
      return;
    }
    else if (data.startsWith("play pos"))
    {
      // printtextbig(data, COLOR_MEDIUM[random(12)]);
      data = "";
      return;
    }
    Serial.printf("dmode=%d\n", dmode);
    if (data.length() > 4)
      if (dmode == 0)
      {

        if (data != olddata)
        {
          olddata = data;
          displaylivescore = random(4);
        }
        maxWait = (data.length() > 10) ? data.length() / 2 : 80;

        // ssgmnt(homescore);

        // drawDigitLivescore(homescore);
        // tsgmnt(homescore);
      }
      else if (dmode == 1)
      {
        // data = data + "%";
        // tb_display_print_String(data.c_str(), 20);
      }
      else if (dmode == 2)
      {
        // displayinfo(data);
        // printWordWrap(data, COLOR_MEDIUM[random(12)]);
      }
      else if (dmode == 3)
      {
        // displayinfo(data);
      }
      else
      {
        // testdrawtext(data, COLOR_MEDIUM[random(10)]);
        // printWordWrap(data, COLOR_MEDIUM[random(12)]);
      }

    data = "";
  }
}

int cx = 0, cy = 15;
void printWordWrap(String text, uint16_t color)
{
  int tl = text.length();
  int cymr = map(tl, 10, 100, 80, 15);
  printSplitString(text, color);
}
void printSplitString(String text, uint16_t color)
{
  int wordStart = 0;
  int wordEnd = 0;
  while ((text.indexOf(' ', wordStart) >= 0) && (wordStart <= text.length()))
  {
    wordEnd = text.indexOf(' ', wordStart + 1);
    // uint16_t len = // tft.textWidth(text.substring(wordStart, wordEnd));
    // if (// tft.getCursorX() + len >= // tft.width()) {
    // tft.println();
    // if (wordStart > 0)
    //   wordStart++;
  }
  // tft.print(text.substring(wordStart, wordEnd));
  wordStart = wordEnd;
}

void printInWin(int winx, int winy, int width, int height, int cx, int cy, String text, bool flushwin)
{
  display.setPartialWindow(winx, winy, width, height);
  // display.setFullWindow();
  display.firstPage();
  do
  {
    if (flushwin)
      display.fillRect(winx, winy, width, height, GxEPD_WHITE);
    // if (drawframe)
    //   display.drawRect(winx, winy, width, height, GxEPD_BLACK);
    // display.drawCircle(50, 50, 40, GxEPD_BLACK);

    int yy = getTextProp("y", text) * (-1);
    Serial.printf(" yy : %d \n", yy);
    display.setCursor(winx + cx, winy + yy + cy);
    display.print(text);
  } while (display.nextPage());
}
void printTextWin(int winx, int winy, int width, int height, String text, bool drawframe)
{
  display.setRotation(3);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(winx, winy, width, height);
  // display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillRect(winx, winy, width, height, GxEPD_WHITE);
    if (drawframe)
      display.drawRect(winx, winy, width, height, GxEPD_BLACK);
    // display.drawCircle(50, 50, 40, GxEPD_BLACK);
    int yy = getTextProp("y", text) * (-1);
    Serial.printf(" yy : %d \n", yy);
    display.setCursor(winx, winy + yy);
    display.print(text);
  } while (display.nextPage());
}

void printTextWin(int winx, int winy, int width, int height, int fontsize, String text, bool drawframe)
{
  display.setRotation(3);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  display.setTextColor(GxEPD_BLACK);
  if (fontsize == 9)
  {
    // display.setFont(&FreeMonoBold9pt7b);
    display.setFont(FMB9);
  }
  else if (fontsize == 12)
  {
    display.setFont(&FreeMonoBold12pt7b);
  }
  else if (fontsize == 18)
  {
    display.setFont(&FreeMonoBold18pt7b);
  }
  else if (fontsize == 24)
  {
    display.setFont(&FreeMonoBold24pt7b);
  }
  else
  {
    // display.setFont(&FreeMonoBold9pt7b);
    display.setFont(FMB9);
  }
  display.setPartialWindow(winx, winy, width, height);
  // display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillRect(winx, winy, width, height, GxEPD_WHITE);
    if (drawframe)
      display.drawRect(winx, winy, width, height, GxEPD_BLACK);
    // display.drawCircle(50, 50, 40, GxEPD_BLACK);

    display.setCursor(winx, winy + 10);
    display.print(text);
  } while (display.nextPage());
}
void printText2(int x, int y, String text, bool flush = false)
{
  display.setRotation(3);
  // display.setFont(&FreeSansBold9pt7b);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  // display.setFont(FMBO9);
  display.setTextColor(GxEPD_BLACK);

  (flush) ? display.setFullWindow() : display.setPartialWindow(x, y, 200 - x, 200 - y);
  display.firstPage();
  do
  {
    if (flush)
      display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y + 12);
    display.print(text);
  } while (display.nextPage());
}

void printText2(int x, int y, int fontsize, String text, bool flush = false)
{
  if (fontsize == 9)
  {
    // //display.setFont(&FreeMonoBold9pt7b);display.setFont(FMB9);
    display.setFont(FMB9);
  }
  else if (fontsize == 12)
  {
    // display.setFont(&FreeMonoBold12pt7b);
    display.setFont(FMB12);
    // display.setFont(FSSB12);
  }
  else if (fontsize == 18)
  {
    // display.setFont(&FreeMonoBold18pt7b);
    display.setFont(FMB18);
  }
  else if (fontsize == 24)
  {
    // display.setFont(&FreeMonoBold24pt7b);
    display.setFont(FMB24);
  }
  else
  {
    // //display.setFont(&FreeMonoBold9pt7b);display.setFont(FMB9);
    display.setFont(FMB9);
  }

  (flush) ? display.setFullWindow() : display.setPartialWindow(x, y, 200 - x, 200 - y);
  display.firstPage();
  do
  {
    if (flush)
      display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y + 12);
    display.print(text);
  } while (display.nextPage());
}
void printText(int x, int y, String text)
{
  display.setRotation(3);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do
  {
    // display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 0, 200, 200, GxEPD_WHITE);
    // display.drawCircle(50, 50, 40, GxEPD_BLACK);
    display.setCursor(x, y);
    display.print(text);
  } while (display.nextPage());
}
void printText(String text, bool flush = false)
{
  display.setRotation(3);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  display.setTextColor(GxEPD_BLACK);
  // display.setFullWindow();
  display.firstPage();
  do
  {
    if (flush)
      display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 12);
    display.print(text);
  } while (display.nextPage());
}

void printText(String text)
{
  display.setRotation(3);
  // display.setFont(&FreeMonoBold9pt7b);
  display.setFont(FMB9);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 12);
    display.print(text);
  } while (display.nextPage());
}
void drawClockFace()
{
  fixClock();
  Serial.printf("clockface : %d \n", clockFace);
  Serial.printf("timelib :wday %d | day %d\n", weekday(), day());
  Serial.printf("tclient :day %d | date %d\n", timeClient.getDay(), timeClient.getDate());
  if (clockFace == 0)
  {
    standartFace();
  }
  else if (clockFace == 1)
  {
    javaneseFace();
  }
  else
  {
    // printClock();
    if (second() % 10 == 0)
    {
      // digitFace(clockFace - 1);
    }
  }

  digitalWrite(2, LOW);
}
void printClock()
{
  Serial.println("print clock");
  fixClock();

  standartFace();
  // javaneseFace();
  // printText(0, random(50, 150), date);
  Serial.printf("now : %d \n", now());
  digitalWrite(2, LOW);

  // Serial.println(getWuku());
  // Serial.printf("wuku : %s \n", getWuku());
  // printTextWin(random(60), random(60), 120, 120, date, true);
}
void standartFace()
{
  String date = timeClient.getFullFormattedTime();
  date = date.substring(0, (date.length() - 3)); // trim second
  // hh = timeClient.getHours(), mm = timeClient.getMinutes(), ss = timeClient.getSeconds();
  hh = hour(), mm = minute(), ss = second();
  date.replace(" ", "\n");
  // printText(0, random(50, 150), date);

  // printText(0, 12, date);

  digitalWrite(2, HIGH);
  printTextWin(0, 0, 200, 32, date, false);

  showDayPray();
}
void javaneseFacee()
{
  // printText2(0, 100, "test", true);
  digitalWrite(2, HIGH);
  printTextWin(0, 0, 200, 32, "test", false);
}
void javaneseFace()
{
  // int currentHour = timeClient.getHours();
  // int currentMinute = timeClient.getMinutes();
  hh = hour(), mm = minute(), ss = second();
  int currentHour = hour();
  int currentMinute = minute();
  String word, word1, word2;
  digitalWrite(2, HIGH);
  // printText2(0, 100, "test", true);
  delay(50);
  if (currentMinute < 40)
  {
    if (currentMinute == 30)
    {

      word = minuteTOword(currentMinute);
      word1 = "\n" + (currentHour == 23) ? "    " : "   ";
      word2 = jamTOword(currentHour - ((currentHour == 23) ? 11 : (-1)));
    }
    else if (currentMinute == 0 || currentMinute == 15)
    {
      word = jamTOword(currentHour);
      word1 = " \n    ";
      word2 = minuteTOword(currentMinute);
    }
    else
    {
      word = jamTOword(currentHour);
      word1 = "\n  luwih\n   ";
      word2 = minuteTOword(currentMinute);
    }
  }
  else
  {

    word = jamTOword(currentHour + 1);
    word1 = "\n   kurang\n      ";
    word2 = minuteTOword(currentMinute);
  }
  // String pasaranWuku = Dino[day()];
  // pasaranWuku = Dino[timeClient.getDay()];
  pasaranWuku = Dino[weekday() - 1];
  pasaranWuku += " ";
  pasaranWuku += pasaran[jumlahhari() % 5];
  pasaranWuku += "\n";
  pasaranWuku += getWuku();
  // pasaranWuku += "\n==============\n";

  // display.setTextWrap(true);
  // Serial.printf("pw  : %s ppw : %s\n", pasaranWuku, prev_pasaranWuku);
  // Serial.print(pasaranWuku);
  // Serial.print(" >< ");
  // Serial.println(prev_pasaranWuku);
  // Serial.printf(" pasaranwuku length : %d \n", pasaranWuku.length());
  display.setFont(FMB12);
  display.setTextColor(GxEPD_BLACK);
  int linespace = 50;
  if (!pasaranWuku.equals(prev_pasaranWuku))
  {
    Serial.println("update pasaran");
    prev_pasaranWuku = pasaranWuku;
    // printTextWin(0, 0, 200, 32, pasaranWuku, false);
    printInWin(0, 0, 200, linespace, 0, 0, pasaranWuku, true);
  }

  // printInWin(0, 0, 200, 32, 0, 0, pasaranWuku, true);
  String triword = word + word1 + word2;
  triword += checkPray();
  // triword.replace(" ", "");
  // pasaranWuku += triword;

  int16_t tbx, tby;
  uint16_t tbw, tbh;
  // display.getTextBounds(triword, 0, 0, &tbx, &tby, &tbw, &tbh);
  // printTextWin(0, 32, 200, 200 - 32, triword, true);
  int nl = countNewlines(triword);
  int fh = getTextProp("h", triword);
  Serial.printf(" fh : %d \n", fh);
  int sy = ((200 - linespace) / 2) - (nl * fh);
  Serial.printf(" sy : %d \n", sy);
  int cy = (checkPray() == "") ? fh / 2 : 0;
  // triword += masehiKeHijriah();
  // printInWin(0, linespace, 200, 200 - linespace, 0, random(sy, sy + 10), triword, true);
  // printInWin(0, linespace, 200, 200 - linespace, 0, fh / 2, triword, true);
  printInWin(0, linespace, 200, 200 - linespace, 0, cy, triword, true);
  // printTextWin(0, 0, 200, 32, pasaranWuku, false);
}

double getJulianDay(int year, int month, int day)
{
  if (month < 3)
  {
    year--;
    month += 12;
  }
  int a = floor(year / 100.0);
  // https: // idn00166.tigoals212.com/football/2734765-bahia-vs-botafogo-rj.html
  int b = 2 - a + floor(a / 4.0);
  return floor(365.25 * (year + 4716)) + floor(30.6001 * (month + 1)) + day + b - 1524.5;
}

// digunakan untuk menghitung hari pasaran
int jumlahhari()
{
  // DateTime now = RTC.now();
  // int d = timeClient.getDate();
  // int m = timeClient.getMonth();
  // int y = timeClient.getYear();
  int d = day();
  int m = month();
  int y = year();
  int hb[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
  int ht = (y - 1970) * 365 - 1;
  int hs = hb[m - 1] + d;
  int kab = 0;
  int i;
  if (y % 4 == 0)
    if (m > 2)
      hs++;
  for (i = 1970; i < y; i++)
    if (i % 4 == 0)
      kab++;

  return (ht + hs + kab);
}
String getWuku()
{

  // timeClient.getDate=day();
  // timeClient.getDay=weekday();
  // bulan kurangi 1 kali 4
  // int wu_m = (timeClient.getMonth() - 1) * 4; // step 1
  int wu_m = (month() - 1) * 4; // step 1
  if (wu_m == 0)
    return "exit wum=0";
  // Serial.printf(" wum : %d \n", wu_m);

  // tgl dibagi 7 dibulatkan
  // int wu_d = round(timeClient.getDate() / 7); // step 2
  // int wu_d = round((timeClient.getDate() - timeClient.getDay()) / 7); // step 2
  int wu_d = round((day() - weekday()) / 7); // step 2
  // Serial.printf(" wud : %d \n", wu_d);

  // int hasil = (wu_m + wu_d > 30) ? (wu_m + wu_d) - 30 : wu_m + wu_d; // step3
  // jumlahkan hasil keduanya
  int hasil = wu_m + wu_d;

  // Serial.printf(" hasil : %d \n", hasil);
  int hasil2 = hasil + nnilaiwuku();
  // Serial.printf(" hasil2 : %d \n", hasil2);
  if (hasil2 > 30)
    hasil2 -= 30;
  // Serial.printf(" hasil2 fix 30 : %d \n", hasil2);
  // int hasil3 = hasil2 + blnpenyesuaian[timeClient.getMonth()];
  int hasil3 = hasil2 + blnpenyesuaian[month()];
  // Serial.printf("hasil3 : %d \n", hasil3);
  return wuku[hasil3 - 1];
}
int nnilaiwuku()
{
  int rtr = nilaiwuku[(timeClient.getYear() - 2020)];
  // Serial.printf("now year %d nnilaiwuku : %d \n", timeClient.getYear(), rtr);
  return rtr;
}
int countNewlines(String str)
{
  int count = 0;
  for (int i = 0; i < str.length(); i++)
  {
    if (str.charAt(i) == '\n')
    {
      count++;
    }
  }
  return count;
}
// x=cursor x
int getTextProp(String p, String text)
{

  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  int r = 0;
  if (p.equals("x"))
    r = tbx;
  else if (p.equals("y"))
    r = tby;
  else if (p.equals("w"))
    r = tbw;
  else if (p.equals("h"))
    r = tbh;
  return r;
}