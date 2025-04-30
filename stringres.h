
// day name in javanese
String const Dino[] = {"Senen", "Seloso", "Rebo", "Kemis", "Jemuah", "Setu", "minggu"};

// clock name in javanese
String const Jam[] = {"tengah\n  wengi", "siji", "loro", "telu", "papat", "limo", "enem", "pitu", "wolu", "songo", "sepuluh", "sewelas",
                      "rolas", "siji", "loro", "telu", "papat", "limo", "enem", "pitu", "wolu", "songo", "sepuluh", "sewelas", "tengah\n  wengi"};
// menit jowo
String const menit[6][10] = {
    {"pas", "siji", "loro", "telu", "papat",
     "limo", "enem", "pitu", "wolu", "songo"},
    {"sepuluh", "sewelas", "rolas", "telulas", "patbelas",
     "seprapat", "nembelas", "pitulas", "wolulas", "songolas"},
    {"rongpuluh", "selikur", "rolikur", "telu likur", "patlikur",
     "selawe", "nemlikur", "pitu likur", "wolu likur", "songo likur"},
    {"setengah", "telung\n     puluh siji", "telung\n    puluh loro", "telung\n     puluh telu", "telung\n     puluh papat",
     "telung\n     puluh limo", " telung\n     puluh enem", "telung\n     puluh pitu", "telung\n     puluh wolu", "telung\n     puluh songo"},
    {"rong puluh", "songolas", "wolulas", "pitulas", "nembelas",
     "seprapat", "patbelas", "telulas", "rolas", "sewelas"},
    {"sepuluh", "songo", "wolu", "pitu", "enem",
     "limo", "papat", "telu", "loro", "siji"}};

String jamTOword(int hour)
{
        // hou
        String word = Jam[hour];
        word.toUpperCase();
        return word;
}
String minuteTOword(int minute)
{
        String word = menit[minute / 10][minute - ((minute / 10) * 10)];
        word.toUpperCase();
        return word;
}
// String amenit[6][10] = {
//     {"pas", "sji", "loro", "telu", "papat",
//      "limo", "enem", "pitu", "wolu", "songo"},
//     {"sepuluh", "sewelas", "rolas", "telulas", "patbelas",
//      "seprapat", "nembelas", "pitulas", "wolulas", "songolas"},
//     {"rongpuluh", "selikur", "rolikur", "telu likur", "patlikur",
//      "selawe", "nemlikur", "pitu likur", "wolu likur", "songo likur"},
//     {"setengah", "telung puluh siji", "telung puluh loro", "telung puluh telu", "telung puluh papat",
//      "telung puluh limo", " telung puluh enem", "telung puluhpitu", "telung puluh wolu", "telung puluh songo"},
//     {"kurang rong puluh", "kurang songolas", "kurang wolulas", "kurang pitulas", "kurang nembelas",
//      "kurang seprapat", "kurang patbelas", "kurang telulas", "kurang rolas", "kurang sewelas"},
//     {"kurang sepuluh", "kurang songo", "kurang wolu", "kurang pitu", "kurang enem",
//      "kurang limo", "kurang papat", "kurang telu", "kurang loro", "kurang siji"}};