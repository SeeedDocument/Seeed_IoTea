// CO2.h

#ifndef _CO2_h
#define _CO2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern int CO2PPM;
extern int CO2_temp;
extern void CO2_init(void);
extern bool CO2_dataRecieve(void);


#endif

