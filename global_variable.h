// #includ
//global variable
const uint32_t COLORS_LIGHT[10] = {
    0xDB5B, 0x97E9, 0x8C7F, 0xFACC, 0xFFED,
    0x4F1F, 0x9ADF, 0xFD0B, 0x5DDF, 0xF9B1};

const uint32_t COLORS_DARK[10] = {
    0x2004, 0x0920, 0x0808, 0x4005, 0x0900,
    0x00E4, 0x280D, 0x20C0, 0x0006, 0x3000};

uint32_t COLOR_MEDIUM[] = {
    PURPLE, BLUE, GREEN, YELLOW, GREENYELLOW,
    PINK, ORANGE, RED, CYAN, MAGENTA};

uint32_t COLOR_MED[] = {
    0x4810, BLUE, GREEN, 0x7380,
    PINK, 0x7380, RED, 0x032D, MAGENTA};

int mm180,hh180;
int hourATCarrow;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

  int rnddot=random(20, 40);
  int rndHandMinuteShadow;
// analog clock variant
float    sx = 0,sy = 1,mx = 1,my = 0,hx = -1,hy = 0;
float    sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=40,osy=40,omx=40,omy=40,ohx=40,ohy=40;

uint16_t x0=0, x1=0, yy0=0, yy1=0;
uint32_t targetTime = 0;                   // for next 1 second timeout
static uint8_t conv2d(const char* p);
// uint8_t  hh=conv2d(__TIME__);              // Get H, M, S from compile time
// uint8_t  mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);

