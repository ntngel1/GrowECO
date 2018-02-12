#include "GatewayController.h"

SoftwareSerial* GatewayController::gateway;
StaticJsonBuffer<256> GatewayController::jsonBuffer;

GatewayController::GatewayController(void) {}

void GatewayController::init(void) {
    gateway = new SoftwareSerial(HW_GATEWAY_RX, HW_GATEWAY_TX, false, 256);
    gateway->begin(9600);
}

void GatewayController::getSensors(ClimateData* data) {
    JsonObject& json = jsonBuffer.createObject();
    json["action"] = 2;
    clearBuffer();

    String r;
    json.printTo(r);

    gateway->println(r);
    jsonBuffer.clear();

    r = get();
    JsonObject& obj = jsonBuffer.parseObject(r);

    if (!obj.success()) {
        jsonBuffer.clear();
        return;
    }

    data->groundTemperature = obj["gnd_temp"].as<uint8_t>();
    data->pressure = obj["pres"].as<uint16_t>();
    jsonBuffer.clear();
}

void GatewayController::updateSensors(ClimateData* data) {
    JsonObject& json = jsonBuffer.createObject();
    json["gnd_hum"] = data->groundHumidity;
    json["air_hum"] = data->airHumidity;
    json["air_temp"] = data->airTemperature;
    json["water"] = data->water;
    json["action"] = 1;

    String r;
    json.printTo(r);
    jsonBuffer.clear();
    send(r);
}

void GatewayController::send(String req) {
    gateway->println(req);
}

String GatewayController::get(void) {
    String r;

    long long t = millis() + RECEIVE_DELAY;

    bool available = false;
    while (millis() < t)
        if (gateway->available() > 0) {
            available = true;
        }

    if (!available)
        return "";

    while (gateway->available() > 0) {
        char c = gateway->read();
        if (c == '\n')
            return r;
        else
            r.concat(c);
    }
}

void GatewayController::clearBuffer(void) {
    while (gateway->available())
        gateway->read();
}

void GatewayController::test(void) {
    while (gateway->available() > 0)
        Serial.write(gateway->read());
    while (Serial.available() > 0)
        gateway->write(Serial.read());
}