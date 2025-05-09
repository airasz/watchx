#include "datajadwal.h"
String infoJadwal = "", prev_infoJadwal = "";
void getPraytaskID(void)
{

  // hh = tnow.hour;
  // mm = tnow.minute;
  formating(); // datajadwal.ino
  if (hh < jsu || (hh == jsu && mm < msu))
  { // jam 24 - shubuh
    ID_ = 0;
    tomorow = 0;
    // if (updateDPray == 1)
    // {
    //         updateDPray = 2;
    //         getPraytaskID();
    // }
  }
  else if (hh > jis || (hh == jis && mm >= mis))
  { // jam isya - 24
    ID_ = 0;
    tomorow = 1;

    // updateDPray = true;
    // if (updateDPray == 0)
    // {
    //         updateDPray = 1;
    //         getPraytaskID();
    // }
  }
  else if ((hh < jdz || (hh == jdz && mm < mdz)) && (hh > jsu || (hh == jsu && mm >= msu)))
  {
    ID_ = 1;
  }
  else if ((hh < jas || (hh == jas && mm < mas)) && (hh > jdz || (hh == jdz && mm >= mdz)))
  {
    ID_ = 2;
  }

  else if ((hh < jmag || (hh == jmag && mm < mmag)) && (hh > jas || (hh == jas && mm >= mas)))
  {
    ID_ = 3;
  }
  else if ((hh < jis || (hh == jis && mm < mis)) && (hh > jmag || (hh == jmag && mm >= mmag)))
  {
    ID_ = 4;
  }
  // Serial.printf("hh %d\n ", hh);
  // Serial.printf("jdz %d\n ", jdz);+ "\n"
  Serial.printf("pray ID %d\n ", ID_);
}
void showDayPray(void)
{
  getPraytaskID();
  //   display.fillScreen(GxEPD_WHITE);
  //   display.setTextColor(GxEPD_BLACK);
  //   display.setFont(&FreeSans9pt7b);
  //   display.setCursor(0, 26);
  //   display.print("Jadwal solat ");

  // printText2(0, 26, "Jadwal solat ", false);
  infoJadwal = "Jadwal solat ";
  int maxday = MaxDate[imnt - 1]; // get maximun day in current month

  String datej;
  if (tomorow)
  {
    datej = "besok, ";
    // print next day
    if (iday + 1 > maxday)
    {
      imnt += 1;
      (imnt > 11) && (imnt = 1); // over december  back to jan
      iday = 1;
      datej += iday;
    }
    else
    {
      datej += iday + 1;
    }
  }
  else
  {
    datej = "hari ini, ";
    // iday += 1;
    datej += iday;
  }
  Serial.printf(" iday : %d \n", iday);
  datej += " ";
  datej += bulan[imnt - 1];
  //   display.print(datej);
  infoJadwal += datej + "\n";
  // printText(datej, false);
  String sdata = "";
  display.setTextColor(GxEPD_BLACK);
  int r = random(10);

  while (r == 8 || r == 5) // avoid color no 5&8
    r = random(10);
  // int color_ = COLOR_MEDIUM[r];
  // Serial.printf(" r : %d \n", r);
  display.setCursor(0, 60);
  for (uint8_t i = 0; i < 5; i++)
  {
    sdata = getDailyJWS(i);
    display.setTextColor(GxEPD_BLACK);
    // display.setFont(FF14);
    // display.setFont(&FreeSans9pt7b);
    display.setFont(FMB9);
    if (i == ID_)
      sdata = ">" + sdata;
    // printText("> " + sdata + "\n", false);
    infoJadwal += sdata + "\n";
    // display.print("> " + sdata + "\n");
  }
  close_incoming_event();
  if (infoJadwal != prev_infoJadwal)
  {
    prev_infoJadwal = infoJadwal;
    printText2(0, 32, infoJadwal, false);
  }
}
// int t; // second elapse next to praytime
bool critical = false;
// bool verycritical = false;
void close_incoming_event()
{ // close_incoming_event code here
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 200);
  // display.setFont(FF18);
  display.setFont(&FreeSans9pt7b);

  for (size_t i = 0; i < 5; i++)
  {
    // Serial.printf("hh : %d  dpraysche %d\n", hh, dPraySche[i][0]);
    if (hh == dPraySche[i][0])
    {
      if (mm < dPraySche[i][1])
      {
        t = dPraySche[i][1] - mm;
        // display.printf("%d menit\nmenjelang %s", t, prayName[i][0]);
        char buff[40];
        sprintf(buff, "%d menit\nmenjelang %s", t, prayName[i][0]);
        infoJadwal += String(buff);
        // printText(infoJadwal, false);
        // infoJadwal += String(buff);
        // printText(infoJadwal, false);
        critical = (t < 15 && t > 0) ? 1 : 0;
        verycritical = (t < 4 && t > 0) ? 1 : 0;
      }
      else
      {
        critical = 0;
        verycritical = 0;
      }

    } // else{t=0;}
    if ((dPraySche[i][0] - hh == 1) && (mm > dPraySche[i][1]))
    {
      t = dPraySche[i][1] + (60 - mm);
      //       display.printf("%d menit\nmenjelang %s", t, prayName[i][0]);
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang %s", t, prayName[i][0]);
      // infoJadwal += String(buff);
      // printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
      verycritical = (t < 4 && t > 0) ? 1 : 0;
    }
  }

  Serial.print("t = ");
  Serial.println(t);
  Serial.print("critical = ");
  Serial.println(critical);
}
String checkPray()
{
  String rtr = "";
  for (size_t i = 0; i < 4; i++)
  {
    if (hh == dPraySche[i][0])
    {
      if (mm < dPraySche[i][1])
      {
        t = dPraySche[i][1] - mm;
        char buff[25];
        sprintf(buff, "\n%d menit maneh %s", t, prayName[i][0]);
        rtr = String(buff);
        infoJadwal += String(buff);
        verycritical = (t < 4 && t > 0) ? 1 : 0;
      }
      else
      {
        verycritical = 0;
      }

    } // else{t=0;}
    if ((dPraySche[i][0] - hh == 1) && (mm > dPraySche[i][1]))
    {
      t = dPraySche[i][1] + (60 - mm);
      char buff[40];
      sprintf(buff, "\n%d menit maneh %s", t, prayName[i][0]);
      rtr = String(buff);
      verycritical = (t < 4 && t > 0) ? 1 : 0;
    }
  }
  if (!rtr.equals(""))
    rtr += "\n";
  Serial.printf("verycritical : %s \n", (verycritical) ? "true" : "false");
  return rtr;
}
void dump()
{

  if (hh == jdz)
  {
    if (mm < mdz)
    {
      t = mdz - mm;
      //       display.printf("%d menit\nmenjelang dzuhur", t);
      //       String cie = sprintf("%d menit\nmenjelang dzuhur", t);
      //       printText(cie, false);
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang dzuhur", t);
      infoJadwal += String(buff);
      printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
    }
    else
    {
      critical = 0;
    }

  } // else{t=0;}
  if ((jdz - hh == 1) && (mm > mdz))
  {
    t = mdz + (60 - mm);
    char buff[40];
    sprintf(buff, "%d menit\nmenjelang dzuhur", t);
    infoJadwal += String(buff);
    printText(infoJadwal, false);
    critical = (t < 15 && t > 0) ? 1 : 0;
  } // else{t=0;}
  if (hh == jas)
  {
    if (mm < mas)
    {
      t = mas - mm;
      //       display.printf("%d menit\nmenjelang azhar", t);
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang azhar", t);
      infoJadwal += String(buff);
      printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
    }
    else
    {
      critical = 0;
    }
  } // else{t=0;}
  if ((jas - hh == 1) && (mm > mas))
  {
    t = mas + (60 - mm);
    char buff[40];
    sprintf(buff, "%d menit\nmenjelang azhar", t);
    infoJadwal += String(buff);
    printText(infoJadwal, false);
    critical = (t < 15 && t > 0) ? 1 : 0;
  } // else{t=0;}
  if (hh == jmag)
  {
    if (mm < mmag)
    {
      t = mmag - mm;
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang maghrib", t);
      infoJadwal += String(buff);
      printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
    }
    else
    {
      critical = 0;
    }
  } // else{t=0;}
  if ((jmag - hh == 1) && (mm > mmag))
  {
    t = mmag + (60 - mm);
    char buff[40];
    sprintf(buff, "%d menit\nmenjelang maghrib", t);
    infoJadwal += String(buff);
    printText(infoJadwal, false);
    critical = (t < 15 && t > 0) ? 1 : 0;
  } // else{t=0;}
  if (hh == jis)
  {
    if (mm < mis)
    {
      t = mis - mm;
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang isya'", t);
      infoJadwal += String(buff);
      printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
    }
    else
    {
      critical = 0;
    }
  } // else{t=0;}
  if ((jis - hh == 1) && (mm > mis))
  {
    t = mis + (60 - mm);
    char buff[40];
    sprintf(buff, "%d menit\nmenjelang isya'", t);
    infoJadwal += String(buff);
    printText(infoJadwal, false);
    critical = (t < 15 && t > 0) ? 1 : 0;
  } // else{t=0;}
  if (hh == jsu)
  {
    if (mm < msu)
    {
      t = msu - mm;
      char buff[40];
      sprintf(buff, "%d menit\nmenjelang shubuh", t);
      infoJadwal += String(buff);
      printText(infoJadwal, false);
      critical = (t < 15 && t > 0) ? 1 : 0;
    }
    else
    {
      critical = 0;
    }
  } // else{t=0;}
  if ((jsu - hh == 1) && (mm > msu))
  {
    t = msu + (60 - mm);
    char buff[40];
    sprintf(buff, "%d menit\nmenjelang shubuh", t);
    infoJadwal += String(buff);
    printText(infoJadwal, false);
    critical = (t < 15 && t > 0) ? 1 : 0;

  } // else{t=0;}
}