#ifndef _BATTERY_H
#define _BATTERY_H
#include <M5StickC.h>
#include "AXP192.h"


bool  is_Charging(){
  
    Wire1.begin(21,22);
    Wire1.beginTransmission(0x34);
    Wire1.write(0x01);
    Wire1.endTransmission(false);
    Wire1.requestFrom(0x34, 1);
  uint8_t data1 =Wire1.read();
  // return data1 & 0b1000000;
  bool ic=data1 & 0b1000000;
  return ic;
}


// static const float levels[] = {4.13, 4.06, 3.98, 3.92, 3.87, 3.82, 3.79, 3.77, 3.74, 3.68, 3.45, 3.00};
static const float levels[] = {4.1, 4.0, 3.9, 3.9, 3.8, 3.8, 3.7, 3.7, 3.7, 3.6, 3.4, 3.00};
int plug[] = {
  B01010,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00010
};
//Created using dot2pic.com
// powercord
const uint16_t powercord[]={
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
  0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
  0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
  0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00};

//Created using dot2pic.com
const uint16_t bluetooth[]={0x01,0x01,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,
  0x01,0x01,0x01,0x00,0x01,0x00,0x00,0x01,0x01,0x00,0x01,0x00,0x00,
  0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,
  0x01,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x01,
  0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x01,0x01,0x01,0x00,
  0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x01,
  0x01,0x01,0x00,0x01,0x01,0x01,0x01,0x01};

//Created using dot2pic.com
int _=0;
const uint16_t bluetoothx[]={
    _,_,1,_,_,_,_,_,
    _,_,1,1,_,_,_,_,
    _,_,1,1,1,_,_,_,
    _,_,1,_,1,1,_,_, 
    1,_,1,1,1,_,_,_,
    _,1,1,1,_,_,_,_,
    _,_,1,1,_,_,_,_,
    _,1,1,1,1,_,_,_,
    1,_,1,_,1,1,_,_,
    _,_,1,1,1,_,_,_,
    _,_,1,1,_,_,_,_,
    _,_,1,_,_,_,_,_};

const uint16_t bluetooth_[]={
    1,1,_,1,1,1,1,1,
    1,1,_,_,1,1,1,1,
    1,1,_,_,_,1,1,1,
    1,1,_,1,_,_,1,1, 
    _,1,_,_,_,1,1,1,
    1,_,_,_,1,1,1,1,
    1,1,_,_,1,1,1,1,
    1,_,_,_,_,1,1,1,
    _,1,_,1,_,_,1,1,
    1,1,_,_,_,1,1,1,
    1,1,_,_,1,1,1,1,
    1,1,_,1,1,1,1,1};
unsigned long axp_last_update;

float getBatteryLevel(float voltage) {
  float level = 1;
  if (voltage >= levels[0]) {
    level = 1;
  } else if (voltage >= levels[1]) {
    level = 0.9;
    level += 0.1 * (voltage - levels[1]) / (levels[0] - levels[1]);
  } else if (voltage >= levels[2]) {
    level = 0.8;
    level += 0.1 * (voltage - levels[2]) / (levels[1] - levels[2]);
  } else if (voltage >= levels[3]) {
    level = 0.7;
    level += 0.1 * (voltage - levels[3]) / (levels[2] - levels[3]);
  } else if (voltage >= levels[4]) {
    level = 0.6;
    level += 0.1 * (voltage - levels[4]) / (levels[3] - levels[4]);
  } else if (voltage >= levels[5]) {
    level = 0.5;
    level += 0.1 * (voltage - levels[5]) / (levels[4] - levels[5]);
  } else if (voltage >= levels[6]) {
    level = 0.4;
    level += 0.1 * (voltage - levels[6]) / (levels[5] - levels[6]);
  } else if (voltage >= levels[7]) {
    level = 0.3;
    level += 0.1 * (voltage - levels[7]) / (levels[6] - levels[7]);
  } else if (voltage >= levels[8]) {
    level = 0.2;
    level += 0.1 * (voltage - levels[8]) / (levels[7] - levels[8]);
  } else if (voltage >= levels[9]) {
    level = 0.1;
    level += 0.1 * (voltage - levels[9]) / (levels[8] - levels[9]);
  } else if (voltage >= levels[10]) {
    level = 0.05;
    level += 0.05 * (voltage - levels[10]) / (levels[9] - levels[10]);
  } else if (voltage >= levels[11]) {
    level = 0.0;
    level += 0.05 * (voltage - levels[11]) / (levels[10] - levels[11]);
  } else {
    level = 0.0;
  }
  return level;
}

