#include <global.hpp>
using namespace Global;
#define cast(var, type) dynamic_cast<type>(var)

void uploadSensorsData(void);
void handleActions(void);

void loop(void)
{
  uploadSensorsData();
  delay(1000);
}

void uploadSensorsData(void) {
  ClimateData data;
  data.groundHumidity = cast(&GroundHumidity, IAnalogSensor*) -> getValueInPercentages();
  data.groundTemperature = cast(&GroundTemperature, ITemperatureSensor*) -> getTemperature();
  data.airTemperature = cast(&Air, ITemperatureSensor*) -> getTemperature();
  data.airHumidity = cast(&Air, IHumiditySensor*) -> getHumidity();
  data.water = WaterLevel.read();

  debug_message("gndhum: ");
  Serial.println(data.groundHumidity);

  debug_message("gndtemp: ");
  Serial.println(data.groundTemperature);

  debug_message("airtemp: ");
  Serial.println(data.airTemperature);

  debug_message("airHum: ");
  Serial.println(data.airHumidity);

  debug_message("water: ");
  Serial.println(data.water);

  ServerController::updateSensors(&data);
}