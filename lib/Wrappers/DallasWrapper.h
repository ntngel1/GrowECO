#ifndef DALLASWRAPPER_H_
#define DALLASWRAPPER_H_

#include "OneWire.h"
#include "DallasTemperature.h"

#include "ISensorReader.h"
#include "ITemperatureSensor.h"

class DallasStandartReader : public ISensorReader {
    public:
        DallasStandartReader(uint8_t pin) {
            _oneWire = new OneWire(pin);
            _sensor = new DallasTemperature(_oneWire);
            _sensor -> begin();
        }
        
        DallasStandartReader(DallasTemperature* sensor) {
            _sensor = sensor;
            _sensor -> begin();
        }

        DallasStandartReader(OneWire* oneWire) {
            _oneWire = oneWire;
            _sensor = new DallasTemperature(_oneWire);
            _sensor -> begin();
        }
        
        float read(void) {
            _sensor -> requestTemperatures();
            return _sensor -> getTempCByIndex(0);
        }

    private:
        OneWire* _oneWire;
        DallasTemperature* _sensor;
};

class DallasWrapper : public ITemperatureSensor {
    public:
        DallasWrapper(ISensorReader* temperatureReader = NULL) {
            if (temperatureReader) {
                setTemperatureReader(temperatureReader);
            } else {
                setTemperatureReader(new NotRealizedReader());
            }
        }
};

#endif