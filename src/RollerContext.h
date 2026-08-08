#pragma once

#include <MySensors.h>
#include <Bounce2mcp.h>

#include "Config.h"
#include "RelayTypes.h"
struct RollerContext
{
  TimedRelayChannel upRelays[noRelays3];
  TimedRelayChannel downRelays[noRelays4];

  BounceMcp upDebouncers[noRelays3];
  BounceMcp downDebouncers[noRelays4];

  MyMessage upMessages[noRelays3];
  MyMessage downMessages[noRelays4];
};
