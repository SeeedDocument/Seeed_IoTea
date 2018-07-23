// 
// 
// 

#include "Dust_other.h"
//???Dust Sensor???
//const int Dust_pin = 8;		
#define sampletime_ms 30000		//sampe 30s&nbsp;;

float Dust_concentration(void) {
	unsigned long lowpulseoccupancy = 0;	//??????
	unsigned long duration;		//???????
	unsigned long Dust_starttime;	//??????
	float ratio = 0;			//??
	float concentration = 0;	//????
	Dust_starttime = millis();	//??????

	while ((millis() - Dust_starttime) < sampletime_ms)
	{
		duration = pulseIn(Dust_pin, LOW);	//??10?
		lowpulseoccupancy = lowpulseoccupancy + duration;
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

//int O2_value(void) {
//	long sum = 0;
//	int out_val = 0;
//	double voltage = 2.58*0.7429;	//????
//	for (int i = 0; i<32; i++)
//	{
//		sum += analogRead(O2_pin);
//	}
//	sum = sum / 32;
//	out_val = sum * 0.6768 / voltage;
//	return out_val;
//}




