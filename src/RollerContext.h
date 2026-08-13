#pragma once

#include <MySensors.h>
#include <Bounce2mcp.h>

#include "Config.h"
#include "RelayTypes.h"
struct RollerContext
{
  TimedRelayChannel upRelays[ROLLER_COUNT];
  TimedRelayChannel downRelays[ROLLER_COUNT];

  BounceMcp upDebouncers[ROLLER_COUNT];
  BounceMcp downDebouncers[ROLLER_COUNT];

  MyMessage upMessages[ROLLER_COUNT];
  MyMessage downMessages[ROLLER_COUNT];
};
