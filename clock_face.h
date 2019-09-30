#include <M5StickC.h>
#include "global_variable.h"

uint8_t hh,mm,ss;
        int hh12=0;
//=========================================================================
void analog_setup2(int s){                                       // ANALOG SETUP
    switch (s)
    {
    case 0:
        
        M5.Lcd.fillScreen(TFT_BLACK);                            // CLEAR DISPLAY
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        // int colorRandomMedium = COLOR_MEDIUM[random(10)];
        M5.Lcd.drawCircle(40,40,40, COLOR_MEDIUM[random(10)]);
        // M5.Lcd.fillCircle( 160, 120, 118, TFT_GREEN);            // CLOCK FACE
        // M5.Lcd.fillCircle( 160, 120, 110, TFT_BLACK);  
        // colorRandomMedium = COLOR_MEDIUM[random(10)];          // LOCK FACE           // LOCK FACE
        // 12 LINES
        for(int i = 0; i<360; i+= 30) {                          
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*38 + 40; yy0 = sy*38 + 41;
            x1 = sx*32 + 40; yy1 = sy*32 + 41;
            M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]);          // DRAW 12 LINES
        }
        // colorRandomMedium = COLOR_MEDIUM[random(10)];
        // 60 DOTS
        for(int i = 0; i<360; i+= 6) {                           
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*33 + 40; yy0 = sy*33 + 40;
            M5.Lcd.drawPixel(x0, yy0,  COLOR_MEDIUM[random(10)]);                  // MINUTE
            if(i== 0 || i==180)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
            if(i==90 || i==270)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        }
        M5.Lcd.fillCircle(40, 41, 3, TFT_RED);    
        break;
    case 1:
        M5.Lcd.fillScreen(TFT_BLACK);                            // CLEAR DISPLAY
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        // int colorRandomMedium = COLOR_MEDIUM[random(10)];
        // M5.Lcd.drawCircle(40,40,40,COLOR_MEDIUM[random(10)]);
        // M5.Lcd.drawCircle(40,40,34,COLOR_MEDIUM[random(10)]);
        // M5.Lcd.drawCircle(40,40,28,COLOR_MEDIUM[random(10)]);
        // M5.Lcd.fillCircle( 160, 120, 118, TFT_GREEN);            // CLOCK FACE
        // M5.Lcd.fillCircle( 160, 120, 110, TFT_BLACK);  
        // colorRandomMedium = COLOR_MEDIUM[random(10)];          // LOCK FACE           // LOCK FACE
        

        hh=RTC_TimeStruct.Hours;
        
        mm=RTC_TimeStruct.Minutes;
        hh12=hh;
        if (hh>=12)hh12=hh-12;
        // M5.Lcd.drawCircle(40,40,38, COLOR_MEDIUM[random(10)]);
        
        //  //progress minute 
        // for(int i = (mm*6); i<360; i++) {                           
        //     sx = cos((i-90)*0.0174532925);
        //     sy = sin((i-90)*0.0174532925);
        //     x0 = sx*38 + 40; yy0 = sy*38 + 40;
        //     // M5.Lcd.fillCircle(x0,yy0,1,RED);
        //     M5.Lcd.drawPixel(x0,yy0,BLACK);
        //     // M5.Lcd.drawPixel(x0, yy0,  COLOR_MEDIUM[random(10)]);                  // MINUTE
        //     // if(i== 0 || i==180)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        //     // if(i==90 || i==270)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        // }
       //progress minute 
        for(int i = 0+2; i<(mm*6)-3; i++) {                           
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*36 + 40; yy0 = sy*36 + 40;
            M5.Lcd.fillCircle(x0,yy0,2,RED);
            // M5.Lcd.drawPixel(x0,yy0,GREEN);
            // M5.Lcd.drawPixel(x0, yy0,  COLOR_MEDIUM[random(10)]);                  // MINUTE
            // if(i== 0 || i==180)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
            // if(i==90 || i==270)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        }
        for(int i = (mm*6); i<360; i++) {                           
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*38 + 40; yy0 = sy*38 + 40;
            x1 = sx*32 + 40; yy1 = sy*32 + 41;
           // M5.Lcd.fillCircle(x0,yy0,1,RED);
            M5.Lcd.drawLine(x0,yy0,x1,yy1,BLACK);
            // M5.Lcd.drawPixel(x0, yy0,  COLOR_MEDIUM[random(10)]);                  // MINUTE
            // if(i== 0 || i==180)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
            // if(i==90 || i==270)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        }
        //progress hour
        for(int i = 0; i<((hh12*30)+(mm/2))-1; i++) {                           
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            // x0 = sx*30 + 40; yy0 = sy*30 + 40;
            // M5.Lcd.fillCircle(x0,yy0,2,BLUE);


            x0 = sx*34 + 40; yy0 = sy*34 + 41;
            x1 = sx*26 + 40; yy1 = sy*26 + 41;
            M5.Lcd.drawLine(x1, yy1, x0, yy0,  BLUE);

            // M5.Lcd.drawPixel(x0, yy0,  COLOR_MEDIUM[random(10)]);                  // MINUTE
            // if(i== 0 || i==180)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
            // if(i==90 || i==270)M5.Lcd.fillCircle(x0,yy0,2,WHITE);  // DOTS
        }
        

        // 12 LINES
        for(int i = 0; i<360; i+= 30) {                          
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*38 + 40; yy0 = sy*38 + 41;
            x1 = sx*32 + 40; yy1 = sy*32 + 41;
            // M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]); 
            M5.Lcd.drawLine(x0, yy0, x1, yy1,  WHITE);          // DRAW 12 LINES
            if(i== 0 || i==180){
                // x0 = sx*38 + 40; yy0 = sy*38 + 41;
                x1 = sx*20 + 40; yy1 = sy*20 + 41;
                M5.Lcd.drawLine(x0, yy0, x1, yy1,  GREEN);          // DRAW 12 LINES
            }if(i==90 || i==270){
                // x0 = sx*30 + 40; yy0 = sy*30 + 41;
                x1 = sx*20 + 40; yy1 = sy*20 + 41;
                M5.Lcd.drawLine(x0, yy0, x1, yy1,  GREEN);          // DRAW 12 LINES
            }
        }
        break;
    case 2:
        M5.Lcd.fillScreen(TFT_BLACK);                            // CLEAR DISPLAY
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        // int colorRandomMedium = COLOR_MEDIUM[random(10)];
        M5.Lcd.drawCircle(40,40,40,PURPLE);
        M5.Lcd.drawCircle(40,40,33,BLUE);
        M5.Lcd.drawCircle(40,40,26,BLUE);
        // M5.Lcd.fillCircle( 160, 120, 118, TFT_GREEN);            // CLOCK FACE
        // M5.Lcd.fillCircle( 160, 120, 110, TFT_BLACK);  
        // colorRandomMedium = COLOR_MEDIUM[random(10)];          // LOCK FACE           // LOCK FACE
        

        hh=RTC_TimeStruct.Hours;
        mm=RTC_TimeStruct.Minutes;
        //dot hour
        sx = cos((((hh*30)+(mm/2))-1-90)*0.0174532925);
        sy = sin((((hh*30)+(mm/2))-1-90)*0.0174532925);
        x0 = sx*28 + 40; yy0 = sy*28 + 40;
        M5.Lcd.fillCircle(x0,yy0,2,WHITE);
        
        //dot minutes                          
        sx = cos(((mm*6)-0-90)*0.0174532925);
        sy = sin(((mm*6)-0-90)*0.0174532925);
        x0 = sx*37 + 40; yy0 = sy*37 + 40;
        M5.Lcd.fillCircle(x0,yy0,2,RED);
       
        // 12 LINES
        for(int i = 0; i<360; i+= 30) {                          
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*37 + 40; yy0 = sy*37 + 40;
            x1 = sx*29 + 40; yy1 = sy*29 + 40;
         //   M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]);          // DRAW 12 LINES
        }
        sx = cos((0-90)*0.0174532925);
        sy = sin((0-90)*0.0174532925);
        x0 = sx*38 + 40; yy0 = sy*38 + 40;
        x1 = sx*28 + 40; yy1 = sy*28 + 40;
        M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]);          // DRAW 12 LINES
        
        break;
    case 3://radar mode
        M5.Lcd.fillScreen(TFT_BLACK);                            // CLEAR DISPLAY
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        // int colorRandomMedium = COLOR_MEDIUM[random(10)];
        M5.Lcd.drawCircle(40,40,40,GREEN);
        M5.Lcd.drawCircle(40,40,30,0x0140);
        M5.Lcd.drawCircle(40,40,20,0x0140);
        M5.Lcd.drawCircle(40,40,10,0x0140);
        // M5.Lcd.fillCircle( 160, 120, 118, TFT_GREEN);            // CLOCK FACE
        // M5.Lcd.fillCircle( 160, 120, 110, TFT_BLACK);  
        // colorRandomMedium = COLOR_MEDIUM[random(10)];          // LOCK FACE           // LOCK FACE
        

        hh=RTC_TimeStruct.Hours;
        mm=RTC_TimeStruct.Minutes;
      
        //dot hour
        sx = cos((((hh*30)+(mm/2))-1-90)*0.0174532925);
        sy = sin((((hh*30)+(mm/2))-1-90)*0.0174532925);
        rnddot=random(20, 36);
        x0 = sx*rnddot + 40; yy0 = sy*rnddot + 40;
        M5.Lcd.fillCircle(x0,yy0,2,GREEN);
        
        //dot minutes                          
        // sx = cos(((mm*6)-0-90)*0.0174532925);
        // sy = sin(((mm*6)-0-90)*0.0174532925);
        // x0 = sx*37 + 40; yy0 = sy*37 + 40;
        // M5.Lcd.fillCircle(x0,yy0,2,RED);
       
        // 12 LINES
        for(int i = 0; i<360; i+= 30) {                          
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*37 + 40; yy0 = sy*37 + 40;
            x1 = sx*29 + 40; yy1 = sy*29 + 40;
         //   M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]);          // DRAW 12 LINES
        }

        
        // 4 LINES
        for(int i = 0; i<360; i+= 30) {                          
            sx = cos((i-90)*0.0174532925);
            sy = sin((i-90)*0.0174532925);
            x0 = sx*38 + 40; yy0 = sy*38 + 41;
            x1 = sx*32 + 40; yy1 = sy*32 + 41;
            // M5.Lcd.drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]); 
            // M5.Lcd.drawLine(x0, yy0, x1, yy1,  WHITE);          // DRAW 12 LINES
            if(i== 0 || i==180){
                // x0 = sx*38 + 40; yy0 = sy*38 + 41;
                x1 = sx*0 + 40; yy1 = sy*0 + 41;
                M5.Lcd.drawLine(x0, yy0, x1, yy1, 0x0140);          // DRAW 12 LINES
            }if(i==90 || i==270){
                // x0 = sx*30 + 40; yy0 = sy*30 + 41;
                x1 = sx*0 + 40; yy1 = sy*0 + 41;
                M5.Lcd.drawLine(x0, yy0, x1, yy1,  0x0140);          // DRAW 12 LINES
            }
        }    
        sdeg = ss*6;                     // 0-59 -> 0-354   Pre-compute
        mdeg = mm*6+sdeg*0.01666667;     // 0-59 -> 0-360 - includes seconds
        hdeg = hh*30+mdeg*0.0833333;     // 0-11 -> 0-360 - inc min and seconds
        hx = cos((hdeg-90)*0.0174532925); hy = sin((hdeg-90)*0.0174532925);
        mx = cos((mdeg-90)*0.0174532925); my = sin((mdeg-90)*0.0174532925);
        sx = cos((sdeg-90)*0.0174532925); sy = sin((sdeg-90)*0.0174532925);
        
        ohx = hx*40+41; ohy = hy*40+41;                        // NEW   HOUR
        omx = mx*40+40; omy = my*40+41;                        // NEW   MIN
        // osx = sx*90+41; osy = sy*90+41;                        // NEW   MIN
        M5.Lcd.drawLine(omx, omy, 40, 41, GREEN);          // DRAW  HOUR
       
    
        break;
    default:
        break;
    } 
}




