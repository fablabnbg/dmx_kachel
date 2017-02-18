#include <DMXSerial.h>
#include "Panel.h"

//Setting up dmx channels. The argument is the startaddress. 
Panel one(1);
Panel two(7);

const int RedPin1 =    3;  // PWM output pin for Red Light.
const int GreenPin1 =  5;  // PWM output pin for Green Light.
const int BluePin1 =   6;  // PWM output pin for Blue Light.
const int RedPin2 =    9;  // PWM output pin for Red Light.
const int GreenPin2 =  10;  // PWM output pin for Green Light.
const int BluePin2 =   11;  // PWM output pin for Blue Light.

#define RedDefaultLevel   100
#define GreenDefaultLevel 200
#define BlueDefaultLevel  255

void setup () {
  DMXSerial.init(DMXReceiver);
  
  // set some default values
  DMXSerial.write(1, 80);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);
  DMXSerial.write(4, 80);
  DMXSerial.write(5, 0);
  DMXSerial.write(6, 0);
  
  // enable pwm outputs
  pinMode(RedPin1,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin1, OUTPUT);
  pinMode(BluePin1,  OUTPUT);
  pinMode(RedPin2,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin2, OUTPUT);
  pinMode(BluePin2,  OUTPUT);

}


void loop() {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  one.updateDMX();
  two.updateDMX();
  one.fadeCalc();
  two.fadeCalc();
  one.strobeCalc();
  two.strobeCalc();
  
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels 
    analogWrite(RedPin1,   one.getRed());
    analogWrite(GreenPin1, one.getGreen());
    analogWrite(BluePin1,  one.getBlue());
    analogWrite(RedPin2,   two.getRed());
    analogWrite(GreenPin2, two.getGreen());
    analogWrite(BluePin2,  two.getBlue());    

  } else {
    // Show pure red color, when no data was received since 5 seconds or more.
    analogWrite(RedPin1,   RedDefaultLevel);
    analogWrite(GreenPin1, GreenDefaultLevel);
    analogWrite(BluePin1,  BlueDefaultLevel);
    analogWrite(RedPin2,   RedDefaultLevel);
    analogWrite(GreenPin2, GreenDefaultLevel);
    analogWrite(BluePin2,  BlueDefaultLevel);
  } // if
}

// End.
