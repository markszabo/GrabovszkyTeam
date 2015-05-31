/*
  TODO: write description
*/

#include "Arduino.h"
#include "IRDistance.h"

const int WAIT_TIME = 1; //ms

IRDistance::IRDistance(int ledPin, int transistorPin)
{
  _ledPin = ledPin;
  _transistorPin = transistorPin;
}

void IRDistance::init(){
  pinMode(_ledPin, OUTPUT);
  pinMode(_transistorPin, INPUT_ANALOG);
}

int IRDistance::measure(){
  int result = analogRead(_transistorPin);
  delay(WAIT_TIME);
  digitalWrite(_ledPin, HIGH);
  delay(WAIT_TIME);
  result = analogRead(_transistorPin) - result; //the actual result is the difference
  delay(WAIT_TIME);
  digitalWrite(_ledPin, LOW);
  return result;
}

