/*
 * LightSensor.h
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

#ifndef __LIGHTSENSOR_H__
#define __LIGHTSENSOR_H__

#include "limits.h"

#include "interface\IGrove.h"
#include "..\origin_driver\Digital_Light_TSL2561.h"

namespace driver {
	class LightSensor;
}

class driver::LightSensor
	: public driver::interface::IGrove {
public:
	LightSensor(uint8_t address = TSL2561_Address);

	bool init(void);
	void measure(void);

	unsigned long getVisibleLux(void);
	uint8_t		  getVisibleLuxHigh(void);
	uint8_t		  getVisibleLuxLow(void);

protected:
	uint8_t				 _address;
	TSL2561_CalculateLux _tsl2561;

	unsigned long _visibleLux;
};

#endif // __LIGHTSENSOR_H__
