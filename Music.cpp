#include "Music.h"
#include "wiring.h"

const int buzzerPin = buzzerPinWIRE;

void Music::tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(buzzerPin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
}

void Music::noTone() {
  tone(buzzerPin, 0);
}

void Music::playMusic(int amt) {
  for (int i = 0; i < amt; i++) {
    tone(buzzerPin, 523);
    delay(500);
    noTone();
    delay(500);
  }
  noTone();
}

Music::Music() {
  pinMode(buzzerPin, OUTPUT);
}
