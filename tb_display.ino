/******************************************************************************
 * tb_display.cpp
 * Library for a simple text buffer scrolling display on the M5StickC.
 * Hague Nusseck @ electricidea
 * v1.3 04.Feb.2020
 * https://github.com/electricidea/M5StickC-TB_Display
 *
 * This library makes it easy to display texts on the M5StickC.
 * The display behaves like a terminal: New text is added at the bottom.
 * The text scrolls up with every new line. The lines are automatically wrapped.
 * The display can be used in any orientation.
 *
 * Changelog:
 * v1.0 = - initial version
 * v1.1 = - Added delay parameter to tb_display_print_String function
 *        - Added text demo in Example (Button B on M5StickC)
 * v1.2 = - Supress of space characters as first character on a new row
 *          after a new line
 *        - Add a word wrapping fuction inside the print_char function
 * v1.3 = - Bugfix if the character that causes a word wrap is a space character
 *
 * Distributed as-is; no warranty is given.
 ******************************************************************************/

#include <Arduino.h>
// #include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
// #include <SPI.h>
#include "tb_display.h"
#include "tft_setup.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip

// #define ST7789_DRIVER
// #define TFT_RGB_ORDER TFT_BGR // Colour order Blue-Green-
// #define TFT_INVERSION_ON
// #define TFT_BACKLIGHT_ON HIGH // HIGH or LOW are options
// #define TFT_BL PIN_D2         // LED back-light (only for ST7789 with backlight control pin)
// #define TFT_DC PIN_D5         // Data Command control pin
// #define TFT_RST PIN_D6        // Reset pin (could connect to NodeMCU RST, see next line)
// #define TFT_BL PIN_D2         // LED back-light (only for ST7789 with backlight control pin)
// #define TFT_MISO PIN_D7
// #define TFT_SCLK

// #define TFT_WIDTH 240  // ST7789 240 x 240 and 240 x 320
// #define TFT_HEIGHT 240 // ST7789 240 x 240
// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)

// For 1.44" and 1.8" TFT with ST7735 use

// TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h
// For 1.54" TFT with ST7789
// Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
// #define TFT_SCLK 13   // set these to be whatever pins you like!
// #define TFT_MOSI 11   // set these to be whatever pins you like!
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// const uint32_t COLOR_MEDIUM[] = {
//     TFT_PURPLE, TFT_GREEN, TFT_YELLOW, TFT_BLUE, TFT_GREENYELLOW,
//     TFT_PINK, TFT_ORANGE, TFT_RED, TFT_CYAN, TFT_MAGENTA, TFT_WHITE};
//  0=PURPLE, 1=GREEN, 2=YELLOW, 3=BLUE, 4=GREENYELLOW,
//  5=PINK, 6=ORANGE, 7=RED, 8=CYAN, 9=MAGENTA, 10=WHITE

int cindexx = (-1);
int colorindex;
int ci, cio;
bool found_new_title = false;
// TextSize 1 is very small on the display = hard to read
// Textsize 2 is good readable without the need of an microscope.
// This code only runs with text size 2!
#define TEXT_SIZE 2
#define TEXT_HEIGHT 16 // Height of text to be printed
// Display size of M5StickC = 160x80
// With TEXT_HEIGHT=16, the screen can display:
//    5 rows of text in portrait mode
//   10 rows of text in landscape mode

// screen buffer for 10 rows of 60 characters max.
#define TEXT_BUFFER_HEIGHT_MAX 18
#define TEXT_BUFFER_LINE_LENGTH_MAX 96
char text_buffer[TEXT_BUFFER_HEIGHT_MAX][TEXT_BUFFER_LINE_LENGTH_MAX];

int text_buffer_height;
int text_buffer_line_length;
int text_buffer_write_pointer_x;
int text_buffer_write_pointer_y;
int text_buffer_read_pointer;
// with tft.setRotation(1)
// the position 0,0 is the upper left corner
// starting a bit more right...
#define SCREEN_XSTARTPOS 5
int screen_xpos = SCREEN_XSTARTPOS;
// start writing at the last line
int screen_ypos;
// maximum width of the screen
int screen_max;

// Enable or disable Waord Wrap
boolean tb_display_word_wrap = true;

// =============================================================
// Initialization of the Text Buffer and Screen
// ScreenRotation values:
// 1 = Button right
// 2 = Button above
// 3 = Button left
// 4 = Button below
// Display size of M5StickC = 160x80pixel
// With TEXT_HEIGHT=16, the screen can display:
//    5 rows of text in landscape mode
//   10 rows of text in portrait mode
// =============================================================
void tb_display_init(int ScreenRotation)
{
  tft.init();
  tft.setRotation(ScreenRotation);
  switch (ScreenRotation)
  {
  case 1:
  case 3:
  {
    // 5 rows of text in landscape mode
    text_buffer_height = 8;
    text_buffer_line_length = 60;
    // width of the screen in landscape mode is 160 pixel
    // A small margin on the right side prevent false print results
    screen_max = 160 - 2;
    break;
  }
  case 2:
  case 4:
  {
    // 10 rows of text in portrait mode
    text_buffer_height = 10;
    text_buffer_line_length = 30;
    // width of the screen in portrait mode is 80 pixel
    // A small margin on the right side prevent false print results
    screen_max = 80 - 2;
    break;
  }
  default:
  {
    break;
  }
  }
  text_buffer_height = 16;
  text_buffer_line_length = 96;

  screen_max = 240 - 2;
  tb_display_clear();
  tb_display_show();
}

