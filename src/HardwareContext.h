#pragma once

#include "ModbusManager.h"
#include "ModbusMaster.h"
#include "WaveshareRelay32CH.h"
#include "ModbusRelayDevice.h"
#include "ModbusOutputDriver.h"
#include "SDM630Meter.h"

class HardwareContext
{
  public:
    ModbusManager modbusManager;
    ModbusMaster modbusMaster;

    WaveshareRelay32CH lightRelay32;
    ModbusRelayDevice rollerRelay16;
    ModbusRelayDevice sprinklerRelay8;

    SDM630Meter sdm630Meter;
    ModbusOutputDriver outputDriver;
};
