#pragma once

#include "ModbusManager.h"

// Uniwersalny, nieblokujący sterownik modułów przekaźnikowych Modbus RTU.
// Używa sprawdzonego trybu TX-only i funkcji 0x05 (Write Single Coil).
class ModbusRelayDevice
{
  public:
    enum Error : byte
    {
      OK = 0,
      NotReady = 1,
      InvalidChannel = 2
    };

    ModbusRelayDevice()
      : _bus(nullptr), _slaveId(1), _channelCount(0), _lastError(NotReady), _txFrames(0) {}

    void begin(ModbusManager& bus, byte slaveId, byte channelCount)
    {
      _bus = &bus;
      _slaveId = slaveId;
      _channelCount = channelCount;
      _lastError = isReady() ? OK : NotReady;
    }

    bool isReady() const
    {
      return _bus != nullptr && _bus->isReady() && _channelCount > 0;
    }

    byte slaveId() const { return _slaveId; }
    byte channelCount() const { return _channelCount; }
    byte lastError() const { return _lastError; }
    unsigned long txFrames() const { return _txFrames; }

    bool writeChannel(byte channel, bool state)
    {
      if (!validateChannel(channel)) {
        return false;
      }

      const uint16_t coilAddress = channel - 1;
      const uint16_t value = state ? 0xFF00 : 0x0000;

      if (!_bus->writeSingleCoilTxOnly(_slaveId, coilAddress, value)) {
        _lastError = NotReady;
        return false;
      }

      _txFrames++;
      _lastError = OK;
      return true;
    }

    bool allOff()
    {
      if (!isReady()) {
        _lastError = NotReady;
        return false;
      }

      bool result = true;
      for (byte channel = 1; channel <= _channelCount; channel++) {
        result = writeChannel(channel, false) && result;
      }
      return result;
    }

  private:
    ModbusManager* _bus;
    byte _slaveId;
    byte _channelCount;
    byte _lastError;
    unsigned long _txFrames;

    bool validateChannel(byte channel)
    {
      if (!isReady()) {
        _lastError = NotReady;
        return false;
      }
      if (channel < 1 || channel > _channelCount) {
        _lastError = InvalidChannel;
        return false;
      }
      return true;
    }
};
