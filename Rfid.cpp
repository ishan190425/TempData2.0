#include <MFRC522.h>
#include <SPI.h>
#include "wiring.h"
#include "Rfid.h"

int count = 0;
const int buzzerPin = buzzerPinWIRE;
MFRC522 mfrc522 = MFRC522(ssPin, resetPinRfid); //creates instance

void Rfid::tone(byte pin, int freq) {
    ledcSetup(0, 2000, 8); // setup beeper
    ledcAttachPin(buzzerPin, 0); // attach beeper
    ledcWriteTone(0, freq); // play tone
}

void Rfid::noTone() {
    tone(buzzerPin, 0);
}
void Rfid::setupRfid() {
  // put your setup code here, to run once:
  SPI.begin();
  mfrc522.PCD_Init();
}

String Rfid::readCard() {

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return "";
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return "";
  }
  //Show UID on serial monitor
  Serial.println("Program has started");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {

    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i]));
  }

  content.replace(" ", "");
    tone(buzzerPin, 523); //creates buzzer noise
    delay(500);
    noTone();
    delay(500);
    tone(buzzerPin, 523); //creates buzzer noise
    delay(500);
    noTone();
  return content;
}
