#pragma once

#include <Arduino.h>
#include <MySensors.h>

#include "RemoteLightConfig.h"
#include "RemoteLightingContext.h"

class RemoteLightingController
{
public:
    explicit RemoteLightingController(
        RemoteLightingContext &context)
        : context(context)
    {
    }

    void update()
    {
        for (byte i = 0; i < REMOTE_LIGHT_COUNT; i++)
        {
            if (!context.debouncers[i].update())
            {
                continue;
            }

            if (context.debouncers[i].read() != LOW)
            {
                continue;
            }

            const bool newState =
                context.statesKnown[i]
                    ? !context.states[i]
                    : true;

            context.messages[i].setDestination(
                REMOTE_LIGHTS[i].destinationNodeId);

            send(
                context.messages[i].set(
                    newState));

            context.states[i] = newState;
            context.statesKnown[i] = true;
        }
    }

    void handleMessage(const MyMessage &message)
    {
        for (byte i = 0; i < REMOTE_LIGHT_COUNT; i++)
        {
            if (message.sender != REMOTE_LIGHTS[i].destinationNodeId)
            {
                continue;
            }

            if (message.sensor != REMOTE_LIGHTS[i].destinationChildId)
            {
                continue;
            }

            if (message.type != V_LIGHT &&
                message.type != V_STATUS)
            {
                continue;
            }

            context.states[i] = message.getBool();
            context.statesKnown[i] = true;

            return;
        }
    }

private:
    RemoteLightingContext &context;
};
