#pragma once

#include <Arduino.h>
#include <MySensors.h>

#include "Version.h"
#include "ChildIds.h"
#include "Config.h"
#include "OutputManager.h"
#include "LightingContext.h"
#include "SprinklerController.h"
#include "RollerShutterController.h"
class MySensorsGateway
{
public:
  explicit MySensorsGateway(
      OutputManager &outputManager,
      LightingContext &lightingContext,
      SprinklerController &sprinklerController,
      RollerShutterController &rollerShutterController)
      : outputManager(outputManager),
        lightingContext(lightingContext),
        sprinklerController(sprinklerController),
        rollerShutterController(rollerShutterController),
        firmwareMessage(ChildId::FIRMWARE_INFO, V_TEXT),
        buildMessage(ChildId::BUILD_INFO, V_TEXT)
  {
  }

  void presentNode()
  {
    sendSketchInfo(FIRMWARE_NAME, FIRMWARE_VERSION);
    present(ChildId::OUTDOOR_LIGHT_SENSOR, S_LIGHT_LEVEL);

    for (int i = 0; i < LIGHT_COUNT; i++)
    {
      present(ChildId::LIGHT_FIRST + i, S_LIGHT);
    }

    for (byte i = 0; i < ROLLER_COUNT; i++)
    {
      present(
          ChildId::ROLLER_FIRST + i,
          S_COVER,
          "Roleta");
    }

#if ENABLE_SPRINKLER_MODULE
    for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++)
    {
      present(
          ChildId::SPRINKLER_FIRST + zone,
          S_BINARY,
          "Spryskiwacz");
    }
#endif

    present(ChildId::FIRMWARE_INFO, S_INFO, "Firmware");
    present(ChildId::BUILD_INFO, S_INFO, "Build");

    reportDiagnostics();
  }

  void update()
  {
    const unsigned long currentMillis = millis();

    if (currentMillis - lastDiagnosticsSent >= DIAGNOSTICS_INTERVAL_MS)
    {
      reportDiagnostics();
    }
  }

  void handleMessage(const MyMessage &message)
  {
    if ((message.type == V_LIGHT || message.type == V_STATUS) &&
        message.sensor >= ChildId::LIGHT_FIRST &&
        message.sensor <= ChildId::LIGHT_LAST)
    {
      const byte lightIndex = message.sensor - ChildId::LIGHT_FIRST;

      outputManager.writeLight(
          lightIndex,
          lightingContext.relays[lightIndex],
          message.getBool());

      saveState(lightIndex, lightingContext.relays[lightIndex].relayState);
      return;
    }

#if ENABLE_SPRINKLER_MODULE
    if ((message.type == V_STATUS || message.type == V_LIGHT) &&
        message.sensor >= ChildId::SPRINKLER_FIRST &&
        message.sensor <= ChildId::SPRINKLER_LAST)
    {
      const byte zone =
          message.sensor - ChildId::SPRINKLER_FIRST;

      sprinklerController.setZone(
          zone,
          message.getBool(),
          true);
    }
#endif
    if (message.sensor >= ChildId::ROLLER_FIRST &&
        message.sensor <= ChildId::ROLLER_LAST)
    {
      const byte rollerIndex =
          message.sensor - ChildId::ROLLER_FIRST;

      switch (message.type)
      {
      case V_UP:
        rollerShutterController.moveUp(rollerIndex);
        return;

      case V_DOWN:
        rollerShutterController.moveDown(rollerIndex);
        return;

      case V_STOP:
        rollerShutterController.stop(rollerIndex);
        return;
      }
    }
  }

private:
  static constexpr unsigned long DIAGNOSTICS_INTERVAL_MS = 30000UL;

  OutputManager &outputManager;
  LightingContext &lightingContext;
  SprinklerController &sprinklerController;
  RollerShutterController &rollerShutterController;
  MyMessage firmwareMessage;
  MyMessage buildMessage;

  unsigned long lastDiagnosticsSent = 0;

  void reportDiagnostics()
  {
    firmwareMessage.set(FIRMWARE_VERSION);
    send(firmwareMessage);

    char buildInfo[24];

    snprintf(
        buildInfo,
        sizeof(buildInfo),
        "%s %s",
        BUILD_DATE,
        BUILD_TIME);

    buildMessage.set(buildInfo);
    send(buildMessage);

    lastDiagnosticsSent = millis();
  }
};
