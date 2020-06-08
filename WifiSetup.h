#include <ArduinoOTA.h>

#include <WiFi.h>


class WifiSetup {
  public:
    void setupWifi();
     void tone(byte pin, int freq);
    void noTone();
    void isConnected();
};
