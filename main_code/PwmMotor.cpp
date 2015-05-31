/*
  TODO: write description
*/

#include "Arduino.h"
#include "PwmMotor.h"

PwmMotor::PwmMotor(int pin) : _timer(timerId)
{
  _pin = pin;
  timerId++; //next object should use the next timer
}

void PwmMotor::init()
{
  pinMode(_pin, OUTPUT);
  // Pause the timer while we're configuring it
  _timer.pause();
  
  _timer.setCount(0); //set actual state
  _timer.setOverflow(30000); //set maximum
  
  // Set up an interrupt on channel 1 and 2
  _timer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  _timer.setMode(TIMER_CH2, TIMER_OUTPUT_COMPARE);
  _timer.setCompare(TIMER_CH1, 1);  // if counter is 1, run interrupt
  _timer.setCompare(TIMER_CH2, 1); 
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
  _timer.pause();
  _timer.setCompare(TIMER_CH2, duty);
  _timer.refresh();
  _timer.resume();
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
