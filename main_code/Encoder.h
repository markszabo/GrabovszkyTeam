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
    long read();
    void write(int targetSide, long value);
    void init();
  private:
    int _channelA;
    int _channelB;
    static void _countPB6();
    static void _countPA15();
};

static volatile long _ticksPB6 = 0;
static volatile long _ticksPA15 = 0;
#endif
