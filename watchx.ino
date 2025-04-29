// Created by:  Airasz
// board esp8266: 1MB/256KBFS, 80mhzCPU, 25MhZcrystalFreq
//  methode: usb or software serial

#include <SPI.h>
#define FS_NO_GLOBALS
#include <FS.h>
#include <SoftwareSerial.h>
// #include <Tone32.h>
// #include "pitches.h"
#include "watchx.h"
#include <TimeLib.h>

// #define SS_DISABLE 0x1062 // black

#define SS_DISABLE 0  // black

#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// ESP32 CS(SS)=5,SCL(SCK)=18,SDA(MOSI)=23,BUSY=15,RES(RST)=2,DC=0

// 1.54'' EPD Module
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ 5, /*DC=*/17, /*RES=*/2, /*BUSY=*/15));  // GDEH0154D67 200x200, SSD1681

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

uint16_t analogClockProps[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
String nsb15 = "NotoSansBold15";
String sui14 = "SegoeUI-14";
String sfpt_r14 = "SFProText-Regular-14";
String sfpt_r16 = "SFProText-Regular-16";
String sfpt_r18 = "SFProText-Regular-18";
String sfpd_r20 = "SFProDisplay-Regular-20";
String sfpd_r24 = "SFProDisplay-Regular-24";
String sfpd_r28 = "SFProDisplay-Regular-28";

int ihscore = 0;  // home score in integer
int iascore = 0;  // away score in integer

const struct site_t {
  char *title;
  char *url;
  char *contentsToDisplay;
} sites[] = {
  { "bananab", "http://192.168.10.232/radio/oradio.php?cmd=status", "title" },
  { "bananay", "http://192.168.1.152/radio/oradio.php?cmd=status", "title" },
  { "orangeb", "http://192.168.10.200/radio/oradio.php?cmd=status", "title" },
  { "orangey", "http://192.168.1.120/radio/oradio.php?cmd=status", "title" }
};
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
int blinkduration = 9;  // by point (1=9)
int endmatch = 0;
int startblink = 0;
int endblink = 0;
#define usbbaud 115200
int dmode = 10;
void setup(void) {
  Serial.begin(115200);
  // serial.begin(96050);
  // tone(BUZZER_PIN, tmpNOTE);
  // noTone(BUZZER_PIN);

  display.init(115200, true, 50, false);

  if (display.epd2.hasFastPartialUpdate) {
    // showPartialUpdate();
    delay(1000);
  }
  display.hibernate();

  pinMode(12, OUTPUT);

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
  while (WiFi.status() != WL_CONNECTED) {
    /* code */

    Serial.print(".");
    delay(200);
  }

  syncTime();
  // tft.fillScreen(TFT_BLACK);
  // ledcSetup(BUZZER_CHANNEL, 1000, 8);        // Configure PWM
  // ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL); // Attach the pin to the PWM channel
}

void syncTime() {
  if (Ping.ping(remote_host)) {
    Serial.println("has internet");
    timeClient.begin();
    timeClient.setTimeOffset(3600 * 7);
    timeClient.update();
    // setSyncProvider(timeClient.getEpochTime());
    // setTime(int hr, int min, int sec, int dy, int mnth, int yr)
    Serial.println("has internet, sync device with internet time");
    setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
            timeClient.getDay(), timeClient.getMonth(), timeClient.getYear());
    drawClockFace();
  } else {
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
void loop() {

  // while (serial.available() > 0)
  // {
  //   delay(10);
  //   c = serial.read();
  //   data += c;
  // }
  while (Serial.available() > 0) {
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length() > 0) {
    if (!data.startsWith("#"))
      proccesData(data);
    else
      proccesCMD(data.substring(1));
    data = "";
  }
  if (millis() > prevmill + 1000) {
    if (second() == 59)
      drawClockFace();
    if (dmode == 10) {
      // Serial.println("analog clock");
      if (oldss != second()) {
        oldss = second();
        if (minute() % 10 == 0 && second() < 4) {
          clockFace = random(5);
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
    if (toScreenSleep > maxWait) {
      toScreenSleep = 0;
      // testdrawtext("waiting for incoming data", COLOR_MEDIUM[random(12)]);
      // printWordWrap("waiting for incoming data", COLOR_MEDIUM[random(12)]);
    }
    prevmill = millis();
  }
  beepnblink();  // beepnblink.ino
}  // end loop
int displaylivescore = 0;
void proccesCMD(String data) {
  if (data.length() > 4) {

    //    Serial.println(data);
    // tb_display_print_String(data.c_str(), 20);
    toScreenSleep = 0;
    // if (data.length() > 10)
    //   maxWait = data.length() / 10
    // else
    maxWait = (data.length() > 18) ? data.length() / 6 : 40;
    // // tft.printf("maxwait = %d\n", maxWait);
    if (data.startsWith("rotation")) {
      int sr = data.substring(9).toInt();
      // printWordWrap("rotated", COLOR_MEDIUM[random(12)]);
      data = "";
      return;
    } else if (data.startsWith("resetscreen")) {
      // tft.fillScreen(TFT_BLACK);
      data = "";
      return;
    } else if (data.startsWith("setnote")) {
      // tft.fillScreen(TFT_BLACK);
      data = data.substring(8);
      // data.replace("\n", "");
      // data.replace("\r", "");
      // data.replace("\0", "");
      for (int i = 0; i < sizeof(notes) / sizeof(struct Note); i++) {
        // Serial.printf("note : -%s- -%s-\n", data, notes[i].name);

        if (data.startsWith(notes[i].name)) {
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

    else if (data.startsWith("blink")) {
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
    } else if (data.startsWith("clockface")) {
      int idata = data.substring(10).toInt();
      if (idata < 5) {
        if (idata != clockFace) {

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
    } else if (data.startsWith("shakeface")) {

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
    } else if (data.startsWith("settime")) {
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
      setTime(h, m, s, 2, 7, 2021);
      data = "";
      // setTime(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
      //             timeClient.getDay(), timeClient.getMonth(), timeClient.getYear());
      prevmill2 = millis();
      return;
    } else if (data.startsWith("longbeep")) {
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
    } else if (data.startsWith("endmatch")) {
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
    } else if (data.startsWith("animation")) {
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
    } else if (data.startsWith("dmode")) {
      if (data == "dmode") {
        // tft.fillScreen(TFT_BLACK);
        // tft.printf("dmode=%d\n0 livescore\n1 typing mode\n2 statis mode", dmode);

        return;
      } else {
        int dmod = data.substring(6).toInt();
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

void proccesData(String data) {

  if (data.length() > 4) {
    if (data.startsWith("noanim")) {
      noanim = true;
      data = data.substring(6);
    }
    toScreenSleep = 0;
    maxWait = (data.length() > 18) ? data.length() / 6 : 40;
    // // tft.printf("maxwait = %d\n", maxWait);
    if (data.startsWith("testnum")) {

      int sr = data.substring(7).toInt();
      // tft.fillScreen(TFT_BLACK);
      // testDTSegment(sr);
      data = "";
      return;
    } else if (data.startsWith("play pos")) {
      // printtextbig(data, COLOR_MEDIUM[random(12)]);
      data = "";
      return;
    }
    Serial.printf("dmode=%d\n", dmode);
    if (data.length() > 4)
      if (dmode == 0) {

        if (data != olddata) {
          olddata = data;
          displaylivescore = random(4);
        }
        maxWait = (data.length() > 10) ? data.length() / 2 : 80;

        // ssgmnt(homescore);

        // drawDigitLivescore(homescore);
        // tsgmnt(homescore);
      } else if (dmode == 1) {
        // data = data + "%";
        // tb_display_print_String(data.c_str(), 20);
      } else if (dmode == 2) {
        // displayinfo(data);
        // printWordWrap(data, COLOR_MEDIUM[random(12)]);
      } else if (dmode == 3) {
        // displayinfo(data);
      } else {
        // testdrawtext(data, COLOR_MEDIUM[random(10)]);
        // printWordWrap(data, COLOR_MEDIUM[random(12)]);
      }

    data = "";
  }
}

int cx = 0, cy = 15;
void printWordWrap(String text, uint16_t color) {

  int tl = text.length();
  int cymr = map(tl, 10, 100, 80, 15);
  printSplitString(text, color);
}
void printSplitString(String text, uint16_t color) {
  int wordStart = 0;
  int wordEnd = 0;
  while ((text.indexOf(' ', wordStart) >= 0) && (wordStart <= text.length())) {
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

void printtextbig(
  String text, uint16_t color) {

  delay(25);
  int tl = text.length();
  oldsdata = text;

  delay(25);
}
void printtextcs(int x, int y,
                 String text, uint16_t color, uint8_t fsize) {

  // tft.unloadFont();
  delay(25);
  if (fsize == 16) {
    // tft.loadFont(sfpt_r16);
  } else if (fsize == 18) {
    // tft.loadFont(sfpt_r18);
  } else if (fsize == 20) {
    // tft.loadFont(sfpd_r20);
  } else if (fsize == 24) {
    // tft.loadFont(sfpd_r24);
  } else {
    // tft.loadFont(sfpt_r16);
  }
  // tft.setCursor(x, y);
  // tft.setTextWrap(true);
  // // tft.setTextColor(TFT_BLACK, TFT_BLACK);
  // // tft.print(oldsdata);
  // // tft.fillScreen(TFT_BLACK);
  // // tft.setTextColor(color, TFT_BLACK);

  // // tft.print(tl);
  // tft.print(text);
  oldsdata = text;

  // tft.unloadFont();
  delay(25);
  // tft.loadFont(sfpt_r14);
}

void printtextcs(
  String text, uint16_t color, uint8_t fsize) {

  // tft.unloadFont();
  delay(25);
  if (fsize == 16) {
    // tft.loadFont(sfpt_r16);
  } else if (fsize == 18) {
    // tft.loadFont(sfpt_r18);
  } else if (fsize == 20) {
    // tft.loadFont(sfpd_r20);
  } else if (fsize == 24) {
    // tft.loadFont(sfpd_r24);
  } else {
    // tft.loadFont(sfpt_r16);
  }
  // tft.setCursor(cx, cy);
  // tft.setTextWrap(true);
  // // tft.setTextColor(TFT_BLACK, TFT_BLACK);
  // // tft.print(oldsdata);
  // tft.fillScreen(TFT_BLACK);
  int tl = text.length();
  int cymr = map(tl, 10, 100, 80, 15);
  // tft.setCursor(cx, random(1, cymr));
  // tft.setTextColor(color, TFT_BLACK);

  // // tft.print(tl);
  // tft.print(text);
  oldsdata = text;

  // tft.unloadFont();
  delay(25);
  // tft.loadFont(sfpt_r14);
}

void printTextWin(int winx, int winy, int width, int height, String text) {
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(winx, winy, width, height);
  // display.setFullWindow();
  display.firstPage();
  do {
    display.fillRect(winx, winy, width, height, GxEPD_WHITE);
    display.drawCircle(50, 50, 40, GxEPD_BLACK);

    display.setCursor(0, 0);
    display.print(text);
  } while (display.nextPage());
}
void printText(int x, int y, String text) {
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.drawCircle(50, 50, 40, GxEPD_BLACK);
    display.setCursor(x, y);
    display.print(text);
  } while (display.nextPage());
}

void printText(String text) {
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 0);
    display.print(text);
  } while (display.nextPage());
}

void drawClockFace() {
  if (clockFace == 0) {
    // analogClock(clockFace);
    printClock();
  } else {
    printClock();
    if (second() % 10 == 0) {
      // digitFace(clockFace - 1);
    }
  }
}
void printClock() {
  String date = timeClient.getFullFormattedTime();
  date.replace(" ", "\n");
  printText(0, random(50, 150), date);
}
