//Wird nicht wirklich benötigt da der tiny auch tone() aus der Aurdiono Bibliothek richtig umsetzt, allerdings nur auf PWM fähigen PINS
#include <Arduino.h>

#define TONE_PIN 0



void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
  int  x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));  
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }  
}


void setup()
{
    pinMode(TONE_PIN, OUTPUT);
}

void startup()
{
  unsigned int startfreq=500;
    for (int8_t i=0;i<5;i++){
      tone(TONE_PIN, startfreq+=500, 100);      
      delay(100);
    }

    delay(2000);
}

void loop()
{
 // Ton 1 (tiefer)
  tone(TONE_PIN, 440);
  delay(500);  // 0,5 Sekunden halten

  // Ton 2 (höher)
  tone(TONE_PIN, 780);
  delay(500);  // 0,5 Sekunden halten
}