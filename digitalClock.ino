// Auth: Ihsan Satriawan
// Desc: Digital clock with animation
void digitFace(int face)
{

    int clock_style = random(3);
    clock_style = face; // force to test
    int x_start = 10;
    int x_delta = 6;
    int r = 8;
    int rd = random(2);
    // rd = 0; // test
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

    hh = hour();
    mm = minute();
    // ss = second();
    int y_start = 36;
    int isize = 10;
    int count = hh * 100 + mm;
    if (clock_style == 0)
    {
        // x_start = 30;
        // y_start = 14;
        isize = 14;
        r = 12;
        for (int pos = 0; pos < 4; pos++)
        {
            uint8_t curr_digit = 0;
            //   x_start += (5 * isize) + 55;
            //   if (pos == 1) {
            //     y_start += 126;
            //     x_start = 30;
            //   }
            if (digitOrder[pos] == 0)
            {
                curr_digit = count / 1000;
                x_start = 30;
                y_start = 14;
                // if (curr_digit == 0)
                //     curr_digit = 11; // make it blank. see on res.h
            }
            else if (digitOrder[pos] == 1)
            {
                curr_digit = count / 100 % 10;
                x_start = 30 + (5 * isize) + 55;
                y_start = 14;
            }
            else if (digitOrder[pos] == 2)
            {
                curr_digit = count / 10 % 10;
                x_start = 30;
                y_start = 14 + 126;
                // curr_digit = 12; // make it (:). see on res.h
            }
            else if (digitOrder[pos] == 3)
            {
                curr_digit = count % 10;
                x_start = 30 + (5 * isize) + 55;
                y_start = 14 + 126;
            }
            // else if (pos == 4)
            // {
            //     curr_digit = count % 10;
            // }
            int rnd = random(10);
            int startrow = 0;
            //==========determite pre x,y position of each digit================
            for (int row = startrow; row < 7; row++)
            {
                for (int col = 0; col < 5; col++)
                {
                    uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                    uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                    // if (DIGITS[curr_digit][row][col] == 1)
                    bool state = DIGITS[curr_digit][row][col];
                    tmpDigit[row][col][0] = x_start + col * isize - 1 + random(4);
                    tmpDigit[row][col][1] = y_start + row * isize - 1 + random(4);
                    // tft.fillCircle(x_start + col * 7 - 1 + random(4), y_start + row * 7 - 1 + random(4), r, colorrnd);
                }
            }

            //   tft.fillRoundRect(x_start - 12, y_start - 12, 5 * isize + 14, 7 * isize + 14, 2, TFT_YELLOW);
            // tft.fillRoundRect((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 0 : 122, (digitOrder[pos] < 2) ? 0 : 122, 118, 118, 2, COLOR_MEDIUM[random(12)]);

            tft.fillRoundRect((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 0 : 122, (digitOrder[pos] < 2) ? 0 : 122, 118, 118, 2, TFT_BLACK);
            tft.drawRoundRect((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 0 : 122, (digitOrder[pos] < 2) ? 0 : 122, 118, 118, 2, COLOR_MEDIUM[random(12)]);

            shuffleArray(patternSequences, patternSequencesSize);
            // int rnd = random(10);
            for (int i = 0; i < 20; i++)
            {
                bool match = false;
                for (int row = 0; row < 7; row++)
                {
                    for (int col = 0; col < 5; col++)
                    {
                        uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                        uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLOR_MEDIUM[random(12)] : COLOR_MEDIUM[random(12)];
                        // if (DIGITS[curr_digit][row][col] == 1)
                        int state = LineTrack[curr_digit][row][col];
                        if (state == patternSequences[i])
                        {
                            //   tft.fillCircle(tmpDigit[row][col][0], tmpDigit[row][col][1], r, colorrnd);
                            tft.fillSmoothCircle(tmpDigit[row][col][0], tmpDigit[row][col][1], r, colorrnd, colorrnd);
                            match = true;
                        }
                        // delay(40);
                    }
                    // delay(40);
                }
                // if (!match)
                //     break;

                if (!noanim && animation)
                    delay(40);
            }

            // x_start += 39;

            //   x_start += (5 * isize) + 55;
            //   if (pos == 1) {
            //     y_start += 126;
            //     x_start = 30;
            //   }
        }
        for (int i = 0; i < 4; i++)
        {
            blockColor[i] = COLOR_MEDIUM[random(12)];
        }
        shuffleArray(digitOrder, digitOrderSize);
    }
    else if (clock_style == 1)
    {
        // int isize = 4;

        x_start = 36;
        y_start = 24;
        isize = 14;
        r = 12;
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

            int startrow = 0;

            tft.fillRoundRect((pos == 0 || pos == 2) ? 0 : 122, (pos < 2) ? 0 : 122, 118, 118, 2, TFT_BLACK);
            tft.drawRoundRect((pos == 0 || pos == 2) ? 0 : 122, (pos < 2) ? 0 : 122, 118, 118, 2, COLOR_MEDIUM[random(12)]);

            // for (int row = 0; row < 7; row++)
            // {
            //     for (int col = 0; col < 5; col++)
            //     {
            //         tft.fillRoundRect(x_start - r + col * isize, y_start - r + row * isize, r * 1, r * 1, 0, TFT_BLACK);
            //     }
            // }
            shuffleArray(patternSequences, patternSequencesSize);
            for (int i = 0; i < 20; i++)
            {
                bool match = false;
                for (int row = 0; row < 7; row++)
                {
                    for (int col = 0; col < 5; col++)
                    {
                        uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                        uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                        // if (DIGITS[curr_digit][row][col] == 1)
                        int state = LineTrack[curr_digit][row][col];
                        if (state == patternSequences[i])
                        {
                            tft.fillRoundRect(x_start - r + col * isize, y_start - r + row * isize, r * 1, r * 1, 0, colorrnd);
                            match = true;
                        }
                        // delay(40);
                    }
                    // delay(40);
                }
                // if (!match)
                //     break;

                if (!noanim && animation)
                    delay(40);
            }
            x_start += (5 * isize) + 55;
            if (pos == 1)
            {
                y_start += 118;
                x_start = 36;
            }
        }
    }
    else if (clock_style == 2)
    {
        // count = 1234;
        int x_pos = 40; // x position of ihscore
        int y_pos = 28; // y position of number
        for (int pos = 0; pos < 4; pos++)
        {
            int xpath[20];
            int ypath[20];
            for (int i = 0; i < 20; i++)
                xpath[i] = 0, ypath[i] = 0;
            uint8_t curr_digit = 0;
            if (digitOrder[pos] == 0)
            {
                curr_digit = count / 1000;

                x_start = x_pos;
                y_start = y_pos;
                // if (curr_digit == 0)
                //     curr_digit = 11; // make it blank. see on res.h
            }
            else if (digitOrder[pos] == 1)
            {
                curr_digit = count / 100 % 10;

                x_start = x_pos + (5 * isize) + 70;
                y_start = y_pos;
            }
            else if (digitOrder[pos] == 2)
            {
                curr_digit = count / 10 % 10;
                x_start = x_pos;
                y_start = y_pos + 120;

                // curr_digit = 10; // make it (-). see on res.h
            }
            else if (digitOrder[pos] == 3)
            {
                curr_digit = count % 10;
                x_start = x_pos + (5 * isize) + 70;
                y_start = y_pos + 120;
            }
            int rnd = random(10);
            int startrow = 0;
            //==========determite pre x,y position of each digit================
            for (int row = 0; row < 7; row++)
            {
                for (int col = 0; col < 5; col++)
                {

                    // Serial.printf("--digit[%d] :  \n", DIGITS[curr_digit][row][col]);
                    uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                    uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                    // if (DIGITS[curr_digit][row][col] == 1)
                    // bool state = DIGITS[curr_digit][row][col];
                    // tmpDigit[row][col][0] = x_start + col * 7 - 1 + random(4);
                    // tmpDigit[row][col][1] = y_start + row * 7 - 1 + random(4);
                    if (LineTrack[curr_digit][row][col] > 0)
                    {
                        int xc = x_start + col * isize - 1 + (random(4));
                        int yc = y_start + row * isize - 1 + (random(4));
                        xpath[LineTrack[curr_digit][row][col] - 1] = xc; // put  squence path X point to array
                        ypath[LineTrack[curr_digit][row][col] - 1] = yc; // put  squence path Y point to array
                                                                         // Serial.printf("---xpath[%d] : %d \n", LineTrack[curr_digit][row][col] - 1, xc);
                                                                         // Serial.printf("--xpath [%d]: %d \n", LineTrack[curr_digit][row][col] - 1, xpath[LineTrack[curr_digit][row][col] - 1]);
                                                                         // Serial.printf("--ypath [%d]: %d \n", LineTrack[curr_digit][row][col] - 1, ypath[LineTrack[curr_digit][row][col] - 1]);
                    }
                    // tft.fillCircle(x_start + col * 7 - 1 + random(4), y_start + row * 7 - 1 + random(4), r, colorrnd);
                }
            }

            // int colll = COLORS_LIGHT[rnd];
            int colll = COLOR_MEDIUM[random(12)];
            int bcoll = TFT_BLACK;
            // if (pos==0){
            // tft.fillRoundRect(x_start - 6, y_start - 6, 5 * isize + 6, 7 * isize + 6, 2, TFT_BLACK);
            // }

            tft.fillCircle((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 60 : 180, (digitOrder[pos] < 2) ? 60 : 180, 60, TFT_BLACK);
            tft.drawSmoothCircle((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 60 : 180, (digitOrder[pos] < 2) ? 60 : 180, 60, COLOR_MEDIUM[random(12)], TFT_BLACK);

            for (int i = 0; i < 19; i++)
            {
                // Serial.printf(" xpath[%d] : %d \n", i, xpath[i]);
                // Serial.print("\n");

                // Serial.printf("curdigit[%d] xpath[%d] : %d \n", curr_digit, i);
                // tft.drawLine(130, 62, 132, 64, colll);
                if (xpath[i + 1] != 0)
                {
                    if (curr_digit == 0)
                    {
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                        if (i == 1)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[15], ypath[15], 4, colll);

                        if (i == 0)
                            tft.drawWideLine(xpath[i], ypath[i], xpath[15], ypath[15], 10, colll, bcoll);
                    }
                    else if (curr_digit == 1)
                    {
                        if (i == 6)
                        {
                            tft.drawWideLine(xpath[i], ypath[i], xpath[8], ypath[8], 10, colll, bcoll);
                        }
                        else
                        {
                            if (i == 7)
                                tft.drawBoldLine(xpath[i - 2], ypath[i - 2], xpath[6], ypath[6], 4, colll);

                            tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                            if (i > 0 && i - 1 != 6)
                                tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                            if (i == 8)
                            {
                                tft.drawWideLine(xpath[6], ypath[6], xpath[8], ypath[8], 10, colll, colll);
                                tft.drawWideLine(xpath[1], ypath[1], xpath[3], ypath[3], 10, colll, colll);
                            }
                        }
                    }
                    else if (curr_digit == 3)
                    {
                        if (i != 7)
                        {
                            tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                            if (i > 0 && i - 1 != 7)
                                tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                            if (i == 8)
                                tft.drawWideLine(xpath[i - 2], ypath[i - 2], xpath[8], ypath[8], 10, colll, bcoll);
                            if (i == 9)
                            {
                                tft.drawBoldLine(xpath[6], ypath[6], xpath[7], ypath[7], 4, colll);
                                tft.drawBoldLine(xpath[6], ypath[6], xpath[5], ypath[5], 4, colll);
                            }
                        }

                        else // i==7
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[8], ypath[8], 4, colll);
                    }
                    else if (curr_digit == 8)
                    {
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);

                        if (i == 0)
                            tft.drawWideLine(xpath[i], ypath[i], xpath[9], ypath[9], 10, colll, bcoll);
                        if (i == 1)
                        {
                            tft.drawWideLine(xpath[i], ypath[i], xpath[16], ypath[16], 10, colll, bcoll);
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[9], ypath[9], 4, colll);
                        }
                        if (i == 2)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[16], ypath[16], 4, colll);
                        if (i == 15)
                        {
                            tft.drawBoldLine(xpath[1], ypath[1], xpath[16], ypath[16], 4, colll);
                            tft.drawBoldLine(xpath[0], ypath[0], xpath[1], ypath[1], 4, colll);
                            tft.drawBoldLine(xpath[0], ypath[0], xpath[9], ypath[9], 4, colll);
                        }
                    }
                    else
                    {
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                    }
                    if (!noanim && animation)
                        delay(50);
                }
                else
                {
                    break; // if not line any more to draw, then exit for loop
                }
            } // endfor

            // x_start += (5 * isize) + 20;
            // if (pos == 1)
            // {
            //     y_start += 100;
            //     x_start = 10;
            // }
        }

        for (int i = 0; i < 4; i++)
        {
            blockColor[i] = COLOR_MEDIUM[random(12)];
        }
        shuffleArray(digitOrder, digitOrderSize);
    }
    else if (clock_style == 3)
    {
        // x_start = 30;
        // y_start = 14;
        isize = 14;
        r = 12;
        for (int pos = 0; pos < 4; pos++)
        {
            uint8_t curr_digit = 0;
            //   x_start += (5 * isize) + 55;
            //   if (pos == 1) {
            //     y_start += 126;
            //     x_start = 30;
            //   }
            if (digitOrder[pos] == 0)
            {
                curr_digit = count / 1000;
                x_start = 30;
                y_start = 14;
                // if (curr_digit == 0)
                //     curr_digit = 11; // make it blank. see on res.h
            }
            else if (digitOrder[pos] == 1)
            {
                curr_digit = count / 100 % 10;
                x_start = 30 + (5 * isize) + 55;
                y_start = 14;
            }
            else if (digitOrder[pos] == 2)
            {
                curr_digit = count / 10 % 10;
                x_start = 30;
                y_start = 14 + 126;
                // curr_digit = 12; // make it (:). see on res.h
            }
            else if (digitOrder[pos] == 3)
            {
                curr_digit = count % 10;
                x_start = 30 + (5 * isize) + 55;
                y_start = 14 + 126;
            }
            // else if (pos == 4)
            // {
            //     curr_digit = count % 10;
            // }
            int rnd = random(10);
            int startrow = 0;
            //==========determite pre x,y position of each digit================
            for (int row = startrow; row < 7; row++)
            {
                for (int col = 0; col < 5; col++)
                {
                    uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                    uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                    // if (DIGITS[curr_digit][row][col] == 1)
                    bool state = DIGITS[curr_digit][row][col];
                    tmpDigit[row][col][0] = x_start + col * isize - 1 + random(4);
                    tmpDigit[row][col][1] = y_start + row * isize - 1 + random(4);
                    // tft.fillCircle(x_start + col * 7 - 1 + random(4), y_start + row * 7 - 1 + random(4), r, colorrnd);
                }
            }

            //   tft.fillRoundRect(x_start - 12, y_start - 12, 5 * isize + 14, 7 * isize + 14, 2, TFT_YELLOW);
            tft.fillRoundRect((digitOrder[pos] == 0 || digitOrder[pos] == 2) ? 0 : 122, (digitOrder[pos] < 2) ? 0 : 122, 118, 118, 2, COLOR_MEDIUM[random(12)]);

            shuffleArray(patternSequences, patternSequencesSize);
            // int rnd = random(10);
            for (int i = 0; i < 20; i++)
            {
                bool match = false;
                for (int row = 0; row < 7; row++)
                {
                    for (int col = 0; col < 5; col++)
                    {
                        uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                        uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_DARK[rnd] : COLORS_DARK[rnd];
                        // if (DIGITS[curr_digit][row][col] == 1)
                        int state = LineTrack[curr_digit][row][col];
                        if (state == patternSequences[i])
                        {
                            //   tft.fillCircle(tmpDigit[row][col][0], tmpDigit[row][col][1], r, colorrnd);
                            tft.fillSmoothCircle(tmpDigit[row][col][0], tmpDigit[row][col][1], r, colorrnd, colorrnd);
                            match = true;
                        }
                        // delay(40);
                    }
                    // delay(40);
                }
                // if (!match)
                //     break;

                if (!noanim && animation)
                    delay(40);
            }

            // x_start += 39;

            //   x_start += (5 * isize) + 55;
            //   if (pos == 1) {
            //     y_start += 126;
            //     x_start = 30;
            //   }
        }
        for (int i = 0; i < 4; i++)
        {
            blockColor[i] = COLOR_MEDIUM[random(12)];
        }
        shuffleArray(digitOrder, digitOrderSize);
    }
}
void digitalClock(int v)
{
    if (v == 1)
    {
        if (ss == 0)
            digitFace(0);
    }
}