#include "groweco_debug.h"

char* __get_current_time__() {
	unsigned long time = millis() / 1000;

	unsigned long hours = time / 3600;
	time -= hours * 3600;

	unsigned long minutes = time / 60;
	time -= minutes * 60; 

	unsigned long seconds = time;

	char *tm = new char[16];
	sprintf(tm, "[%02d:%02d:%02d]", hours, minutes, seconds);

	return tm;
}

void debug_error(const char* err) {
	#ifdef DEBUG_ENABLED
		Serial.print(__get_current_time__());
		Serial.print(" DEBUG ERROR: ");
		Serial.println(err);
	#endif
}

void debug_message(const char* msg) {
	#ifdef DEBUG_ENABLED
		Serial.print(__get_current_time__());
		Serial.print(" DEBUG MESSAGE: ");
		Serial.println(msg);
	#endif
}