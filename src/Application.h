#pragma once

#include "SetupManager.h"
#include "LightSensorController.h"
#include "LightingController.h"
#include "RollerShutterController.h"

class Application
{
  public:
    explicit Application(
  RelayManager& relayManager,
  Mcp23017Manager& mcpManager,
  LightingContext& lightingContext,
   RollerContext& rollerContext
)
  : setupManager(
      relayManager,
      mcpManager,
      lightingContext,
      rollerContext
    ),
    lightingController(
      relayManager,
      lightingContext
    ),
    rollerShutterController(relayManager, rollerContext)
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
