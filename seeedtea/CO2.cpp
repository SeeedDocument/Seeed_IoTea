
#include "CO2.h"
#include <SoftwareSerial.h>
int CO2PPM;
int CO2_temp;

SoftwareSerial CO2_serial(4, 5);      // TX, RX

const unsigned char cmd_get_sensor[] =		//send data to CO2 Sensor
{
	0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
};

void CO2_init(void) {
	CO2_serial.begin(9600);
}

bool CO2_dataRecieve(void)
{
    byte data[20];
    int i = 0;
	int flag = 0;
	memset(data, 0, sizeof(data));
    //transmit command data
    for(i=0; i<sizeof(cmd_get_sensor); i++)
    {
        CO2_serial.write(cmd_get_sensor[i]);
    }
    delay(10);
    //begin reveiceing data
    if(CO2_serial.available())
    {
        while(CO2_serial.available())
        {
            for(i=0;i<sizeof(data); i++)
            {
                data[i] = CO2_serial.read();
				if (i >= 4) 
				{
					if (data[i - 4] == 255) 
					{
						if (data[i - 3] == 134 && flag == 0) {
							CO2PPM = (int)data[i-2] * 256 + (int)data[i-1];
							CO2_temp = (int)data[i] - 40;
							i = sizeof(data) - 5;
							flag = 1;
						}
					}
				}
            }
        }
    }
	/*for (int j = 0;j < sizeof(data);j++) {
		SerialUSB.print(data[j]);
		SerialUSB.print("  ");
	}
	SerialUSB.println(CO2PPM);*/
	return flag;
    
}




