/*
 * O2Sensor.cpp
 * An OOP driver class for Grove - Gas Sensor(O2)
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

#include "O2Sensor.h"

driver::O2Sensor::O2Sensor(uint8_t pin, float vRef)
	:_pin(pin), _vRef(vRef), _concentration(0.0)
{
}

bool driver::O2Sensor::init(void)
{
	return true;
}

void driver::O2Sensor::measure(void)
{
	_concentration = readVout() * 0.21 / 2.0 * 100;
}

float driver::O2Sensor::getConcentration(void)
{
	return _concentration;
}

uint8_t driver::O2Sensor::getConcentrationByte(void)
{
	return (uint8_t)_concentration;
}

float driver::O2Sensor::readVout(void)
{
	long sum = 0;

	for (auto i = 0; i < 32; i++) {
		sum += analogRead(_pin);
	}

	sum >>= 5;

	return sum * (_vRef / 1023.0);
}
