#pragma once

#include "ModbusManager.h"

// Nieblokujący sterownik Waveshare RTU Modbus Relay Module 32CH.
// Wysyła polecenia przez wspólny ModbusManager w trybie TX-only.
class WaveshareRelay32CH
{
  public:
    enum Error : byte
    {
      OK = 0,
      NotReady = 1,
      InvalidChannel = 2,
      Unsupported = 3
    };

    WaveshareRelay32CH()
      : _bus(nullptr), _slaveId(1), _lastError(NotReady), _txFrames(0) {}

    void begin(ModbusManager& bus, byte slaveId)
    {
      _bus = &bus;
      _slaveId = slaveId;
      _lastError = bus.isReady() ? OK : NotReady;
    }

    bool isReady() const
    {
      return _bus != nullptr && _bus->isReady();
    }

    byte slaveId() const { return _slaveId; }
    byte lastError() const { return _lastError; }
    unsigned long txFrames() const { return _txFrames; }

    const char* lastErrorText() const
    {
      switch (_lastError) {
        case OK: return "OK";
        case NotReady: return "Not ready";
        case InvalidChannel: return "Invalid channel";
        case Unsupported: return "Unsupported in non-blocking TX-only mode";
        default: return "Unknown";
      }
    }

    bool writeChannel(byte channel, bool state)
    {
      if (!validateChannel(channel)) {
        return false;
      }

      const uint16_t coilAddress = channel - 1;
      const uint16_t value = state ? 0xFF00 : 0x0000;
      return send(coilAddress, value);
    }

    bool toggleChannel(byte channel)
    {
      if (!validateChannel(channel)) {
        return false;
      }

      return send(channel - 1, 0x5500);
    }

    bool allOff()
    {
      if (!isReady()) {
        _lastError = NotReady;
        return false;
      }

      for (byte channel = 1; channel <= 32; channel++) {
        if (!writeChannel(channel, false)) {
          return false;
        }
      }
      return true;
    }

    bool writeAll(uint32_t stateMask)
    {
      if (!isReady()) {
        _lastError = NotReady;
        return false;
      }

      for (byte channel = 1; channel <= 32; channel++) {
        const bool state = (stateMask & (1UL << (channel - 1))) != 0;
        if (!writeChannel(channel, state)) {
          return false;
        }
      }
      return true;
    }

    bool readAll(uint32_t& stateMask)
    {
      stateMask = 0;
      _lastError = Unsupported;
      return false;
    }

    bool readChannel(byte channel, bool& state)
    {
      state = false;
      _lastError = (channel < 1 || channel > 32) ? InvalidChannel : Unsupported;
      return false;
    }

  private:
    ModbusManager* _bus;
    byte _slaveId;
    byte _lastError;
    unsigned long _txFrames;

    bool validateChannel(byte channel)
    {
      if (!isReady()) {
        _lastError = NotReady;
        return false;
      }
      if (channel < 1 || channel > 32) {
        _lastError = InvalidChannel;
        return false;
      }
      return true;
    }

    bool send(uint16_t coilAddress, uint16_t value)
    {
      if (!_bus->writeSingleCoilTxOnly(_slaveId, coilAddress, value)) {
        _lastError = NotReady;
        return false;
      }
      _txFrames++;
      _lastError = OK;
      return true;
    }
};
