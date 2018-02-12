#ifndef WATERING_CONTROLLER_H_
#define WATERING_CONTROLLER_H_

#include <Arduino.h>
#include "HygrometerWrapper.h"
#include "ServerController.h"
#include "groweco_debug.h"
#include <Ticker.h>

class WateringController {
    public:

        WateringController(uint8_t pin, HygrometerWrapper* hygrometer) : _pin(pin), _hyg(hygrometer) {
        }
        
        void init(void) {
            _disable_watering();
        }

        void water(void);
        void process(void);

    private:
        void _enable_watering(void);
        void _disable_watering(void);
        uint8_t _pin;
        HygrometerWrapper* _hyg;
        Ticker _ticker;
};

#endif