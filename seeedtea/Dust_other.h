// Dust_other.h

#ifndef _DUST_OTHER_h
#define _DUST_OTHER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
//extern const int Dust_pin;
#define Dust_pin 3
//#define O2_pin A1
extern float Dust_concentration(void);
extern int O2_value(void);


#endif

