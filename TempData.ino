#include <Arduino.h>
#include "Data.h"
#include "Rfid.h"
#include "WifiSetup.h"
#include <Adafruit_MLX90614.h>
#include "Rangefinder.h" 

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Rangefinder* rangefinder = new Rangefinder();

using namespace std;

Data* dataTemp = new Data();
Rfid* reader = new Rfid();
WifiSetup* wifi = new WifiSetup();
String ID;
float temp = 96;

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
    Serial.print(rangfinder->getDistanceCM());
    while(15 >= rangefinder->getDistanceCM() || rangedfinder->getDistanceCM >= 17){
      Serial.print(rangfinder->getDistanceCM());
      delay(1000);
    }
    Serial.println("ID: " + ID + " " + "Temp: "+temp);
    wifi->isConnected();
    dataTemp->dataSetup();
    dataTemp->sendData(temp, ID);
    dataTemp->dataDisconnect();
    delay(2000);
  }
}
