#include "WateringController.h"
#define cast(var, type) dynamic_cast<type>(var)
extern void uploadSensorsData(void);

void __disable_watering__(uint8_t pin) {
    digitalWrite(pin, HIGH);
}

void WateringController::process(void) {
    if (ServerController::settings.autowatering_enabled && (cast(_hyg, IAnalogSensor*)->getValueInPercentages() < ServerController::settings.autowatering_threshold)) {
        water();
    }
}

void WateringController::water() {
    _enable_watering();
    _ticker.attach(1.5, __disable_watering__, _pin);
}

void WateringController::_enable_watering(void) {
    digitalWrite(_pin, LOW);
}

void WateringController::_disable_watering(void) {
    digitalWrite(_pin, HIGH);
}