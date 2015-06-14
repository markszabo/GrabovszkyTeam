/*
  Class for generating pwm signal
  Functions for timers are based on this code:
    http://static.leaflabs.com/pub/leaflabs/maple-docs/latest/timers.html#timers
    http://static.leaflabs.com/pub/leaflabs/maple-docs/latest/lang/api/hardwaretimer.html#lang-hardwaretimer
  Usage: 
    PwmMotor onboardLed(PC15); 
    setup: onboardLed.init()
    loop: onboardLed.setDuty(outputValue); //set the pwm duty. Goes from 2 to 30000
*/

#include "Arduino.h"
#include "PwmMotor.h"

#define DUTY_STOP_THRESHOLD 10000
//if pwm is set to be under 10000 the motor stops

PwmMotor::PwmMotor(int pin) : _timer(timerId)
{
  _pin = pin;
  timerId++; //next object should use the next timer
  _directionPin = PIN_UNDEFINED;
  _modePin = PIN_UNDEFINED;
}

PwmMotor::PwmMotor(int pin, int directionPin) : _timer(timerId)
{
  _pin = pin;
  timerId++; //next object should use the next timer
  _directionPin = directionPin;
  _modePin = PIN_UNDEFINED;
}

PwmMotor::PwmMotor(int pin, int directionPin, int modePin) : _timer(timerId)
{
  _pin = pin;
  timerId++; //next object should use the next timer
  _directionPin = directionPin;
  _modePin = modePin;
}

void PwmMotor::init()
{
  if(_directionPin != PIN_UNDEFINED) pinMode(_directionPin, OUTPUT);
  if(_modePin != PIN_UNDEFINED){
    pinMode(_modePin, OUTPUT);
    digitalWrite(_modePin, HIGH);
  }
  
  _initTimer();
}

void PwmMotor::_initTimer()
{
  pinMode(_pin, OUTPUT);
  // Pause the timer while we're configuring it
  _timer.pause();
  
  _timer.setCount(0); //set actual state
  _timer.setOverflow(30000); //set maximum
  
  // Set up an interrupt on channel 1 and 2
  _timer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  _timer.setMode(TIMER_CH2, TIMER_OUTPUT_COMPARE);
  _timer.setCompare(TIMER_CH1, 0);  // if counter is 0, run interrupt
  _timer.setCompare(TIMER_CH2, 0); 
  /*
     attachInterrupt can only take a static function wiht no parameter, so I needed to declare different function for each relevant led
     if pwm would be needed on other pins, please feel free to add it :) ps: don't forget to add it to the header file too
     more about the issue: http://stackoverflow.com/questions/15669017/cant-use-attachinterrupt-in-a-library
                           http://forum.arduino.cc/index.php?topic=45574.0
  */
  switch(_pin) 
  {
  case PC15:
    _timer.attachInterrupt(TIMER_CH1, _on_led_PC15);
    _timer.attachInterrupt(TIMER_CH2, _off_led_PC15);
    break;
  case PB1:
    _timer.attachInterrupt(TIMER_CH1, _on_led_PB1);
    _timer.attachInterrupt(TIMER_CH2, _off_led_PB1);
    break;
  case PA7:
    _timer.attachInterrupt(TIMER_CH1, _on_led_PA7);
    _timer.attachInterrupt(TIMER_CH2, _off_led_PA7);
    break;
  }

  // Refresh the timer's count, prescale, and overflow
  _timer.refresh();

  // Start the timer counting
  _timer.resume();
}

void PwmMotor::setDuty(int duty){
  if(_directionPin != PIN_UNDEFINED){
    /*if(duty > 0 && _directionPin == PA6) digitalWrite(_directionPin, LOW);
    if(duty > 0 && _directionPin == PB0) digitalWrite(_directionPin, HIGH);
    if(duty < 0 && _directionPin == PA6) digitalWrite(_directionPin, HIGH);
    if(duty < 0 && _directionPin == PB0) digitalWrite(_directionPin, LOW);*/
    if(duty > 0) digitalWrite(_directionPin, LOW);
    if(duty < 0) digitalWrite(_directionPin, HIGH);
    _setUnsignedDuty(abs(duty));
  }
  else _setUnsignedDuty(duty);
}

void PwmMotor::_setUnsignedDuty(int uduty)
{
  _timer.pause();
  if(uduty>DUTY_STOP_THRESHOLD && uduty<30000){
    _timer.setCompare(TIMER_CH2, uduty);
    _timer.refresh();
    _timer.resume();
  }else if(uduty>=30000){
    _timer.setCompare(TIMER_CH2, 29999);
    _timer.refresh();
    _timer.resume();    
  }else{ //if uduty < DUTY_STOP_THRESHOLD
    digitalWrite(_pin, LOW);
  }
}

void PwmMotor::_on_led_PC15()
{
  digitalWrite(PC15, HIGH);
}

void PwmMotor::_off_led_PC15()
{
  digitalWrite(PC15, LOW);
}

void PwmMotor::_on_led_PB1()
{
  digitalWrite(PB1, HIGH);
}

void PwmMotor::_off_led_PB1()
{
  digitalWrite(PB1, LOW);
}

void PwmMotor::_on_led_PA7()
{
  digitalWrite(PA7, HIGH);
}

void PwmMotor::_off_led_PA7()
{
  digitalWrite(PA7, LOW);
}
