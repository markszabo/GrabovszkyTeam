/*
  TODO: write description
*/
#ifndef IRDistance_h
#define IRDistance_h

#include "Arduino.h"

class IRDistance
{
  public:
    IRDistance(int ledPin, int transistorPin);
    int measure();
    void init();
  private:
    int _ledPin;
    int _transistorPin;
};

#endif
