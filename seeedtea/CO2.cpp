
#include "CO2.h"
int CO2PPM;
int CO2_temp;
#define co2_delay 2500		//���ζ�ȡ���ݵļ��

#define CO2_serial Serial1
unsigned char data[9];
const unsigned char cmd_get_sensor[] =		//send data to CO2 Sensor
{
	0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
};

unsigned int get_co2();		//��ȡһ�ζ�����̼�����������ݣ�����0Ϊ���ݴ���

void CO2_init(void) {
	CO2_serial.begin(9600);
}

unsigned int CO2_dataRecieve(void)		//��ȡ������̼�����������ݡ�����0Ϊ����
{
	int sum = 0;
	int x = 0;
	unsigned int CO2PPM;
	for (char i = 7; i>0; i--)			//�ϵ��ǰ7�����ݲ�׼ȷ����Ҫ����
	{
		CO2PPM = get_co2();
		SerialUSB.print("1 = ");
		SerialUSB.println(CO2PPM);
		delay(co2_delay);
	}
	SerialUSB.println("preheat ok");	
	for (char i = 4; i>0; i--)			//�ӵڰ˴����ݿ�ʼ��4��ƽ��ֵ
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

unsigned int get_co2() {			//��ȡһ�δ��������ݡ�����0Ϊ���ݴ���
	Feed_dog();		//ι����ͬʱ����
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
		return 0;	//����У��δͨ��
	}
	else
	{
		CO2PPM = (int)data[2] * 256 + (int)data[3];
		SerialUSB.print("CO2PPM = ");
		SerialUSB.println(CO2PPM);
		return CO2PPM;
	}
}




