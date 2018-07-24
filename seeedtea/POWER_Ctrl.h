// POWER_Ctrl.h

#ifndef _POWER_CTRL_h
#define _POWER_CTRL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DS18B20_pin 8
#define Solar_pin A2
#define Battery_pin A3
#define Fan_pin 9
void Fan(bool Fan_state);	//1为开风扇
bool power_ctrl_init();		//初始化温度和电压读取。返回1为正常
int get_box_temperature();	//返回盒子的温度
uint8_t get_voltage();		//返回电池电压值，已放大10倍
bool power_ctrl();			//1为电池有电，0为电池没电

#endif

