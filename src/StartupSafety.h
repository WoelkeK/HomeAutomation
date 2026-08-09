#pragma once

#include <Arduino.h>

#include "Config.h"
#include "OutputConfig.h"
#include "ChannelConfig.h"

// Ustawia lokalny pin przekaźnika w bezpieczny stan OFF.
// Dla przekaźników ACTIVE LOW:
// OFF = HIGH.
//
// Najpierw ustawiamy stan HIGH przez digitalWrite(),
// a dopiero potem pinMode(OUTPUT), żeby uniknąć krótkiego impulsu LOW.
inline void setPinSafeOff(int pin)
{
  digitalWrite(pin, RELAY_OFF);
  pinMode(pin, OUTPUT);
}

inline void prepareLocalRelayPinsSafeOff()
{
  // ŚWIATŁA
  for (int i = 0; i < noRelays1; i++) {
    const OutputConfig& output =
        LIGHT_CHANNELS[i].output;

    if (output.type == OutputType::MegaPin) {
      setPinSafeOff(output.megaPin);
    }
  }

  // ROLETY - GÓRA
  for (int i = 0; i < noRelays3; i++) {
    const OutputConfig& output =
        ROLLER_UP_CHANNELS[i].output;

    if (output.type == OutputType::MegaPin) {
      setPinSafeOff(output.megaPin);
    }
  }

  // ROLETY - DÓŁ
  for (int i = 0; i < noRelays4; i++) {
    const OutputConfig& output =
        ROLLER_DOWN_CHANNELS[i].output;

    if (output.type == OutputType::MegaPin) {
      setPinSafeOff(output.megaPin);
    }
  }
}
