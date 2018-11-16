/*
 * DustSensor.cpp
 * An OOP driver class for Grove - Dust Sensor
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

#include "DustSensor.h"

driver::DustSensor::DustSensor(uint8_t pin)
	: _pin(pin), _startTime(0), _occupancy(0), _concentration(0.0)
{
}

bool driver::DustSensor::init(void)
{
	_startTime = millis();

	return true;
}

void driver::DustSensor::measure(void)
{
	float ratio = 0.0;

	_occupancy += pulseIn(_pin, LOW);

	ratio = _occupancy / ((millis() - _startTime) * 10.0);
	_concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
}

float driver::DustSensor::getConcentration(void)
{
	return _concentration;
}

uint8_t driver::DustSensor::getConcentrationHighByte(void)
{
	return (uint8_t)((uint16_t)_concentration >> 8);
}

uint8_t driver::DustSensor::getConcentrationLowByte(void)
{
	return (uint8_t)_concentration;
}
