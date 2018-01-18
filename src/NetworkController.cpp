#include "NetworkController.h"

WiFiManager NetworkController::manager;
WiFiManagerParameter* NetworkController::token = new WiFiManagerParameter("token", "Type your device token here", "", 33);

void NetworkController::connectWiFi(const char* defaultSSID) {
	manager.addParameter(token);
	manager.setSaveConfigCallback(__network_controller_save_config_callback__);
	manager.autoConnect(defaultSSID);
}


/* 
	Declaring it separately from class instead of declaring in the private of class
	because WiFiManager by tzapu throwing compilation error (callback should be in global namespace)
	See code of setSaveConfigCallback WiFiManager method below:

										      / there is little problem
	void WiFiManager::setAPCallback( void (*func)(WiFiManager* myWiFiManager) ) {
  		_apcallback = func;
	}
*/
void __network_controller_save_config_callback__(void) {
	const char* value = (NetworkController::token)->getValue();
	DataStore::save("token", value);
}
