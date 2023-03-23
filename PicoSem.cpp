/*
  PicoSem.h
  Simple library to exchange data between core0 and core1
  of a Raspberry Pi Pico under Arduino IDE framework
  Created by Luigi Lavezzaro, 22 March 2023 
  Released into the public domain.
*/
#include "PicoSem.h"

PicoSem::PicoSem(bool f0, bool f1){
  _full0=f0;
  _full1=f1;
}

void PicoSem::setDataEmptyFor(uint8_t core){
  _core=core;
  if(_core==0) _full1=false;
  if(_core==1) _full0=false;
}

bool PicoSem::canISendTo(uint8_t core){
  _core=core;
  if (_core==0) return !_full1;
  if (_core==1) return !_full0;
  Serial.println("canISendTo() ERROR - program stopping...");
  for(;;){}                     // STOP program
}

void PicoSem::setDataReadyFor(uint8_t core){
  _core=core;
  if(_core==0) _full1=true;
  if(_core==1) _full0=true;
}

void PicoSem::setDataReadBy(uint8_t core){
  _core=core;
  if(_core==0) _full1=false;
  if(_core==1) _full0=false;
}

bool PicoSem::anyDataFor(uint8_t core){
  _core=core;
  if(_core==0) return _full1;
  if(_core==1) return _full0;
  Serial.println("anyDataFor() ERROR - program stopping...");
  for(;;){}                     // STOP program
}

