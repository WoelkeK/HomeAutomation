#pragma once

#include <Arduino.h>
#include "RelayTypes.h"

struct RemoteLightConfig
{
    InputDevice buttonDevice;
    byte buttonPin;
    byte destinationNodeId;
    byte destinationChildId;
};

constexpr RemoteLightConfig REMOTE_LIGHTS[] = {
    {
        InputDevice::MCP1,
        14,
        1, // Slave01
        7  // Child 7 = fizyczny Waveshare CH8
    }};

constexpr byte REMOTE_LIGHT_COUNT =
    sizeof(REMOTE_LIGHTS) / sizeof(REMOTE_LIGHTS[0]);
