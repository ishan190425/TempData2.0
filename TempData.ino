#include <Arduino.h>
#include "Data.h"
#include "Rfid.h"
#include "WifiSetup.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "Rangefinder.h" 

using namespace std;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Rangefinder* rangefinder = new Rangefinder();

Data* dataTemp = new Data();
Rfid* reader = new Rfid();
WifiSetup* wifi = new WifiSetup();
String ID;


void setup() {
  rangefinder->rangeSetup();
  mlx.begin();
  Serial.begin(115200);
  Serial.flush();
  reader->setupRfid();
  wifi->setupWifi();
}

void loop() {
  ID = reader->readCard();
  //rangefinder->checkRange();
  if (ID.length() > 0) {
    Serial.println(rangefinder->getDistanceCM());
    if(15 < rangefinder->getDistanceCM() && rangefinder->getDistanceCM() < 17) {
    rangefinder->checkRange();
    Serial.println("ID: " + ID + " " + "Temp: 42");
    wifi->isConnected();
    dataTemp->dataSetup();
    dataTemp->sendData(42, ID);
    dataTemp->dataDisconnect();
    delay(2000);
    }
  }
}
