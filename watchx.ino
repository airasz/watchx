//mym5stick watch
#include <M5StickC.h>
#include "battery.h"
#include "res.h"
#include "clock_face.h"

#include <Preferences.h>
Preferences preferences;

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
// #include "Free_Fonts.h"
// LOAD_GFXFF // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
// #define GFXFF 1
// #define SMOOTH_FONT
// #define GFXFF 1

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t value = 0;

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

bool standby = 0;
bool newNotification = 0;
String pushmsg;
bool clockHasSet = 0;
int indexOfBody;
int indexOfNotif = -1;
String header;
String body1, body2, body3, body4;
String msgg[] = {body1, body2, body3, body4};
String msg1, msg2, msg3, msg4;
String msgg2[] = {msg1, msg2, msg3, msg4};
String header1, header2, header3, header4;
String headers[] = {header1, header2, header3, header4};
bool flashInfo = 0;
bool showmsg = 0;
int countindex;

int BUTTON_HOME = GPIO_NUM_37;
int BUTTON_PIN = GPIO_NUM_39;

//=======RTC DATA=======
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int lcdBrightness = 9;
RTC_DATA_ATTR int clock_style = 0;
RTC_DATA_ATTR int savedScreenOrientation = 1;

uint8_t minbright = 7;
uint8_t maxbright = 15;
uint8_t lastBrightness;
int16_t accX = 0;
int16_t accY = 0;
int16_t accZ = 0;

int16_t gyroX = 0;
int16_t gyroY = 0;
int16_t gyroZ = 0;

int page = 0;
int lastPage;
long last_rtc_update_time = 0;
int increament = 0;
// const uint32_t COLORS_LIGHT[10] = {
//   0xff4aad, 0x0e88fe, 0xcc03fc, 0xfe49ad, 0xff0505,
//   0xfa660d, 0xfff800, 0x14fa00, 0x0496ff, 0xc900ff
// };

// const uint32_t COLORS_DARK[10] = {
//   0x471f32, 0x002548, 0x3b004b, 0x3e1a2c, 0x4a000c,
//   0x4a1e00, 0x4b4500, 0x004700, 0x022242, 0x380249
// };

byte zero = 0x00; //workaround for issue #527
int ct1 = 1;
int ta = 9;
int tb = 8;
int tc = 7;
int t1, t2, t3, j, mn, d, tg, bl, th, hk, tg2;
String hari;
String b1, b2, baris1, baris2;
int k = 1;
int tm = 1;
int j_1, j_2, m1, m2, d1, d2;
int ct2, ct3, ht;
boolean lt1 = false;
boolean lt3 = false;
boolean lt2 = false;
boolean jshalat = true;
String kl = "±";

int Bulan, tgl, sh, is, dz, as, mg;
int clockMode = 1;
//analog clock variable

int longSleep;
#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 18       /* Time ESP32 will go to sleep (in seconds) */
int screenTimeout = 15;

