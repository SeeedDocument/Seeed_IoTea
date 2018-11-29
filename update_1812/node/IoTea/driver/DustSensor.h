/*
 * DustSensor.h
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

#ifndef __DUSTSENSOR_H__
#define __DUSTSENSOR_H__

#include "Arduino.h"
#include "math.h"

#include "interface\IGrove.h"

namespace driver {
	class DustSensor;
}

class driver::DustSensor 
	: public driver::interface::IGrove {
public:
	DustSensor(uint8_t pin);

	bool init(void);
	void measure(void);

	float getConcentration(void);

	uint8_t getConcentrationHighByte(void);
	uint8_t getConcentrationLowByte(void);

protected:
	uint8_t		  _pin;
	unsigned long _startTime;
	unsigned long _occupancy;

	float _concentration;
};

#endif // __DUSTSENSOR_H__
