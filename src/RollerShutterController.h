#pragma once

#include "RelayManager.h"
#include "RollerContext.h"

class RollerShutterController
{
  public:
    RollerShutterController(
      RelayManager& relayManager,
      RollerContext& rollerContext
    )
      : relayManager(relayManager),
        rollerContext(rollerContext)
    {
    }

    void update()
    {
      const unsigned long currentMillis = millis();

      for (byte k = 0; k < noRelays3; k++) {

        // GORA
        if (rollerContext.upDebouncers[k].update()) {
          const int value3 =
              rollerContext.upDebouncers[k].read();

          if (value3 == LOW) {
            rollerContext.upRelays[k].buttonPushedMillis =
                currentMillis;

            rollerContext.upRelays[k].ROLReady = true;
          }
        }

        if (rollerContext.upRelays[k].ROLReady) {
          rollerContext.downRelays[k].ROLReady = false;

          if (!rollerContext.downRelays[k].relayState) {
            relayManager.toggleRoller(
              rollerContext.downRelays[k]
            );

            send(
              rollerContext.downMessages[k].set(
                rollerContext.downRelays[k].relayState
              )
            );
          }

          if (
            static_cast<unsigned long>(
              currentMillis -
              rollerContext.upRelays[k].buttonPushedMillis
            ) > rollerContext.upRelays[k].turnOnDelay
          ) {
            relayManager.toggleRoller(
              rollerContext.upRelays[k]
            );

            send(
              rollerContext.upMessages[k].set(
                rollerContext.upRelays[k].relayState
              )
            );

            rollerContext.upRelays[k].ledTurnedOnAt =
                currentMillis;

            rollerContext.upRelays[k].ROLReady = false;
          }
        }

        if (!rollerContext.upRelays[k].relayState) {
          if (
            static_cast<unsigned long>(
              currentMillis -
              rollerContext.upRelays[k].ledTurnedOnAt
            ) >= rollerContext.upRelays[k].turnOffDelay
          ) {
            relayManager.toggleRoller(
              rollerContext.upRelays[k]
            );

            send(
              rollerContext.upMessages[k].set(
                rollerContext.upRelays[k].relayState
              )
            );
          }
        }

        // DOL
        if (rollerContext.downDebouncers[k].update()) {
          const int value4 =
              rollerContext.downDebouncers[k].read();

          if (value4 == LOW) {
            rollerContext.downRelays[k].buttonPushedMillis =
                currentMillis;

            rollerContext.downRelays[k].ROLReady = true;
          }
        }

        if (rollerContext.downRelays[k].ROLReady) {
          rollerContext.upRelays[k].ROLReady = false;

          if (!rollerContext.upRelays[k].relayState) {
            relayManager.toggleRoller(
              rollerContext.upRelays[k]
            );

            send(
              rollerContext.upMessages[k].set(
                rollerContext.upRelays[k].relayState
              )
            );
          }

          if (
            static_cast<unsigned long>(
              currentMillis -
              rollerContext.downRelays[k].buttonPushedMillis
            ) > rollerContext.downRelays[k].turnOnDelay
          ) {
            relayManager.toggleRoller(
              rollerContext.downRelays[k]
            );

            send(
              rollerContext.downMessages[k].set(
                rollerContext.downRelays[k].relayState
              )
            );

            rollerContext.downRelays[k].ledTurnedOnAt =
                currentMillis;

            rollerContext.downRelays[k].ROLReady = false;
          }
        }

        if (!rollerContext.downRelays[k].relayState) {
          if (
            static_cast<unsigned long>(
              currentMillis -
              rollerContext.downRelays[k].ledTurnedOnAt
            ) >= rollerContext.downRelays[k].turnOffDelay
          ) {
            relayManager.toggleRoller(
              rollerContext.downRelays[k]
            );

            send(
              rollerContext.downMessages[k].set(
                rollerContext.downRelays[k].relayState
              )
            );
          }
        }
      }
    }

  private:
    RelayManager& relayManager;
    RollerContext& rollerContext;
};
