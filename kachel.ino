// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialRecv.ino: Sample DMX application for retrieving 3 DMX values:
// address 1 (red) -> PWM Port 9
// address 2 (green) -> PWM Port 6
// address 3 (blue) -> PWM Port 5
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// 28.12.2011 changed to channels 1..3 (RGB) for compatibility with the DmxSerialSend sample.
// 10.05.2012 added some lines to loop to show how to fall back to a default color when no data was received since some time.
// - - - - -

#include <DMXSerial.h>
#include "Panel.h"

// Constants for demo program

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
