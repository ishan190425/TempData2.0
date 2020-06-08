#include <Arduino.h>
#include "Data.h"
#include "Rfid.h"
#include "WifiSetup.h"
#include <Adafruit_MLX90614.h>
#include "Rangefinder.h"
#include <Wire.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Rangefinder* rangefinder = new Rangefinder();

using namespace std;

Data* dataTemp = new Data();
Rfid* reader = new Rfid();
WifiSetup* wifi = new WifiSetup();
String ID;
float temp;

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
  if (ID.length() > 0) {
    while (15 >= rangefinder->getDistanceCM() || rangefinder->getDistanceCM() >= 17) {
      Serial.println(rangefinder->getDistanceCM());
      delay(500);
    }
    rangefinder->checkRange();
    temp = mlx.readObjectTempF() + 10.5;
    Serial.println("ID: " + ID + " " + "Temp: " + temp);
    wifi->isConnected();
    dataTemp->dataSetup();
    dataTemp->sendData(temp, ID);
    dataTemp->dataDisconnect();
    delay(2000);
  }
}
