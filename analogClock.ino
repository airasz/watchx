

// #include "aWatch.h"

// convert html rgb to rgb565
int rgbToHex(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t rgb = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (long)b;
    uint16_t rgb565 = (((rgb & 0xf80000) >> 8) | ((rgb & 0xfc00) >> 5) | ((rgb & 0xf8) >> 3));
    return rgb565;
}
// void updateClock();
//=========================================================================
float sdeg, mdeg, hdeg, oldsdeg, oldmdeg, oldhdeg, ooldsdeg;
int hh, mm, ss;
void analogClock(int v)
{

    int wipetracelong, px, dgree, old_rnddot;
    long dmCover; // daily distance covered
                  //   tnow = ttgo->rtc->getDateTime();
                  //   int nday = day,
                  //       nmonth = month,
                  //       nyear = year, g = 250;
    String const dw[] = {"MGG", "SEN", "SEL", "RBU", "KMS", "JMT", "SBT"};
    //   int dow = ttgo->rtc->getDayOfWeek(nday, nmonth, nyear);
    // Serial.printf(" day of week : %d \n", dow);
    hh = hour();
    mm = minute();
    ss = second();
    //   v -= 6;
    int hh12 = hh >= 12 ? hh - 12 : hh; // hh += hh > 12 ? (-12) : 0;
    int hq;
    hq = getQuadrant(hh);
    sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
    mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
    hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
                                       // face=6> standart analog
                                       //   Serial.println("analog clock ?");
                                       //   Serial.printf("clock v  : %d \n", v);
    ooldsdeg = (ss - 1) * 6;
    if (ss == 0)
    {
        // tft.fillScreen(TFT_BLACK);
        updateSecondhand = false;
        fillacf();
        //     oldsdeg = (ss - 1) * 6;                   // 0-59 -> 0-354   Pre-compute
        //     oldmdeg = mm * 6 + oldsdeg * 0.01666667;  // 0-59 -> 0-360 - includes seconds
        //     oldmdeg = hh * 30 + oldmdeg * 0.0833333;  // 0-11 -> 0-360 - inc min and seconds
        // if (ss % 15 == 0)
        // {
        oldsdeg = (ss - 1) * 6;                  // 0-59 -> 0-354   Pre-compute
        oldmdeg = mm * 6 + oldsdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
        oldhdeg = hh * 30 + oldmdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
        // }
    }
    if (v == 0)
    {
        if (!updateSecondhand)
        {

            //     Serial.println("analog clock 0");
            // tft.fillScreen(TFT_BLACK); // CLEAR DISPLAY
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            // int o_colcircle;
            int o_colcircle = analogClockProps[0];
            // int i_colcircle;
            int i_colcircle = analogClockProps[1];
            tft.drawSmoothCircle(120, 120, 112, o_colcircle, TFT_BLACK);
            tft.fillSmoothCircle(120, 120, 110, i_colcircle, o_colcircle);
            // 12 LINES
            // rainbow color for every multiple 5  minute line mark
            for (int i = 0; i < 360; i += 30)
                tft.drawLine(posX(110, i), posY(110, i), posX(102, i), posY(102, i), analogClockProps[2]); // DRAW 12 LINES

            // 60 DOTS
            for (int i = 0; i < 360; i += 6)
            {
                tft.drawPixel(posX(108, i), posY(109, i), analogClockProps[3]); // MINUTE DOT
                if (i % 90 == 0)
                    tft.fillCircle(posX(108, i), posY(109, i), 3, TFT_WHITE); // DOTS
            }
            // middle dot
            tft.fillCircle(120, 120, 3, analogClockProps[4]); // CENTER DOT
            // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);

            tft.drawWideLine(posX(60, hdeg), posY(60, hdeg), 120, 120, 6, analogClockProps[5], i_colcircle); // DRAW  HOUR
            tft.drawWideLine(posX(71, mdeg), posY(71, mdeg), 120, 120, 6, analogClockProps[6], i_colcircle); // DRAW  MINUTE
            tft.drawWideLine(posX(81, sdeg), posY(81, sdeg), 120, 120, 4, analogClockProps[7], i_colcircle); // DRAW  MINUTE
            tft.fillSmoothCircle(120, 120, 6, analogClockProps[4], i_colcircle);
            updateSecondhand = true;
        }
        else
        {

            int i_colcircle = analogClockProps[1];

            //     tft.fillSmoothCircle(120, 120, 84, i_colcircle, i_colcircle);
            //     tft.drawWideLine(posX(60, oldhdeg), posY(60, oldhdeg), 120, 120, 6, i_colcircle, i_colcircle); // DRAW  HOUR
            //       if (ss % 5 == 0) {
            //         tft.drawWideLine(posX(71, oldmdeg), posY(71, oldmdeg), 120, 120, 6, i_colcircle, i_colcircle);    // DRAW  MINUTE
            //         tft.drawWideLine(posX(71, mdeg), posY(71, mdeg), 120, 120, 6, analogClockProps[6], i_colcircle);  // DRAW  MINUTE
            //       }
            tft.drawWideLine(posX(81, ooldsdeg), posY(81, ooldsdeg), 120, 120, 4, i_colcircle, i_colcircle); // DRAW  MINUTE
            // tft.fillSmoothCircle(120, 120, 6, analogClockProps[4], i_colcircle);

            tft.drawWideLine(posX(60, oldhdeg), posY(60, oldhdeg), 120, 120, 6, analogClockProps[5], i_colcircle); // DRAW  HOUR
            tft.drawWideLine(posX(71, oldmdeg), posY(71, oldmdeg), 120, 120, 6, analogClockProps[6], i_colcircle); // DRAW  MINUTE
            tft.drawWideLine(posX(81, sdeg), posY(81, sdeg), 120, 120, 4, analogClockProps[7], i_colcircle);       // DRAW  MINUTE
            tft.fillSmoothCircle(120, 120, 6, analogClockProps[4], i_colcircle);
        }
    }
    // cf 13 >chaotic pendulum
    else if (v == 1)
    {
        tft.fillScreen(TFT_BLACK);           // CLEAR DISPLAY
        hdeg = hh12 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
        hq = getQuadrant(hh12);
        hq = (hh12 / 3) + 1; // get quadrant
        int xx2 = 120;
        int yy2 = 120;
        int xx, yy, mx, my;
        // int xx = posX(50, hdeg, xx2);
        // int yy = posY(50, hdeg, yy2);
        // int mx = posX(80, mdeg, xx);
        // int my = posY(80, mdeg, yy);
        if (mx > 180)
        {
            xx2 = xx2 - (mx - 180);
        }
        if (mx < 60)
        {
            xx2 = xx2 + (60 - mx);
        }

        if (my > 180)
        {
            yy2 = yy2 - (my - 180);
        }
        if (my < 60)
        {
            yy2 = yy2 + (60 - my);
        }

        xx = posX(50, hdeg, xx2);
        mx = posX(80, mdeg, xx);
        yy = posY(50, hdeg, yy2);
        my = posY(80, mdeg, yy);
        // int hcol, mcol;
        int hcol = COLOR_MEDIUM[random(10)];
        int mcol = COLOR_MEDIUM[random(10)];
        // draw a minute line guide
        for (int i = 0; i < 720; i += 6)
            if (i + 1 > mdeg - 50 && i + 1 < mdeg + 50 || i + 1 > (360 + mdeg) - 50 && i + 1 < (mdeg + 360) + 50)
                tft.drawWideLine(posX(90, i, xx), posY(90, i, yy), posX(90 - ((i % 15 == 0) ? 20 : 10), i, xx), posY(90 - ((i % 15 == 0) ? 20 : 10), i, yy), (i % 15 == 0) ? 2 : 1, ((i % 15 == 0) ? rgbToHex(200, 80, 0) : TFT_YELLOW), TFT_BLACK); // DRAW  MINUTE

        tft.drawWideLine(mx, my, xx, yy, 6, mcol, TFT_BLACK); // DRAW  MINUTE
        tft.fillSmoothCircle(xx, yy, 6, TFT_WHITE, TFT_BLACK);
        // draw pie hour line guide
        for (int i = 0; i < 720; i += 30)
            if (i + 1 > hdeg - 60 && i + 1 < hdeg + 60 || i + 1 > (360 + hdeg) - 60 && i + 1 < (hdeg + 360) + 60)
                tft.drawWideLine(posX(60, i, xx2), posY(60, i, yy2), posX(60 - ((i % 90 == 0) ? 20 : 10), i, xx2), posY(60 - ((i % 90 == 0) ? 20 : 10), i, yy2), (i % 90 == 0) ? 3 : 2, TFT_WHITE, TFT_BLACK); // DRAW  MINUTE

        tft.drawWideLine(xx, yy, xx2, yy2, 6, hcol, TFT_BLACK); // DRAW  HOUR HAND
        tft.fillSmoothCircle(xx2, yy2, 6, TFT_WHITE, TFT_BLACK);
    }
    //   else if (v == 7)
    //   {
    //     // CF=11
    //     javaneseClock(hh, mm); // clock_face_text.ino

    //     if (enableSS)
    //       screenServer();
    //   }
    //   else if (v == 8)
    //   {
    //     // CF=12
    //     mathFace(hh, mm); // clock_face_text.ino

    //     if (enableSS)
    //       screenServer();
    //   }
}
// tft.drawLine(*(pos(hh, mm) + 0), *(pos(hh, mm) + 1), 120, 120, 0x3186); //

float getCos(int degree)
{
    float r = cos((degree - 90) * 0.0174532925);
    return r;
}
float getSin(int degree)
{
    float r = sin((degree - 90) * 0.0174532925);
    return r;
}
int posX(int radius, int degree)
{
    int r = getCos(degree) * radius + 120;
    return r;
}
int posY(int radius, int degree)
{
    int r = getSin(degree) * radius + 120;
    return r;
}

int posX(int radius, int degree, int pivot)
{
    int r = getCos(degree) * radius + pivot;
    return r;
}
int posY(int radius, int degree, int pivot)
{
    int r = getSin(degree) * radius + pivot;
    return r;
}
int getQuadrant(int hh)
{
    // if (hh < 3)
    //   return 1;
    // if (hh >= 3 && hh < 6)
    //   return 2;
    // if (hh >= 6 && hh < 9)
    //   return 3;
    // if (hh >= 9 && hh < 12)
    //   return 4;

    return (hh / 3) + 1;
}
void assignDegree()
{
}