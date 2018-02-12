#ifndef GATEWAY_CONTROLLER_H_
#define GATEWAY_CONTROLLER_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ArduinoJson.h"

#include "hardware.h"

#include "ClimateData.h"

#define RECEIVE_DELAY 1200

class GatewayController {
    public:
        static void init(void);

        static void getSensors(ClimateData* data);
        static void updateSensors(ClimateData* data);
        static void test(void);

    private:
        GatewayController(void);
        
        static void send(String req);
        static String get(void);

        static void clearBuffer(void);

        static SoftwareSerial* gateway;
        static StaticJsonBuffer<256> jsonBuffer;
};

#endif