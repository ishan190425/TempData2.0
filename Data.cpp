#include <dummy.h>

#include "Data.h"


extern const char *host = "script.google.com";
extern const int httpsPort = 443;
const char *GScriptId = "AKfycbxaJjnqGv5WAzQwEtz1nMmP4a-hdE5CTaxsBxAYpJJp_M4gqvk";

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?tag=";

//String payload = "42";


String FinalStringToSend;


HTTPSRedirect *client = nullptr;
// used to store the values of free stack and heap
// before the HTTPSRedirect object is instantiated
// so that they can be written to Google sheets
// upon instantiation
void Data::dataSetup() {

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");

  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
      flag = true;
      break;
    } else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }
}

void Data::sendData(float inputVal, String id) {
  String myString = String(inputVal);
  FinalStringToSend = url + id + "&value=" + myString;


  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
      FinalStringToSend = url + myString;
      client->POST(FinalStringToSend, host);
      client->GET(FinalStringToSend, host);
    }
  } else {
    Serial.println(" >> Failed to POST data");
  }
  client->GET(FinalStringToSend, host);
}


void Data::dataDisconnect() {
  client->stop();
}
