/*
  PicoSem.h
  Simple library to exchange data between core0 and core1
  of a Raspberry Pi Pico under Arduino IDE framework
  Created by Luigi Lavezzaro, 22 March 2023 
  Released into the public domain.
*/
#ifndef PicoSem_h
#define PicoSem_h
#include "Arduino.h"

class PicoSem {
  public:
    PicoSem(bool f0, bool f1);
    void setDataEmptyFor(uint8_t core);
    bool canISendTo(uint8_t core);
    void setDataReadyFor(uint8_t core);
    void setDataReadBy(uint8_t core);
    bool anyDataFor(uint8_t core);

  private:
    uint8_t _core;
    bool _full0;
    bool _full1;
};

#endif