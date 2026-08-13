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
  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    const OutputConfig &output =
        LIGHT_CHANNELS[i].output;

    if (output.type == OutputType::MegaPin)
    {
      setPinSafeOff(output.megaPin);
    }
  }

  // ROLETY
  for (int i = 0; i < ROLLER_COUNT; i++)
  {
    const OutputConfig &upOutput =
        ROLLERS[i].upOutput;

    const OutputConfig &downOutput =
        ROLLERS[i].downOutput;

    if (upOutput.type == OutputType::MegaPin)
    {
      setPinSafeOff(upOutput.megaPin);
    }

    if (downOutput.type == OutputType::MegaPin)
    {
      setPinSafeOff(downOutput.megaPin);
    }
  }
}
