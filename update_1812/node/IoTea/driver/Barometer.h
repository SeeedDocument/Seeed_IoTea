/*
 * Barometer.h
 * A repacking library for Grove - Barometer Sensor(BME280)
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

#ifndef __BAROMETER_H__
#define __BAROMETER_H__

#include "Arduino.h"

#include "interface\IGrove.h"
#include "..\origin_driver\Seeed_BME280.h"

namespace driver {
	class Barometer;
}

class driver::Barometer
	: public driver::interface::IGrove {
public:
	Barometer(uint8_t address = BME280_ADDRESS);

	bool init(void);
	void measure(void);

	float	 getTemperature(void);
	uint32_t getHumidity(void);
	float	 getAltitude(void);

	uint8_t	getTemperatureByte(void);
	uint8_t	getHumidityByte(void);
	uint8_t	getAltitudeHighByte(void);
	uint8_t	getAltitudeLowByte(void);

protected:
	BME280	_bme280;
	uint8_t	_address;

	float	 _temperature;
	uint32_t _humidity;
	float	 _altitude;
};

#endif // __BAROMETER_H__
