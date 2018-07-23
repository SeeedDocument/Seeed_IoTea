#include "Oxygen.h"

#define O2_preheat_time	60000		//预热时间1分钟
bool O2_init_flag = 0;					//1为准备好了
float calibration_voltage;	//校准后的电压
#define O2_percentage 208.00


int O2_value()		//获取O2数据
{
	unsigned int sum = 0;
	if (O2_init_flag == 0)
	{
		O2_init_flag = 1;					//上电校正一次
		pinMode(O2_pin, INPUT);
		for (unsigned char i = 64;i > 0;i--)
		{
			sum = sum + analogRead(O2_pin);
			delay(100);
		}
		sum = sum >> 6;
		calibration_voltage = sum / O2_percentage;//获得校正系数
		//SerialUSB.println(calibration_voltage);
		return 208;						//校准成功
	}
	else
	{
		for (unsigned char i = 32;i > 0;i--)
		{
			sum = sum + analogRead(O2_pin);
			delay(50);
		}
		sum = sum >> 5;
		//SerialUSB.println(sum);
		sum = sum / calibration_voltage;
		//SerialUSB.println(sum);
		return sum;
	}
}

