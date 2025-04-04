

void shuffleArray(int *array, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = random(0, i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Segment activation patterns for numbers 0-9 (A-G segments)
const byte digitPatterns[11] = {
    0b1111110, // 0
    0b0110000, // 1
    0b1101101, // 2
    0b1111001, // 3
    0b0110011, // 4
    0b1011011, // 5
    0b1011111, // 6
    0b1110000, // 7
    0b1111111, // 8
    0b1111011, // 9
    0b0000001, // 10 as "-" sign
};

// Segment positions (relative to x,y)
const int segments[7][4] = {
    {1, 0, 3, 0}, // A (top)
    {4, 1, 4, 3}, // B (upper right)
    {4, 4, 4, 6}, // C (lower right)
    {1, 7, 3, 7}, // D (bottom)
    {0, 4, 0, 6}, // E (lower left)
    {0, 1, 0, 3}, // F (upper left)
    {1, 4, 3, 4}  // G (middle)
};

// {1, 0, 3, 0}, // A (top)
// {4, 1, 4, 3}, // B (upper right)
// {4, 4, 4, 6}, // C (lower right)
// {1, 7, 3, 7}, // D (bottom)
// {0, 4, 0, 6}, // E (lower left)
// {0, 1, 0, 3}, // F (upper left)
// {1, 3, 3, 3}  // G (middle)
// #define SS_DISABLE 0x18c3
void drawSegment(int x, int y, int segment, bool state, int size, uint32_t col)
{
    int x0, y0, x1, y1;
    if (segment == 0)
    {
        x0 = (x + segments[segment][0] * size);
        y0 = (y + segments[segment][1] * size) + (size / 2);
        x1 = (x + segments[segment][2] * size);
        y1 = (y + segments[segment][3] * size) + (size / 2);
    }
    else if (segment == 3)
    {
        x0 = (x + segments[segment][0] * size);
        y0 = (y + segments[segment][1] * size) - (size / 2);
        x1 = (x + segments[segment][2] * size);
        y1 = (y + segments[segment][3] * size) - (size / 2);
    }
    else if (segment == 6)
    {
        x0 = (x + segments[segment][0] * size);
        y0 = (y + segments[segment][1] * size) - (size / 2);
        x1 = (x + segments[segment][2] * size);
        y1 = (y + segments[segment][3] * size) - (size / 2);
    }
    else
    {
        x0 = (x + segments[segment][0] * size);
        y0 = y + segments[segment][1] * size;
        x1 = (x + segments[segment][2] * size);
        y1 = y + segments[segment][3] * size;
    }

    // tft.drawLine(x0, y0, x1, y1, state ? TFT_RED : TFT_BLACK);
    if (x0 == x1)
    { // Vertical segment
        tft.drawWideLine(x0, y0, x1, y1, 10, state ? col : SS_DISABLE, TFT_BLACK);
        // tft.drawWideLine(x0 - 1, y0, x1 - 1, y1, 10, state ? TFT_RED : TFT_BLACK, TFT_BLACK);
        // tft.drawWideLine(x0 + 1, y0, x1 + 1, y1, 10, state ? TFT_RED : TFT_BLACK, TFT_BLACK);
        // tft.drawLine(x0 - 1, y0, x1 - 1, y1, state ? TFT_RED : TFT_BLACK);
        // tft.drawLine(x0 + 1, y0, x1 + 1, y1, state ? TFT_RED : TFT_BLACK);
    }
    else
    { // Horizontal segment
        tft.drawWideLine(x0, y0, x1, y1, 10, state ? col : SS_DISABLE, TFT_BLACK);
        // tft.drawWideLine(x0, y0 - 1, x1, y1 - 1, 10, state ? TFT_RED : TFT_BLACK, TFT_BLACK);
        // tft.drawWideLine(x0, y0 + 1, x1, y1 + 1, 10, state ? TFT_RED : TFT_BLACK, TFT_BLACK);
        // tft.drawLine(x0, y0 - 1, x1, y1 - 1, state ? TFT_RED : TFT_BLACK);
        // tft.drawLine(x0, y0 + 1, x1, y1 + 1, state ? TFT_RED : TFT_BLACK);
    }
}

void draw7Segment(int x, int y, int number, int size, uint32_t col)
{
    byte pattern = digitPatterns[number];
    // for (int i = 0; i < 7; i++)
    // {
    //     // bool state = bitRead(pattern, 6 - i); // Bits are A to G (MSB to LSB)
    //     bool state = bitRead(pattern, 6 - sevensegment[i]); // Bits are A to G (MSB to LSB)
    //     drawSegment(x, y, sevensegment[i], true, size, SS_DISABLE);
    //     delay(50);
    // }
    for (int i = 0; i < 7; i++)
    {
        bool state = bitRead(pattern, 6 - sevensegment[i]); // Bits are A to G (MSB to LSB)
        drawSegment(x, y, sevensegment[i], state, size, col);

        if (!noanim && animation)
            delay(75);
    }
}
String old_score;
void ssgmnt(String score)
{

    int sz = 16; // segment size
    int x = 10, y = 16;
    int sssize = sizeof(sevensegment) / sizeof(sevensegment[0]);
    if (score != old_score)
    {
        tft.fillScreen(TFT_BLACK);
        cx = 0, cy = 0;
        // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, hometeam, COLOR_MEDIUM[random(10)], 16);
        // tft.setCursor(0, 82);
        // tft.print(awayteam);
        cx = 0, cy = 130;
        // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);
        int sssize = sizeof(sevensegment) / sizeof(sevensegment[0]);
        old_score = score;
    }
    else
    {
        // tft.fillScreen(TFT_BLACK);
        cx = 0, cy = 0;
        // drawtext(hometeam, TFT_BLACK);
        printtextcs(cx, cy, hometeam, TFT_BLACK, 16);
        // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, hometeam, COLOR_MEDIUM[random(10)], 16);
        // tft.setCursor(0, 82);
        // tft.print(awayteam);
        cx = 0, cy = 130;
        // drawtext(awayteam, TFT_BLACK);
        printtextcs(cx, cy, awayteam, TFT_BLACK, 16);
        // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);

        int sssize = sizeof(sevensegment) / sizeof(sevensegment[0]);
        draw7Segment(x, y, 8, sz, TFT_BLACK); // Position at (20,20) with size 10
        shuffleArray(sevensegment, sssize);
        draw7Segment(x + (sz * 5), y, 8, sz, TFT_BLACK); // Position at (20,20) with size 10
        shuffleArray(sevensegment, sssize);
        draw7Segment(x + (sz * 10), y, 8, sz, TFT_BLACK); // Position at (20,20) with size 10

        // drawDigit(60, 10, 10, ihscore, COLOR_MEDIUM[random(12)]);
    }
    shuffleArray(sevensegment, sssize);
    draw7Segment(x, y, ihscore, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
    shuffleArray(sevensegment, sssize);
    draw7Segment(x + (sz * 5), y, 10, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
    shuffleArray(sevensegment, sssize);
    draw7Segment(x + (sz * 10), y, iascore, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
}

//=================5x3 digit font=======================
int sizee = 10;    // size of each box
byte space = 2;    // space between boxes
int fromTop = 14;  // positon x
int fromLeft = 10; // position y
int Round = 0;

short number = 0;
int digits = 0;

short colors[2] = {TFT_BLACK, TFT_GREEN}; // first colour is color of background , second is color of digit

int oldarr[5][3] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}

};
void drawDigit(int x, int y, int fsize, int digit, uint16_t color)
{
    sizee = fsize;
    fromTop = y;
    fromLeft = x;
    colors[1] = color;
    String n = String(digit);
    for (int z = 0; z < n.length(); z++)
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 3; j++)
            {
                String c = n.substring(z, z + 1);
                int b = c.toInt();
                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[b][i][j]]);
                // delay(20);
            }
}

