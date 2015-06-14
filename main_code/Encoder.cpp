/*
  TODO: write description
*/

#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int side)
{
  if(side == LEFT){
  _channelA = PA15;
  _channelB = PB3;
  }else if(side == RIGHT){
  _channelA = PB7;
  _channelB = PB6;
  }
}

void Encoder::init(){
  switch (_channelA)
  {
    case PB6:
      attachInterrupt(_channelA, _countPB6, RISING);
      break;
    case PA15:
      attachInterrupt(_channelA, _countPA15, RISING);
      break;
  }
  pinMode(_channelB, INPUT);
}

long Encoder::read(){
  switch (_channelA)
  {
    case PB6:
      return _ticksPB6;
    case PA15:
      return _ticksPA15;
  }
}

void Encoder::write(int targetSide, long value){
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
 if(digitalRead(PB3) == HIGH) _ticksPA15++;
  else _ticksPA15--;
}
