#pragma once
#include <Arduino.h>
#include <MySensors.h>
#include "OutputManager.h"
#include "LightingContext.h"

class LightingController
{
public:
  LightingController(
      OutputManager &outputManager,
      LightingContext &context)
      : outputManager(outputManager),
        context(context)

  {
  }

  void update()
  {
    for (byte i = 0; i < LIGHT_COUNT; i++)
    {

      if (LIGHT_CHANNELS[i].buttonDevice == InputDevice::None)
      {
        continue;
      }

      if (!context.debouncers[i].update())
      {
        continue;
      }

      const int buttonState =
          context.debouncers[i].read();

      if (buttonState != LOW)
      {
        continue;
      }

      outputManager.toggleLight(
          i,
          context.relays[i]);

      send(
          context.messages[i].set(
              context.relays[i].relayState));

      saveState(
          i,
          context.relays[i].relayState);
    }
  }

private:
  OutputManager &outputManager;
  LightingContext &context;
};