//======================BLE class========================
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    Serial.println("device connected");
    Serial.print("clock has set = ");
    Serial.println(clockHasSet);
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    Serial.println("device disconnected");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{

  String info;
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0)
    {
      info = "";
      Serial.println("*********");
      Serial.print("Received Value: ");

      for (int i = 0; i < rxValue.length(); i++)
      {

        Serial.print(rxValue[i]);
        info += (rxValue[i]);
      }
      pushmsg = info;
      // oled(info);
      // showmsg = 1;
      Serial.println();
      Serial.print("info = ");
      Serial.println(info);
      Serial.println();
      Serial.println("*********");
      M5.Axp.ScreenBreath(9);
      // M5.Lcd.fillScreen(BLACK);

      if (pushmsg.substring(0, 2) != "TT")
      {
        // splittingMsg();
        // indexOfNotif=(-1);
        countindex = (-1);
        listMsg();
        standby = 0;
        newNotification = 1; // flag new notification has received
        showmsg = 1;         // tell system if notification list not empty
        increament = screenTimeout - 1;
      }
      else
      {
        //TTssmmHH
        //TT20190624_231348
        //  setTime(0,14,1,6,5,17); h,m,s ,d,m,y
        // int
        if (!clockHasSet)
        {

          //set RTC
          RTC_TimeTypeDef TimeStruct;
          TimeStruct.Hours = pushmsg.substring(11, 13).toInt();
          TimeStruct.Minutes = pushmsg.substring(13, 15).toInt();
          TimeStruct.Seconds = pushmsg.substring(15).toInt();
          M5.Rtc.SetTime(&TimeStruct);
          RTC_DateTypeDef DateStruct;
          DateStruct.WeekDay = 5;
          DateStruct.Month = pushmsg.substring(6, 8).toInt();
          DateStruct.Date = pushmsg.substring(8, 10).toInt();
          DateStruct.Year = pushmsg.substring(2, 6).toInt();
          M5.Rtc.SetData(&DateStruct);
          clockHasSet = 1;
        }
      }
    }
  }

  void listMsg()
  {

    int maxCOB = 120;     //maximum length of body 
    int nl = pushmsg.indexOf(0x0A); // get index of first new line sign
    header = pushmsg.substring(0, nl);
    Serial.print("header = ");
    Serial.println(header);
    String msgbody = pushmsg.substring(nl + 1);
    Serial.print("msgbody = ");
    Serial.println(msgbody);

    int msglength = msgbody.length();
    Serial.print("msglength = ");
    Serial.println(msglength);

    if (msglength > maxCOB)
      msgbody = msgbody.substring(0, maxCOB - 4) + "..."; //truncating if more than 240 character
    Serial.print("msgbody truncated =");
    Serial.println(msgbody);
    msglength = msgbody.length();
    Serial.print("TRUNC msglength = ");
    Serial.println(msglength);
    // if (msg1==""){
    //   // body1==;
    //   indexOfNotif++;
    // }
    indexOfNotif++;
    if (indexOfNotif > 3)
    {
      indexOfNotif = 3;
    }

    Serial.print("indexOfNotif = ");
    Serial.println(indexOfNotif);
    header4 = header3;
    header3 = header2;
    header2 = header1;
    header1 = header;
    msg4 = msg3;
    msg3 = msg2;
    msg2 = msg1;
    msg1 = msgbody;

    msgg2[0] = msg1;
    msgg2[1] = msg2;
    msgg2[2] = msg3;
    msgg2[3] = msg4;
    headers[0] = header1;
    headers[1] = header2;
    headers[2] = header3;
    headers[3] = header4;

    Serial.print("msg1 = ");
    Serial.println(msg1);
  }
};

void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason)
  {
  case 1:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    break;
  case 2:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    screenTimeout = 10;
    break;
  case 3:
    Serial.println("Wakeup caused by timer");
    screenTimeout = 5;
    break;
  case 4:
    Serial.println("Wakeup caused by touchpad");
    screenTimeout = 5;
    break;
  case 5:
    Serial.println("Wakeup caused by ULP program");
    break;
  default:
    Serial.println("Wakeup was not caused by deep sleep");
    break;
  }
}
void setup()
{
  // put your setup code here, to run once:
  M5.begin();
  M5.IMU.Init();
  // M5.Lcd.SMOOTH_FONT();
  M5.Axp.ScreenBreath(lcdBrightness);
  Serial.begin(115200);
  // lcd_set_brightness(30);
  M5.Lcd.setRotation(savedScreenOrientation);
  M5.Lcd.fillScreen(BLACK);
  // clock_style=6;
  print_wakeup_reason();
  M5.Lcd.setTextSize(1);
  // M5.Lcd.setCursor(40, 0, 2);
  // M5.Lcd.println("RTC TEST");
  delay(50);
  // Create the BLE Device
  BLEDevice::init("M5StickC");
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);

  pCharacteristic->setCallbacks(new MyCallbacks());

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  // //set RTC
  // RTC_TimeTypeDef TimeStruct;
  // TimeStruct.Hours   = 9;
  // TimeStruct.Minutes = 26;
  // TimeStruct.Seconds = 10;
  // M5.Rtc.SetTime(&TimeStruct);
  // RTC_DateTypeDef DateStruct;
  // DateStruct.WeekDay = 5;
  // DateStruct.Month = 9;
  // DateStruct.Date = 13;
  // DateStruct.Year = 2019;
  // M5.Rtc.SetData(&DateStruct);

  pinMode(BUTTON_HOME, INPUT | PULLUP);
  pinMode(BUTTON_PIN, INPUT | PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_HOME), ButtonAListener, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), setBrightness, RISING);

  preferences.begin("UI", false);
  clock_style = preferences.getInt("cStyle", 0);
  preferences.end();
  home3();
}

void setBrightness()
{
  lcdBrightness++;
  increament = screenTimeout -1;
  if (lcdBrightness > maxbright)
  {
    lcdBrightness = minbright;
  }
  Serial.printf("LCD Brightness = %d\n", lcdBrightness);
  delay(10);
}

