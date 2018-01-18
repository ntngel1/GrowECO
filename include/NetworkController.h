#ifndef NETWORK_CONTROLLER_H_
#define NETWORK_CONTROLLER_H_

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include "WiFiManager.h"
#include "ServerController.h"
#include "DataStore.h"
#include "groweco_debug.h"

#define DEFAULT_CONFIGURE_SSID "GrowECO_dev"

class NetworkController {
	public:
		static void connectWiFi(const char* defaultSSID = DEFAULT_CONFIGURE_SSID);
		static WiFiManagerParameter *token;
	private:
		static WiFiManager manager;

		friend void __network_controller_save_config_callback__(void);

		NetworkController(void) {}
		~NetworkController(void) {}
};

void __network_controller_save_config_callback__(void);

#endif
