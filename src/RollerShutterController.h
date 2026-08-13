#pragma once

#include <Arduino.h>
#include <MySensors.h>
#include <Bounce2mcp.h>

#include "OutputManager.h"
#include "RollerContext.h"
#include "ChannelConfig.h"

class RollerShutterController
{
public:
  RollerShutterController(
      OutputManager &outputManager,
      RollerContext &rollerContext)
      : outputManager(outputManager),
        rollerContext(rollerContext)
  {
  }

  void moveUp(byte rollerIndex)
  {
    if (rollerIndex >= ROLLER_COUNT)
      return;

    const unsigned long currentMillis = millis();

    rollerContext.upRelays[rollerIndex].buttonPushedMillis =
        currentMillis;

    rollerContext.upRelays[rollerIndex].ROLReady = true;
  }

  void moveDown(byte rollerIndex)
  {
    if (rollerIndex >= ROLLER_COUNT)
      return;

    const unsigned long currentMillis = millis();

    rollerContext.downRelays[rollerIndex].buttonPushedMillis =
        currentMillis;

    rollerContext.downRelays[rollerIndex].ROLReady = true;
  }

  void stop(byte rollerIndex)
  {
    if (rollerIndex >= ROLLER_COUNT)
      return;

    TimedRelayChannel &upRelay =
        rollerContext.upRelays[rollerIndex];

    TimedRelayChannel &downRelay =
        rollerContext.downRelays[rollerIndex];

    upRelay.ROLReady = false;
    downRelay.ROLReady = false;

    if (!upRelay.relayState)
    {
      outputManager.toggleRoller(
          ROLLERS[rollerIndex].upOutput,
          upRelay);
    }

    if (!downRelay.relayState)
    {
      outputManager.toggleRoller(
          ROLLERS[rollerIndex].downOutput,
          downRelay);
    }
  }

  void update()
  {
    const unsigned long currentMillis = millis();

    for (byte k = 0; k < ROLLER_COUNT; k++)
    {

      processDirection(
          currentMillis,
          rollerContext.upRelays[k],
          rollerContext.downRelays[k],
          rollerContext.upDebouncers[k],
          rollerContext.upMessages[k],
          rollerContext.downMessages[k],
          ROLLERS[k].upOutput,
          ROLLERS[k].downOutput);

      processDirection(
          currentMillis,
          rollerContext.downRelays[k],
          rollerContext.upRelays[k],
          rollerContext.downDebouncers[k],
          rollerContext.downMessages[k],
          rollerContext.upMessages[k],
          ROLLERS[k].downOutput,
          ROLLERS[k].upOutput);
    }
  }

private:
  OutputManager &outputManager;
  RollerContext &rollerContext;

  void processDirection(
      unsigned long currentMillis,
      TimedRelayChannel &relay,
      TimedRelayChannel &oppositeRelay,
      BounceMcp &debouncer,
      MyMessage &message,
      MyMessage &oppositeMessage,
      const OutputConfig &output,
      const OutputConfig &oppositeOutput)
  {
    if (debouncer.update())
    {
      if (debouncer.read() == LOW)
      {
        relay.buttonPushedMillis = currentMillis;
        relay.ROLReady = true;
      }
    }

    if (relay.ROLReady)
    {
      oppositeRelay.ROLReady = false;

      if (!oppositeRelay.relayState)
      {
        outputManager.toggleRoller(
            oppositeOutput,
            oppositeRelay);

        send(
            oppositeMessage.set(
                oppositeRelay.relayState));
      }

      if (
          static_cast<unsigned long>(
              currentMillis - relay.buttonPushedMillis) > relay.turnOnDelay)
      {
        outputManager.toggleRoller(
            output,
            relay);

        send(
            message.set(
                relay.relayState));

        relay.ledTurnedOnAt = currentMillis;
        relay.ROLReady = false;
      }
    }

    if (!relay.relayState)
    {
      if (
          static_cast<unsigned long>(
              currentMillis - relay.ledTurnedOnAt) >= relay.turnOffDelay)
      {
        outputManager.toggleRoller(
            output,
            relay);

        send(
            message.set(
                relay.relayState));
      }
    }
  }
};
