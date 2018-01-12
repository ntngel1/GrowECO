#include "Arduino.h"
#include <global.hpp>
#include "NetworkController.h"
using namespace Global;

#define cast(var, type) dynamic_cast<type>(var)

void setup(void)
{
  pinMode(D6, OUTPUT);
  digitalWrite(D6, HIGH);
  delay(5000);
  Serial.begin(9600);

  ads1115.attach(0, cast(&waterLevel, IAnalogSensor*));
  ads1115.attach(1, cast(&gndHumidity, IAnalogSensor*));
  /*
  server.connectWiFi("100 rubley odin chas", "Marmaz111");
  switch (server.checkServer()) {
    case ServerController::SERVER_CONNECTED:
      Serial.println("Подключен к серверу!");
      break;
    case ServerController::BAD_AUTH_KEY:
      Serial.println("Неверный токен!");
      break;
    case ServerController::SERVER_ERROR:
      Serial.println("Непредвиденная ошибка сервера!");
      break;
  }
  */
  //NetworkController net;
  //net.connectWiFi();
}

void loop(void)
{
  /*
  ClimateData data;
  data.groundHumidity = cast(&gndHumidity, IAnalogSensor*) -> getValueInPercentages();
  data.groundTemperature = cast(&dallasSensor, ITemperatureSensor*) -> getTemperature();
  data.airTemperature = cast(&dhtSensor, ITemperatureSensor*) -> getTemperature();
  data.airHumidity = cast(&dhtSensor, IHumiditySensor*) -> getHumidity();
  data.water = waterLevel.read();

  server.updateParameters(&data);
  delay(1000);
  */
  debug_error("test");
  delay(1000);
}
