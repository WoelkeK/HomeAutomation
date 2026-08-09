#pragma once

#include <Arduino.h>
#include "ModbusRelayDevice.h"

class ModbusOutputDriver
{
  public:
    ModbusOutputDriver()
      : _lightModule(nullptr),
        _rollerModule(nullptr)
    {
    }

    void attachLightModule(ModbusRelayDevice& module)
    {
      _lightModule = &module;
    }

    void attachRollerModule(ModbusRelayDevice& module)
    {
      _rollerModule = &module;
    }

    bool write(
      byte slaveId,
      byte channel,
      bool state
    )
    {
      if (
        _lightModule != nullptr &&
        slaveId == _lightModule->slaveId()
      ) {
        return _lightModule->writeChannel(
          channel,
          state
        );
      }

      if (
        _rollerModule != nullptr &&
        slaveId == _rollerModule->slaveId()
      ) {
        return _rollerModule->writeChannel(
          channel,
          state
        );
      }

      return false;
    }

  private:
  ModbusRelayDevice* _lightModule;
  ModbusRelayDevice* _rollerModule;
};
extern ModbusOutputDriver modbusRelayOutput;
