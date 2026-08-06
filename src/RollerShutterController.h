#pragma once

#include "RelayManager.h"

class RollerShutterController
{
  public:
    explicit RollerShutterController(RelayManager& relayManager)
      : relayManager(relayManager)
    {
    }

    void update()
    {
      const unsigned long currentMillis = millis();

      for (byte k = 0; k < noRelays3; k++) {
        if (debouncer3[k].update()) {
          const int value3 = debouncer3[k].read();

          if (value3 == LOW) {
            Relays3[k].buttonPushedMillis = currentMillis;
            Relays3[k].ROLReady = true;
          }
        }

        if (Relays3[k].ROLReady) {
          Relays4[k].ROLReady = false;

          if (!Relays4[k].relayState) {
            relayManager.toggleRoller(Relays4[k]);
            send(msg4[k].set(Relays4[k].relayState));
          }

          if (
            static_cast<unsigned long>(
              currentMillis - Relays3[k].buttonPushedMillis
            ) > Relays3[k].turnOnDelay
          ) {
            relayManager.toggleRoller(Relays3[k]);
            send(msg3[k].set(Relays3[k].relayState));

            Relays3[k].ledTurnedOnAt = currentMillis;
            Relays3[k].ROLReady = false;
          }
        }

        if (!Relays3[k].relayState) {
          if (
            static_cast<unsigned long>(
              currentMillis - Relays3[k].ledTurnedOnAt
            ) >= Relays3[k].turnOffDelay
          ) {
            relayManager.toggleRoller(Relays3[k]);
            send(msg3[k].set(Relays3[k].relayState));
          }
        }

        if (debouncer4[k].update()) {
          const int value4 = debouncer4[k].read();

          if (value4 == LOW) {
            Relays4[k].buttonPushedMillis = currentMillis;
            Relays4[k].ROLReady = true;
          }
        }

        if (Relays4[k].ROLReady) {
          Relays3[k].ROLReady = false;

          if (!Relays3[k].relayState) {
            relayManager.toggleRoller(Relays3[k]);
            send(msg3[k].set(Relays3[k].relayState));
          }

          if (
            static_cast<unsigned long>(
              currentMillis - Relays4[k].buttonPushedMillis
            ) > Relays4[k].turnOnDelay
          ) {
            relayManager.toggleRoller(Relays4[k]);
            send(msg4[k].set(Relays4[k].relayState));

            Relays4[k].ledTurnedOnAt = currentMillis;
            Relays4[k].ROLReady = false;
          }
        }

        if (!Relays4[k].relayState) {
          if (
            static_cast<unsigned long>(
              currentMillis - Relays4[k].ledTurnedOnAt
            ) >= Relays4[k].turnOffDelay
          ) {
            relayManager.toggleRoller(Relays4[k]);
            send(msg4[k].set(Relays4[k].relayState));
          }
        }
      }
    }

  private:
    RelayManager& relayManager;
};
