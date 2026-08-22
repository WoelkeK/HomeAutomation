#pragma once

#include "SetupManager.h"
#include "LightSensorController.h"
#include "LightingController.h"
#include "RollerShutterController.h"
#include "RemoteLightingContext.h"

class Application
{
public:
  explicit Application(
      OutputManager &outputManager,
      Mcp23017Manager &mcpManager,
      LightingContext &lightingContext,
      RollerContext &rollerContext,
      RemoteLightingContext &remoteLightingContext)
      : setupManager(
            outputManager,
            mcpManager,
            lightingContext,
            rollerContext,
            remoteLightingContext),
        lightingController(
            outputManager,
            lightingContext),
        rollerShutterController(
            outputManager,
            rollerContext)
  {
  }

  void begin()
  {
    setupManager.begin();
  }

  void update()
  {
    lightSensorController.update();
    lightingController.update();
    rollerShutterController.update();
  }

private:
  SetupManager setupManager;
  LightSensorController lightSensorController;
  LightingController lightingController;
  RollerShutterController rollerShutterController;
};
