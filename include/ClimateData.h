/**
    GrowECO Project

    ClimateController.h
    Purpose: -

    @author Kirill Shepelev
    @version 1.0 28/09/2017
*/

#ifndef CLIMATE_DATA_H_
#define CLIMATE_DATA_H_

#include "Arduino.h"
#include "ArduinoJson.h"

struct ClimateData {
  uint8_t groundHumidity;
  uint8_t groundTemperature;
  uint8_t airHumidity;
  uint8_t airTemperature;
  uint8_t water;
  uint16_t pressure;

  String toJson(void) {
    StaticJsonBuffer<256> jsonBuffer; // буфер для парсинга JSON
    JsonObject& json = jsonBuffer.createObject();

    json["ground_humidity"] = this->groundHumidity;
    json["ground_temperature"] = this->groundTemperature;
    json["air_humidity"] = this->airHumidity;
    json["air_temperature"] = this->airTemperature;
    json["water"] = this->water;
    json["pressure"] = this->pressure;

    String jsonText;
    json.printTo(jsonText); // кодируем JSON в текст
    jsonBuffer.clear();

    return jsonText;
  }

};

#endif
