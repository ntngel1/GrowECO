#ifndef HYGROMETERWRAPPER_H_
#define HYGROMETERWRAPPER_H_

#include "ISensorReader.h"
#include "IAnalogSensor.h"

class HygrometerStandartReader : public ISensorReader {
    public:
        HygrometerStandartReader(uint8_t pin) {
            _pin = pin;
        }

        float read(void) {
            uint16_t value = analogRead(_pin);
            return 100 - map(value, 0, _maxValue, 0, 100);
        }

    private:
        static const uint16_t _maxValue = 1023;

        uint8_t _pin;
};

class HygrometerWrapper : public IAnalogSensor {
    public:
        HygrometerWrapper(ISensorReader* reader = NULL) {
            if (reader) {
                setAnalogReader(reader);
            } else {
                setAnalogReader(new NotRealizedReader());
            }
        }
};

#endif
