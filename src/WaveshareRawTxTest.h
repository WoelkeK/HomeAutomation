#pragma once

// Bardzo prosty test sprzętowy Modbus TX.
// Nie używa ModbusMaster, nie czeka na odpowiedź i nie blokuje loop().
// Cel: sprawdzić, czy Arduino Mega wysyła coś na Serial1 i czy przekaźnik 1 klika.
class WaveshareRawTxTest
{
  public:
    void begin()
    {
#if ENABLE_WAVESHARE_RAW_TX_TEST
      MODBUS_RTU_SERIAL.begin(MODBUS_RTU_BAUD_RATE);
      _enabled = true;
      _lastToggle = millis();
      _state = false;
      Serial.println(F("Waveshare RAW TX test enabled: relay 1 ON/OFF without response wait."));
#endif
    }

    void update()
    {
#if ENABLE_WAVESHARE_RAW_TX_TEST
      if (!_enabled) {
        return;
      }

      const unsigned long now = millis();
      if (now - _lastToggle < WAVESHARE_RAW_TEST_INTERVAL_MS) {
        return;
      }
      _lastToggle = now;
      _state = !_state;

      if (_state) {
        sendFrame(_relay1On, sizeof(_relay1On));
        Serial.println(F("RAW Modbus: relay 1 ON frame sent"));
      } else {
        sendFrame(_relay1Off, sizeof(_relay1Off));
        Serial.println(F("RAW Modbus: relay 1 OFF frame sent"));
      }
#endif
    }

  private:
    bool _enabled = false;
    bool _state = false;
    unsigned long _lastToggle = 0;

    // Slave 1, function 05, coil 0, ON/OFF, CRC zgodne z Waveshare 32CH.
    const byte _relay1On[8]  = {0x01, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A};
    const byte _relay1Off[8] = {0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA};

    void sendFrame(const byte* frame, byte length)
    {
      MODBUS_RTU_SERIAL.write(frame, length);
      MODBUS_RTU_SERIAL.flush();
    }
};
