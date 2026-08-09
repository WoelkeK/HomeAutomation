#pragma once

#include "ModbusManager.h"
#include "ModbusMaster.h"
#include "ModbusRelayDevice.h"
#include "ModbusOutputDriver.h"
#include "SDM630Meter.h"

class HardwareContext
{
  public:
    ModbusManager modbusManager;
    ModbusMaster modbusMaster;

    ModbusRelayDevice lightRelayModule;
    ModbusRelayDevice rollerRelayModule    ;
    ModbusRelayDevice sprinklerRelayModule;

    SDM630Meter sdm630Meter;
    ModbusOutputDriver outputDriver;
};
