// 
// 
// 
#include<Arduino.h>
#include <LoRaWan.h>
#include "seeed_Lora.h"
char buffer[256];

void Lora_begin(void) {
	lora.init();
	memset(buffer, 0, 256);
	lora.getVersion(buffer, 256, 1);
	//SerialUSB.print(buffer);

	memset(buffer, 0, 256);
	lora.getId(buffer, 256, 1);
	//SerialUSB.print(buffer);

	lora.setKey("2B7E151628AED2A6ABF7158809CF4F3C", "2B7E151628AED2A6ABF7158809CF4F3C", "2B7E151628AED2A6ABF7158809CF4F3C");

	lora.setDeciveMode(LWABP);
	lora.setDataRate(DR0, EU868);

	lora.setChannel(0, 868.1);
	lora.setChannel(1, 868.3);
	lora.setChannel(2, 868.5);

	lora.setReceiceWindowFirst(0, 868.1);
	lora.setReceiceWindowSecond(869.5, DR3);

	lora.setDutyCycle(false);
	lora.setJoinDutyCycle(false);

	lora.setPower(14);
}

void Lora_send(unsigned char length){
	bool result = false;

	//result = lora.transferPacket("Hello World!", 10);
	result = lora.transferPacket(Lora_data, length, 10);

	if (result)
	{
		short length;
		short rssi;

		memset(buffer, 0, 256);
		length = lora.receivePacket(buffer, 256, &rssi);
		/*
		if (length)
		{
			SerialUSB.print("Length is: ");
			SerialUSB.println(length);
			SerialUSB.print("RSSI is: ");
			SerialUSB.println(rssi);
			SerialUSB.print("Data is: ");
			for (unsigned char i = 0; i < length; i++)
			{
				SerialUSB.print("0x");
				SerialUSB.print(buffer[i], HEX);
				SerialUSB.print(" ");
			}
			SerialUSB.println();
		}*/
	}
}


