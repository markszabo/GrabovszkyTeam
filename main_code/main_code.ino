#include "IRDistance.h"
#include "PwmMotor.h"
#include "Piezo.h"

int sensorValue = 0;
int outputValue = 0;
int soundNr = 0;

IRDistance IRLeftBack(PB14, PA2);
IRDistance IRLeftFront(PB13, PA3);
IRDistance IRRightBack(PB13, PA5);
IRDistance IRRightFront(PB14, PA4);

PwmMotor onboardLed(PC15); 
Piezo buzzer(PB15);

void setup() {
  IRLeftBack.init();
  IRLeftFront.init();
  IRRightBack.init();
  IRRightFront.init();
  onboardLed.init();
  buzzer.init();
  
  Serial.begin(19200); //the actual baudrate will be the double of it. Dunno why :D
}

void loop() {
  sensorValue = IRLeftBack.measure();
  Serial.print("LeftBack: ");
  Serial.print(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 0, 30000);
  onboardLed.setDuty(outputValue);
  
  sensorValue = IRLeftFront.measure();
  Serial.print(" LeftFront: ");
  Serial.print(sensorValue);
  if(sensorValue > 400) buzzer.r2D2();
  
  sensorValue = IRRightFront.measure();
  Serial.print(" RightFront: ");
  Serial.print(sensorValue);
  if(sensorValue > 400) buzzer.laugh2();
  
  sensorValue = IRRightBack.measure();
  Serial.print(" RightBack: ");
  Serial.println(sensorValue);
  if(sensorValue > 400){
    Serial.print("Playing the ");
    Serial.print(soundNr);
    Serial.println("th sound.");
    switch(soundNr){
      case 0:
        buzzer.squeak();
        break;
      case 1:
        buzzer.catcall();
        break;
      case 2:
        buzzer.ohhh();
        break;
      case 3:
        buzzer.laugh();
        break;
      case 4:
        buzzer.closeEncounters();
        break;
      case 5:
        buzzer.laugh2();
        break;
      case 6:
        buzzer.waka();
        break;
      case 7:
        buzzer.r2D2();
        break;
      case 8:
        buzzer.ariel();
        soundNr = -1;
        break;
    }
    soundNr++;
    }
  delay(333);
}
