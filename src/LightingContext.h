#pragma once
#include <MySensors.h>
#include <Bounce2mcp.h>

#include "Config.h"
#include "RelayTypes.h"
struct LightingContext
{
  RelayChannel relays[LIGHT_COUNT];
  BounceMcp debouncers[LIGHT_COUNT];
  MyMessage messages[LIGHT_COUNT];
};
