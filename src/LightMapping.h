#pragma once

// Sterownik_Master_090726 v2.0.1
// Jedyny plik, w którym definiujemy fizyczne przypisanie świateł do modułu Waveshare.
// Zmiana kolejności przewodów w rozdzielni wymaga zmiany tylko poniższej tabeli.
//
// Uwaga:
// - sensorId MySensors nadal wynika z kolejności LightId i pozostaje bez zmian,
// - rolety nie korzystają z tej tabeli i nadal zostają na lokalnych wyjściach Mega,
// - kanały Waveshare są numerowane 1..32.

struct LightOutputMapping
{
  LightId id;
  byte slaveId;
  byte relayChannel;
};

const LightOutputMapping LIGHT_OUTPUT_MAP[noRelays1] = {
  {LightId::Kotlownia,              WAVESHARE_RELAY_SLAVE_ID,  10},
  {LightId::Garaz,                  WAVESHARE_RELAY_SLAVE_ID,  22},
  {LightId::Lazienka,               WAVESHARE_RELAY_SLAVE_ID,  9},
  {LightId::Garderoba,              WAVESHARE_RELAY_SLAVE_ID,  14},
  {LightId::Sportowy,               WAVESHARE_RELAY_SLAVE_ID,  5},
  {LightId::Gabinet,                WAVESHARE_RELAY_SLAVE_ID,  26},
  {LightId::Rozdzielnia,            WAVESHARE_RELAY_SLAVE_ID,  24},
  {LightId::KuchniaOczka,           WAVESHARE_RELAY_SLAVE_ID,  18},
  {LightId::KuchniaSufit,           WAVESHARE_RELAY_SLAVE_ID,  13},
  {LightId::OswietlenieZewnetrzne1, WAVESHARE_RELAY_SLAVE_ID, 19},
  {LightId::SalonStol,              WAVESHARE_RELAY_SLAVE_ID, 25},
  {LightId::SalonScianaZegar,       WAVESHARE_RELAY_SLAVE_ID, 16},
  {LightId::HolSpoty,               WAVESHARE_RELAY_SLAVE_ID, 15},
  {LightId::SalonSufitRGB,          WAVESHARE_RELAY_SLAVE_ID, 2},
  {LightId::SalonOknoTvPlyta,       WAVESHARE_RELAY_SLAVE_ID, 6},
  {LightId::SalonOczka,             WAVESHARE_RELAY_SLAVE_ID, 8},
  {LightId::KorytarzSchodyRGB,      WAVESHARE_RELAY_SLAVE_ID, 1},
  {LightId::KorytarzOczkaSufit,     WAVESHARE_RELAY_SLAVE_ID, 7},
  {LightId::KorytarzHolSpot2x,      WAVESHARE_RELAY_SLAVE_ID, 23},
  {LightId::RezerwaPin7,            WAVESHARE_RELAY_SLAVE_ID, 20  }
};

inline OutputAddress modbusOutputAddress(byte slaveId, byte relayChannel)
{
  return {OutputBackend::ModbusRelay32CH, -1, slaveId, relayChannel};
}

inline OutputAddress outputForLight(LightId id)
{
  for (byte i = 0; i < noRelays1; i++) {
    if (LIGHT_OUTPUT_MAP[i].id == id) {
      return modbusOutputAddress(LIGHT_OUTPUT_MAP[i].slaveId, LIGHT_OUTPUT_MAP[i].relayChannel);
    }
  }

  // Fallback bezpieczeństwa: nie powinien wystąpić, ale w razie błędu mapowania
  // nie sterujemy żadnym fizycznym lokalnym pinem.
  return modbusOutputAddress(WAVESHARE_RELAY_SLAVE_ID, 1);
}
