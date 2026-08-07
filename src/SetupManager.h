#pragma once

#include "RelayManager.h"
#include "Mcp23017Manager.h"

class SetupManager
{
  public:
    SetupManager(
      RelayManager& relayManager,
      Mcp23017Manager& mcpManager,
        LightingContext& lightingContext
    )
      : relayManager(relayManager),
        mcpManager(mcpManager),
        lightingContext(lightingContext)
    {
    }

    void begin()
    {
      // initialize all the readings to 0
      for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        readings[thisReading] = 0;
      }

      mcpManager.begin();

      // Initialize Relays1 with corresponding buttons
      for (int i = 0; i < noRelays1; i++) {
       lightingContext.relays[i].buttonPin = LIGHT_CHANNELS[i].buttonPin;
        lightingContext.relays[i].relayPin = LIGHT_CHANNELS[i].relayPin;

        lightingContext.messages[i].sensor = LIGHT_CHANNELS[i].sensorId;
        lightingContext.messages[i].type = V_LIGHT;

        mcpManager.configureInput(
          LIGHT_CHANNELS[i].buttonDevice,
          lightingContext.relays[i].buttonPin
        );

        lightingContext.debouncers[i] = BounceMcp();

        lightingContext.debouncers[i].attach(
          mcpManager.device(LIGHT_CHANNELS[i].buttonDevice),
         lightingContext.relays[i].buttonPin,
          100
        );

        lightingContext.debouncers[i].interval(50);

        relayManager.safeOff(LIGHT_CHANNELS[i].output);

#if RESTORE_LIGHTS_FROM_EEPROM_ON_BOOT
        lightingContext.relays[i].relayState = loadState(i);
#else
        lightingContext.relays[i].relayState = false;
#endif

        relayManager.writeLight(
          i,
          lightingContext.relays[i],
          lightingContext.relays[i].relayState
        );

        send(lightingContext.messages[i].set(lightingContext.relays[i].relayState));
      }

      // Initialize Relays3 - rolety gora
      for (int k = 0; k < noRelays3; k++) {
        Relays3[k].buttonPin = ROLLER_UP_CHANNELS[k].buttonPin;
        Relays3[k].relayPin = ROLLER_UP_CHANNELS[k].relayPin;
        Relays3[k].turnOffDelay =
            ROLLER_UP_CHANNELS[k].turnOffDelay;

        msg3[k].sensor = ROLLER_UP_CHANNELS[k].sensorId;
        msg3[k].type = V_LIGHT;

        mcpManager.configureInput(
          ROLLER_UP_CHANNELS[k].buttonDevice,
          Relays3[k].buttonPin
        );

        relayManager.safeOff(Relays3[k].relayPin);
        relayManager.writeRoller(Relays3[k], true);

        send(msg3[k].set(Relays3[k].relayState));

        debouncer3[k] = BounceMcp();

        debouncer3[k].attach(
          mcpManager.device(ROLLER_UP_CHANNELS[k].buttonDevice),
          Relays3[k].buttonPin,
          100
        );

        debouncer3[k].interval(50);
      }

      // Initialize Relays4 - rolety dol
      for (int k = 0; k < noRelays4; k++) {
        Relays4[k].buttonPin =
            ROLLER_DOWN_CHANNELS[k].buttonPin;

        Relays4[k].relayPin =
            ROLLER_DOWN_CHANNELS[k].relayPin;

        Relays4[k].turnOffDelay =
            ROLLER_DOWN_CHANNELS[k].turnOffDelay;

        msg4[k].sensor =
            ROLLER_DOWN_CHANNELS[k].sensorId;

        msg4[k].type = V_LIGHT;

        mcpManager.configureInput(
          ROLLER_DOWN_CHANNELS[k].buttonDevice,
          Relays4[k].buttonPin
        );

        relayManager.safeOff(Relays4[k].relayPin);
        relayManager.writeRoller(Relays4[k], true);

        send(msg4[k].set(Relays4[k].relayState));

        debouncer4[k] = BounceMcp();

        debouncer4[k].attach(
          mcpManager.device(ROLLER_DOWN_CHANNELS[k].buttonDevice),
          Relays4[k].buttonPin,
          100
        );

        debouncer4[k].interval(50);
      }
    }

  private:
    RelayManager& relayManager;
    Mcp23017Manager& mcpManager;
    LightingContext& lightingContext;;
};
