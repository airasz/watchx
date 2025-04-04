
// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define ST7789_DRIVER
// #define TFT_RGB_ORDER TFT_BGR // Colour order Blue-Green-
// #define TFT_INVERSION_ON
// #define TFT_BACKLIGHT_ON HIGH // HIGH or LOW are options
// #define TFT_BL PIN_D2         // LED back-light (only for ST7789 with backlight control pin)
// #define TFT_DC PIN_D5  // Data Command control pin
// #define TFT_RST PIN_D6 // Reset pin (could connect to NodeMCU RST, see next line)
// #define TFT_BL PIN_D2  // LED back-light (only for ST7789 with backlight control pin)
// #define TFT_MOSI PIN_D7
// #define TFT_SCLK PIN_D8

// #define TFT_DC PIN_D1  // Data Command control pin
// #define TFT_RST PIN_D0 // Reset pin (could connect to NodeMCU RST, see next line)
// #define TFT_BL PIN_D2  // LED back-light (only for ST7789 with backlight control pin)
// #define TFT_CS 33
// #define TFT_RST 14 // you can also connect this to the Arduino reset
// // in which case, set this #define pin to -1!
// #define TFT_DC 26

#define TFT_WIDTH 240  // ST7789 240 x 240 and 240 x 320
#define TFT_HEIGHT 240 // ST7789 240 x 240

#define LOAD_GLCD  // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2 // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4 // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6 // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7 // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8 // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
// #define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY  20000000
#define SPI_FREQUENCY 27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  55000000 // STM32 SPI1 only (SPI2 maximum is 27MHz)
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY 20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY 2500000

#define SUPPORT_TRANSACTIONS