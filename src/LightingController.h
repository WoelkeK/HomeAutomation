#pragma once

#include "RelayManager.h"
#include "LightingContext.h"

class LightingController
{
  public:
    LightingController(
      RelayManager& relayManager,
      LightingContext& context
    )
      : relayManager(relayManager),
        context(context)
    {
    }

    void update()
    {
      for (byte i = 0; i < noRelays1; i++) {
        if (!context.debouncers[i].update()) {
          continue;
        }

        const int buttonState =
            context.debouncers[i].read();

        if (buttonState != LOW) {
          continue;
        }

        relayManager.toggleLight(
          i,
          context.relays[i]
        );

        send(
          context.messages[i].set(
            context.relays[i].relayState
          )
        );

        saveState(
          i,
          context.relays[i].relayState
        );
      }
    }

  private:
    RelayManager& relayManager;
    LightingContext& context;
};
