// #pragma once

// #include <Arduino.h>
// #include <MySensors.h>
// #include <Bounce2mcp.h>

// #include "OutputManager.h"
// #include "RollerContext.h"

// class RollerShutterController
// {
//   public:
//     RollerShutterController(
//       OutputManager& outputManager,
//       RollerContext& rollerContext
//     )
//       : outputManager(outputManager),
//         rollerContext(rollerContext)
//     {
//     }

//     void update()
//     {
//       const unsigned long currentMillis = millis();

//       for (byte k = 0; k < noRelays3; k++) {

//         // GORA
//         if (rollerContext.upDebouncers[k].update()) {
//           const int value3 =
//               rollerContext.upDebouncers[k].read();

//           if (value3 == LOW) {
//             rollerContext.upRelays[k].buttonPushedMillis =
//                 currentMillis;

//             rollerContext.upRelays[k].ROLReady = true;
//           }
//         }

//         if (rollerContext.upRelays[k].ROLReady) {
//           rollerContext.downRelays[k].ROLReady = false;

//           if (!rollerContext.downRelays[k].relayState) {
//             outputManager.toggleRoller(
//               rollerContext.downRelays[k]
//             );

//             send(
//               rollerContext.downMessages[k].set(
//                 rollerContext.downRelays[k].relayState
//               )
//             );
//           }

//           if (
//             static_cast<unsigned long>(
//               currentMillis -
//               rollerContext.upRelays[k].buttonPushedMillis
//             ) > rollerContext.upRelays[k].turnOnDelay
//           ) {
//             outputManager.toggleRoller(
//               rollerContext.upRelays[k]
//             );

//             send(
//               rollerContext.upMessages[k].set(
//                 rollerContext.upRelays[k].relayState
//               )
//             );

//             rollerContext.upRelays[k].ledTurnedOnAt =
//                 currentMillis;

//             rollerContext.upRelays[k].ROLReady = false;
//           }
//         }

//         if (!rollerContext.upRelays[k].relayState) {
//           if (
//             static_cast<unsigned long>(
//               currentMillis -
//               rollerContext.upRelays[k].ledTurnedOnAt
//             ) >= rollerContext.upRelays[k].turnOffDelay
//           ) {
//             outputManager.toggleRoller(
//               rollerContext.upRelays[k]
//             );

//             send(
//               rollerContext.upMessages[k].set(
//                 rollerContext.upRelays[k].relayState
//               )
//             );
//           }
//         }

//         // DOL
//         if (rollerContext.downDebouncers[k].update()) {
//           const int value4 =
//               rollerContext.downDebouncers[k].read();

//           if (value4 == LOW) {
//             rollerContext.downRelays[k].buttonPushedMillis =
//                 currentMillis;

//             rollerContext.downRelays[k].ROLReady = true;
//           }
//         }

//         if (rollerContext.downRelays[k].ROLReady) {
//           rollerContext.upRelays[k].ROLReady = false;

//           if (!rollerContext.upRelays[k].relayState) {
//             outputManager.toggleRoller(
//               rollerContext.upRelays[k]
//             );

//             send(
//               rollerContext.upMessages[k].set(
//                 rollerContext.upRelays[k].relayState
//               )
//             );
//           }

//           if (
//             static_cast<unsigned long>(
//               currentMillis -
//               rollerContext.downRelays[k].buttonPushedMillis
//             ) > rollerContext.downRelays[k].turnOnDelay
//           ) {
//             outputManager.toggleRoller(
//               rollerContext.downRelays[k]
//             );

//             send(
//               rollerContext.downMessages[k].set(
//                 rollerContext.downRelays[k].relayState
//               )
//             );

//             rollerContext.downRelays[k].ledTurnedOnAt =
//                 currentMillis;

//             rollerContext.downRelays[k].ROLReady = false;
//           }
//         }

//         if (!rollerContext.downRelays[k].relayState) {
//           if (
//             static_cast<unsigned long>(
//               currentMillis -
//               rollerContext.downRelays[k].ledTurnedOnAt
//             ) >= rollerContext.downRelays[k].turnOffDelay
//           ) {
//             outputManager.toggleRoller(
//               rollerContext.downRelays[k]
//             );

//             send(
//               rollerContext.downMessages[k].set(
//                 rollerContext.downRelays[k].relayState
//               )
//             );
//           }
//         }
//       }
//     }

//   private:
//     OutputManager& outputManager;
//     RollerContext& rollerContext;
// };
#pragma once

#include <Arduino.h>
#include <MySensors.h>
#include <Bounce2mcp.h>

#include "OutputManager.h"
#include "RollerContext.h"
#include "ChannelConfig.h"

class RollerShutterController
{
  public:
    RollerShutterController(
      OutputManager& outputManager,
      RollerContext& rollerContext
    )
      : outputManager(outputManager),
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
            outputManager.toggleRoller(
              ROLLER_DOWN_CHANNELS[k].output,
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
            outputManager.toggleRoller(
              ROLLER_UP_CHANNELS[k].output,
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
            outputManager.toggleRoller(
              ROLLER_UP_CHANNELS[k].output,
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
            outputManager.toggleRoller(
              ROLLER_UP_CHANNELS[k].output,
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
            outputManager.toggleRoller(
              ROLLER_DOWN_CHANNELS[k].output,
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
            outputManager.toggleRoller(
              ROLLER_DOWN_CHANNELS[k].output,
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
    OutputManager& outputManager;
    RollerContext& rollerContext;
};
