void beepnblink()
{
    if (millis() > prevmill2 + 100)
    {
        angka++;
        if (angka == startblink)
        {
            if (blinking)
            {
                countblink++;
                // analogWrite(12, 255);
                NEO.setPixelColor(0, NEO.Color(0, 170, 0));
                NEO.show();
                tone(BUZZER_PIN, tmpNOTE);
                if (countblink > nblinking)
                {
                    blinking = false;
                    analogWrite(12, 0);
                    NEO.setPixelColor(0, 0);
                    NEO.show();
                    countblink = 0;
                    // ledcWrite(BUZZER_CHANNEL, 0);
                    noTone(BUZZER_PIN);
                }
            }
        }
        if (angka == endblink)
        {
            if (blinking)
            {
                // analogWrite(12, 0);
                NEO.setPixelColor(0, 0);
                NEO.show();
                // ledcWrite(BUZZER_CHANNEL, 0);
                noTone(BUZZER_PIN);
                if (endmatch == 2)
                {
                    Serial.println("endmatch == 2");
                    endmatch = 0;
                    endblink = 9;
                }
                else if (endmatch == 1)
                {
                    endblink = 19;
                    startblink = 9;
                    endmatch = 2;
                }
            }

            angka = 0;
        }
        prevmill2 = millis();
    }
}