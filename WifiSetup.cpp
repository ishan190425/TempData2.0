#include "WifiSetup.h"
#include "wiring.h"
const char* ssid = "MyHomeWifiGuest";
const char* password = "Iamaguest";
const int buzzerPin = buzzerPinWIRE;

void WifiSetup::tone(byte pin, int freq) {
    ledcSetup(0, 2000, 8); // setup beeper
    ledcAttachPin(buzzerPin, 0); // attach beeper
    ledcWriteTone(0, freq); // play tone
}

void WifiSetup::noTone() {
    tone(buzzerPin, 0);
}
void WifiSetup::setupWifi() {
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  // flush() is needed to print the above (connecting...) message reliably,
  // in case the wireless connection doesn't go through
  Serial.flush();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    tone(buzzerPin, 523); //creates buzzer noise
    delay(500);
    noTone();
    delay(500);
    tone(buzzerPin, 523);
    delay(500);
    noTone();
    delay(500);
    tone(buzzerPin, 523);
    delay(500);
    noTone();
}

void WifiSetup::isConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi();
  }
  return;
}
