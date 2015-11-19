
#ifndef MARLIN_H
#define MARLIN_H

#if ARDUINO >= 100 
  #if defined(__AVR_ATmega644P__)
    #include "WProgram.h"
  #else
    #include "Arduino.h"
  #endif
#else
   #include "WProgram.h"
#endif

void manage_inactivity();
void calculate_delta(float cartesian[3]);
extern bool feedmultiplychanged;

#ifdef FWRETRACT
extern bool retracted;
#endif

#endif
