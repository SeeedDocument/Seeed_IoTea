/*
 * SoilSensor.h
 * A repacking library for Soil Moisture & Temperature Sensor
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

#ifndef __SOILSENSOR_H__
#define __SOILSENSOR_H__

#include "Arduino.h"

#include "interface\IGrove.h"
#include "..\origin_driver\SHT1x.h"

namespace driver {
	class SoilSensor;
}

class driver::SoilSensor
	: public driver::interface::IGrove {
public:
	SoilSensor(uint8_t dataPin, uint8_t clockPin);

	bool init(void);
	void measure(void);

	float getTemperature(void);
	float getHumidity(void);

	uint8_t	getTemperatureByte(void);
	uint8_t	getHumidityByte(void);
protected:
	SHT1x _sht1x;

	float _temperature;
	float _humidity;
};

#endif // __SOILSENSOR_H__
