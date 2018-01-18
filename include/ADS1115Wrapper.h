#ifndef ADS1115WRAPPER_H_
#define ADS1115WRAPPER_H_

#include "Adafruit_ADS1015.h"

#include "ISensorReader.h"
#include "IAnalogSensor.h"

class ADS1115Reader : public ISensorReader {
    public:
        ADS1115Reader(Adafruit_ADS1115* ads, uint8_t channel) {
            _ads = ads;
            _channel = channel;

            _ads -> begin();
        }
    
        float read(void) {
            uint16_t value = _ads -> readADC_SingleEnded(_channel);
            value = map(value, 0, maxValue, 0, 100);
            return (value > 100 ? 0 : value);
        }

    private:
        static const uint16_t maxValue = 16384;

        Adafruit_ADS1115* _ads;
        uint8_t _channel;
};

class ADS1115Wrapper {
    public:
        ADS1115Wrapper(uint8_t addr = ADS1015_ADDRESS) {
            _ads = new Adafruit_ADS1115(addr);
            _ads -> setGain(GAIN_ONE);
        }

        void attach(uint8_t channel, IAnalogSensor* sensor) {
            sensor -> setAnalogReader(new ADS1115Reader(_ads, channel));
        }

    private:
        Adafruit_ADS1115* _ads;
};

#endif