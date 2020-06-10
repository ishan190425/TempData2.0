#include <MFRC522.h>
#include <SPI.h>
#include "wiring.h"
#include "Rfid.h"
#include "Music.h"

int count = 0;

MFRC522 mfrc522 = MFRC522(ssPin, resetPinRfid); //creates instance
Music* buzzer2 = new Music();



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
  buzzer2->playMusic(2);
  return content;
}
