#include "Panel.h"
#include <Arduino.h>

Panel::Panel(uint8_t setStartAddress)
{
  startAddress = setStartAddress;
}

void Panel::updateDMX() {
	density = DMXSerial.read(startAddress);
	setFade(DMXSerial.read(startAddress+4));
	setStrobe(DMXSerial.read(startAddress+5));  
  if(!fade) {
    colors[0] = DMXSerial.read(startAddress+1); 
    colors[1] = DMXSerial.read(startAddress+2);
    colors[2] = DMXSerial.read(startAddress+3);
  }
}

void Panel::fadeCalc() {
  if(fade && millis() - lastmillisfade > fade) {
    lastmillisfade = millis();
    int z = (y<=1) ? y + 1 : 0;
    colors[y] = 255-x;
    colors[z] = x;
    if(++x >= 255) {
      x = 0;
      if (++y >= 3) {
        y=0;
      }
    }
  }
}

void Panel::strobeCalc() {
  if(strobe && millis() - lastmillisstrobe > strobe) {
    lastmillisstrobe = millis();
    strobeon++;
    if(strobeon==5) {
      strobeon=0;
    }
  }
}


uint8_t Panel::getRed() {
  if(!strobe || !strobeon) {
	  return colors[0]*density/255;
  }
  else {
    return 0;
  }   
}
uint8_t Panel::getBlue() {
  if(!strobe || !strobeon) {
    return colors[1]*density/255;
  }
  else {
    return 0;
  }   
}
uint8_t Panel::getGreen() {
  if(!strobe || !strobeon) {
    return colors[2]*density/255;
  }
  else {
    return 0;
  }   
}


void Panel::setFade(uint8_t fadetimer) {
  if (fadetimer == 0)
  {
    fade = 0;
    return;
  }
  fade = 26-fadetimer/40;
}

void Panel::setStrobe(uint8_t strobetimer) {
  if (strobetimer == 0)
  {
    strobe = 0;
    return;
  }
  strobe = (260-strobetimer)/20;
}