bool saveIt = false;
void loop()
{
  // put your main code here, to run repeatedly:
  secondTick();
}

void savePreference()
{
  if (saveIt)
  {
    preferences.begin("UI", false);
    preferences.putInt("cStyle", clock_style);
    preferences.end();
    saveIt = 0;
  }
}

int lastminute;
void secondTick()
{
  if (millis() - last_rtc_update_time > 1000)
  {
    increament++;
    cekIMU();
    savePreference();
    if (increament == 1)
    {
      M5.axp.GetIusbinData();
      // Serial.printf("GetVusbinData = %d\n",M5.axp.GetVusbinData());
      // Serial.printf("GetIchargeData = %d\n",M5.Axp.GetIchargeData());
      // home3();
      // if (page != lastPage)
      //   updateScreenByPage(page);
      if (page != 1)
        updateScreenByPage(page);
      if (lcdBrightness != lastBrightness)
        M5.Axp.ScreenBreath(lcdBrightness);
      lastBrightness = lcdBrightness;
    }
    else if (increament > screenTimeout)
    {
      if (!standby)
      {
      }
      else
      {
      }

      // if (M5.axp.isCharging())
      if (is_Charging)
      {
        M5.Rtc.GetTime(&RTC_TimeStruct);
        if (lastminute != RTC_TimeStruct.Minutes)
        {
          // home3();
          // updateScreenByPage(page);
          // (clockMode==1)?drawPowerPlug(90,45):drawPowerPlug(50,0);
          (clock_style > 1) ? drawPowerPlug(90, 45) : drawPowerPlug(50, 0);
          lastminute = RTC_TimeStruct.Minutes;
        }
        increament = 2;
      }
      else
      {
        // gosleep();
      }

      updateScreenByPage(page);
      //  gosleep();
      // if (page == 0)
      // {
      //   M5.Axp.ScreenBreath(0);
      //   M5.Axp.SetSleep();
      // }
      // Serial.printf("screen time out  = %d\n", screenTimeout);
      // Serial.printf("page  = %d\n", page);
      

      increament = 2;
    }

    last_rtc_update_time = millis();
  }
}
void gosleep()
{

  M5.Lcd.fillScreen(BLACK);
  lcd_set_brightness(0);
  M5.Axp.ScreenBreath(0);
  int sleepdetik = 50;
  int sleepmenit = 2; //max 35
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_HOME, 0);
  // esp_sleep_enable_timer_wakeup(sleepmenit *60* uS_TO_S_FACTOR);  //maximum 2,147,483,647 micro Seconds / about 35 minutes
  Serial.println("\r\nGoing to sleep now\r\n");
  M5.axp.SetSleep();
  esp_deep_sleep_start();
  // home2();
  // increament=2;
}

float ACCx1 = 0.31;
float ACCx2 = 0.11; //(-0.14);
float ACCy1 = 1.05;
int flip = 0;
int lastFlip = 0;
bool ready_to_switch = false;
void cekIMU()
{

  // M5.IMU.getGyroAdc(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelAdc(&accX, &accY, &accZ);
  // Serial.printf("GX>%.2f   GY>%.2f   GZ%.2f  ---  ", ((float) gyroX) * M5.IMU.gRes, ((float) gyroY) * M5.IMU.gRes,((float) gyroZ) * M5.IMU.gRes);
  // Serial.printf("ACX%.2f   ACY%.2f   ACZ%.2f      \n",((float) accX) * M5.IMU.aRes,
  //   ((float) accY) * M5.IMU.aRes, ((float) accZ) * M5.IMU.aRes);
  if (((float)accX) * M5.IMU.aRes < ACCx2)
  {
    flip = 3;
    // clockMode=random(7);
    // if (clockMode>4){
    //   clockMode=1;
    // }else
    // {
    //   clockMode=0;
    // }

    if (flip != lastFlip)
    {
      M5.Lcd.setRotation(3);
      if (page == 0)
      {
        updateScreenByPage(page);
      }
      else if (page == 1)
      {
        updateScreenByPage(page);
      }
      // home3();
      lastFlip = flip;
    }
  }
  else if (((float)accX) * M5.IMU.aRes > ACCx1)
  {
    flip = 1;
    if (flip != lastFlip)
    {
      M5.Lcd.setRotation(1);
      if (page == 0)
      {
        updateScreenByPage(page);
      }
      else if (page == 1)
      {
        updateScreenByPage(page);
      }
      // home3();
      lastFlip = flip;
    }
  }
  else if (((float)accY) * M5.IMU.aRes > ACCy1)
  {
    if (!ready_to_switch){
      Serial.println("swith mode on");
      ready_to_switch = 1;
    }

    // updateScreenByPage(0);
    home3();
  }
  else if (((float)accY) * M5.IMU.aRes <ACCy1)
  {

    if (ready_to_switch){
      Serial.println("swith mode off");
      ready_to_switch = 0;
    }
  }
  else
  {

    flip = 0;
  }
}

