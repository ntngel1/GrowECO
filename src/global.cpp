#include "global.hpp"

#define cast(var, type) dynamic_cast<type>(var)

using namespace Global;

void initNetwork(void);
void initServer(void);
void initHardware(void);
void initDebug(void);

void setup(void)
{
    initDebug();
    initNetwork();
    initServer();
    initHardware();
}









namespace Global {
    DHT _dht(HW_DHT11, DHT11);

    ADS1115Wrapper ads1115(HW_ADS1115_ADDR);

    DHTWrapper Air(
        new DHTStandartHumidityReader(&_dht),
        new DHTStandartTemperatureReader(&_dht)
    );

    DallasWrapper GroundTemperature(
        new DallasStandartReader(HW_DS18B20)
    );
    
    HygrometerWrapper GroundHumidity(new HygrometerStandartReader(HW_HUMIDITY));

    HygrometerWrapper WaterLevel;
}

void initNetwork(void) {
    NetworkController::connectWiFi();
}

void initServer(void) {
    ServerController::setHost(SERVER_ADDR);
    //ServerController::setToken(DataStore::read("token"));
    ServerController::setToken("7bce33dd350db18b2b5a4327345860b0");
}


void initHardware(void) {
    ads1115.attach(HW_WATER_LEVEL, cast(&WaterLevel, IAnalogSensor*));
}

void initDebug(void) {
    #ifdef DEBUG_ENABLED
        Serial.begin(9600);
    #endif
}