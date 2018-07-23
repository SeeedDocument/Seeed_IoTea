// seeed_Lora.h

#ifndef _SEEED_LORA_h
#define _SEEED_LORA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern unsigned char Lora_data[15];
extern void Lora_begin(void);
extern void Lora_send(unsigned char length);
#endif

