#include "NetworkController.h"

NetworkController::NetworkController() {
	token = new WiFiManagerParameter("Token", "Type here your device token", "", 33);
}

NetworkController::~NetworkController() {
	delete token;
}

void NetworkController::connectWiFi(const char* defaultSSID) {
	manager.addParameter(*token);

	manager.setSaveConfigCallback(__network_controller_save_config_callback__);

	manager.autoConnect(defaultSSID);
}


/* 
	Declaring it separately from class instead of declaring in the private methods of class
	because WiFiManager by tzapu throwing compilation error (callback should be in global namespace)
	See code of setSaveConfigCallback WiFiManager method below:

										      / there is little problem
	void WiFiManager::setAPCallback( void (*func)(WiFiManager* myWiFiManager) ) {
  		_apcallback = func;
	}
*/
void __network_controller_save_config_callback__() {
	debug_message("Save config callback is called");
	const char* value = token->getValue();
	debug_message(value);
}
