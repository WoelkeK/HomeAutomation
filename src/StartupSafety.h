#pragma once

// Ustawia lokalne piny przekaźników w stan bezpieczny jak najwcześniej po starcie.
// Dla przekaźników ACTIVE LOW stan OFF = HIGH.
// Ważne: digitalWrite(RELAY_OFF) przed pinMode(OUTPUT) zapobiega krótkiemu impulsowi LOW.
inline void setPinSafeOff(int pin)
{
  digitalWrite(pin, RELAY_OFF);
  pinMode(pin, OUTPUT);
}

inline void prepareLocalRelayPinsSafeOff()
{
  for (int i = 0; i < noRelays1; i++) {
    if (LIGHT_CHANNELS[i].output.backend == OutputBackend::MegaLocalPin) {
      setPinSafeOff(LIGHT_CHANNELS[i].output.megaPin);
    }
  }

  for (int i = 0; i < noRelays3; i++) {
    setPinSafeOff(relayPin3[i]);
  }

  for (int i = 0; i < noRelays4; i++) {
    setPinSafeOff(relayPin4[i]);
  }
}
