#pragma once

extern WaveshareRelay32CH waveshare32ch;

// Test klasy WaveshareRelay32CH bez blokowania pętli.
// W przeciwieństwie do starego ModbusMaster nie czeka na odpowiedź.
class WaveshareSafeDriverTest
{
  public:
    void begin()
    {
#if ENABLE_WAVESHARE_SAFE_DRIVER_TEST
      _enabled = true;
      _lastToggle = millis();
      _state = false;
      Serial.println(F("Waveshare safe driver test enabled: relay 1 ON/OFF, TX-only."));
#endif
    }

    void update()
    {
#if ENABLE_WAVESHARE_SAFE_DRIVER_TEST
      if (!_enabled) {
        return;
      }

      const unsigned long now = millis();
      if (now - _lastToggle < WAVESHARE_SAFE_DRIVER_TEST_INTERVAL_MS) {
        return;
      }

      _lastToggle = now;
      _state = !_state;

      if (waveshare32ch.writeChannel(WAVESHARE_SAFE_DRIVER_TEST_CHANNEL, _state)) {
        Serial.print(F("Waveshare safe driver: relay "));
        Serial.print(WAVESHARE_SAFE_DRIVER_TEST_CHANNEL);
        Serial.println(_state ? F(" ON") : F(" OFF"));
      } else {
        Serial.print(F("Waveshare safe driver error: "));
        Serial.println(waveshare32ch.lastErrorText());
      }
#endif
    }

  private:
    bool _enabled = false;
    bool _state = false;
    unsigned long _lastToggle = 0;
};
