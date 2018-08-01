// Author: zxd    Date:2018/07/23
// 本库文件用来进行电源管理和温度控制
// 16V分压电阻：3K和12K       23V分压电阻：3K和18K


//温控风扇调试。如果装箱就注释掉。
//#define FAN_ON

#include "POWER_Ctrl.h"
#include "OneWire.h"			//1线式通讯协议 库文件
#include "DallasTemperature.h"	//DS18B20 库文件

//电压系数，被放大了10倍
#define Battery_coefficient 0.159864	//ADC读数乘以这个系数就是电池电压
#define Solar_coefficient   0.22559	//ADC读数乘以这个系数就是太阳能电压

//风扇开始运行温度和光强
#define Fan_start_temp 45
#define Fan_start_light 500


//电压都被放大10倍，例如126表示12.6V
uint8_t Battery_voltage;
uint8_t Solar_voltage;

/****************** DS18B20相关 ***************************/
#define Slower_Mode		//慢速模式获取温度。注释掉即为快速模式

OneWire oneWire(DS18B20_pin);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

void printAddress(DeviceAddress deviceAddress)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (deviceAddress[i] < 16) SerialUSB.print("0");
		SerialUSB.print(deviceAddress[i], HEX);
	}
}

/*****************************************************/

bool power_ctrl_init()		//初始化温度和电压读取。返回1为正常
{
	pinMode(Solar_pin, INPUT);
	pinMode(Battery_pin, INPUT);
	pinMode(Fan_pin, OUTPUT);
	Fan(1);
	SerialUSB.print("Locating devices...");
	sensors.begin();
	SerialUSB.print("Found ");
	SerialUSB.print(sensors.getDeviceCount(), DEC);
	SerialUSB.println(" devices.");
	delay(1000);
	Fan(0);
	if (!sensors.getAddress(insideThermometer, 0))
	{
		SerialUSB.println("Unable to find address for Device 0");
		return 0;
	}
	else
		return 1;
}

int get_box_temperature()	//获取盒子内部温度
{
	int box_temp;
	sensors.requestTemperatures();
#ifdef Slower_Mode
	// method 1 - slower
	box_temp = sensors.getTempC(insideThermometer);
	
#else
	// method 2 - faster
	float tempC = sensors.getTempC(insideThermometer);
#endif

	if (box_temp > -50 && box_temp < 100)
	{
		SerialUSB.print("temp = ");
		SerialUSB.println(box_temp);
		return box_temp;
	}
	else
		return 0xffff;
}

uint8_t get_voltage()	//返回电池电压值，已放大10倍
{
	uint16_t B_vol = 0;
	uint16_t S_vol = 0;
	for (uint8_t i = 16; i > 0; i--)
	{
		B_vol = B_vol + analogRead(Battery_pin);
		S_vol = S_vol + analogRead(Solar_pin);
		delay(20);
	}
	//SerialUSB.print("analogRead = ");
	//SerialUSB.println(analogRead(Battery_pin));
	if (B_vol < 16384) {		//16384 = 1024 * 16
		Battery_voltage = (B_vol >> 4) * Battery_coefficient;
	}
	else
	{
		Battery_voltage = 255;
	}
	
	if (S_vol < 16384)
	{
		Solar_voltage = (S_vol >> 4) * Solar_coefficient;
	}
	else
	{
		Solar_voltage = 255;
	}
	SerialUSB.print("battery = ");
	SerialUSB.println(Battery_voltage);
	return Battery_voltage;
}


/*************************************** 
 * bool power_ctrl()控制风扇和决策传感器电源开关
 * 返回值：1为允许打开传感器电源。0为不允许。
 * 输入参数：无
 ****************************************/
void Fan(bool Fan_state)	//1为开风扇
{
	if (Fan_state) {
		digitalWrite(Fan_pin, 0);	//开风扇
	}
	else {
		digitalWrite(Fan_pin, 1);
	}	
}

bool power_ctrl()	//1为电池有电，0为电池没电
{
	int box_temp = 0;		//箱子温度
	//int light = 0;			//光线强度
	bool power_state = 0;	//1为电池有电，0为电池没电
	if (box_temp == 0xff)
		box_temp = 0;
	get_voltage();
	Fan(0);
#ifdef FAN_ON
	Battery_voltage = 127;
#endif // FAN_ON
	if (255 != Battery_voltage)
	{
		if (115 < Battery_voltage)
		{
			power_state = 1;
			if (TSL2561_data >= Fan_start_light)
			{
				if (box_temp >= Fan_start_temp)
				{
					Fan(1);
				}
			}
		}
		else
		{
			power_state = 0;
		}
	}
	else
	{
		power_state = 0;
	}
	return power_state;
}


