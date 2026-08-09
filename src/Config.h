#pragma once
# include <Arduino.h>

// Nazwa i wersja firmware są zdefiniowane centralnie w Version.h.

// Czujnik światła
#define LIGHT_SENSOR_ANALOG_PIN A0

// Ustawienie polaryzacji dla przekaźników ACTIVE LOW / ACTIVE HIGH
#define RELAY_ON 0
#define RELAY_OFF 1

// Liczba kanałów
#define noRelays1 20
#define noRelays3 7
#define noRelays4 7

// Adresy MCP23017
const byte addr1 = 0x00; // uwaga: zamieniony adres z 3
const byte addr2 = 0x01;
const byte addr3 = 0x03;

const int numReadings = 100;

// Bezpieczny start przekaźników
// 0 = po starcie wszystkie światła lokalne pozostają OFF, niezależnie od EEPROM.
// 1 = po starcie światła wracają do ostatniego stanu zapisanego w EEPROM.
#define RESTORE_LIGHTS_FROM_EEPROM_ON_BOOT 0

// Modbus RTU Master - osobna magistrala dla urządzeń Modbus.
// Serial2 pozostaje dla sieci MySensors RS485.
// Modbus pozostaje na Serial1: TX1=18, RX1=19.
// MySensors korzysta z AUTO_DIRECTION i nie używa pinu DE.
// 0 = Modbus nie jest inicjalizowany i żaden kanał go nie używa.
// 1 = inicjalizacja magistrali Modbus oraz sterownika Waveshare.
#define ENABLE_WAVESHARE_MODBUS 1
#define MODBUS_RTU_SERIAL Serial1
#define MODBUS_RTU_BAUD_RATE HouseConfig::Modbus::BAUD_RATE
#define MODBUS_RTU_TIMEOUT_MS HouseConfig::Modbus::TIMEOUT_MS
#define MODBUS_RTU_RETRIES HouseConfig::Modbus::RETRIES

// Kierunek nadajnika RS485 dla magistrali Modbus.
// 0 = konwerter z automatycznym kierunkiem transmisji albo ręcznie spięte DE/RE.
// 1 = klasyczny MAX485 z pinem DE/RE sterowanym z Arduino.
#define MODBUS_RTU_USE_DE_PIN 0
#define MODBUS_RTU_DE_PIN HouseConfig::Modbus::DE_PIN

// Tryb testowy przez Serial Monitor.
// Działa tylko, gdy ENABLE_WAVESHARE_MODBUS = 1.
// Komendy: m1on, m1off, malloff, mread, mdiag
// W Etapie 10C komendy zapisu są TX-only, czyli nie czekają na odpowiedź i nie blokują MySensors.
#define ENABLE_WAVESHARE_SERIAL_TEST 0

// Najbezpieczniejszy test TX dla Waveshare.
// 1 = co kilka sekund wysyła surową ramkę 0x05 ON/OFF na przekaźnik 1 po Serial1,
//     bez czekania na odpowiedź. Dzięki temu nie blokuje MySensors/OpenHAB.
// 0 = wyłączony.
#define ENABLE_WAVESHARE_RAW_TX_TEST 0
#define WAVESHARE_RAW_TEST_INTERVAL_MS 2000

// Waveshare RTU Modbus Relay Module 32CH
#define WAVESHARE_DEFAULT_SLAVE_ID HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID

// Rezerwacja pod przyszły licznik energii SDM630 na tej samej magistrali.
#define ENABLE_SDM630_METER 0
#define SDM630_DEFAULT_SLAVE_ID HouseConfig::Modbus::SDM630_SLAVE_ID


// Etap 10C: bezpieczny test drivera WaveshareRelay32CH.
// Działa tylko, gdy ENABLE_WAVESHARE_MODBUS = 1.
// 1 = co kilka sekund przełącza wybrany kanał przez klasę WaveshareRelay32CH,
//     bez oczekiwania na odpowiedź Modbus.
#define ENABLE_WAVESHARE_SAFE_DRIVER_TEST 0
#define WAVESHARE_SAFE_DRIVER_TEST_CHANNEL 1
#define WAVESHARE_SAFE_DRIVER_TEST_INTERVAL_MS 2000

// Waveshare RTU Modbus Relay Module 8CH - spryskiwacze.
// Harmonogram i czasy normalnej pracy pozostają w OpenHAB.
#define ENABLE_SPRINKLER_MODULE 1
#define SPRINKLER_RELAY_SLAVE_ID HouseConfig::Modbus::SPRINKLER_RELAY_SLAVE_ID
#define SPRINKLER_ZONE_COUNT ChildId::SPRINKLER_COUNT
#define SPRINKLER_ALLOW_MULTIPLE_ZONES 0
#define SPRINKLER_MAX_RUNTIME_MS (45UL * 60UL * 1000UL)
