#pragma once

extern RelayChannel Relays1[noRelays1];

class RelayManager
{
  public:
    explicit RelayManager(ModbusRelayOutputDriver& modbusRelayOutput)
      : modbusRelayOutput(modbusRelayOutput)
    {
    }

    void safeOff(const OutputAddress& output)
    {
      if (output.backend == OutputBackend::MegaLocalPin) {
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

    void writeLight(LightId id, bool state)
    {
      byte index = lightIndex(id);

      if (index >= noRelays1) {
        return;
      }

      writeLight(index, Relays1[index], state);
    }

    void toggleLight(LightId id)
    {
      byte index = lightIndex(id);

      if (index >= noRelays1) {
        return;
      }

      toggleLight(index, Relays1[index]);
    }

    void writeLight(RelayChannel& relay, bool state)
    {
      relay.relayState = state;

      digitalWrite(
        relay.relayPin,
        relay.relayState ? RELAY_ON : RELAY_OFF
      );
    }

    void writeRoller(TimedRelayChannel& relay, bool state)
    {
      relay.relayState = state;

      digitalWrite(
        relay.relayPin,
        relay.relayState ? RELAY_OFF : RELAY_ON
      );
    }

    void toggleLight(byte channelIndex, RelayChannel& relay)
    {
      writeLight(
        channelIndex,
        relay,
        !relay.relayState
      );
    }

    void toggleLight(RelayChannel& relay)
    {
      writeLight(
        relay,
        !relay.relayState
      );
    }

    void toggleRoller(TimedRelayChannel& relay)
    {
      writeRoller(
        relay,
        !relay.relayState
      );
    }

  private:
    ModbusRelayOutputDriver& modbusRelayOutput;

    void writeOutput(
      const OutputAddress& output,
      int physicalState
    )
    {
      switch (output.backend) {

        case OutputBackend::MegaLocalPin:
          digitalWrite(
            output.megaPin,
            physicalState
          );
          break;

        case OutputBackend::ModbusRelay32CH:
          modbusRelayOutput.write(
            output.modbusSlaveId,
            output.modbusChannel,
            physicalState == RELAY_ON
          );
          break;
      }
    }
};
