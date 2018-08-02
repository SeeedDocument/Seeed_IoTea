
#include "CO2.h"
int CO2PPM;
int CO2_temp;
#define co2_delay 2500		//两次读取数据的间隔

#define CO2_serial Serial1
unsigned char data[9];
const unsigned char cmd_get_sensor[] =		//send data to CO2 Sensor
{
	0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
};

unsigned int get_co2();		//获取一次二氧化碳传感器的数据，返回0为数据错误

void CO2_init(void) {
	CO2_serial.begin(9600);
}

unsigned int CO2_dataRecieve(void)		//获取二氧化碳传感器的数据。返回0为错误
{
	int sum = 0;
	int x = 0;
	unsigned int CO2PPM;
	for (char i = 7; i>0; i--)			//上电后前7次数据不准确，需要丢弃
	{
		CO2PPM = get_co2();
		SerialUSB.print("1 = ");
		SerialUSB.println(CO2PPM);
		delay(co2_delay);
	}
	SerialUSB.println("preheat ok");	
	for (char i = 4; i>0; i--)			//从第八次数据开始做4次平均值
	{
		CO2PPM = get_co2();
		if (CO2PPM != 0)
		{
			sum = sum + CO2PPM;
			x++;
		}
		delay(co2_delay);
	}
	CO2PPM = sum / x;
	SerialUSB.print("finish CO2PPM = ");
	SerialUSB.println(CO2PPM);
	return CO2PPM;
}

unsigned int get_co2() {			//获取一次传感器数据。返回0为数据错误
	Feed_dog();		//喂狗，同时闪灯
	unsigned int CO2PPM;
	uint8_t i;
	for (i = 0; i<sizeof(cmd_get_sensor); i++)
	{
		CO2_serial.write(cmd_get_sensor[i]);
		//delayMicroseconds(100);
	}
	delay(100);
	if (CO2_serial.available())
	{
		while (CO2_serial.available())
		{
			for (i = 0; i<9; i++)
			{
				data[i] = CO2_serial.read();
			}
		}
	}
	
	for (int j = 0; j < sizeof(data); j++) {
		SerialUSB.print(data[j]);
		SerialUSB.print("  ");
	}
	SerialUSB.println("  ");
	

	if ((i != 9) || (1 + (0xFF ^ (byte)(data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]))) != data[8])
	{
		return 0;	//数据校验未通过
	}
	else
	{
		CO2PPM = (int)data[2] * 256 + (int)data[3];
		SerialUSB.print("CO2PPM = ");
		SerialUSB.println(CO2PPM);
		return CO2PPM;
	}
}




