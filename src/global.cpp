#include "global.hpp"

#define cast(var, type) dynamic_cast<type>(var)

using namespace Global;

void initNetwork(void);
void initServer(void);
void initHardware(void);
void initDebug(void);

void setup(void)
{   
    pinMode(HW_PUMP, OUTPUT);
    initDebug();
    wateringController.init();
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
    
    HygrometerWrapper GroundHumidity(new HygrometerStandartReader(HW_HUMIDITY));

    HygrometerWrapper WaterLevel;

    WateringController wateringController(HW_PUMP, &GroundHumidity);
}

void initNetwork(void) {
    NetworkController::connectWiFi();
}

void initServer(void) {
    ServerController::setHost(SERVER_ADDR);
    ServerController::setToken(DataStore::read("token"));
    ServerController::getSettings(false);
}


void initHardware(void) {
    ads1115.attach(HW_WATER_LEVEL, cast(&WaterLevel, IAnalogSensor*));
    GatewayController::init();
}

void initDebug(void) {
    #ifdef DEBUG_ENABLED
        Serial.begin(9600);
    #endif
}