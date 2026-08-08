#pragma once

#include "RelayManager.h"
#include "Mcp23017Manager.h"


class SetupManager
{
  public:
    SetupManager(
      RelayManager& relayManager,
      Mcp23017Manager& mcpManager,
        LightingContext& lightingContext,
        RollerContext& rollerContext
    )
      : relayManager(relayManager),
        mcpManager(mcpManager),
        lightingContext(lightingContext),
        rollerContext(rollerContext)
    {
    }

 void begin()
{
  initializeHardware();
  initializeLights();
  initializeRollers();
}


  private:
    RelayManager& relayManager;
    Mcp23017Manager& mcpManager;
    LightingContext& lightingContext;
    RollerContext& rollerContext;


    
void initializeHardware()
{
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  mcpManager.begin();
}

void initializeLights()
{
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

    send(
      lightingContext.messages[i].set(
        lightingContext.relays[i].relayState
      )
    );
  }
}

void initializeRollers()
{
  for (int k = 0; k < noRelays3; k++) {
    rollerContext.upRelays[k].buttonPin =
        ROLLER_UP_CHANNELS[k].buttonPin;

    rollerContext.upRelays[k].relayPin =
        ROLLER_UP_CHANNELS[k].relayPin;

    rollerContext.upRelays[k].turnOffDelay =
        ROLLER_UP_CHANNELS[k].turnOffDelay;

    rollerContext.upMessages[k].sensor =
        ROLLER_UP_CHANNELS[k].sensorId;

    rollerContext.upMessages[k].type = V_LIGHT;

    mcpManager.configureInput(
      ROLLER_UP_CHANNELS[k].buttonDevice,
      rollerContext.upRelays[k].buttonPin
    );

    relayManager.safeOff(
      rollerContext.upRelays[k].relayPin
    );

    relayManager.writeRoller(
      rollerContext.upRelays[k],
      true
    );

    send(
      rollerContext.upMessages[k].set(
        rollerContext.upRelays[k].relayState
      )
    );

    rollerContext.upDebouncers[k] = BounceMcp();

    rollerContext.upDebouncers[k].attach(
      mcpManager.device(
        ROLLER_UP_CHANNELS[k].buttonDevice
      ),
      rollerContext.upRelays[k].buttonPin,
      100
    );

    rollerContext.upDebouncers[k].interval(50);
  }

  for (int k = 0; k < noRelays4; k++) {
    rollerContext.downRelays[k].buttonPin =
        ROLLER_DOWN_CHANNELS[k].buttonPin;

    rollerContext.downRelays[k].relayPin =
        ROLLER_DOWN_CHANNELS[k].relayPin;

    rollerContext.downRelays[k].turnOffDelay =
        ROLLER_DOWN_CHANNELS[k].turnOffDelay;

    rollerContext.downMessages[k].sensor =
        ROLLER_DOWN_CHANNELS[k].sensorId;

    rollerContext.downMessages[k].type = V_LIGHT;

    mcpManager.configureInput(
      ROLLER_DOWN_CHANNELS[k].buttonDevice,
      rollerContext.downRelays[k].buttonPin
    );

    relayManager.safeOff(
      rollerContext.downRelays[k].relayPin
    );

    relayManager.writeRoller(
      rollerContext.downRelays[k],
      true
    );

    send(
      rollerContext.downMessages[k].set(
        rollerContext.downRelays[k].relayState
      )
    );

    rollerContext.downDebouncers[k] = BounceMcp();

    rollerContext.downDebouncers[k].attach(
      mcpManager.device(
        ROLLER_DOWN_CHANNELS[k].buttonDevice
      ),
      rollerContext.downRelays[k].buttonPin,
      100
    );

    rollerContext.downDebouncers[k].interval(50);
  }
}
};
