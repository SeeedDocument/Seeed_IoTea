// POWER_Ctrl.h

#ifndef _POWER_CTRL_h
#define _POWER_CTRL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DS18B20_pin 8
#define Solar_pin A3
#define Battery_pin A2
#define Fan_pin 9
//电源控制引脚，低开高关
#define Air_CtrlPin 10
#define Soil_CtrlPin 11
extern int TSL2561_data;	//光传感器数据
void Fan(bool Fan_state);	//1为开风扇
bool power_ctrl_init();		//初始化温度和电压读取。返回1为正常
int get_box_temperature();	//返回盒子的温度
uint8_t get_voltage();		//返回电池电压值，已放大10倍
bool power_ctrl();			//1为电池有电，0为电池没电
int get_Light_data();		//获取光线强度，辅助判断风扇开关

#endif

