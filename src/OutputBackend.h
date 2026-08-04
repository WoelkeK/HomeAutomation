#pragma once

// Etap 5: rozdzielenie fizycznego sposobu sterowania wyjściem.
// Docelowo światła będą mogły być stopniowo przenoszone z lokalnych pinów Mega
// na moduły przekaźnikowe Modbus RTU, bez zmiany logiki LightingController.

enum class OutputBackend : byte
{
  MegaLocalPin,
  ModbusRelay32CH
};

struct OutputAddress
{
  OutputBackend backend;
  int megaPin;
  byte modbusSlaveId;
  byte modbusChannel;
};
