/*
  TODO: write description
*/
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

#define LEFT 1
#define RIGHT 0

class Encoder
{
  public:
    Encoder(int side);
    int read();
    void write(int targetSide, int value);
    void init();
  private:
    int _channelA;
    int _channelB;
    static void _countPB6();
    static void _countPA15();
    static volatile int _ticksPA15;
};
static volatile int _ticksPB6=0;

#endif
