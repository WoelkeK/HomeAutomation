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
  LightingContext& lightingContext
)
  : setupManager(
      relayManager,
      mcpManager,
      lightingContext
    ),
    lightingController(
      relayManager,
      lightingContext
    ),
    rollerShutterController(relayManager)
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
