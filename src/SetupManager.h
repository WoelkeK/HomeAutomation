#pragma once

#include <MySensors.h>
#include <Bounce2mcp.h>

#include "Config.h"
#include "ChannelConfig.h"
#include "RelayTypes.h"
#include "OutputManager.h"
#include "Mcp23017Manager.h"
#include "LightingContext.h"
#include "RollerContext.h"

class SetupManager
{
public:
  SetupManager(
      OutputManager &outputManager,
      Mcp23017Manager &mcpManager,
      LightingContext &lightingContext,
      RollerContext &rollerContext)
      : outputManager(outputManager),
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
  OutputManager &outputManager;
  Mcp23017Manager &mcpManager;
  LightingContext &lightingContext;
  RollerContext &rollerContext;

  void initializeHardware()
  {
    mcpManager.begin();
  }

  void initializeLights()
  {
    for (int i = 0; i < LIGHT_COUNT; i++)
    {
      lightingContext.messages[i].sensor =
          LIGHT_CHANNELS[i].sensorId;

      lightingContext.messages[i].type =
          V_LIGHT;

      mcpManager.configureInput(
          LIGHT_CHANNELS[i].buttonDevice,
          LIGHT_CHANNELS[i].buttonPin);

      lightingContext.debouncers[i] = BounceMcp();

      lightingContext.debouncers[i].attach(
          mcpManager.device(
              LIGHT_CHANNELS[i].buttonDevice),
          LIGHT_CHANNELS[i].buttonPin,
          100);

      lightingContext.debouncers[i].interval(50);

      outputManager.safeOff(
          LIGHT_CHANNELS[i].output);

#if RESTORE_LIGHTS_FROM_EEPROM_ON_BOOT
      lightingContext.relays[i].relayState =
          loadState(i);
#else
      lightingContext.relays[i].relayState =
          false;
#endif

      outputManager.writeLight(
          i,
          lightingContext.relays[i],
          lightingContext.relays[i].relayState);

      send(
          lightingContext.messages[i].set(
              lightingContext.relays[i].relayState));
    }
  }
  void initializeRollers()
  {
    for (int k = 0; k < ROLLER_COUNT; k++)
    {
      const RollerConfig &config = ROLLERS[k];

      // GÓRA
      rollerContext.upRelays[k].turnOffDelay =
          config.upTurnOffDelay;

      rollerContext.upMessages[k].sensor =
          config.sensorId;

      rollerContext.upMessages[k].type =
          V_LIGHT;

      mcpManager.configureInput(
          config.buttonDevice,
          config.upButtonPin);

      outputManager.safeOff(
          config.upOutput);

      outputManager.writeRoller(
          config.upOutput,
          rollerContext.upRelays[k],
          true);

      send(
          rollerContext.upMessages[k].set(
              rollerContext.upRelays[k].relayState));

      rollerContext.upDebouncers[k] =
          BounceMcp();

      rollerContext.upDebouncers[k].attach(
          mcpManager.device(
              config.buttonDevice),
          config.upButtonPin,
          100);

      rollerContext.upDebouncers[k].interval(50);

      // DÓŁ
      rollerContext.downRelays[k].turnOffDelay =
          config.downTurnOffDelay;

      rollerContext.downMessages[k].sensor =
          config.sensorId;

      rollerContext.downMessages[k].type =
          V_LIGHT;

      mcpManager.configureInput(
          config.buttonDevice,
          config.downButtonPin);

      outputManager.safeOff(
          config.downOutput);

      outputManager.writeRoller(
          config.downOutput,
          rollerContext.downRelays[k],
          true);

      send(
          rollerContext.downMessages[k].set(
              rollerContext.downRelays[k].relayState));

      rollerContext.downDebouncers[k] =
          BounceMcp();

      rollerContext.downDebouncers[k].attach(
          mcpManager.device(
              config.buttonDevice),
          config.downButtonPin,
          100);

      rollerContext.downDebouncers[k].interval(50);
    }
  }
};
