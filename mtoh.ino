double tahunBulan = 354.367068;
double tahunMatahari = 365.25;

String namaBulanHijriah[] = {"Muharram", "Safar", "Rabiul awal", "Rabiul akhir", "Jumadil awal", "Jumadil akhir", "Rajab", "Sya'ban", "Ramadhan", "Syawal", "Dzulkaidah", "Dzulhijjah"};
String namaBulanMasehi[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
uint16_t jumlahHariPerBulanHijriah[] = {0, 30, 59, 89, 118, 148, 177, 207, 236, 266, 295, 325, 354};
uint16_t jumlahHariPerBulanMasehi[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

String nowHijr()
{
    uint32_t totalDays = jumlahHariDariTanggal(day(), month(), year());
    return masehiKeHijriah();
}
uint32_t jumlahHariDariTanggal(byte tanggal, byte bulan, uint16_t tahun)
{
    uint32_t jumlahHari = (uint32_t)tahun * 365;
    for (uint16_t i = 0; i < tahun; i++)
    {
        if (!(i % 4))
        {
            jumlahHari++;
        }
    }
    jumlahHari += jumlahHariPerBulanMasehi[bulan - 1];
    if ((bulan >= 2) && !(tahun % 4))
    {
        jumlahHari++;
    }
    jumlahHari += tanggal;
    return jumlahHari + 259; // base 18 April 1999
}

String masehiKeHijriah()
{
    int dateh, mh, yh;
    uint16_t HariMasehi = jumlahHariDariTanggal(day(), month(), year());
    uint16_t sisaHari;
    yh = floor(HariMasehi / tahunBulan);
    sisaHari = HariMasehi - (tahunBulan * yh);

    for (byte i = 0; i < sizeof(jumlahHariPerBulanHijriah); i++)
    {
        if (sisaHari <= jumlahHariPerBulanHijriah[i])
        {
            sisaHari -= jumlahHariPerBulanHijriah[i - 1];
            mh = i;
            break;
        }
    }
    dateh = sisaHari;
    yh += 1420;
    char buff[25];
    // sprintf
    return "\n" + String(dateh) + " " + String(namaBulanHijriah[mh - 1]) + " " + String(yh += 1420);
}