void draw_battery_percent(int clock_style) {

  double vbat = 0.0;
  vbat      = M5.Axp.GetVbatData() * 1.1 / 1000;
  float battery_percent = getBatteryLevel(vbat);
//  Serial.printf("power data %d\n", M5.axp.GetPowerbatData());
//  Serial.printf("is charging %d\n", M5.axp.isCharging());
//  Serial.print("is charging ");
//  Serial.println(M5.axp.isCharging());
//  if(clockMode==0){
 if(clock_style<2){
      
      M5.Lcd.setTextColor(0xAA00FF00);
      M5.Lcd.setTextSize(1);
      M5.Lcd.setCursor(122, 2);
      M5.Lcd.print(battery_percent * 100, 1);
      M5.Lcd.print("% ");
      if(M5.axp.isCharging()){
        M5.Lcd.setCursor(90, 2);    
        
      }
      M5.Lcd.setCursor(2,0);
      M5.Lcd.printf("vbat:%.1fV\r\n",vbat);
  }
  // else if (clockMode==1)
  else
  {
      M5.Lcd.setTextColor(0xAA00FF00);
      M5.Lcd.setTextSize(1);
      
      M5.Lcd.setCursor(90 ,59);
      M5.Lcd.print(battery_percent * 100, 1);
      M5.Lcd.print("% ");
      if(M5.axp.isCharging()){
        M5.Lcd.setCursor(90, 2);
        // M5.Lcd.printf("charging");
        // M5.Lcd.printf("%d",plug);     
        
      }
      M5.Lcd.setCursor(90,68);
      M5.Lcd.printf("vbat:%.1fV\r\n",vbat);
  }
}

void drawPowerPlug( uint16_t x,uint16_t y){
        M5.Lcd.fillRoundRect(x,y,14,8,0,WHITE);
        M5.Lcd.drawBitmap(x,y,14,8,powercord,BLACK);
}

void drawBLLogo( uint16_t x,uint16_t y){
        M5.Lcd.fillRoundRect(x,y,8,12,0,BLUE);
        M5.Lcd.drawBitmap(x,y,8,12,bluetooth_,BLACK);
}
// void check_update_battery() {
//   unsigned long now = millis();
//   if (now - axp_last_update > 400) {
//     axp_data = axp_read();
//     axp_last_update = now;
//   }
// }

// void page_axp_info() {
//   check_update_battery();
//   axp_power_data d = axp_data;

//   M5.Lcd.setTextSize(1);
//   M5.Lcd.setTextColor(0xAAFF0000);
//   M5.Lcd.setCursor(40, 2);
//   M5.Lcd.print("Battery Info");

//   draw_battery_percent();

//   M5.Lcd.setTextSize(1);
//   M5.Lcd.setTextColor(0xAAFFFFFF);

//   int start_y = 13;
//   int delta_y = 9;
//   int start_x = 5;
//   M5.Lcd.setCursor(start_x, start_y);
//   M5.Lcd.print("vbat=");
//   M5.Lcd.print(d.vbat_v, 3);
//   M5.Lcd.print("V");

//   M5.Lcd.setCursor(start_x, start_y + delta_y);
//   M5.Lcd.print("chg=");
//   M5.Lcd.print(d.icharge_ma);
//   M5.Lcd.print("mA");

//   M5.Lcd.setCursor(start_x, start_y + delta_y * 2);
//   M5.Lcd.print("dis=");
//   M5.Lcd.print(d.idischarge_ma);
//   M5.Lcd.print("mA");

//   M5.Lcd.setCursor(start_x, start_y + delta_y * 3);
//   M5.Lcd.print("watt=");
//   M5.Lcd.print(d.bat_mw, 1);
//   M5.Lcd.print("mW");

//   M5.Lcd.setCursor(start_x, start_y + delta_y * 4);
//   M5.Lcd.print("coin=");
//   M5.Lcd.print(d.coin);

//   M5.Lcd.setCursor(start_x, start_y + delta_y * 5);
//   M5.Lcd.print("coout=");
//   M5.Lcd.print(d.coout);

//   M5.Lcd.setCursor(start_x, start_y + delta_y * 6);
//   M5.Lcd.print("ccc=");
//   M5.Lcd.print(d.ccc, 2);

//   M5.Lcd.setCursor(80, start_y);
//   M5.Lcd.print("vbus? ");
//   M5.Lcd.print(d.vbus_present);

//   M5.Lcd.setCursor(80, start_y + delta_y);
//   M5.Lcd.print("vbus=");
//   M5.Lcd.print(d.vbus_v, 3);
//   M5.Lcd.print("V");

//   M5.Lcd.setCursor(80, start_y + delta_y * 2);
//   M5.Lcd.print("ibus=");
//   M5.Lcd.print(d.ibus_ma, 2);
//   M5.Lcd.print("mA");

//   M5.Lcd.setCursor(80, start_y + delta_y * 3);
//   M5.Lcd.print("PWR On USB? ");
//   M5.Lcd.print(d.is_plug_power_on);

//   M5.Lcd.setCursor(80, start_y + delta_y * 4);
//   M5.Lcd.print("temp=");
//   M5.Lcd.print(d.temperature, 1);
//   M5.Lcd.print("C");

//   M5.Lcd.setCursor(80, start_y + delta_y * 5);
//   M5.Lcd.print("charging? ");
//   M5.Lcd.print(d.is_charging);

//   M5.Lcd.setCursor(80, start_y + delta_y * 6);
//   M5.Lcd.print("bat_chg? ");
//   M5.Lcd.print(d.batt_current_direction);
// }

#endif // _BATTERY_H
