
void formating(void)
{
  // if (updateDPray>0)
  // {
  // if (timeClient.getYear() == 1970)
  // {
  //   timeClient.update();
  // }
  // else
  // {
  //   WiFi.mode(WIFI_OFF);
  //   setCpuFrequencyMhz(20);
  // }
  imnt = timeClient.getMonth(), iday = timeClient.getDate();
  Serial.printf("mnt : %d | day %d\n", imnt, iday);
  getPdata(imnt, iday);
  for (size_t i = 0; i < 5; i++)
  {
    dPraySche[i][0] = dPray[i] / 100;
    dPraySche[i][1] = dPray[i] - ((dPray[i] / 100) * 100);
    // Serial.printf(" dPraySche : %d | %d\n", dPraySche[i][0], dPraySche[i][1]);
  }

  jsu = dPray[0] / 100;
  msu = dPray[0] - ((dPray[0] / 100) * 100);
  jdz = dPray[1] / 100;
  mdz = dPray[1] - ((dPray[1] / 100) * 100);
  jas = dPray[2] / 100;
  mas = dPray[2] - ((dPray[2] / 100) * 100);
  jmag = dPray[3] / 100;
  mmag = dPray[3] - ((dPray[3] / 100) * 100);
  jis = dPray[4] / 100;
  mis = dPray[4] - ((dPray[4] / 100) * 100);
  // updateDPray = false;
  // }
  // dbFile.close();
}
void getPdata(uint8_t mnt, uint8_t day)
{
  dbFile = SPIFFS.open("/" + String(mnt - 1) + ".json", "r");
  // File dbFile = SPIFFS.open("/0.json", "r");
  if (!dbFile)
  {
    Serial.println("ERROR: DB file not found");
    // return false;
  }
  DynamicJsonDocument doc(3248);
  DeserializationError err = deserializeJson(doc, dbFile);
  if (err)
  {
    Serial.println("ERROR: " + String(err.c_str()));
    // return false;
  }
  for (size_t i = 0; i < 5; i++)
  {
    int in = doc[String(day)][i];
    dPray[i] = in;
  }
  // Serial.printf("pray day: %02d | mnt:  %02d | prayID%02d \n", day, mnt, in);

  dbFile.close();
}
uint16_t getpray(uint8_t mnt, uint8_t day, uint8_t prayID)
{
  // Serial.printf("load month  : %d \n", mnt-1);
  dbFile = SPIFFS.open("/" + String(mnt - 1) + ".json", "r");
  // File dbFile = SPIFFS.open("/0.json", "r");
  if (!dbFile)
  {
    Serial.println("ERROR: DB file not found");
    // return false;
  }
  DynamicJsonDocument doc(3248);
  DeserializationError err = deserializeJson(doc, dbFile);
  if (err)
  {
    Serial.println("ERROR: " + String(err.c_str()));
    // return false;
  }
  int in = doc[String(day)][prayID];
  // Serial.printf("pray day: %02d | mnt:  %02d | prayID%02d \n", day, mnt, in);

  // dbFile.close();
  return in;
}

// return string
String getDailyJWS(int id)
{
  // String jadwal = "";
  char jadwal[20];
  int maxday = MaxDate[imnt - 1];
  // formating();
  if (tomorow)
  {
    // if maximum day, jump to next month
    if (iday + 1 > maxday)
    {
      imnt += 1;
      iday = 1;
    }
    else
    {
      iday += 1;
    }
  }
  String pname = prayName[id][0];
  for (size_t i = prayName[id][0].length(); i < 8; i++)
  {
    pname += " ";
  }

  sprintf(jadwal, "%s  %02i:%02i", pname, dPraySche[id][0], dPraySche[id][1]);
  // switch (id)
  // {
  // case 0:
  //   //                                                           .___________.
  //   //                                                  v----v----.         |
  //   sprintf(jadwal, "Subuh    > %02i:%02i", jsu, msu);
  //   // jadwal = "Subuh    > 0";
  //   // jadwal += jsu;
  //   // jadwal += (msu < 10) ? ":0" : ":";
  //   // jadwal += msu;

  //   break;
  // case 1:
  //   sprintf(jadwal, "Dzuhur   > %02i:%02i", jdz, mdz);
  //   break;
  // case 2:
  //   sprintf(jadwal, "Ashar    > %02i:%02i", jas, mas);
  //   break;
  // case 3:
  //   sprintf(jadwal, "Maghrib  > %02i:%02i", jmag, mmag);
  //   break;
  // case 4:
  //   sprintf(jadwal, "Isya'    > %02i:%02i", jis, mis);
  //   break;
  // default:
  //   break;
  // }
  if (tomorow)
    iday -= 1;
  return jadwal;
}