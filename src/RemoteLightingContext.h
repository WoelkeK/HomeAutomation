#pragma once

#include <MySensors.h>
#include <Bounce2mcp.h>

struct RemoteLightingContext
{
    BounceMcp debouncer;
    MyMessage message;

    bool state = false;
    bool stateKnown = false;
};
