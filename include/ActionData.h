#ifndef ACTION_DATA_H_
#define ACTION_DATA_H_

#include "ArduinoJson.h"
#include <Arduino.h>

struct ActionData {
  uint8_t actionCode;

  ActionData(String& json) : actionCode(0) {
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json.c_str());
    if (!root.success()) {
      return;
    }
    uint8_t actionCode = root["action"]["action_code"].as<uint8_t>();
    jsonBuffer.clear();
    this->actionCode = actionCode;
  }
};

#endif
