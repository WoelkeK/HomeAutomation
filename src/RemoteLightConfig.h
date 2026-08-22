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

    // Switch na dole przy wyjściu na taras, sterowanie światłem na tarasie(Slave01, CH8)
    {
        InputDevice::MCP1,
        14,
        1, // Slave01
        7  // Child 7 = fizyczny Waveshare CH8
    },
    {
        // Switch na dole przy wyjściu głównym, sterowanie lampami chodnik Slave01 CH9){
        InputDevice::MCP1,
        4,
        1, // Slave01
        16 // Child 8 = Waveshare CH9
    }

};

constexpr byte REMOTE_LIGHT_COUNT =
    sizeof(REMOTE_LIGHTS) / sizeof(REMOTE_LIGHTS[0]);
