#pragma once
#include <Arduino.h>

// Etap 5: rozdzielenie fizycznego sposobu sterowania wyjściem.
// Docelowo światła będą mogły być stopniowo przenoszone z lokalnych pinów Mega
// na moduły przekaźnikowe Modbus RTU, bez zmiany logiki LightingController.
// Zmiana nazewnictwa: OutputDriver -> OutputType, OutputDriverConfig -> OutputConfig, OutputDriverType -> OutputType.

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
