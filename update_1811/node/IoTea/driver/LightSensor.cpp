/*
 * LightSensor.cpp
 * A repacking library for Grove - Digital Light Sensor
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

#include "LightSensor.h"

driver::LightSensor::LightSensor(uint8_t address)
	: _address(address), _visibleLux(0)
{
}

bool driver::LightSensor::init(void)
{
	_tsl2561.init();

	return true;
}

void driver::LightSensor::measure(void)
{
	_visibleLux = _tsl2561.readVisibleLux();
}

unsigned long driver::LightSensor::getVisibleLux(void)
{
	return _visibleLux;
}

uint8_t driver::LightSensor::getVisibleLuxHigh(void)
{
	return (uint8_t)((uint16_t)_visibleLux >> 8);
}

uint8_t driver::LightSensor::getVisibleLuxLow(void)
{
	return (uint8_t)_visibleLux;
}
