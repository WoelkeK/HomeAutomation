#pragma once

#include "RelayManager.h"

class LightingController
{
  public:
    explicit LightingController(RelayManager& relayManager)
      : relayManager(relayManager)
    {
    }

    void update()
    {
      for (byte i = 0; i < noRelays1; i++) {
        if (!debouncer1[i].update()) {
          continue;
        }

        const int buttonState = debouncer1[i].read();

        if (buttonState != LOW) {
          continue;
        }

        relayManager.toggleLight(i, Relays1[i]);

        send(
          msg1[i].set(Relays1[i].relayState)
        );

        saveState(
          i,
          Relays1[i].relayState
        );
      }
    }

  private:
    RelayManager& relayManager;
};
