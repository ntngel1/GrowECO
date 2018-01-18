/**
    GrowECO Project

    Buzzer.h
    Purpose: Library for controlling buzzer

    @author Kirill Shepelev
    @version 1.0 28/09/2017
*/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "Arduino.h"
#include "Pitches.h"
#include "functional"

class Buzzer {
  public:
    Buzzer() {
      this -> _pin = 0;
    }
    Buzzer(uint8_t pin) {
      this -> _pin = pin;
    }
    inline void play(int frequency, int duration) {
      tone(_pin, frequency);
      delay(duration);
      noTone(_pin);
      delay(duration);
    }

    template <class T>
    inline void play(int frequency, int duration, T* obj, void (T::*function)(void)) {
      long mil;
      tone(_pin, frequency);
      mil = millis() + duration;
      while (millis() < mil) (obj->*function)();
      noTone(_pin);
      mil = millis() + duration;
      while (millis() < mil) (obj->*function)();
    }

    inline void play(int frequency, int duration, std::function<void(void)> function) {
      long mil;
      tone(_pin, frequency);
      mil = millis() + duration;
      while (millis() < mil) function();
      noTone(_pin);
      mil = millis() + duration;
      while (millis() < mil) function();
    }

    template <class T>
    inline void playSequence(int frequencies[], int durations[], int length, T* obj, void (T::*function)(void)) {
      for (int i = 0; i < length; i++) {
        play(frequencies[i], durations[i], obj, function);
      }
    }

    inline void playSequence(int frequencies[], int durations[], int length, std::function<void(void)> function) {
      for (int i = 0; i < length; i++) {
        play(frequencies[i], durations[i], function);
      }
    }
  private:
    uint8_t _pin;
};

#endif