// =============================================================
// clear the text buffer
// without refreshing the screen
// call tb_display_show(); to clear the screen
// =============================================================
void tb_display_clear()
{
  for (int line = 0; line < TEXT_BUFFER_HEIGHT_MAX; line++)
  {
    for (int charpos = 0; charpos < TEXT_BUFFER_LINE_LENGTH_MAX; charpos++)
    {
      text_buffer[line][charpos] = '\0';
    }
  }
  text_buffer_read_pointer = 0;
  text_buffer_write_pointer_x = 0;
  text_buffer_write_pointer_y = text_buffer_height - 1;
  screen_xpos = SCREEN_XSTARTPOS;
  screen_ypos = TEXT_HEIGHT * (text_buffer_height - 1);
}

// =============================================================
// clear the screen and display the text buffer
// =============================================================
void tb_display_show()
{
  tft.fillScreen(TFT_BLACK);
  // Serial.println("tb display show");
  int yPos = 0;
  found_new_title = false;
  for (int n = 0; n < text_buffer_height; n++)
  {
    Serial.printf(" n : %d \n", n);
    // modulo operation for line position

    int line = (text_buffer_read_pointer + n) % text_buffer_height;
    int xPos = SCREEN_XSTARTPOS;
    int charpos = 0;
    while (xPos < screen_max && text_buffer[line][charpos] != '\0')
    {
      // (colorindex++ > 9) && (colorindex = 0);
      // tft.setTextColor(COLOR_MEDIUM[colorindex]);
      if (text_buffer[line][charpos] == '#')
      {
        found_new_title = true;
      }

      // xPos += tft.drawChar(text_buffer[line][charpos], xPos, yPos, TEXT_SIZE);
      // Serial.print(text_buffer[line][charpos]);
      charpos++;
    }
  }
  if (found_new_title)
  {
    Serial.println("found new title");
    cio = ci - 1;
    (cio < 0) && (cio == 10);
    tft.setTextColor(COLOR_MEDIUM[cio]);
  }
  else
  {
    Serial.println("not found new title");
    cio = ci;
    tft.setTextColor(COLOR_MEDIUM[cio]);
  }
  for (int n = 0; n < text_buffer_height; n++)
  {
    // modulo operation for line position

    int line = (text_buffer_read_pointer + n) % text_buffer_height;
    int xPos = SCREEN_XSTARTPOS;
    int charpos = 0;

    while (xPos < screen_max && text_buffer[line][charpos] != '\0')
    {
      // (colorindex++ > 9) && (colorindex = 0);
      // tft.setTextColor(COLOR_MEDIUM[colorindex]);
      if (text_buffer[line][charpos] == '#')
      {
        ci = text_buffer[line][charpos - 1] - '0';
        tft.setTextColor(COLOR_MEDIUM[ci]);
      }

      xPos += tft.drawChar(text_buffer[line][charpos], xPos, yPos, TEXT_SIZE);
      charpos++;
    }
    // if (text_buffer[line][charpos] == '+')
    // {
    //   (colorindex-- < 0) && (colorindex = 9);
    //   // tft.setTextColor(COLOR_MEDIUM[colorindex]);
    // }
    // if (text_buffer[line][charpos] == '+')
    // {
    //   (colorindex-- < 0) && (colorindex = 9);
    //   tft.setTextColor(COLOR_MEDIUM[colorindex]);
    // }
    yPos = yPos + TEXT_HEIGHT;
  }
  screen_xpos = SCREEN_XSTARTPOS;
}

// =============================================================
// creates a new line and scroll the display upwards
// =============================================================
void tb_display_new_line()
{
  // Serial.println("tb_display_new_line");
  text_buffer_write_pointer_x = 0;
  text_buffer_write_pointer_y++;
  text_buffer_read_pointer++;
  // circular buffer...
  if (text_buffer_write_pointer_y >= text_buffer_height)
    text_buffer_write_pointer_y = 0;
  if (text_buffer_read_pointer >= text_buffer_height)
    text_buffer_read_pointer = 0;
  // clear the actual new line for writing (first character a null terminator)
  text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = '\0';
  tb_display_show();
}

