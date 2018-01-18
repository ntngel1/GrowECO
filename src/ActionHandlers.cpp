#include "ActionHandlers.h"
#include <Arduino.h>

void ActionHandlers::__watering_handler__(void) {
    Serial.println("Watering handler called");
}