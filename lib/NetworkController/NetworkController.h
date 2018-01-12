#ifndef NETWORK_CONTROLLER_H_
#define NETWORK_CONTROLLER_H_

#include "groweco_debug.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"

#define DEFAULT_CONFIGURE_SSID "GrowECO_dev"

class NetworkController {
	public:
		NetworkController(void);
		~NetworkController(void);

		void connectWiFi(const char* defaultSSID = DEFAULT_CONFIGURE_SSID);
	private:
		WiFiManager wifiManager;
		WiFiManagerParameter *token;
};

#endif
