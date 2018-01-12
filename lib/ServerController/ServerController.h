/**
    GrowECO Project

    ServerController.h
    Purpose: Library for controlling server (data exchange and etc)

    @author Kirill Shepelev
    @version 1.0 28/09/2017
*/

#ifndef SERVER_CONTROLLER_H_
#define SERVER_CONTROLLER_H_

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "ArduinoJson.h"
#include "ClimateData.h"

typedef uint16_t HTTPStatusCode;

class ServerController {
    public:
        // Enumeration with statuses of connection
        enum ConnectionStatus {
            NONE,
            CONNECTED_WIFI,
            WIFI_ERROR,
            BAD_AUTH_KEY,
            SERVER_CONNECTED,
            SERVER_ERROR,
        };

        // Enumeration with codes of actions
        enum ActionCode {
          ACTION_NONE,
          PLANT_WATER,
          UPDATE_FIRMWARE,
          RESET_SETTINGS
        };

        /**
         * Server Controller Constructor
         * @param _host Host where server is located
         */
        ServerController(const char* _host) : _host(_host) {}

        /**
         * Server Controller Constructor
         * @param _host    Host where server is located
         * @param _authKey AuthKey for authorization
         */
        ServerController(const char* _host, const char* _authKey) :  _host(_host), _authKey(_authKey) {}

        /**
         * Connect to WiFi
         * @param  ssid     SSID of WiFi
         * @param  password Password of WiFi
         * @return          Status of Connection (CONNECTION_CONNECTED_WIFI or CONNECTION_WIFI_ERROR)
         */
        ConnectionStatus connectWiFi(const char* ssid, const char* password);

        /**
         * Check Server is available
         * @return  Status of Connection (CONNECTION_SERVER_CONNECTED, CONNECTION_BAD_AUTH_KEY or CONNECTION_SERVER_ERROR)
         */
        ConnectionStatus checkServer(void);

        /**
         * Init Server Controller
         * @return  Status of Connection (CONNECTION_SERVER_CONNECTED, CONNECTION_BAD_AUTH_KEY or CONNECTION_SERVER_ERROR)
         */
        inline ConnectionStatus init(void) {
          return checkServer();
        }

        /**
         * Set other AuthKey
         * @param  _authKey AuthKey
         * @return          Status of Connection (CONNECTION_SERVER_CONNECTED, CONNECTION_BAD_AUTH_KEY or CONNECTION_SERVER_ERROR)
         */
        inline ConnectionStatus setAuthKey(const char* _authKey) {
          this -> _authKey = _authKey;

          return checkServer();
        }

        /**
         * Update sensors data on the server
         * @param data Data of the sensors
         */
        void updateParameters(ClimateData *data);

        /**
         * Handle actions that proceeded from the server
         */
        void handleActions(void);

        void addHandler(uint8_t actionCode, std::function<void(void)>) {

        }

        HTTPStatusCode lastStatusCode = 0; // contains last HTTP status code

    private:
        const char* _authKey;
        const char* _host;
};

#endif
