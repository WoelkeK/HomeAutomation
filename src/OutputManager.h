#pragma once
#include <Arduino.h>

#include "OutputConfig.h"
#include "RelayTypes.h"
#include "ChannelConfig.h"
#include "Config.h"
#include "StartupSafety.h"
#include "ModbusOutputDriver.h"
class OutputManager
{
  public:
    explicit OutputManager(ModbusOutputDriver& modbusRelayOutput)
      : modbusRelayOutput(modbusRelayOutput)
    {
    }

    void safeOff(const OutputConfig& output)
    {
      if (output.type == OutputType::MegaPin) {
        setPinSafeOff(output.megaPin);
      }
    }

    void safeOff(int pin)
    {
      setPinSafeOff(pin);
    }

    void writeLight(byte channelIndex, RelayChannel& relay, bool state)
    {
      relay.relayState = state;

      writeOutput(
        LIGHT_CHANNELS[channelIndex].output,
        relay.relayState ? RELAY_ON : RELAY_OFF
      );
    }

    // void writeRoller(TimedRelayChannel& relay, bool state)
    // {
    //   relay.relayState = state;

    //   digitalWrite(
    //     relay.relayPin,
    //     relay.relayState ? RELAY_OFF : RELAY_ON
    //   );
    // }

void writeRoller(
  const OutputConfig& output,
  TimedRelayChannel& relay,
  bool state
)
{
  relay.relayState = state;

  if (output.type == OutputType::MegaPin) {
    digitalWrite(
      output.megaPin,
      relay.relayState ? RELAY_OFF : RELAY_ON
    );
    return;
  }

  if (output.type == OutputType::ModbusRelay) {
    modbusRelayOutput.write(
      output.modbusSlaveId,
      output.modbusChannel,
      !relay.relayState
    );
  }
}


    void toggleLight(byte channelIndex, RelayChannel& relay)
    {
      writeLight(
        channelIndex,
        relay,
        !relay.relayState
      );
    }

    // void toggleRoller(TimedRelayChannel& relay)
    // {
    //   writeRoller(
    //     relay,
    //     !relay.relayState
    //   );
    // }

void toggleRoller(
  const OutputConfig& output,
  TimedRelayChannel& relay
)
{
  writeRoller(
    output,
    relay,
    !relay.relayState
  );
}

  private:
    ModbusOutputDriver& modbusRelayOutput;
   
    void writeOutput(
      const OutputConfig& output,
      int physicalState
    )
    {
      switch (output.type) {

        case OutputType::MegaPin:
          digitalWrite(
            output.megaPin,
            physicalState
          );
          break;

        case OutputType::ModbusRelay:
          modbusRelayOutput.write(
            output.modbusSlaveId,
            output.modbusChannel,
            physicalState == RELAY_ON
          );
          break;
      }
    }
};
