/*
 * Application.h
 * Main class of project IoTea
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

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Arduino.h"

#include "interface\IApplication.h"
#include "..\driver\Barometer.h"
#include "..\driver\CO2Sensor.h"
#include "..\driver\DustSensor.h"
#include "..\driver\LightSensor.h"
#include "..\driver\LoRaWan.h"
#include "..\driver\O2Sensor.h"
#include "..\driver\SoilSensor.h"
#include "..\middleware\Sensor.h"
#include "..\origin_driver\Adafruit_SleepyDog.h"
#include "..\origin_driver\Vector.h"
#include "..\middleware\interface\IGetValue.h"

namespace application {
	class Application;
}

class application::Application 
	: public application::interface::IApplication {
public:
	~Application(void);

	// implement interface IApplication
	void setup(void);
	void loop(void);

	uint8_t getErrorCode(void);

	// singleton pattern
	static application::Application * getInstance(void);

protected:
	// platform and groves
	driver::LoRaWan * _lora;
	Vector<driver::interface::IGrove *> _groves;

	// abstrict sensors
	uint8_t _errorCode;
	Vector<middleware::interface::IGetValue *> _sensors;
	
	// singleton pattern
	Application(void);
	static application::Application _instance;

	void initLoRa(void);
	void initSensors(void);
	void measureGroves(void);

	void addBarometer(void);
	void addCO2Sensor(void);
	void addDustSensor(void);
	void addLightSensor(void);
	void addO2Sensor(void);
	void addSoilSensor(void);
	void addVoltageSensor(void);
	void addErrorCodeSensor(void);
};

#endif // __APPLICATION_H__
