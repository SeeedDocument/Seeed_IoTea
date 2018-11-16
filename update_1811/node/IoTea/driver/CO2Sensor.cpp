/*
 * CO2Sensor.cpp
 * An OOP driver class for Grove - CO2 Sensor
 *
 * Copyright (c) 2018 seeed technology inc.
 * Author		: Lets Blu
 * Created Time	: Oct 2018
 * Modified Time:
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "CO2Sensor.h"

const uint8_t driver::CO2Sensor::COMMAND[] = {
	0xff, 0x01, 0x86, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x79
};

driver::CO2Sensor::CO2Sensor(uint8_t rxPin, uint8_t txPin)
	: _serial(SoftwareSerial(rxPin, txPin)), _concentration(0)
{
}

bool driver::CO2Sensor::init(void)
{
	_serial.begin(9600);
	while (!_serial);

	return true;
}

void driver::CO2Sensor::measure(void)
{
	int sum = 0;
	uint8_t readBuffer[] = {
		0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};

	// transmit command data
	for (auto i = 0; i < sizeof(COMMAND); i++) {
		_serial.write(COMMAND[i]);
	}

	delay(10);

	// begin reveiceing data
	while (_serial.available()) {
		sum = 0;
		for (auto i = 0; i < 9; i++) {
			readBuffer[i] = _serial.read();
			sum += (i >= 1 && i <= 7) ? readBuffer[i] : 0;
		}
	}

	if ((1 + (0xFF ^ (uint8_t)sum)) != readBuffer[8]) {
		_concentration = 0;
	}
	else {
		_concentration = (readBuffer[2] << 8) | readBuffer[3];
	}
}

uint16_t driver::CO2Sensor::getConcentration(void)
{
	return _concentration;
}

uint8_t driver::CO2Sensor::getConcentrationHighByte(void)
{
	return (uint8_t)(_concentration >> 8);
}

uint8_t driver::CO2Sensor::getConcentrationLowByte(void)
{
	return (uint8_t)_concentration;
}
