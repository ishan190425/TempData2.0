#include <Arduino.h>
#include "Data.h"
#include "Rfid.h"
#include "WifiSetup.h"
//This is a test
//testing123
using namespace std;

Data* dataTemp = new Data();
Rfid* reader = new Rfid();
WifiSetup* wifi = new WifiSetup();
String ID;


void setup() {
  Serial.begin(115200);
  Serial.flush();
  reader->setupRfid();
  wifi->setupWifi();
}

void loop() {
  ID = reader->readCard();
  if (ID.length() > 0) {
    Serial.println("ID: " + ID + " " + "Temp: 42");
    wifi->isConnected();
    dataTemp->dataSetup();
    dataTemp->sendData(42, ID);
    dataTemp->dataDisconnect();
    delay(2000);
  }
}
