#ifndef IANALOG_SENSOR_H_
#define IANALOG_SENSOR_H_

#include "ISensor.h"
#include "ISensorReader.h"

class IAnalogSensor : public ISensor {
    public:
        float getValueInPercentages(void) {
            return read();
        }

        void setAnalogReader(ISensorReader* reader) {
            this -> _reader = reader;
        }

        ISensorReader* getHumidityReader(void) {
            return getReader();
        }
};

#endif