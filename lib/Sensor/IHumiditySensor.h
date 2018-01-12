#ifndef IHUMIDITY_SENSOR_H_
#define IHUMIDITY_SENSOR_H_

#include "ISensor.h"
#include "ISensorReader.h"

class IHumiditySensor : public ISensor {
    public:
        float getHumidity(void) {
            return read();
        }

        void setHumidityReader(ISensorReader* reader) {
            this -> _reader = reader;
        }

        ISensorReader* getHumidityReader(void) {
            return getReader();
        }
};

#endif