void lcd_set_brightness(uint8_t brightness)
{
  Wire.beginTransmission(0x34);
  Wire.write(0x28);
  Wire.write(((brightness & 0x0f) << 4));
  Wire.endTransmission();
}
int colorMin = 120;

int GOTO;

void home3()
{
  int count = 0;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  // th = RTC_DateStruct.Year;
  // bl = RTC_DateStruct.Month;
  // tg = RTC_DateStruct.Date;
  // j = RTC_TimeStruct.Hours;
  // // j=bcdToDec( RTC_TimeStruct.Hours);
  // mn = RTC_TimeStruct.Minutes;
  // d = RTC_TimeStruct.Seconds;

  // perhitungan();

  // digital mode
  clockMode = random(2);
  // clockMode=1;

  // original code come from https://github.com/eggfly/M5StickCProjects for digital mode
  // just modify some line

  if (clock_style < 2)
  {

    count = RTC_TimeStruct.Hours * 100 + RTC_TimeStruct.Minutes;

    int x_start = 5;
    int x_delta = 6;
    int r = 5;
    int rd = random(2);
    for (int n = 0; n < 10; n++)
    {
      // canvas.fillCircle(x_start + x_delta * n, 4, r, COLORS_LIGHT[n]);
    }

    int y2 = 11;
    for (int n = 0; n < 10; n++)
    {
      // canvas.fillCircle(x_start + x_delta * n, y2, r, COLORS_DARK[n]);
    }
    // int testgigit=DIGITS[0][0][4];
    // Serial.printf("testgigit %d\n",testgigit);
    int y_start = 14;
    for (int pos = 0; pos < 4; pos++)
    {
      uint8_t curr_digit = 0;
      if (pos == 0)
      {
        curr_digit = count / 1000;
      }
      else if (pos == 1)
      {
        curr_digit = count / 100 % 10;
      }
      else if (pos == 2)
      {
        curr_digit = count / 10 % 10;
      }
      else if (pos == 3)
      {
        curr_digit = count % 10;
      }
      int rnd = random(10);
      for (int row = 0; row < 7; row++)
      {
        for (int col = 0; col < 5; col++)
        {
          uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
          uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
          if (DIGITS[curr_digit][row][col] == 1)
          {
            if (clock_style == 0)
            {
              M5.Lcd.fillCircle(x_start + col * 7 - 1 + random(4), y_start + row * 7 - 1 + random(4), r, colorrnd);
              // M5.Lcd.fillCircle(x_start + col * 7 -1+random(4), y_start + row * 7-1+random(4), 3, BLACK);
              // M5.Lcd.fillCircle(x_start + col * 7 -1+random(4), y_start + row * 7-1+random(4), r, colorrnd);
            }
            else if (clock_style == 1)
            {
              M5.Lcd.fillRoundRect(x_start - r + col * 7, y_start - r + row * 7, r * 2, r * 2, 0, colorrnd);
            }
          }
          else
          {
            if (clock_style == 1)
            {
              M5.Lcd.drawRoundRect(x_start - r + col * 7, y_start - r + row * 7, r * 2, r * 2, 0, colorrnd);
            }
            else if (clock_style == 0)
            {
              // M5.Lcd.drawCircle(x_start + col * 7, y_start + row * 7, r, colorrnd);
            }
          }
          // M5.Lcd.fillRect (x_start + col * 7, y_start + row * 7, r, colorrnd);
          //RGB565 = (((RGB888&0xf80000)>>8) + ((RGB888&0xfc00)>>5) + ((RGB888&0xf8)>>3));
        }
      }
      x_start += 39;
    }
  }
  //analog mode
  else
  // else if (clockMode==1)
  {
    // analog_setup2();                              // READ DATA
    // analogClockVariant(random(4));               // READ DATA
    analogClockVariant(clock_style);
  }

  draw_battery_percent(clock_style);
  M5.Lcd.setTextSize(1);
  printDate();
}

