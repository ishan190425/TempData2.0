#//include <WiFi.h>
#include "HTTPSRedirect.h"
#include "wiring.h"

class Data {
public:
    void dataSetup();

    void sendData(float, String);

    void dataDisconnect();

    void isConnected();

};
