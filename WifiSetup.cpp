#include "WifiSetup.h"
#include "wiring.h"
#include "Music.h"
const char* ssid = "Enter Wifi Name";
const char* password = "Enter Wifi Password";
Music* buzzer1 = new Music();


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
    buzzer1->playMusic(3);
}

void WifiSetup::isConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi();
  }
  return;
}
