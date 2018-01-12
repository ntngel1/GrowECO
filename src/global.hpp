#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define SERVER_ADDR "http://groweco-dev.herokuapp.com"
#define AUTH_KEY "7bce33dd350db18b2b5a4327345860b0"

#include "Arduino.h"
#include "Wire.h"
#include "Hardware.h"

#include "DHT.h"

#include "ADS1115Wrapper.h"
#include "DallasWrapper.h"
#include "DHTWrapper.h"
#include "HygrometerWrapper.h"

#include "IAnalogSensor.h"
#include "ITemperatureSensor.h"
#include "IHumiditySensor.h"
#include "ISensorReader.h"

#include "ServerController.h"
#include "ClimateData.h"
#include "groweco_debug.h"

namespace Global {
  ServerController server(SERVER_ADDR, AUTH_KEY);

  DHT _dht(HARDWARE_AIR_SENSOR_PIN, DHT11);

  ADS1115Wrapper ads1115(0x49);

  DallasWrapper dallasSensor(
    new DallasStandartReader(HARDWARE_GROUND_TEMP_SENSOR_PIN));

    DHTWrapper dhtSensor(
    new DHTStandartHumidityReader(&_dht),
    new DHTStandartTemperatureReader(&_dht)
  );

  HygrometerWrapper waterLevel;
  HygrometerWrapper gndHumidity(new HygrometerStandartReader(HARDWARE_GROUND_HUMIDITY_SENSOR_PIN));
}

#endif
