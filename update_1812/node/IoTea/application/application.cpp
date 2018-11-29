/*
 * Application.cpp
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

#include "application.h"

using namespace driver;
using namespace driver::interface;
using namespace middleware;
using namespace middleware::interface;
using namespace application;
using namespace application::interface;

Application Application::_instance;

application::Application::~Application(void)
{
	for (auto i = 0; i < _sensors.size(); i++) {
		delete _sensors[i];
		_sensors[i] = nullptr;
	}

	for (auto i = 0; i < _groves.size(); i++) {
		delete _groves[i];
		_groves[i] = nullptr;
	}
}

void application::Application::setup(void)
{
	Watchdog.enable(16000);
	SerialUSB.println("WATCHDOG ENABLE");

	initLoRa();
	initSensors();
}

void application::Application::loop(void)
{
	uint8_t message[15] = { 0 };
	
	measureGroves();
	SerialUSB.print("MESSAGE: ");

	for (size_t i = 0; i < _sensors.size(); i++) {
		message[i] = _sensors[i]->getValue();
		
		SerialUSB.print(message[i]);
		SerialUSB.print(" ");
	}

	_errorCode = 0;
	Watchdog.reset();
	SerialUSB.println("\r\nWATCHDOG RESET");

	_lora->transferPacket(message, sizeof(message));
}

uint8_t application::Application::getErrorCode(void)
{
	return _errorCode;
}

application::Application * application::Application::getInstance(void)
{
	return &_instance;
}

application::Application::Application(void)
	: _lora(LoRaWan::getInstance()), _errorCode(0)
{
}

void application::Application::initLoRa(void)
{
	_lora->init();

	// memset(buffer, 0, 256);
	// _lora->getVersion(buffer, 256, 1);
	// SerialUSB.print(buffer);

	// memset(buffer, 0, 256);
	// _lora->getId(buffer, 256, 1);
	// SerialUSB.print(buffer);

	_lora->setKey("2B7E151628AED2A6ABF7158809CF4F3C", 
		"2B7E151628AED2A6ABF7158809CF4F3C", "2B7E151628AED2A6ABF7158809CF4F3C");

	_lora->setDeciveMode(LWABP);
	_lora->setDataRate(DR0, EU868);

	_lora->setChannel(0, 868.1);
	_lora->setChannel(1, 868.3);
	_lora->setChannel(2, 868.5);

	_lora->setReceiceWindowFirst(0);
	_lora->setReceiceWindowSecond(869.5, DR3);

	_lora->setPower(20);
}

void application::Application::initSensors(void)
{
	addBarometer();
	addCO2Sensor();
	addDustSensor();
	addLightSensor();
	addO2Sensor();
	addSoilSensor();
	//addVoltageSensor();
	addErrorCodeSensor();

	for (auto i = 0; i < _groves.size(); i++) {
		_errorCode |= _groves[i]->init() ? 0x00 : (0x01 << i);
	}
}

void application::Application::measureGroves(void)
{
	for (auto i = 0; i < _groves.size(); i++) {
		_groves[i]->measure();
	}
}

void application::Application::addBarometer(void)
{
	Barometer * barometer = new Barometer(0x76);

	_groves.push_back(barometer);

	_sensors.push_back(new Sensor<Barometer>(barometer, &Barometer::getTemperatureByte));
	_sensors.push_back(new Sensor<Barometer>(barometer, &Barometer::getHumidityByte));
	_sensors.push_back(new Sensor<Barometer>(barometer, &Barometer::getAltitudeHighByte));
	_sensors.push_back(new Sensor<Barometer>(barometer, &Barometer::getAltitudeLowByte));
}

void application::Application::addCO2Sensor(void)
{
	CO2Sensor * co2Sensor = new CO2Sensor(4, 5);

	_groves.push_back(co2Sensor);

	_sensors.push_back(new Sensor<CO2Sensor>(co2Sensor, &CO2Sensor::getConcentrationHighByte));
	_sensors.push_back(new Sensor<CO2Sensor>(co2Sensor, &CO2Sensor::getConcentrationLowByte));
}

void application::Application::addDustSensor(void)
{
	DustSensor * dustSensor = new DustSensor(3);

	_groves.push_back(dustSensor);

	_sensors.push_back(new Sensor<DustSensor>(dustSensor, &DustSensor::getConcentrationHighByte));
	_sensors.push_back(new Sensor<DustSensor>(dustSensor, &DustSensor::getConcentrationLowByte));
}

void application::Application::addLightSensor(void)
{
	LightSensor * lightSensor = new LightSensor(0x29);

	_groves.push_back(lightSensor);

	_sensors.push_back(new Sensor<LightSensor>(lightSensor, &LightSensor::getVisibleLuxHigh));
	_sensors.push_back(new Sensor<LightSensor>(lightSensor, &LightSensor::getVisibleLuxLow));
}

void application::Application::addO2Sensor(void)
{
	O2Sensor * o2Sensor = new O2Sensor(A1);

	_groves.push_back(o2Sensor);

	_sensors.push_back(new Sensor<O2Sensor>(o2Sensor, &O2Sensor::getConcentrationByte));
}

void application::Application::addSoilSensor(void)
{
	SoilSensor * soilSensor = new SoilSensor(7, 6);

	_groves.push_back(soilSensor);

	_sensors.push_back(new Sensor<SoilSensor>(soilSensor, &SoilSensor::getTemperatureByte));
	_sensors.push_back(new Sensor<SoilSensor>(soilSensor, &SoilSensor::getHumidityByte));
}

void application::Application::addVoltageSensor(void)
{
	_sensors.push_back(new Sensor<LoRaWan>(_lora, &LoRaWan::getBatteryVoltage));
}

void application::Application::addErrorCodeSensor(void)
{
	_sensors.push_back(new Sensor<Application>(this, &Application::getErrorCode));
}
