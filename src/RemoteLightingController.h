#pragma once

#include <Arduino.h>
#include <MySensors.h>

#include "RemoteLightingContext.h"

class RemoteLightingController
{
public:
    RemoteLightingController(
        RemoteLightingContext &context,
        byte destinationNodeId,
        byte destinationChildId)
        : context(context),
          destinationNodeId(destinationNodeId),
          destinationChildId(destinationChildId)
    {
    }

    void update()
    {
        if (!context.debouncer.update())
        {
            return;
        }

        if (context.debouncer.read() != LOW)
        {
            return;
        }

        const bool newState =
            context.stateKnown ? !context.state : true;

        context.message.setDestination(
            destinationNodeId);

        send(
            context.message.set(
                newState));

        context.state = newState;
        context.stateKnown = true;
    }

    void handleMessage(const MyMessage &message)
    {
        if (message.sender != destinationNodeId)
        {
            return;
        }

        if (message.sensor != destinationChildId)
        {
            return;
        }

        if (message.type != V_LIGHT &&
            message.type != V_STATUS)
        {
            return;
        }

        context.state = message.getBool();
        context.stateKnown = true;
    }

private:
    RemoteLightingContext &context;

    byte destinationNodeId;
    byte destinationChildId;
};
