#include "ActionHandlers.h"
#include <Arduino.h>
#include "global.hpp"
#include "WateringController.h"

extern WateringController Global::wateringController;

void ActionHandlers::__none_handler__(void) {
}

void ActionHandlers::__watering_handler__(void) {
    Global::wateringController.water();
}