#pragma once
#include <Arduino.h>
// Czujnik światła
#define LIGHT_SENSOR_ANALOG_PIN A0

// Ustawienie polaryzacji dla przekaźników ACTIVE LOW / ACTIVE HIGH
#define RELAY_ON 0
#define RELAY_OFF 1

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

// Rezerwacja pod przyszły licznik energii SDM630 na tej samej magistrali.
#define ENABLE_SDM630_METER 0
#define SDM630_DEFAULT_SLAVE_ID HouseConfig::Modbus::SDM630_SLAVE_ID

// Waveshare RTU Modbus Relay Module 8CH - spryskiwacze.
// Harmonogram i czasy normalnej pracy pozostają w OpenHAB.
#define ENABLE_SPRINKLER_MODULE 1
#define SPRINKLER_ZONE_COUNT ChildId::SPRINKLER_COUNT
#define SPRINKLER_ALLOW_MULTIPLE_ZONES 0
#define SPRINKLER_MAX_RUNTIME_MS (45UL * 60UL * 1000UL)

// Waveshare RTU Modbus Relays Światła i rolety
#define LIGHT_COUNT 21
#define ROLLER_COUNT 8
