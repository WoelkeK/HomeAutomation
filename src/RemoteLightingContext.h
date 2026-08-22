#pragma once

#include <MySensors.h>
#include <Bounce2mcp.h>

#include "RemoteLightConfig.h"

struct RemoteLightingContext
{
    BounceMcp debouncers[REMOTE_LIGHT_COUNT];
    MyMessage messages[REMOTE_LIGHT_COUNT];

    bool states[REMOTE_LIGHT_COUNT] = {};
    bool statesKnown[REMOTE_LIGHT_COUNT] = {};
};
