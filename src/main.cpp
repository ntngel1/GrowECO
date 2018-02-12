#include <global.hpp>
using namespace Global;
#define cast(var, type) dynamic_cast<type>(var)
#include "groweco_debug.h"

void uploadSensorsData(void);
void handleActions(void);

void loop(void)
{
  uploadSensorsData();
  ServerController::getSettings();
  wateringController.process();
  handleActions();
  debug_message(" ");
}

void uploadSensorsData(void) {
  ClimateData data;
  data.groundHumidity = cast(&GroundHumidity, IAnalogSensor*) -> getValueInPercentages();
  data.airTemperature = cast(&Air, ITemperatureSensor*) -> getTemperature();
  data.airHumidity = cast(&Air, IHumiditySensor*) -> getHumidity();
  data.water = WaterLevel.read();

  GatewayController::getSensors(&data);
  ServerController::updateSensors(&data);
/*
  Serial.print("Water: ");
  Serial.println(data.water);

  Serial.print("Ground Humidity: ");
  Serial.println(data.groundHumidity);

  Serial.print("Ground Temperature: ");
  Serial.println(data.groundTemperature);

  Serial.print("Air Humidity: ");
  Serial.println(data.airHumidity);

  Serial.print("Air Temperature: ");
  Serial.println(data.airTemperature);

  Serial.print("Pressure: ");
  Serial.println(data.pressure);
  */
}

void handleActions(void) {
  ActionData d = ServerController::getAction();
  ActionHandler::handleAction(d);
}