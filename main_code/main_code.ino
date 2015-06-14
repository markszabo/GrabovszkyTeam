#include "IRDistance.h"
#include "PwmMotor.h"
#include "Piezo.h"
#include "Encoder.h"

int leftError = 0;
int rightError = 0;
int P = 100;

IRDistance IRLeftBack(PB14, PA2);
IRDistance IRLeftFront(PB13, PA3);
IRDistance IRRightBack(PB13, PA5);
IRDistance IRRightFront(PB14, PA4);


PwmMotor leftMotor(PA7, PA6, PB2);
PwmMotor onboardLed(PC15);
PwmMotor rightMotor(PB1, PB0);

Encoder encoderLeft(LEFT);
Encoder encoderRight(RIGHT);

void setup() {
  IRLeftBack.init();
  IRLeftFront.init();
  IRRightBack.init();
  IRRightFront.init();
  onboardLed.init();
  
  encoderLeft.init();
  encoderRight.init();
  leftMotor.init();
  rightMotor.init();
  
 /* pinMode(PA6, OUTPUT);
  pinMode(PB2, OUTPUT);
  pinMode(PB0, OUTPUT); //B direction
      digitalWrite(PA6, LOW); //A dir
    digitalWrite(PB0, HIGH); //B dir
  digitalWrite(PB2, HIGH);*/
  Serial.begin(19200); //the actual baudrate will be the double of it. Dunno why :D
  delay(2000);
}

void loop() {
  leftError = 1000-encoderLeft.read();
  rightError = 1000-encoderRight.read();
    leftMotor.setDuty(P*leftError);
    rightMotor.setDuty(P*rightError);
  Serial.print(encoderLeft.read());
  Serial.print("  ");
  Serial.println(encoderRight.read());
  /*
  digitalWrite(PA6, LOW);
  digitalWrite(PB2, HIGH);
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
  */
}
