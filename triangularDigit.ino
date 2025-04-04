int tenSegment[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// Segment activation patterns for numbers 0-9 (A-G segments)
uint32_t TenSegmenPaterns[11][10] = {
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 1}, // 0
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 1}, // 1
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // 2
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // 3
    {1, 0, 0, 1, 1, 0, 1, 0, 1, 1}, // 4
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1}, // 5
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // 6
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 1}, // 7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // 9
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0}  // 10 as "-" sign
};

uint32_t triangularpos[10][3][2] = {
    {{0, 0}, {0, 0}, {0, 0}},  // 0
    {{0, 0}, {0, 0}, {0, 0}},  // 1
    {{0, 0}, {0, 0}, {0, 0}},  // 2
    {{0, 0}, {0, 0}, {0, 0}},  // 3
    {{0, 0}, {0, 0}, {0, 0}},  // 4
    {{0, 0}, {0, 0}, {0, 0}},  // 5
    {{0, 0}, {0, 0}, {0, 0}},  // 6
    {{0, 0}, {0, 0}, {0, 0}},  // 7
    {{0, 0}, {0, 0}, {0, 0}},  // 8
    {{0, 0}, {0, 0}, {0, 0}}}; // 9

/* //
//
//    a
//    /\
//   /| \
//  / |  \
// /  |   \
//c --d--- b
//
*/
void fillingTriangular_old(int x, int y, int size, int gap)
{
  float btp = sqrt((size * size) + ((size / 2) * (size / 2))); // a to d
  float btpg = sqrt((gap * gap) + ((gap / 2) * (gap / 2)));    // gap to gap
  for (int i = 0; i < 10; i++)
  {
    if (i == 0)
    {
      triangularpos[i][0][0] = x;              // x
      triangularpos[i][0][1] = y;              // y
      triangularpos[i][1][0] = x + int(btp);   // x1
      triangularpos[i][1][1] = y + (size / 2); // y1
      triangularpos[i][2][0] = x;              // x2
      triangularpos[i][2][1] = y + size;       // y2
    }
    else if (i == 1)
    {
      triangularpos[i][0][0] = x;                           // x
      triangularpos[i][0][1] = y + size + gap;              // y
      triangularpos[i][1][0] = x + int(btp);                // x1
      triangularpos[i][1][1] = y + (size / 2) + size + gap; // y1
      triangularpos[i][2][0] = x;                           // x2
      triangularpos[i][2][1] = y + size + size + gap;       // y2
    }
    else if (i == 2)
    {
      triangularpos[i][0][0] = x + int(btp) + int(btpg) + gap;       // x
      triangularpos[i][0][1] = y - (size / 2) - (gap / 2);           // y
      triangularpos[i][1][0] = x + (int(btp) * 2) + int(btpg) + gap; // x1
      triangularpos[i][1][1] = y - (gap / 2);                        // y1
      triangularpos[i][2][0] = x + int(btp) + int(btpg) + gap;       // x2
      triangularpos[i][2][1] = y + (size / 2) - (gap / 2);           // y2
    }
    else if (i == 3)
    {
      triangularpos[i][0][0] = x + int(btp) + int(btpg) + gap;       // x
      triangularpos[i][0][1] = y + (size / 2) + (gap / 2);           // y
      triangularpos[i][1][0] = x + (int(btp) * 2) + int(btpg) + gap; // x1========V
      triangularpos[i][1][1] = y + size + (gap / 2);                 // y1
      triangularpos[i][2][0] = x + int(btp) + int(btpg) + gap;       // x2
      triangularpos[i][2][1] = y + ((size / 2) + (gap / 2)) + size;  // y2
    }
    else if (i == 4)
    {
      triangularpos[i][0][0] = x + int(btp) + int(btpg) + gap;                // x
      triangularpos[i][0][1] = y + size + gap + (size / 2) + (gap / 2);       // y
      triangularpos[i][1][0] = x + (int(btp) * 2) + int(btpg) + gap;          // x1
      triangularpos[i][1][1] = y + (size * 2) + gap + (gap / 2);              // y1
      triangularpos[i][2][0] = x + int(btp) + int(btpg) + gap;                // x2
      triangularpos[i][2][1] = y + (size * 2) + gap + (gap / 2 + (size / 2)); // y2
    }
    else if (i == 5)
    {
      triangularpos[i][0][0] = x + int(btpg);                // x
      triangularpos[i][0][1] = y - (gap / 2);                // y
      triangularpos[i][1][0] = x + int(btpg) + int(btp);     // x1
      triangularpos[i][1][1] = y - (size / 2) - (gap / 2);   // y1
      triangularpos[i][2][0] = x + int(btpg) + int(btp);     // x2
      triangularpos[i][2][1] = y + (size / 2) - (gap / gap); // y2
    }
    else if (i == 6)
    {
      triangularpos[i][0][0] = x + int(btpg);                       // x
      triangularpos[i][0][1] = y + size + (gap / 2);                // y
      triangularpos[i][1][0] = x + int(btpg) + int(btp);            // x1
      triangularpos[i][1][1] = y + (size / 2) + (gap / 2);          // y1
      triangularpos[i][2][0] = x + int(btpg) + int(btp);            // x2
      triangularpos[i][2][1] = y + ((size / 2) + (gap / 2)) + size; // y2
    }
    else if (i == 7)
    {
      triangularpos[i][0][0] = x + int(btpg);                                 // x
      triangularpos[i][0][1] = y + (size * 2) + gap + (gap / 2);              // y
      triangularpos[i][1][0] = x + int(btpg) + int(btp);                      // x1
      triangularpos[i][1][1] = y + size + gap + (size / 2) + (gap / 2);       // y1
      triangularpos[i][2][0] = x + int(btpg) + int(btp);                      // x2
      triangularpos[i][2][1] = y + (size * 2) + gap + (gap / 2 + (size / 2)); // y2
    }
    else if (i == 8)
    {
      triangularpos[i][0][0] = x + int(btp) + (int(btpg * 2)) + gap;       // x
      triangularpos[i][0][1] = y + (size / 2);                             // y
      triangularpos[i][1][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x1
      triangularpos[i][1][1] = y;                                          // y1
      triangularpos[i][2][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x2
      triangularpos[i][2][1] = y + size;                                   // y2
    }
    else if (i == 9)
    {
      triangularpos[i][0][0] = x + int(btp) + (int(btpg * 2)) + gap;       // x
      triangularpos[i][0][1] = y + (size / 2) + size + gap;                // y
      triangularpos[i][1][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x1
      triangularpos[i][1][1] = y + size + gap;                             // y1
      triangularpos[i][2][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x2
      triangularpos[i][2][1] = y + size + size + gap;                      // y2
    }
  }
}
void fillingTriangular(int x, int y, int size, int gap)
{
  float btp = sqrt((size * size) - ((size / 2) * (size / 2))); // a to d
  float btpg = sqrt((gap * gap) - ((gap / 2) * (gap / 2)));    // gap to gap
  for (int i = 0; i < 10; i++)
    if (i < 5)
    {
      if (i < 2)
      {
        triangularpos[i][0][0] = x;            // x0
        triangularpos[i][2][0] = x;            // x2
        triangularpos[i][1][0] = x + int(btp); // x1
        if (i == 0)
        {

          triangularpos[i][0][1] = y;                  // y0
          triangularpos[i + 8][0][1] = y;              // y0
          triangularpos[i][1][1] = y + (size / 2);     // y1
          triangularpos[i + 8][1][1] = y + (size / 2); // y1
          triangularpos[i][2][1] = y + size;           // y2
          triangularpos[i + 8][2][1] = y + size;       // y2
        }
        else if (i == 1)
        {
          triangularpos[i][0][1] = y + size + gap;                  // y0
          triangularpos[i + 8][0][1] = y + size + gap;              // y0
          triangularpos[i][1][1] = y + (size / 2) + size + gap;     // y1
          triangularpos[i + 8][1][1] = y + (size / 2) + size + gap; // y1
          triangularpos[i][2][1] = y + size + size + gap;           // y2
          triangularpos[i + 8][2][1] = y + size + size + gap;       // y2
        }
      }
      else
      {
        triangularpos[i][0][0] = x + int(btp) + int(btpg) + gap;       // x0
        triangularpos[i][2][0] = x + int(btp) + int(btpg) + gap;       // x2
        triangularpos[i][1][0] = x + (int(btp) * 2) + int(btpg) + gap; // x1
        if (i == 2)
        {
          triangularpos[i][0][1] = y - (size / 2) - (gap / 2);     // y0
          triangularpos[i + 3][0][1] = y - (size / 2) - (gap / 2); // y0
          triangularpos[i][1][1] = y - (gap / 2);                  // y1
          triangularpos[i + 3][1][1] = y - (gap / 2);              // y1
          triangularpos[i][2][1] = y + (size / 2) - (gap / 2);     // y2
          triangularpos[i + 3][2][1] = y + (size / 2) - (gap / 2); // y2
        }
        else if (i == 3)
        {
          triangularpos[i][0][1] = y + (size / 2) + (gap / 2);              // y0
          triangularpos[i + 3][0][1] = y + (size / 2) + (gap / 2);          // y0
          triangularpos[i][1][1] = y + size + (gap / 2);                    // y1
          triangularpos[i + 3][1][1] = y + size + (gap / 2);                // y1
          triangularpos[i][2][1] = y + ((size / 2) + (gap / 2)) + size;     // y2
          triangularpos[i + 3][2][1] = y + ((size / 2) + (gap / 2)) + size; // y2
        }
        else if (i == 4)
        {
          triangularpos[i][0][1] = y + size + gap + (size / 2) + (gap / 2);           // y0
          triangularpos[i + 3][0][1] = y + size + gap + (size / 2) + (gap / 2);       // y0
          triangularpos[i][1][1] = y + (size * 2) + gap + (gap / 2);                  // y1
          triangularpos[i + 3][1][1] = y + (size * 2) + gap + (gap / 2);              //
          triangularpos[i][2][1] = y + (size * 2) + gap + (gap / 2 + (size / 2));     // y2
          triangularpos[i + 3][2][1] = y + (size * 2) + gap + (gap / 2 + (size / 2)); // y2
        }
      }
    }
    else
    {
      if (i < 8)
      {
        triangularpos[i][0][0] = x + int(btpg) + int(btp); // x0
        triangularpos[i][2][0] = x + int(btpg) + int(btp); // x1
        triangularpos[i][1][0] = x + int(btpg);            // x2
      }
      else
      {
        triangularpos[i][0][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x0
        triangularpos[i][2][0] = x + (int(btpg) * 2) + (int(btp) * 2) + gap; // x1
        triangularpos[i][1][0] = x + int(btp) + (int(btpg * 2)) + gap;       // x2
      }
    }
}
// #define SS_DISABLE 0x18c3

void drawTSegment(int x, int y, int segment, bool state, int size, uint32_t col)
{
  int x0, y0, x1, y1, x2, y2;
  x0 = (x + triangularpos[segment][0][0]);
  y0 = (y + triangularpos[segment][0][1]);
  x1 = (x + triangularpos[segment][1][0]);
  y1 = (y + triangularpos[segment][1][1]);
  x2 = (x + triangularpos[segment][2][0]);
  y2 = (y + triangularpos[segment][2][1]);
  tft.fillTriangle(x0, y0, x1, y1, x2, y2, (state) ? col : SS_DISABLE);
  // if (state) {
  //   tft.fillTriangle(x0, y0, x1, y1, x2, y2, col);
  // } else {
  //   tft.fillTriangle(x0, y0, x1, y1, x2, y2, SS_DISABLE);
  //   tft.drawTriangle(x0, y0, x1, y1, x2, y2, col);
  // }
}

void drawT7Segment(int x, int y, int number, int size, uint32_t col)
{
  fillingTriangular(x, y, size, 4);
  uint16_t tmppaterns[10];
  for (int i = 0; i < 10; i++)
  {
    tmppaterns[i] = TenSegmenPaterns[number][i];
  }
  if (!noanim && animation)
    for (int i = 0; i < 10; i++) // random flicker animation before displaying the number
    {
      for (int i = 0; i < 10; i++)
      {
        bool state = random(2);
        // Serial.print(state);
        drawTSegment(x, y, tenSegment[i], state, size, col);
        delay(5);
      }
      if (!noanim && animation)
        delay(25);
    }
  for (int i = 0; i < 10; i++)
  {
    bool state = TenSegmenPaterns[number][i];
    // Serial.print(state);
    drawTSegment(x, y, tenSegment[i], state, size, col);

    if (!noanim && animation)
      delay(75);
  }
}
// String old_score;
void tsgmnt(String score)
{
  int sz = 22; // segment size

  int gap = int(sqrt(sz));
  float btp = sqrt((sz * sz) - ((sz / 2) * (sz / 2))); // a to d
  Serial.printf("btp : %f \n", btp);
  float btpg = sqrt((gap * gap) - ((gap / 2) * (gap / 2))); // gap to gap
  Serial.printf("btpg : %f \n", btpg);

  int x = 10, y = 20;
  // int nextpos = (sz * 2) - (sz / 2);
  // int nextpos = (int(btpg) * 2) + (int(btp) * 2) + gap + gap;
  int nextpos = (int(btpg) * 2) + (int(btp) * 1) + gap + gap;

  if (score != old_score)
  {
    tft.fillScreen(TFT_BLACK);
    cx = 0, cy = 0;
    // drawtext(hometeam, COLOR_MEDIUM[random(10)]);
    printtextcs(cx, cy, hometeam, TFT_BLACK, 16);

    // tft.setCursor(0, 82);
    // tft.print(awayteam);
    cx = 0, cy = 106;
    // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
    printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);
    int sssize = sizeof(sevensegment) / sizeof(sevensegment[0]);
    drawT7Segment(x, y, ihscore, sz, COLOR_MEDIUM[random(12)]);                     // Position at (20,20) with size 10
    drawT7Segment(x + nextpos, y, 10, sz, COLOR_MEDIUM[random(12)]);                // Position at (20,20) with size 10
    drawT7Segment(x + nextpos + nextpos, y, iascore, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
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
    cx = 0, cy = 106;
    printtextcs(cx, cy, awayteam, TFT_BLACK, 16);
    // drawtext(awayteam, TFT_BLACK);
    printtextcs(cx, cy, awayteam, COLOR_MEDIUM[random(10)], 16);
    // drawtext(awayteam, COLOR_MEDIUM[random(10)]);
    int sssize = sizeof(sevensegment) / sizeof(sevensegment[0]);
    drawT7Segment(x, y, ihscore, sz, COLOR_MEDIUM[random(12)]);                     // Position at (20,20) with size 10
    drawT7Segment(x + nextpos, y, 10, sz, COLOR_MEDIUM[random(12)]);                // Position at (20,20) with size 10
    drawT7Segment(x + nextpos + nextpos, y, iascore, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
  }
}
void testDTSegment(int number)
{

  // drawT7Segment(x, y, number, sz, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
  // drawT7Segment(10, 10, number, 16, COLOR_MEDIUM[random(12)]); // Position at (20,20) with size 10
  number = 1000 + (number * 100) + number;
  displayDigitHW(number);
}