void analogClockVariant(int v)
{
    v-=2;
    switch (v)
    {
    case 0:
        analog_setup2(v);
        hh=RTC_TimeStruct.Hours;
        mm=RTC_TimeStruct.Minutes;
        ss=RTC_TimeStruct.Seconds;
        // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);
        sdeg = ss*6;                     // 0-59 -> 0-354   Pre-compute
        mdeg = mm*6+sdeg*0.01666667;     // 0-59 -> 0-360 - includes seconds
        hdeg = hh*30+mdeg*0.0833333;     // 0-11 -> 0-360 - inc min and seconds
        hx = cos((hdeg-90)*0.0174532925); hy = sin((hdeg-90)*0.0174532925);
        mx = cos((mdeg-90)*0.0174532925); my = sin((mdeg-90)*0.0174532925);
        sx = cos((sdeg-90)*0.0174532925); sy = sin((sdeg-90)*0.0174532925);
        
        M5.Lcd.drawLine(ohx, ohy, 40, 41, TFT_BLACK);          // ERASE HOUR
        M5.Lcd.drawLine(omx, omy, 40, 41, TFT_BLACK);          // ERASE MIN
        // M5.Lcd.drawLine(osx, osy, 40, 41, TFT_BLACK);          // ERASE SEC
        ohx = hx*26+41; ohy = hy*26+41;                        // NEW   HOUR
        omx = mx*36+40; omy = my*36+41;                        // NEW   MIN
        // osx = sx*90+41; osy = sy*90+41;                        // NEW   MIN
        M5.Lcd.drawLine(ohx, ohy, 40, 41, COLOR_MEDIUM[random(10)]);          // DRAW  HOUR
        M5.Lcd.drawLine(omx, omy, 40, 41, COLOR_MEDIUM[random(10)]);               // DRAW  MIN 
        // M5.Lcd.drawLine(20, 12, 40, 41, GREEN);          // DRAW  HOUR
        // M5.Lcd.drawLine(omx, omy, 40, 41, BLUE);               // DRAW  MIN 
        // Serial.printf("ohx=%01d, ohy=%02d, \n",ohx,ohy);
        // Serial.printf("omx=%01d, omy=%02d, \n",omx,omy);
        // M5.Lcd.drawLine(osx, osy, 40, 41, TFT_RED  );          // DRAW  SEC
        M5.Lcd.fillCircle(40, 41, 3, TFT_RED);                 // DOT   CENTER
        break;

    case 1:
        analog_setup2(v);
        Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);
        sdeg = ss*6;                     // 0-59 -> 0-354   Pre-compute
        mdeg = mm*6+sdeg*0.01666667;     // 0-59 -> 0-360 - includes seconds
        hdeg = hh*30+mdeg*0.0833333;     // 0-11 -> 0-360 - inc min and seconds
        hx = cos((hdeg-90)*0.0174532925); hy = sin((hdeg-90)*0.0174532925);
        mx = cos((mdeg-90)*0.0174532925); my = sin((mdeg-90)*0.0174532925);
        sx = cos((sdeg-90)*0.0174532925); sy = sin((sdeg-90)*0.0174532925);
        
        // M5.Lcd.drawLine(ohx, ohy, 40, 41, TFT_BLACK);          // ERASE HOUR
        // M5.Lcd.drawLine(omx, omy, 40, 41, TFT_BLACK);          // ERASE MIN
        // M5.Lcd.drawLine(osx, osy, 40, 41, TFT_BLACK);          // ERASE SEC
        ohx = hx*31+41; ohy = hy*31+41;                        // NEW   HOUR
        omx = mx*28+40; omy = my*38+41;                        // NEW   MIN
        // M5.Lcd.fillCircle(ohx,ohy,2 ,BLUE);
        // M5.Lcd.fillCircle(omx,omy,2,WHITE);
        // Serial.printf("ohx=%01d, ohy=%02d, \n",ohx,ohy);
        // Serial.printf("omx=%01d, omy=%02d, \n",omx,omy);
        
        break;

    case 2:
        analog_setup2(v);
        hh=RTC_TimeStruct.Hours;
        mm=RTC_TimeStruct.Minutes;
        ss=RTC_TimeStruct.Seconds;
        // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);
        sdeg = ss*6;                     // 0-59 -> 0-354   Pre-compute
        mdeg = mm*6+sdeg*0.01666667;     // 0-59 -> 0-360 - includes seconds
        hdeg = hh*30+mdeg*0.0833333;     // 0-11 -> 0-360 - inc min and seconds
        hx = cos((hdeg-90)*0.0174532925); hy = sin((hdeg-90)*0.0174532925);
        mx = cos((mdeg-90)*0.0174532925); my = sin((mdeg-90)*0.0174532925);
        sx = cos((sdeg-90)*0.0174532925); sy = sin((sdeg-90)*0.0174532925);
        
        // M5.Lcd.drawLine(ohx, ohy, 40, 41, TFT_BLACK);          // ERASE HOUR
        // M5.Lcd.drawLine(omx, omy, 40, 41, TFT_BLACK);          // ERASE MIN
        // M5.Lcd.drawLine(osx, osy, 40, 41, TFT_BLACK);          // ERASE SEC
        ohx = hx*31+41; ohy = hy*31+41;                        // NEW   HOUR
        omx = mx*36+41; omy = my*38+41;                        // NEW   MIN
        // M5.Lcd.fillCircle(ohx,ohy,2 ,BLUE);
        // M5.Lcd.fillCircle(omx,omy,2,WHITE);
        break;


    case 3:

        analog_setup2(v);
        break;
    default:
        break;
    }
}