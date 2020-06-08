#include "Arduino.h"

class Rfid {
  public:
    String readCard();
 void tone(byte pin, int freq);
    void noTone();
    void setupRfid();

};
