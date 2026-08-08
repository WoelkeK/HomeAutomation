#pragma once

#include "SetupManager.h"
#include "LightSensorController.h"
#include "LightingController.h"
#include "RollerShutterController.h"

class Application
{
  public:
    explicit Application(
  OutputManager& outputManager,
  Mcp23017Manager& mcpManager,
  LightingContext& lightingContext,
  RollerContext& rollerContext
)
  : setupManager(
    outputManager,
      mcpManager,
      lightingContext,
      rollerContext
    ),
    lightingController(
      outputManager,
      lightingContext
    ),
    rollerShutterController(outputManager, rollerContext)
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