// =============================================================
// print a single character
// the character is added to the text buffer and
// directly printed on the screen.
// The text is automatically wrapped if longer than the display
// example:
//    tb_display_print_char('X');
// =============================================================
void tb_display_print_char(byte data)
{
  // Serial.printf("posX  : %d \n", text_buffer_write_pointer_x);
  // check for LF for new line
  if (data == '\n')
  {
    // cindexx--;
    // (cindexx < 0) && (cindexx = 9);
    // tft.setTextColor(COLOR_MEDIUM[cindexx]);
    // last character in the text_buffer line  should be always a null terminator
    text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = '\0';
    tb_display_new_line();
  }
  // only 'printable' characters
  if (data > 31 && data < 128)
  {

    if (data == '\n')
    {
      // cindexx++;
      // (cindexx > 9) && (cindexx = 0);
      // tft.setTextColor(COLOR_MEDIUM[cindexx]);
    }
    // Serial.write(data, BYTE);
    String sss = String(data);
    // Serial.print(sss);
    // print the character and get the new xpos
    screen_xpos += tft.drawChar(data, screen_xpos, screen_ypos, TEXT_SIZE);
    // if maximum number of characters reached
    if (text_buffer_write_pointer_x >= text_buffer_line_length - 1)
    {
      tb_display_new_line();

      // draw the character again because it was out of the screen last time

      screen_xpos += tft.drawChar(data, screen_xpos, screen_ypos, TEXT_SIZE);
    }
    // or if line wrap is reached
    if (screen_xpos >= screen_max)
    {
      // prepare for Word-Wrap stuff...
      // the buffer for storing the last word content
      char Char_buffer[TEXT_BUFFER_LINE_LENGTH_MAX];
      int n = 1;
      Char_buffer[0] = data;
      Char_buffer[n] = '\0';
      // if Word-Wrap, go backwards and get the last "word" by finding the
      // last space character:
      if (tb_display_word_wrap)
      {
        int test_pos = text_buffer_write_pointer_x - 1;
        // get backwards and search a space character
        while (test_pos > 0 && text_buffer[text_buffer_write_pointer_y][test_pos] != ' ')
        {
          // store all the characters on the way back to the last space character
          Char_buffer[n] = text_buffer[text_buffer_write_pointer_y][test_pos];
          test_pos--;
          n++;
          Char_buffer[n] = '\0';
        }
        // if there was no space character in the row, Word-Wrap is not possible
        if (test_pos == 0)
        {
          // don't use the buffer but draw the character passed to the function
          n = 1;
        }
        else
        {
          // otherwise use the buffer to print the last found characters of the word
          // but only, if the charachter that causes a word wrap is not a space character
          if (data != ' ')
          {
            // place a \0 at the position of the found space so that the drawing fuction ends here
            text_buffer[text_buffer_write_pointer_y][test_pos] = '\0';
          }
        }
      }
      tb_display_new_line();
      // icharacter passed to the function is a space character, then don't display
      // it as the first character of the new line
      if (data == ' ')
        // don't use the buffer at all
        n = 0;
      n--;
      while (n >= 0)
      {
        if (data == 43)
        {
          // cindexx++;
          // (cindexx > 9) && (cindexx = 0);
          // tft.setTextColor(COLOR_MEDIUM[cindexx]);
        }
        // draw the characters from the buffer back on the screen

        screen_xpos += tft.drawChar(Char_buffer[n], screen_xpos, screen_ypos, TEXT_SIZE);
        // Serial.print(Char_buffer[n]);
        // write the characters into the screen buffer of the new line
        text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = Char_buffer[n];
        text_buffer_write_pointer_x++;
        n--;
      }
      text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = '\0';
    }
    else
    {
      // write the character into the screen buffer
      text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = data;
      text_buffer_write_pointer_x++;
      // following character a null terminator to clear the old characters of the line
      text_buffer[text_buffer_write_pointer_y][text_buffer_write_pointer_x] = '\0';
    }
  }
} // end void

// =============================================================
// print a string
// The string is added to the text buffer and directly printed
// on the screen.
// The otional parameter "chr_delay" allows a "character by character"
// processing of the String. Then, it looks like Teletype or Typewriter
// The delay is in milliseconds.
// The text is automatically wrapped if longer than the display
// example:
//    tb_display_print_String("a new line\n");
//    tb_display_print_String("one\nand two lines\n");
//
//    char String_buffer[128];
//    snprintf(String_buffer, sizeof(String_buffer), "\nthe value: %i",value);
//    tb_display_print_String(String_buffer);
//
//    std::string msg;
//    msg = ss.str();
//    const char * c_msg = msg.c_str();
//    tb_display_print_String(c_msg);
// =============================================================
void tb_display_print_String(const char *s, int chr_delay)
{
  // cindexx++;
  // (cindexx > 9) && (cindexx = 0);
  // tft.setTextColor(COLOR_MEDIUM[cindexx]);
  while (*s != 0)
  {
    tb_display_print_char(*s++);
    if (chr_delay > 0)
      delay(chr_delay);
  }
}

void tb_display_setTexColor()
{
  // tft.setTextColor(color);

  tft.setTextColor(COLOR_MEDIUM[random(10)]);
}
void increaseCio()
{
  (cio-- < 0) && (cio = 9);
}
