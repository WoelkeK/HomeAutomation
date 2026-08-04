#pragma once

extern ModbusMaster modbusMaster;
extern WaveshareRelay32CH waveshare32ch;

class ModbusTestConsole
{
  public:
    void update()
    {
#if ENABLE_WAVESHARE_MODBUS && ENABLE_WAVESHARE_SERIAL_TEST
      while (Serial.available()) {
        char c = Serial.read();
        if (c == '\r') {
          continue;
        }
        if (c == '\n') {
          _buffer[_index] = '\0';
          handleCommand(_buffer);
          _index = 0;
        } else if (_index < sizeof(_buffer) - 1) {
          _buffer[_index++] = c;
        }
      }
#endif
    }

  private:
    char _buffer[24];
    byte _index = 0;

#if ENABLE_WAVESHARE_MODBUS && ENABLE_WAVESHARE_SERIAL_TEST
    void handleCommand(const char* cmd)
    {
      if (equals(cmd, "m1on")) {
        printResult("m1on", waveshare32ch.writeChannel(1, true));
      } else if (equals(cmd, "m1off")) {
        printResult("m1off", waveshare32ch.writeChannel(1, false));
      } else if (equals(cmd, "malloff")) {
        printResult("malloff", waveshare32ch.allOff());
      } else if (equals(cmd, "mread")) {
        printReadAll();
      } else if (equals(cmd, "mdiag")) {
        printDiagnostics();
      } else if (cmd[0] == 'm' && cmd[1] >= '1' && cmd[1] <= '9') {
        handleRelayCommand(cmd);
      } else if (cmd[0] != '\0') {
        Serial.print(F("Unknown Modbus command: "));
        Serial.println(cmd);
        Serial.println(F("Commands: m1on, m1off, m2on..m32off, malloff, mread, mdiag"));
      }
    }

    bool equals(const char* a, const char* b)
    {
      while (*a && *b) {
        if (*a++ != *b++) return false;
      }
      return *a == '\0' && *b == '\0';
    }

    void handleRelayCommand(const char* cmd)
    {
      byte pos = 1;
      int channel = 0;
      while (cmd[pos] >= '0' && cmd[pos] <= '9') {
        channel = channel * 10 + (cmd[pos] - '0');
        pos++;
      }

      if (channel < 1 || channel > 32) {
        Serial.println(F("Invalid relay channel. Use 1..32."));
        return;
      }

      if (equals(cmd + pos, "on")) {
        bool ok = waveshare32ch.writeChannel((byte)channel, true);
        printResult(cmd, ok);
      } else if (equals(cmd + pos, "off")) {
        bool ok = waveshare32ch.writeChannel((byte)channel, false);
        printResult(cmd, ok);
      } else {
        Serial.println(F("Invalid command. Example: m12on or m12off."));
      }
    }

    void printResult(const char* cmd, bool ok)
    {
      Serial.print(F("Modbus command "));
      Serial.print(cmd);
      Serial.print(F(" -> "));
      Serial.println(ok ? F("OK") : F("FAIL"));
      if (!ok) {
        Serial.print(F("Error: "));
        Serial.println(waveshare32ch.lastErrorText());
      }
    }

    void printReadAll()
    {
      uint32_t mask = 0;
      bool ok = waveshare32ch.readAll(mask);
      Serial.print(F("Waveshare readAll -> "));
      Serial.println(ok ? F("OK") : F("FAIL"));
      if (ok) {
        Serial.print(F("Mask HEX: 0x"));
        Serial.println(mask, HEX);
      } else {
        Serial.print(F("Error: "));
        Serial.println(waveshare32ch.lastErrorText());
      }
    }

    void printDiagnostics()
    {
      Serial.println(F("===== MODBUS DIAG ====="));
      Serial.print(F("Ready: "));
      Serial.println(modbusMaster.isReady() ? F("YES") : F("NO"));
      Serial.print(F("TX: "));
      Serial.println(modbusMaster.txFrames());
      Serial.print(F("RX: "));
      Serial.println(modbusMaster.rxFrames());
      Serial.print(F("Timeouts: "));
      Serial.println(modbusMaster.timeouts());
      Serial.print(F("CRC errors: "));
      Serial.println(modbusMaster.crcErrors());
      Serial.print(F("Errors: "));
      Serial.println(modbusMaster.errors());
      Serial.print(F("Last error: "));
      Serial.println(modbusMaster.lastErrorText());
    }
#endif
};