void printDate()
{
  if (clock_style < 2)
  {
    M5.Lcd.setCursor(0, 65);
    M5.Lcd.setTextSize(1);
    // M5.Lcd.setTextColor(0x00aadd00, 0);
    M5.Lcd.setTextColor(WHITE);
    // M5.Rtc.GetData(&RTC_DateStruct);
    M5.Lcd.printf("%d, %04d-%02d-%02d\n", RTC_DateStruct.WeekDay, RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    // M5.Lcd.printf("Week: %d\n",RTC_DateStruct.WeekDay);
    //===if new notification arrived
    if (newNotification)
    {
      // M5.Lcd.setCursor(130, 65);
      // M5.Lcd.setTextColor(WHITE);
      // M5.Lcd.printf("N");
      // M5.Lcd.drawCentreString("NO",125, 70)
      drawBLLogo(151, 69);
    }
    // M5.Rtc.GetData(&RTC_DateStruct);
  }
  else
  {

    int cX = 85;
    int cY = 0;
    int textSixe = 1;
    M5.Lcd.setCursor(cX, 0);
    M5.Lcd.setTextSize(textSixe);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    // M5.Lcd.printf("   %d\n %04d-%02d-%02d\n",RTC_DateStruct.WeekDay, RTC_DateStruct.Year, RTC_DateStruct.Month,RTC_DateStruct.Date);
    if (newNotification)
    {
      // M5.Lcd.setCursor(90, 15);
      // M5.Lcd.setTextColor(WHITE);
      // M5.Lcd.printf("N");
      drawBLLogo(90, 15);
    }
  }
}
void ButtonAListener()
{
  increament = screenTimeout -1;
  // Serial.printf("tanggal %d\n", tg);
  // standup position for switch clock face
  if (page == 0)
  {
    if(ready_to_switch){

      clock_style++;
      if (clock_style > 5)
      {
        clock_style = 0;
      }
      // save to eeprom
      if (!saveIt)
        saveIt = 1;
      // Serial.println("switch clock");
    }
    else
    {
      
      (showmsg) ? page = 1 : page = 0;
            
      increament = screenTimeout - 1;
      newNotification = 0;
      delay(10);
    }
    
  }


  else
  {
    // (page==0)?page=1:page=0;
    // if (page == 0)
    // {
    //   (showmsg) ? page = 1 : page = 0;
    // }
    // else
    // {
    //   page = 0;
    // }
    // page=0;
    // Serial.println("reset counter increament on else");

    // increament=2;
    // updateScreenByPage(page);
    increament = screenTimeout - 1;
    newNotification = 0;
  }
}
void updateScreenByPage(int page)
{
  // home3();
  switch (page)
  {
  case 0:
    home3();
    break;

  case 1:
    // jadwal_show();
    showNotif();
    showmsg = 1;
    // countindex--;     // avoid show next notofication if device change orientation
    break;

  default:
    break;
  }
  lastPage = page;
}

//==========notofications manager==========
void showNotif()
{
  // if (showmsg&&header=="WhatsApp")
  if (showmsg)
  {

    countindex++;
   
    screenTimeout = msgg2[countindex].length() / 10; //dynamic notification timeout depending message length
    if (countindex > indexOfNotif)
    {
      countindex = 0;
      page = 0; // back to clock face

      screenTimeout = 15;
      // gosleep()
      standby = 1;
      // M5.Axp.ScreenBreath(0);
      // M5.Lcd.fillScreen(BLACK);
      showmsg=0;    //false
    }

    displayinfo(headers[countindex], msgg2[countindex]);
    // if(msgg[countindex]!="")
    //   displayinfo(headers[], msgg[countindex]);

    // screenTimeout=3;
    Serial.print("countindex>");
    Serial.println(countindex);
    // Serial.print("indexOfBody>");
    // Serial.println(indexOfBody);
    Serial.print("msgg2= ");
    Serial.println(msgg2[countindex]);
  }
}

void displayinfo(String Header, String body)
{
  M5.Lcd.fillScreen(BLACK);
  // M5.Lcd.setFont();
  M5.Lcd.setTextColor(0xAA00FF00);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 0);

  M5.Lcd.print(Header);
  M5.Lcd.setTextColor(WHITE);
  // M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 9);
  // Serial.print("msgg = ");
  // Serial.println(msgg[countindex-1]);
  M5.Lcd.setTextWrap(true);
  M5.Lcd.print(body);
  // display.display();
}