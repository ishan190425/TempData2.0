class Rangefinder {
  public:
    float getDistanceCM();
    void rangeSetup();
    void checkRange();
    void tone(byte pin, int freq);
    void noTone();
    Rangefinder();
};
