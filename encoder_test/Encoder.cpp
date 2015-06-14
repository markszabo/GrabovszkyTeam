/*
  TODO: write description
*/

#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int side)
{
  _channelA = PB6;
  _channelB = PB7;
}

void Encoder::init(){
      attachInterrupt(_channelA, _countPB6, RISING);
      _ticksPB6 = 0;
  pinMode(_channelB, INPUT);
}

int Encoder::read(){
  switch (_channelA)
  {
    case PB6:
      return _ticksPB6;
    case PA15:
      return _ticksPA15;
  }
}

void Encoder::write(int targetSide, int value){
  if(targetSide == LEFT)
    _ticksPA15 = value;
  else if(targetSide == RIGHT)
    _ticksPB6 = value;
}

void Encoder::_countPB6()
{
 if(digitalRead(PB7) == HIGH) _ticksPB6--;
  else _ticksPB6++;
}

void Encoder::_countPA15()
{
 if(digitalRead(PB3) == HIGH) _ticksPA15--;
  else _ticksPA15++;
}
