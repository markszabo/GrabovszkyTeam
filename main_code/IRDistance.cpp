/*
  TODO: write description
*/

#include "Arduino.h"
#include "IRDistance.h"

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
  digitalWrite(_ledPin, HIGH);
  result = analogRead(_transistorPin) - result; //the actual result is the difference
  digitalWrite(_ledPin, LOW);
  return result;
}

