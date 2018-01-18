#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define SERVER_ADDR "http://groweco-dev.herokuapp.com"
#define AUTH_KEY "7bce33dd350db18b2b5a4327345860b0"

#include "Arduino.h"
#include "Wire.h"
#include "Hardware.h"

#include "groweco_debug.h"
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
#include "NetworkController.h"
#include "ClimateData.h"
//#include "ActionData.h"
#include "DataStore.h"

namespace Global {
  extern DHT _dht;

  extern ADS1115Wrapper ads1115;

  extern DHTWrapper Air;

  extern DallasWrapper GroundTemperature;
  
  extern HygrometerWrapper GroundHumidity;

  extern HygrometerWrapper WaterLevel;
}

#endif
