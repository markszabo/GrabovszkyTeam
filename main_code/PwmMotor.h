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
#ifndef PwmMotor_h
#define PwmMotor_h

#include "Arduino.h"

class PwmMotor
{
  public:
    PwmMotor(int pin);
    void init();
    void write();
    void setDuty(int duty);
  private:
    int _pin;
    HardwareTimer _timer;
    static void _on_led_PC15();
    static void _off_led_PC15();
    static void _on_led_PB1();
    static void _off_led_PB1();
    static void _on_led_PA7();
    static void _off_led_PA7();
};
static int timerId = 2; //first timer has to be nr 2, since Serial already uses timer nr 1
#endif
