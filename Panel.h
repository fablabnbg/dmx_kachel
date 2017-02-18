#ifndef Panel_h
#define Panel_h

#include <Arduino.h>
#include <DMXSerial.h>


class Panel {
  private:
    int startAddress;
    uint8_t density;
    uint8_t x,y,z;
    uint8_t colors[3] = {0,0,0};
    uint8_t strobe = false;
    uint8_t fade = 0;
    long lastmillisstrobe = 0;
    long lastmillisfade = 0;
    uint8_t strobeon;
    void setStrobe(uint8_t strobetimer);
    void setFade(uint8_t fadetimer);


  public:
    Panel(uint8_t setStartAddress);
    void updateDMX();
    uint8_t getRed();
    uint8_t getBlue();
    uint8_t getGreen();
    void fadeCalc();
    void strobeCalc();
};



#endif
