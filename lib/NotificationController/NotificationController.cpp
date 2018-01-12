#include "NotificationController.h"

NotificationController::NotificationController(Buzzer *buzzer, WS2812FX *led, int speed)
{
  this -> _buzzer = buzzer;
  this -> _led = led;
  this -> _ledSpeed = speed;
}

NotificationController::NotificationController(Buzzer *buzzer, WS2812FX *led, LiquidCrystal_I2C *lcd, int speed)
{
  this -> _buzzer = buzzer;
  this -> _led = led;
  this -> _ledSpeed = speed;
  this -> _lcd = lcd;
}

void NotificationController::init(void)
{
  if (_led != NULL) {
    _led -> init();
    _led -> setBrightness(255);
    _led -> start();
    setLedSettings(0x000000, FX_MODE_STATIC, NORMAL, _ledSpeed);
  }

  if (_lcd != NULL) {
    _lcd -> begin(D2, D1);
    _lcd -> backlight();
    _lcd -> clear();
  }

  currentState = NORMAL;
}

void NotificationController::setState(StateType state, String message[2])
{
  switch (state) {
    case BAD:
      BASE_SETUP(BAD) {
        int frequencies[] = {NOTE_B6, NOTE_C7, NOTE_CS7}; // частоты к проигрыванию
        int durations[] = {40, 50, 60}; // длительности задержек

        setLedSettings(0xFF0000, FX_MODE_BLINK, BAD, _ledSpeed); // настраиваем светодиод
        setLCDText(message);

        _buzzer -> playSequence(frequencies, durations, 3, _led, &WS2812FX::service); // проигрываем частоты
      }
      _buzzer -> play(NOTE_CS7, 60, _led, &WS2812FX::service); // проигрываем частоту
      break;

    case REGENARATION:
      BASE_SETUP(REGENARATION) {
        int frequencies[] = {NOTE_C7, NOTE_CS7, NOTE_B6};
        int durations[] = {40, 50, 60};

        setLedSettings(0x00FF00, FX_MODE_FADE, REGENARATION, _ledSpeed);
        setLCDText(message);

        _buzzer -> playSequence(frequencies, durations, 3, _led, &WS2812FX::service);
      }
      _led -> service();
      break;

    case SEMI_REGENERATION:
      BASE_SETUP(SEMI_REGENERATION) {
        setLedSettings(0xFFFF00, FX_MODE_FADE, SEMI_REGENERATION, _ledSpeed);
        setLCDText(message);

        _buzzer -> play(NOTE_D5, 120, _led, &WS2812FX::service);
      }
      _led -> service();
      break;

    case DEGRADATION:
      BASE_SETUP(DEGRADATION) {
        int frequencies[] = {NOTE_E7, NOTE_G7};
        int durations[] = {40, 120};

        setLedSettings(0xFF0000, FX_MODE_FADE, DEGRADATION, _ledSpeed);
        setLCDText(message);

        _buzzer -> playSequence(frequencies, durations, 2, _led, &WS2812FX::service);
      }
      _led -> service();
      break;

    case NORMAL:
      BASE_SETUP(NORMAL) {
        setLedSettings(0x0, FX_MODE_STATIC, NORMAL, _ledSpeed);
        setLCDText(message);
      }
      _led -> service();
      break;

    case SUCCESS:
      BASE_SETUP(SUCCESS) {
        setLedSettings(0x00FF00, FX_MODE_STATIC, SUCCESS, _ledSpeed);
        setLCDText(message);
      }
      _led -> service();
      break;
    case FAILURE:
      BASE_SETUP(FAILURE) {
        setLedSettings(0xFF0000, FX_MODE_STATIC, FAILURE, _ledSpeed);
        setLCDText(message);
      }
      _led -> service();
      break;
    default:
    BASE_SETUP(NORMAL) {
      setLedSettings(0x0, FX_MODE_STATIC, NORMAL, _ledSpeed);
      setLCDText(message);
    }
    _led -> service();
    break;
  }
}

NotificationController::StateType NotificationController::getCurrentState(void)
{
  return currentState;
}

void NotificationController::setLedSpeed(uint8_t speed)
{
  _ledSpeed = speed;
  _led -> setSpeed(_ledSpeed);
}

void NotificationController::setLedSettings(uint32_t color, uint8_t fx_mode, StateType state, uint8_t speed)
{
  _led -> setColor(color);
  _led -> setMode(fx_mode);
  setLedSpeed(speed);
  currentState = state;
}

void NotificationController::setLCDText(String *message) {
  if (_lcd != NULL) {
    _lcd -> clear();
    if (message[0] != NULL) {
      _lcd -> setCursor(0, 0);
      _lcd -> print(message[0].c_str());
    }
    if (message[1] != NULL) {
      _lcd -> setCursor(0, 1);
      _lcd -> print(message[1].c_str());
    }
  }
}
