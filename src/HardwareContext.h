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

    ModbusRelayDevice lightRelay32;
    ModbusRelayDevice rollerRelay16;
    ModbusRelayDevice sprinklerRelay8;

    SDM630Meter sdm630Meter;
    ModbusOutputDriver outputDriver;
};
