/*
 * SoilSensor.cpp
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

#include "SoilSensor.h"

driver::SoilSensor::SoilSensor(uint8_t dataPin, uint8_t clockPin)
	: _sht1x(dataPin, clockPin), _temperature(0.0), _humidity(0.0)
{
}

bool driver::SoilSensor::init(void)
{
	return true;
}

void driver::SoilSensor::measure(void)
{
	_temperature = _sht1x.readTemperatureC();
	_humidity = _sht1x.readHumidity();
}

float driver::SoilSensor::getTemperature(void)
{
	return _temperature;
}

float driver::SoilSensor::getHumidity(void)
{
	return _humidity;
}

uint8_t driver::SoilSensor::getTemperatureByte(void)
{
	return (uint8_t)_temperature;
}

uint8_t driver::SoilSensor::getHumidityByte(void)
{
	return (uint8_t)_humidity;
}
