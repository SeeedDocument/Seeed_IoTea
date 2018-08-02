// 
// 
// 

#include "Dust_other.h"
//Dust Sensor
//const int Dust_pin = 8;		
#define sampletime_ms 30000		//采样时间30s;

float Dust_concentration(void) {
	unsigned long lowpulseoccupancy = 0;	
	unsigned long duration;		//
	unsigned long Dust_starttime;	//
	float ratio = 0;			//
	float concentration = 0;	//
	Dust_starttime = millis();	//

	while ((millis() - Dust_starttime) < sampletime_ms)
	{
		duration = pulseIn(Dust_pin, LOW);
		lowpulseoccupancy = lowpulseoccupancy + duration;
		Feed_dog();		//喂狗，同时闪灯
	}
	//SerialUSB.print("lowpulseoccupancy=");
	//SerialUSB.println(lowpulseoccupancy);
	if (lowpulseoccupancy != 0) {
		ratio = lowpulseoccupancy / (sampletime_ms*10.0);  // Integer percentage 0=>100
		concentration = 1.1*pow(ratio, 3) - 3.8*pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
		lowpulseoccupancy = 0;
		return concentration;
	}
	else
	{
		return 0;
	}
}
