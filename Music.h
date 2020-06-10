#include <ArduinoOTA.h>
#include "Arduino.h"
class Music {
  public:
    Music();
    void tone(byte pin, int freq);
    void noTone();
    void playMusic(int amt);
};
