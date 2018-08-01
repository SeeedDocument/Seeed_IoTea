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
//��Դ�������ţ��Ϳ��߹�
#define Air_CtrlPin 10
#define Soil_CtrlPin 11
extern int TSL2561_data;	//�⴫��������
void Fan(bool Fan_state);	//1Ϊ������
bool power_ctrl_init();		//��ʼ���¶Ⱥ͵�ѹ��ȡ������1Ϊ����
int get_box_temperature();	//���غ��ӵ��¶�
uint8_t get_voltage();		//���ص�ص�ѹֵ���ѷŴ�10��
bool power_ctrl();			//1Ϊ����е磬0Ϊ���û��
int get_Light_data();		//��ȡ����ǿ�ȣ������жϷ��ȿ���

#endif

