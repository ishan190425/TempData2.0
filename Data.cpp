#include "Data.h"


const char *host = "script.google.com";
const int httpsPort = 443;
const char *GScriptId = "AKfycbx8w3G55xhOEcICzu1wchXZTzxXJeNg_5wPGIEM";

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?tag=";

String payload = "42";


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
            Serial.println("test1");
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

    //payload = "tag=aaaa&value=122";
    //client->POST(url, host, payload, false);
    //client->GET(url, host);
}

void Data::sendData(float inputVal, String id) {
    String myString = String(inputVal);
    FinalStringToSend = url + id + "&value=" + myString;


    if (client != nullptr) {
        if (!client->connected()) {
            client->connect(host, httpsPort);
            payload = "42";
            //Serial.println("POST Data to Sheet");
            FinalStringToSend = url + myString;
            //Serial.println("POST url :" + FinalStringToSend);
            client->POST(FinalStringToSend, host, payload);
            client->GET(FinalStringToSend, host);
        }
        //client->GET(FinalStringToSend, host);
    } else {
        Serial.println(" >> Failed to POST data");
    }
    //Serial.println("GET url :" + FinalStringToSend);
    client->GET(FinalStringToSend, host);
}


void Data::dataDisconnect() {
    client->connect("google.com", 443);
}
