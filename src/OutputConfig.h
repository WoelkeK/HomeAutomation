#pragma once
#include <Arduino.h>

// Konfiguracja fizycznego sposobu sterowania wyjściem.
// Wyjście może być lokalnym pinem Mega albo przekaźnikiem Modbus RTU.

enum class OutputType : byte
{
  MegaPin,
  ModbusRelay
};

struct OutputConfig
{
  OutputType type;
  int megaPin;
  byte modbusSlaveId;
  byte modbusChannel;
};
