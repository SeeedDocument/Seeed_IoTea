/*
 * Sensor.h
 * A abstract sensor class, used to provide unified sensor interface
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

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "Arduino.h"

#include "interface\IGetValue.h"

namespace middleware {
	template <typename T> class Sensor;
}

template <typename T>
class middleware::Sensor 
	: public middleware::interface::IGetValue {
public:
	Sensor(T * realSensor, uint8_t(T::*getValueMethod)(void));

	uint8_t getValue(void);

protected:
	T * _realSensor;
	uint8_t(T::*_getValueMethod)(void);
};

template<typename T>
inline middleware::Sensor<T>::Sensor(T * realSensor, uint8_t(T::* getValueMethod)(void))
	: _realSensor(realSensor), _getValueMethod(getValueMethod)
{
}

template<typename T>
inline uint8_t middleware::Sensor<T>::getValue(void)
{
	return (_realSensor->*_getValueMethod)();
}

#endif // __SENSOR_H__
