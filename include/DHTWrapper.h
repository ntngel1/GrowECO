#ifndef DHTWRAPPER_H_
#define DHTWRAPPER_H_

#include "ISensorReader.h"
#include "IHumiditySensor.h"
#include "ITemperatureSensor.h"

#include "DHT.h"

class DHTStandartHumidityReader : public ISensorReader {
    public:
        DHTStandartHumidityReader(DHT* dht) {
            _dht = dht;
            _dht -> begin();
        }

        float read(void) {
            return _dht -> readHumidity();
        }

    private:
        DHT* _dht;
};

class DHTStandartTemperatureReader : public ISensorReader {
    public:
        DHTStandartTemperatureReader(DHT* dht) {
            _dht = dht;
            _dht -> begin();
        }

        float read(void) {
            return _dht -> readTemperature();
        }
    
    private:
        DHT* _dht;
};

class DHTWrapper : public IHumiditySensor, public ITemperatureSensor {
    public:
        DHTWrapper(ISensorReader* humidityReader    = NULL,
                   ISensorReader* temperatureReader = NULL) 
        {
            if (humidityReader) {
                setHumidityReader(humidityReader);
            } else {
                setHumidityReader(new NotRealizedReader());
            }

            if (temperatureReader) {
                setTemperatureReader(temperatureReader);
            } else {
                setTemperatureReader(new NotRealizedReader());
            }
        }
};

#endif