void drawAnimatedDigit(int x, int y, int fsize, int digit, uint16_t color)
{
    sizee = fsize;
    fromTop = y;
    fromLeft = x;
    colors[1] = color;
    String n = String(digit);
    bool animate = true;

    int anp = 32;
    int f = 0;
    int z = 0;

    String c = n.substring(z, z + 1);
    int b = c.toInt();

    for (int m = 1; m < 21; m++)
    {
        anp--;
        if (m % 5 == 0)
            f++;
        int rnda = random(0, anp);
        for (int i = 0; i < 5; i++)
        {
            if (i <= (f - 1))
            {
                for (int j = 0; j < 3; j++)
                {
                    tft.fillRoundRect((z * (sizee * 8)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, (digit == 10) ? colors[arr[10][i][j]] : colors[arr[b][i][j]]);
                    // tft.fillRoundRect(fromLeft + j * sizee - 1, fromTop + i * sizee - 1, sizee, sizee, Round, (digit == 10) ? colors[arr[10][i][j]] : colors[arr[b][i][j]]);
                    // delay(20);
                }
            }
            else
            {
                for (int j = 0; j < 3; j++)
                {
                    int rnd = random(2);
                    tft.fillRoundRect((z * (sizee * 8)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                    // tft.fillRoundRect(fromLeft + j * sizee - 1, fromTop + i * sizee - 1, sizee, sizee, Round, colors[rnd]);
                }
            }
            if (i == 4 && f == 4)
            {
                for (int j = 0; j < 3; j++)
                {
                    tft.fillRoundRect((z * (sizee * 8)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, (digit == 10) ? colors[arr[10][i][j]] : colors[arr[b][i][j]]);
                    // tft.fillRoundRect(fromLeft + j * sizee - 1, fromTop + i * sizee - 1, sizee, sizee, Round, (digit == 10) ? colors[arr[10][i][j]] : colors[arr[b][i][j]]);
                    // delay(20);
                }
            }
        }
        if (!noanim && animation)
            delay(60);
    }
}

void drawAnimatedDigitd(int x, int y, int fsize, int digit, uint16_t color) // pixelate from top to bottom
{
    sizee = fsize;
    fromTop = y;
    fromLeft = x;
    colors[1] = color;
    String n = String(digit);
    bool animate = true;
    for (int z = 0; z < n.length(); z++)
    {
        int anp = 32;
        // for (int m = 0; m < 20; m++)
        // {
        // anp--;

        int rnda = random(0, anp);
        for (int i = 0; i < 5; i++)
        {
            for (int k = 0; k < 5; k++)
            {

                for (int j = 0; j < 3; j++)
                {

                    String c = n.substring(z, z + 1);
                    int b = c.toInt();
                    int rnd = random(2);
                    if (digit != 10)
                    {
                        // if (rnd == arr[b][i][j])
                        // {

                        if (arr[b][i][j] == 1) // in shape
                        {
                            if (rnda < 2)
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[b][i][j]]);
                            else
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                        }
                        else
                        {
                            if (rnda < 2)
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[b][i][j]]);
                            else
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                        }
                        // tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                    }
                    else
                    {

                        if (arr[b][i][j] == 1) // in shape
                        {
                            if (rnda < 2)
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[10][i][j]]);
                            else
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                        }
                        else
                        {
                            if (rnda < 2)
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[10][i][j]]);
                            else
                                tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[rnd]);
                        }
                    }
                    // tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[random(2)]);
                    // delay(20);
                }
                if (!noanim && animation)
                    delay(80);
            }
            for (int j = 0; j < 3; j++)
            {

                String c = n.substring(z, z + 1);
                int b = c.toInt();
                int rnd = random(2);
                if (digit != 10)
                {

                    tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[b][i][j]]);
                }
                else
                {
                    tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[10][i][j]]);
                }
                // delay(20);
            }
        }
        //     delay(80);
        // }
        if (digit != 10)
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 3; j++)
                {
                    String c = n.substring(z, z + 1);
                    int b = c.toInt();
                    tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[b][i][j]]);
                    // delay(20);
                }
        else
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 3; j++)
                {
                    String c = n.substring(z, z + 1);
                    int b = c.toInt();
                    tft.fillRoundRect((z * (sizee * 4)) + fromLeft + (j * sizee) + (j * space), fromTop + (i * sizee) + (i * space), sizee, sizee, Round, colors[arr[10][i][j]]);
                    // delay(20);
                }
    }
}
void drawDigitLivescore(String score)
{

    int sz = 16; // segment size
    int x = 10, y = 30;
    int digit = (ihscore * 100) + iascore;
    if (score != old_score)
    {
        tft.fillScreen(TFT_BLACK);
        cx = 0, cy = 0;
        // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, hometeam, COLOR_MEDIUM[random(10)], 16);
        // tft.setCursor(0, 82);
        // tft.print(awayteam);
        cx = 0, cy = 110;
        // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);
        drawAnimatedDigit(20, 20, sz, digit, COLOR_MEDIUM[random(12)]);
        drawAnimatedDigit(20 + (sz * 3) + (2 * 3), 20, sz, 10, COLOR_MEDIUM[random(12)]); /// draw '-' digit
        drawAnimatedDigit(20 + (sz * 3) + (2 * 3) + (sz * 3) + (2 * 3), 20, sz, iascore, COLOR_MEDIUM[random(12)]);
        // drawAnimatedDigit(20 + (10 * 3) + (2 * 3), 20, 10, 0, COLOR_MEDIUM[random(12)]);
        // drawAnimatedDigit(20 + (10 * 3) + (2 * 3) + (10 * 3) + (2 * 3), 20, 10, iascore, COLOR_MEDIUM[random(12)]);
        old_score = score;
    }
    else
    {
        // tft.fillScreen(TFT_BLACK);
        cx = 0, cy = 0;
        // drawtext(hometeam, TFT_BLACK);
        printtextcs(cx, cy, hometeam, TFT_BLACK, 16);
        // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, hometeam, COLOR_MEDIUM[random(10)], 16);
        // tft.setCursor(0, 82);
        // tft.print(awayteam);
        cx = 0, cy = 110;
        // drawtext(awayteam, TFT_BLACK);
        printtextcs(cx, cy, awayteam, TFT_BLACK, 16);
        // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
        printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);

        // drawAnimatedDigit(20, 20, 10, digit, COLOR_MEDIUM[random(12)]);
        drawAnimatedDigit(20, 20, sz, ihscore, COLOR_MEDIUM[random(12)]);
        drawAnimatedDigit(20 + (sz * 3) + (2 * 3), 20, sz, 10, COLOR_MEDIUM[random(12)]); /// draw '-' digit
        drawAnimatedDigit(20 + (sz * 3) + (2 * 3) + (sz * 3) + (2 * 3), 20, sz, iascore, COLOR_MEDIUM[random(12)]);
    }
}
void displayscore(String score)
{

    tft.fillScreen(TFT_BLACK);
    // tft.setTextColor(TFT_GREENYELLOW);
    tft.setCursor(0, 0);
    cx = 0, cy = 0;
    // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
    printtextcs(cx, cy, hometeam, COLOR_MEDIUM[random(10)], 16);
    cx = 0, cy = 110;
    // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
    printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);
    // printWordWrap(hometeam, COLOR_MEDIUM[random(12)]);
    score.replace("-", "");
    score.replace(" ", "");
    int count = 0;
    count = (homescore.toInt() * 100) + awayscore.toInt();
    // count = score.toInt();
    Serial.printf("count  : %d \n", count);
    displayDigitHW(count);
}
void displayDigitHW(int count)
{

    int clock_style = random(3);
    // clock_style = 1; // force to test
    int x_start = 25;
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
    int y_start = 36;
    int isize = 10;
    if (clock_style == 0)
        for (int pos = 1; pos < 4; pos++)
        {
            uint8_t curr_digit = 0;
            if (pos == 0)
            {
                curr_digit = count / 1000;
                if (curr_digit == 0)
                    curr_digit = 11; // make it blank. see on res.h
            }
            else if (pos == 1)
            {
                curr_digit = count / 100 % 10;
            }
            else if (pos == 2)
            {
                // curr_digit = count / 10 % 10;
                curr_digit = 10; // make it (-). see on res.h
            }
            else if (pos == 3)
            {
                curr_digit = count % 10;
            }
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
            // suffling row order
            // shuffleArray(tmpRow, tmpRowSize);
            // for (int row = 0; row < 7; row++)
            // {
            //     // suffling collum order
            //     shuffleArray(tmpCol, tmpColSize);
            //     for (int col = 0; col < 5; col++)
            //     {
            //         uint32_t color = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
            //         uint32_t colorrnd = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
            //         // if (DIGITS[curr_digit][row][col] == 1)
            //         bool state = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]];
            //         if (state)
            //             tft.fillCircle(tmpDigit[tmpRow[row]][tmpCol[col]][0], tmpDigit[tmpRow[row]][tmpCol[col]][1], r, colorrnd);
            //         delay(40);
            //     }
            //     delay(40);
            // }
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
                        uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                        // if (DIGITS[curr_digit][row][col] == 1)
                        int state = LineTrack[curr_digit][row][col];
                        if (state == patternSequences[i])
                        {
                            tft.fillCircle(tmpDigit[row][col][0], tmpDigit[row][col][1], r, colorrnd);
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
            x_start += (5 * isize) + 20;
        }
    else if (clock_style == 1)
    {
        // int isize = 4;
        for (int pos = 1; pos < 4; pos++)
        {
            uint8_t curr_digit = 0;
            if (pos == 0)
            {
                curr_digit = count / 1000;
                if (curr_digit == 0)
                    curr_digit = 11; // make it blank. see on res.h
            }
            else if (pos == 1)
            {
                curr_digit = count / 100 % 10;
            }
            else if (pos == 2)
            {
                // curr_digit = count / 10 % 10;
                curr_digit = 10; // make it (-). see on res.h
            }
            else if (pos == 3)
            {
                curr_digit = count % 10;
            }
            int rnd = random(10);

            int startrow = 0;

            // suffling row order
            // shuffleArray(tmpRow, tmpRowSize);
            // for (int row = 0; row < 7; row++)
            // {
            //     // suffling collum order
            //     shuffleArray(tmpCol, tmpColSize);
            //     for (int col = 0; col < 5; col++)
            //     {
            //         uint32_t color = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
            //         uint32_t colorrnd = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
            //         // if (DIGITS[curr_digit][row][col] == 1)
            //         bool state = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]];
            //         if (state)
            //             tft.fillRoundRect(x_start - r + tmpCol[col] * 7, y_start - r + tmpRow[row] * 7, r * 1, r * 1, 0, colorrnd);

            //         delay(40);
            //     }
            //     delay(40);
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

            // x_start += 39;
            x_start += (5 * isize) + 20;
        }
    }
    else if (clock_style == 2)
    {
        // count = 1234;
        int x_start = 20; // x position of ihscore
        int y_start = 30; // y position of number
        for (int pos = 1; pos < 4; pos++)
        {
            int xpath[20];
            int ypath[20];
            for (int i = 0; i < 20; i++)
                xpath[i] = 0, ypath[i] = 0;
            uint8_t curr_digit = 0;
            if (pos == 0)
            {
                // curr_digit = count / 1000;
                if (curr_digit == 0)
                    curr_digit = 11; // make it blank. see on res.h
            }
            else if (pos == 1)
            {
                curr_digit = count / 100 % 10;
            }
            else if (pos == 2)
            {
                // curr_digit = count / 10 % 10;
                curr_digit = 10; // make it (-). see on res.h
            }
            else if (pos == 3)
            {
                curr_digit = count % 10;
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

            int colll = COLORS_LIGHT[rnd];
            int bcoll = TFT_BLACK;

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
                        //   tft.drawBoldLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                        if (i == 1)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[15], ypath[15], 4, colll);

                        // tft.drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                        if (i == 0)
                            //   tft.drawBoldLine(xpath[i], ypath[i], xpath[15], ypath[15], 4, colll);
                            tft.drawWideLine(xpath[i], ypath[i], xpath[15], ypath[15], 10, colll, bcoll);
                        // tft.drawLine(xpath[i], ypath[i], xpath[15], ypath[15], colll);
                    }
                    else if (curr_digit == 1)
                    {
                        if (i == 6)
                        {
                            //   tft.drawBoldLine(xpath[i], ypath[i], xpath[9], ypath[9], 4, colll);
                            tft.drawWideLine(xpath[i], ypath[i], xpath[8], ypath[8], 10, colll, bcoll);
                            // tft.drawLine(xpath[i], ypath[i], xpath[9], ypath[9], colll);}
                        }
                        else
                        { //   tft.drawBoldLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);

                            if (i == 7)
                            {
                                tft.drawBoldLine(xpath[i - 2], ypath[i - 2], xpath[6], ypath[6], 4, colll);
                            }
                            tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                            if (i > 0 && i - 1 != 6)
                                tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                            // tft.drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);}
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
                            // tft.drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                            tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                            if (i > 0 && i - 1 != 7)
                                tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                            //   tft.drawBoldLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                            if (i == 8)
                                //   tft.drawBoldLine(xpath[i], ypath[i], xpath[8], ypath[8], 4, colll);
                                tft.drawWideLine(xpath[i - 2], ypath[i - 2], xpath[8], ypath[8], 10, colll, bcoll);
                            if (i == 9)
                            {
                                tft.drawBoldLine(xpath[6], ypath[6], xpath[7], ypath[7], 4, colll);
                                tft.drawBoldLine(xpath[6], ypath[6], xpath[5], ypath[5], 4, colll);
                            }
                            // tft.drawLine(xpath[i], ypath[i], xpath[8], ypath[8], colll);
                        }

                        else // i==7
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[8], ypath[8], 4, colll);
                    }
                    else if (curr_digit == 8)
                    {
                        // tft.drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);

                        //   tft.drawBoldLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                        if (i == 0)
                            //   tft.drawBoldLine(xpath[i], ypath[i], xpath[9], ypath[9], 4, colll);
                            tft.drawWideLine(xpath[i], ypath[i], xpath[9], ypath[9], 10, colll, bcoll);
                        // tft.drawLine(xpath[i], ypath[i], xpath[9], ypath[9], colll);
                        if (i == 1)
                        //   tft.drawBoldLine(xpath[i], ypath[i], xpath[16], ypath[16], 4, colll);
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
                        // tft.drawLine(xpath[i], ypath[i], xpath[16], ypath[16], colll);
                    }
                    else
                    {
                        // tft.drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                        tft.drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                        if (i > 0)
                            tft.drawBoldLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                        // tft.drawWideLine(xpath[-i], ypath[-i], xpath[i], ypath[i], 6, colll, bcoll);
                        // tft.drawBoldLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                    }
                    if (!noanim && animation)
                        delay(50);
                }
                else
                {
                    break; // if not line any more to draw, then exit for loop
                }
            } // endfor
            // suffling row order
            //   shuffleArray(tmpRow, tmpRowSize);
            //   for (int row = 0; row < 7; row++)
            //   {
            //       // suffling collum order
            //       shuffleArray(tmpCol, tmpColSize);
            //       for (int col = 0; col < 5; col++)
            //       {
            //           uint32_t color = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
            //           uint32_t colorrnd = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
            //           // if (DIGITS[curr_digit][row][col] == 1)
            //           bool state = DIGITS[curr_digit][tmpRow[row]][tmpCol[col]];
            //           if (state)
            //               tft.fillCircle(tmpDigit[tmpRow[row]][tmpCol[col]][0], tmpDigit[tmpRow[row]][tmpCol[col]][1], r, colorrnd);
            //           delay(40);
            //       }
            //       delay(40);
            //   }
            x_start += (5 * isize) + 20;
            // Serial.printf("x_start : %d \n", x_start);
        }
    }
}
