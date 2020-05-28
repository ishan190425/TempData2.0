#include <Arduino.h>
#include "Data.h"
#include "Rfid.h"
#include "WifiSetup.h"

using namespace std;

Data* dataTemp = new Data();
Rfid* reader = new Rfid();
WifiSetup* wifi = new WifiSetup();
String ID;
float temp = 47;

void setup() {
  Serial.begin(115200);
  Serial.flush();
  reader->setupRfid();
  wifi->setupWifi();
}

void loop() {
  ID = reader->readCard();
  if (ID.length() > 0) {
    Serial.println("ID: " + ID + " " + "Temp: "+temp);
    wifi->isConnected();
    dataTemp->dataSetup();
    dataTemp->sendData(temp, ID);
    dataTemp->dataDisconnect();
    delay(2000);
  }
}
