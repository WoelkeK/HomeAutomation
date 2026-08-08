#pragma once
#include <MySensors.h>
#include <Bounce2mcp.h>

#include "Config.h"
#include "RelayTypes.h"
struct LightingContext
{
  RelayChannel relays[noRelays1];
  BounceMcp debouncers[noRelays1];
  MyMessage messages[noRelays1];
};
