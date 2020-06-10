#include "Arduino.h"

class Rfid {
  public:
    String readCard();
    void setupRfid();
};
