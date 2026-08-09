#pragma once

#include <Arduino.h>

#include "LightId.h"
#include "OutputConfig.h"

enum class InputDevice : byte
{
  MCP1,
  MCP2,
  MCP3
};

struct LightChannelConfig
{
  LightId id;
  byte sensorId;
  int buttonPin;
  InputDevice buttonDevice;
  OutputConfig output;
};

struct RollerChannelConfig
{
  byte sensorId;
  int buttonPin;
  InputDevice buttonDevice;
  OutputConfig output;
  unsigned long turnOffDelay;
};
