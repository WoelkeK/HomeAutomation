#pragma once

//Obecnie nie jest jeszcze używany przez logikę domu.

class SDM630Meter
{
  public:
    SDM630Meter() : _bus(nullptr), _slaveId(2), _lastError(ModbusMaster::NotReady) {}

    void begin(ModbusMaster& bus, byte slaveId)
    {
      _bus = &bus;
      _slaveId = slaveId;
      _lastError = ModbusMaster::OK;
    }

    bool isReady() const
    {
      return _bus != nullptr && _bus->isReady();
    }

    byte lastError() const
    {
      return _lastError;
    }

    // Placeholder: SDM630 zwykle zwraca wartości jako 32-bit float w dwóch rejestrach.
    bool readHoldingRegisters(uint16_t startAddress, uint16_t quantity, uint16_t* registers, byte registerCapacity, byte& registersRead)
    {
      if (!isReady()) {
        _lastError = ModbusMaster::NotReady;
        return false;
      }

      const bool ok = _bus->readHoldingRegisters(_slaveId, startAddress, quantity, registers, registerCapacity, registersRead);
      _lastError = _bus->lastError();
      return ok;
    }

  private:
    ModbusMaster* _bus;
    byte _slaveId;
    byte _lastError;
};
