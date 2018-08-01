// Author: zxd    Date:2018/07/23
// �����ļ��������е�Դ������¶ȿ���
// 16V��ѹ���裺3K��12K       23V��ѹ���裺3K��18K


//�¿ط��ȵ��ԡ����װ���ע�͵���
//#define FAN_ON

#include "POWER_Ctrl.h"
#include "OneWire.h"			//1��ʽͨѶЭ�� ���ļ�
#include "DallasTemperature.h"	//DS18B20 ���ļ�

//��ѹϵ�������Ŵ���10��
#define Battery_coefficient 0.159864	//ADC�����������ϵ�����ǵ�ص�ѹ
#define Solar_coefficient   0.22559	//ADC�����������ϵ������̫���ܵ�ѹ

//���ȿ�ʼ�����¶Ⱥ͹�ǿ
#define Fan_start_temp 45
#define Fan_start_light 500


//��ѹ�����Ŵ�10��������126��ʾ12.6V
uint8_t Battery_voltage;
uint8_t Solar_voltage;

/****************** DS18B20��� ***************************/
#define Slower_Mode		//����ģʽ��ȡ�¶ȡ�ע�͵���Ϊ����ģʽ

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

bool power_ctrl_init()		//��ʼ���¶Ⱥ͵�ѹ��ȡ������1Ϊ����
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

int get_box_temperature()	//��ȡ�����ڲ��¶�
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

uint8_t get_voltage()	//���ص�ص�ѹֵ���ѷŴ�10��
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
 * bool power_ctrl()���Ʒ��Ⱥ;��ߴ�������Դ����
 * ����ֵ��1Ϊ����򿪴�������Դ��0Ϊ������
 * �����������
 ****************************************/
void Fan(bool Fan_state)	//1Ϊ������
{
	if (Fan_state) {
		digitalWrite(Fan_pin, 0);	//������
	}
	else {
		digitalWrite(Fan_pin, 1);
	}	
}

bool power_ctrl()	//1Ϊ����е磬0Ϊ���û��
{
	int box_temp = 0;		//�����¶�
	//int light = 0;			//����ǿ��
	bool power_state = 0;	//1Ϊ����е磬0Ϊ���û��
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


