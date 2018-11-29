/*
 * CO2Sensor.h
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

#ifndef __CO2SENSOR_H__
#define __CO2SENSOR_H__

#include "Arduino.h"
#include "SoftwareSerial.h"

#include "interface\IGrove.h"

namespace driver {
	class CO2Sensor;
}

class driver::CO2Sensor
	: public driver::interface::IGrove {
public:
	CO2Sensor(uint8_t rxPin, uint8_t txPin);

	bool init(void);
	void measure(void);

	uint16_t getConcentration(void);

	uint8_t getConcentrationHighByte(void);
	uint8_t getConcentrationLowByte(void);

protected:
	SoftwareSerial	_serial;
	static const uint8_t COMMAND[];

	uint16_t _concentration;
};

#endif // __CO2SENSOR_H__
