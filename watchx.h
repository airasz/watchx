
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <ESP32Ping.h>
// #include <ESP8266WiFi.h>#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "stringres.h"
#include "Free_Fonts.h"
#include "mathematicalize.h"
// #include <LittleFS.h>

// #include "FS.h"
#include "note.h"

WiFiMulti wifimulti;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const char *remote_host = "www.google.co.id";
int sevensegment[7] = {0, 1, 2, 3, 4, 5, 6};
int tmpRow[7] = {0, 1, 2, 3, 4, 5, 6};
int tmpRowSize = sizeof(tmpRow) / sizeof(tmpRow[0]);
int tmpCol[5] = {0, 1, 2, 3, 4};
int tmpColSize = sizeof(tmpCol) / sizeof(tmpCol[0]);
int patternSequences[20] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20};
int patternSequencesSize = sizeof(patternSequences) / sizeof(patternSequences[0]);
void shuffleArray(int *array, int size);

const uint8_t MaxDate[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

String const bulan[] =
    {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli",
     "Agustus", "September", "Oktober", "November", "Desember"};
auto tomorow = false;
uint8_t imnt, iday;
String prev_pasaranWuku = "";
int ID_;
uint32_t tmpDigit[7][5][2] = {
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}}};

uint32_t oldDigit_0[7][5][2] = {
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}}};

uint32_t oldDigit_1[7][5][2] = {
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}}};

uint32_t oldDigit_2[7][5][2] = {
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}}};

uint32_t oldDigit_3[7][5][2] = {
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}},
    {{0, 0},
     {0, 0},
     {0, 0},
     {0, 0},
     {0, 0}}};
uint16_t blockColor[4] = {0, 0, 0, 0};
int digitOrder[4] = {0, 1, 2, 3};
int digitOrderSize = sizeof(digitOrder) / sizeof(digitOrder[0]);
uint8_t digitOrderIndex = 0;

uint8_t jsu, msu, jdz, mdz, jas, mas, jmag, mmag, jis, mis;
int dPray[5] = {0, 0, 0, 0, 0};
int dPraySche[5][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
String const prayName[5][2] = {
    {"Subuh", "su"},
    {"Dzuhur", "dz"},
    {"Ashar", "as"},
    {"Maghrib", "mg"},
    {"Isya", "is"},
};
int updateDPray = 0;
bool scfc = false; // save if clock face change
int hh, mm, ss;