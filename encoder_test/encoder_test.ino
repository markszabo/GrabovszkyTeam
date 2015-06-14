/*volatile long w1=0;

void wheel1()
{
 if(digitalRead(PB3) == HIGH) w1--;
  else w1++;
}

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(PA15, wheel1, RISING);
  pinMode(PB3, INPUT);
  Serial.begin(19200); 
}

void loop() {
  Serial.println(w1);
  // put your main code here, to run repeatedly:
  delay(1000);
}*/

#include "Encoder.h"

Encoder encoderRight(0);
void setup(){
  encoderRight.init();
  Serial.begin(19200); //the actual baudrate will be the double of it. Dunno why :D
}

void loop() {
  //Serial.print(encoderLeft.read());
  Serial.print("  ");
  Serial.println(encoderRight.read());
  delay(1000);
  }
