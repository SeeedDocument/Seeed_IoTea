/*
 * Barometer.cpp
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

#include "Barometer.h"

driver::Barometer::Barometer(uint8_t address)
	: _address(address), _temperature(0), _humidity(0), _altitude(0)
{
}

bool driver::Barometer::init(void)
{
	return _bme280.init(_address);
}

void driver::Barometer::measure(void)
{
	_temperature = _bme280.getTemperature();
	_humidity = _bme280.getHumidity();
	_altitude = _bme280.calcAltitude(_bme280.getPressure());
}

float driver::Barometer::getTemperature(void)
{
	return _temperature;
}

uint32_t driver::Barometer::getHumidity(void)
{
	return _humidity;
}

float driver::Barometer::getAltitude(void)
{
	return _altitude;
}

uint8_t driver::Barometer::getTemperatureByte(void)
{
	return (uint8_t)_temperature;
}

uint8_t driver::Barometer::getHumidityByte(void)
{
	return (uint8_t)_humidity;
}

uint8_t driver::Barometer::getAltitudeHighByte(void)
{
	return (uint8_t)((uint16_t)_altitude >> 8);
}

uint8_t driver::Barometer::getAltitudeLowByte(void)
{
	return (uint8_t)_altitude;
}
