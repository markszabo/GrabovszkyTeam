/*
  Class for using the onboard Piezo buzzer
  This class is heavily based on this code: http://www.mycontraption.com/?wpdmact=process&did=My5ob3RsaW5r
  Usage: 
    Piezo buzzer(PB15);
    setup: buzzer.init()
    loop: buzzer.r2D2(); //to play some tone
*/

#include "Arduino.h"
#include "Piezo.h"

Piezo::Piezo(int pin)
{
  _pin = pin;
}

void Piezo::init(){
   pinMode(_pin, OUTPUT);
}

void Piezo::_beep(float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(_pin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(_pin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     

void Piezo::scale() 
{    
          _beep(note_C7,500); //C: play the note C for 500ms 
          _beep(note_D7,500); //D 
          _beep(note_E7,500); //E 
          _beep(note_F7,500); //F 
          _beep(note_G7,500); //G 
          _beep(note_A7,500); //A 
          _beep(note_B7,500); //B 
          _beep(note_C8,500); //C 
}  

void Piezo::r2D2(){
          _beep(note_A7,100); //A 
          _beep(note_G7,100); //G 
          _beep(note_E7,100); //E 
          _beep(note_C7,100); //C
          _beep(note_D7,100); //D 
          _beep(note_B7,100); //B 
          _beep(note_F7,100); //F 
          _beep(note_C8,100); //C 
          _beep(note_A7,100); //A 
          _beep(note_G7,100); //G 
          _beep(note_E7,100); //E 
          _beep(note_C7,100); //C
          _beep(note_D7,100); //D 
          _beep(note_B7,100); //B 
          _beep(note_F7,100); //F 
          _beep(note_C8,100); //C 
}

void Piezo::closeEncounters() {
          _beep(note_Bb5,300); //B b
          delay(50);
          _beep(note_C6,300); //C
          delay(50);
          _beep(note_Ab5,300); //A b
          delay(50);
          _beep(note_Ab4,300); //A b
          delay(50);
          _beep(note_Eb5,500); //E b   
          delay(500);     
          
          _beep(note_Bb4,300); //B b
          delay(100);
          _beep(note_C5,300); //C
          delay(100);
          _beep(note_Ab4,300); //A b
          delay(100);
          _beep(note_Ab3,300); //A b
          delay(100);
          _beep(note_Eb4,500); //E b   
          delay(500);  
          
          _beep(note_Bb3,300); //B b
          delay(200);
          _beep(note_C4,300); //C
          delay(200);
          _beep(note_Ab3,300); //A b
          delay(500);
          _beep(note_Ab2,300); //A b
          delay(550);
          _beep(note_Eb3,500); //E b      
}

void Piezo::ariel() {

          _beep(note_C6,300); //C
          delay(50);
          _beep(note_D6,300); //D
          delay(50);
          _beep(note_Eb6,600); //D#
          delay(250);
          
          _beep(note_D6,300); //D
          delay(50);
          _beep(note_Eb6,300); //D#
          delay(50);
          _beep(note_F6,600); //F
          delay(250);
          
          _beep(note_C6,300); //C
          delay(50);
          _beep(note_D6,300); //D
          delay(50);
          _beep(note_Eb6,500); //D#
          delay(50);          
          _beep(note_D6,300); //D
          delay(50);
          _beep(note_Eb6,300); //D#
          delay(50);             
          _beep(note_D6,300); //D
          delay(50);
          _beep(note_Eb6,300); //D#
          delay(50);
          _beep(note_F6,600); //F
          delay(50); 

}
 

void Piezo::laugh2() {
          _beep(note_C6,200); //C
          _beep(note_E6,200); //E  
          _beep(note_G6,200); //G 
          _beep(note_C7,200); //C 
          _beep(note_C6,200); //C
          delay(50);
          _beep(note_C6,200); //C
          _beep(note_E6,200); //E  
          _beep(note_G6,200); //G 
          _beep(note_C7,200); //C 
          _beep(note_C6,200); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
          delay(50);
          _beep(note_C6,50); //C
}
  
void Piezo::squeak() {
  for (int i=100; i<5000; i=i*1.45) {
    _beep(i,60);
  }
  delay(10);
  for (int i=100; i<6000; i=i*1.5) {
    _beep(i,20);
  }
}

void Piezo::waka() {
  for (int i=1000; i<3000; i=i*1.05) {
    _beep(i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    _beep(i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    _beep(i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    _beep(i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    _beep(i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    _beep(i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    _beep(i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    _beep(i,10);
  }
}

void Piezo::catcall() {
  for (int i=1000; i<5000; i=i*1.05) {
    _beep(i,10);
  }
 delay(300);
 
  for (int i=1000; i<3000; i=i*1.03) {
    _beep(i,10);
  }
  for (int i=3000; i>1000; i=i*.97) {
    _beep(i,10);
  }
}

void Piezo::ohhh() {
  for (int i=1000; i<2000; i=i*1.02) {
    _beep(i,10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    _beep(i,10);
  }
}

void Piezo::uhoh() {
  for (int i=1000; i<1244; i=i*1.01) {
    _beep(i,30);
  }
  delay(200);
  for (int i=1244; i>1108; i=i*.99) {
    _beep(i,30);
  }
}

void Piezo::laugh() {
  for (int i=1000; i<2000; i=i*1.10) {
    _beep(i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    _beep(i,10);
  }
  delay(50);
  for (int i=1000; i<2000; i=i*1.10) {
    _beep(i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    _beep(i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    _beep(i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    _beep(i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    _beep(i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    _beep(i,10);
  }
  delay(50);
}

