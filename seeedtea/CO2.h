// CO2.h

#ifndef _CO2_h
#define _CO2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern void CO2_init(void);
extern unsigned int CO2_dataRecieve(void);
extern void Feed_dog(void);		//Œππ∑£¨Õ¨ ±…¡µ∆

#endif

