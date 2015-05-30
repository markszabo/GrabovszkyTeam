/*
  TODO: write description
*/
#ifndef PwmMotor_h
#define PwmMotor_h

#include "Arduino.h"

class PwmMotor
{
  public:
    PwmMotor(int pin, int timerId);
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

#endif
