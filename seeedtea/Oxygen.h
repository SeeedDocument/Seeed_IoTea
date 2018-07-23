// Oxygen.h

#ifndef _OXYGEN_h
#define _OXYGEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define O2_pin A1
extern bool O2_init_flag;
int O2_value();		//获取O2数据


#endif

