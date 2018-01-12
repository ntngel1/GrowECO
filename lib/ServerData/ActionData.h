#ifndef ACTION_DATA_H_
#define ACTION_DATA_H_

#include <Arduino>
#include "ArduinoJson.h"

struct ActionData {
  uint8_t actionCode;

  ActionData(String json) : actionCode(0) {
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(json.c_str());
    if (!json.success()) {
      return;
    }
    uint8_t actionCode = json["action_code"].as<uint8_t>();
    this->actionCode = actionCode;
  }
};

#endif
