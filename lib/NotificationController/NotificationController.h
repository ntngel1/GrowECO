/**
    GrowECO Project

    NotificationController.h
    Purpose: Library for notifying

    @author Kirill Shepelev
    @version 1.0 28/09/2017
*/

#ifndef NOTIFICATION_CONTROLLER_H_
#define NOTIFICATION_CONTROLLER_H_

#include "Arduino.h"
#include <Wire.h>

#include "Buzzer.h"
#include "WS2812FX.h"
#include <LiquidCrystal_I2C.h>

#define BASE_SETUP(x) if(currentState != x)

class NotificationController {

  public:
    enum StateType {
      BAD,
      REGENARATION,
      DEGRADATION,
      SEMI_REGENERATION,
      NORMAL,
      SUCCESS,
      FAILURE
    };

    NotificationController(Buzzer *buzzer, WS2812FX *led, int speed = 200);

    NotificationController(Buzzer *buzzer, WS2812FX *led, LiquidCrystal_I2C *lcd, int speed = 200);

    void init(void);

    void setState(StateType state, String message[2] = {});
    StateType getCurrentState(void);

  private:
    void setLedSpeed(uint8_t speed);
    void setLedSettings(uint32_t color, uint8_t fx_mode, StateType state, uint8_t speed = 200);
    void setLCDText(String message[2]);

    int _ledSpeed;
    LiquidCrystal_I2C* _lcd;
    Buzzer* _buzzer;
    WS2812FX* _led;
    StateType currentState;
};

#endif
