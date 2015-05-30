#include "IRDistance.h"
#include "PwmMotor.h"

int sensorValue = 0;
int outputValue = 0;

IRDistance IRLeftBack(PB14, PA2);
PwmMotor onboardLed(PC15, 2); //do not use timer nr 1, since Serial already uses it

void setup() {
  IRLeftBack.init();
  onboardLed.init();
  Serial.begin(19200); //the actual baudrate will be the double of it. Dunno why :D
}

void loop() {
  sensorValue = IRLeftBack.measure();
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 0, 30000);
  
  onboardLed.setDuty(outputValue);
  delay(1000);
}
