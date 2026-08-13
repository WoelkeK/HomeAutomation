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

struct RollerConfig
{
  byte sensorId;

  int upButtonPin;
  int downButtonPin;

  InputDevice buttonDevice;

  OutputConfig upOutput;
  OutputConfig downOutput;

  unsigned long upTurnOffDelay;
  unsigned long downTurnOffDelay;
};
