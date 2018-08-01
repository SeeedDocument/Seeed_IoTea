/*
 Name:		Auto_Reset.ino
 Created:	2018/4/22 13:34:54
 Author:	zxd
*/

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(13, INPUT);
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);		//�͵�ƽ��λ
	Serial.begin(9600);
}

int IN(void) {
	return digitalRead(13);
}

// the loop function runs over and over again until power down or reset
unsigned long old_time = 0;
const int RESET_TIME = 30000;		//15������Ӧ������
void loop() {
	if (IN() == 1)
	{
		old_time = millis();
		Serial.println("1");
		while (IN() == 1)
		{
			if (millis() - old_time > RESET_TIME)	//�����ʱ�͸�λ
			{
				digitalWrite(7, LOW);
				delay(200);
				digitalWrite(7, HIGH);
				break;
			}
		}
	}
	else
	{
		old_time = millis();
		Serial.println("0");
		while (IN() == 0)
		{
			if (millis() - old_time > RESET_TIME)	//�����ʱ�͸�λ
			{
				digitalWrite(7, LOW);
				delay(200);
				digitalWrite(7, HIGH);
				break;
			}
		}
	}
}


