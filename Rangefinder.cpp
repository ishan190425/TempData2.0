#include "Arduino.h"
#include "Rangefinder.h"
#include "wiring.h"
//PUT IN WIRING LATER
const int red = redWIRE;
const int green = greenWIRE;
const int triggerPin = triggerPinWIRE;
const int echoPin = echoPinWIRE;
const int buzzerPin = buzzerPinWIRE;


static portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

static volatile unsigned long startTime;
static volatile unsigned long roundTripTime;
hw_timer_t *timer = NULL;

/*
   The procedure is to send a 10us pulse on the trigger line to
   cause the ultrasonic burst to be sent out the speaker. When
   that happens, the echo line will go high. When the echo from
   the sound returns, the echo line will go low. This pulse length
   is measured using the pulseIn function that returns the round-trip
   time in microseconds which is then converted to centimeters and
   returned.
   The timer interrupt routine will send the 10us pulse every 100ms and
   the sensor ISR will time from the rising edge to the falling edge.
   This time is saved in "roundTripTime" and used to compute the distance.
*/

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  digitalWrite(triggerPin, LOW);  // be sure to start from low
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // 10us pulse to start the process
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR sensorISR() {
  portENTER_CRITICAL(&synch);
  if (digitalRead(echoPin)) {
    startTime = micros();
  } else {
    roundTripTime = micros() - startTime;
  }
  portEXIT_CRITICAL(&synch);
}

/*
   Initialize the rangefinder with the trigger pin and echo pin
   numbers.
*/
Rangefinder::Rangefinder() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100000, true);
  timerAlarmEnable(timer);
  attachInterrupt(digitalPinToInterrupt(echoPin), sensorISR, CHANGE);
}

/*
   Get the distance from the rangefinder
*/
float Rangefinder::getDistanceCM() {
  float distance;
  portENTER_CRITICAL(&synch);
  distance = (roundTripTime * 0.0343) / 2.0;
  portEXIT_CRITICAL(&synch);
  return distance;
}

void Rangefinder::rangeSetup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);

}

void Rangefinder::tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(buzzerPin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
}

void Rangefinder::noTone() {
  tone(buzzerPin, 0);
}

void Rangefinder::checkRange() {
  //Serial.print(getDistanceCM());
  //if(15 < getDistanceCM() && getDistanceCM() < 17) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  tone(buzzerPin, 523); //creates buzzer noise
  delay(500);
  noTone();
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  // }
  Serial.println();
  delay(500);
}
