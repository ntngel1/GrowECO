#ifndef ITEMPERATURE_SENSOR_H_
#define ITEMPERATURE_SENSOR_H_

#include "ISensor.h"
#include "ISensorReader.h"

class ITemperatureSensor : public ISensor {
    public:
        float getTemperature(void) {
            return read();
        }

        void setTemperatureReader(ISensorReader* reader) {
            _reader = reader;
        }

        ISensorReader* getTemperatureReader(void) {
            return getReader();
        }
};

#endif