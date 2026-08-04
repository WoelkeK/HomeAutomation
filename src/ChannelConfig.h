#pragma once

// Sterownik_Master_090726 v2.0.1: konfiguracja kanałów w jednym miejscu.
// Wejścia pozostają na MCP23017, rolety zostają na lokalnych wyjściach Mega.
// Wszystkie światła korzystają z LightMapping.h i są kierowane na Waveshare Modbus RTU 32CH.

enum class ChannelKind : byte
{
  Light,
  RollerUp,
  RollerDown
};

enum class InputDevice : byte
{
  MCP1,
  MCP2,
  MCP3
};

struct LightChannelConfig
{
  LightId id;
  byte sensorId;
  int relayPin;
  int buttonPin;
  InputDevice buttonDevice;
  OutputAddress output;
};

struct RollerChannelConfig
{
  byte sensorId;
  int relayPin;
  int buttonPin;
  InputDevice buttonDevice;
  OutputAddress output;
  unsigned long turnOffDelay;
};

const LightChannelConfig LIGHT_CHANNELS[noRelays1] = {
  {LightId::Garderoba, 0, 37, 13, InputDevice::MCP1, outputForLight(LightId::Garderoba)},
  {LightId::Sportowy, 1, 43, 12, InputDevice::MCP1, outputForLight(LightId::Sportowy)},
  {LightId::Gabinet, 2, 8, 11, InputDevice::MCP1, outputForLight(LightId::Gabinet)},
  {LightId::Rozdzielnia, 3, A14, 10, InputDevice::MCP1, outputForLight(LightId::Rozdzielnia)},
  {LightId::Lazienka, 4, 45, 8, InputDevice::MCP1, outputForLight(LightId::Lazienka)},
  {LightId::Garaz, 5, 34, 7, InputDevice::MCP1, outputForLight(LightId::Garaz)},
  {LightId::KuchniaOczka, 6, 35, 6, InputDevice::MCP1, outputForLight(LightId::KuchniaOczka)},
  {LightId::KuchniaSufit, 7, 46, 5, InputDevice::MCP1, outputForLight(LightId::KuchniaSufit)},
  {LightId::OswietlenieZewnetrzne1, 8, 49, 4, InputDevice::MCP1, outputForLight(LightId::OswietlenieZewnetrzne1)},
  {LightId::RezerwaPin7, 9, 7, 3, InputDevice::MCP1, outputForLight(LightId::RezerwaPin7)},
  {LightId::SalonStol, 10, A12, 2, InputDevice::MCP1, outputForLight(LightId::SalonStol)},
  {LightId::SalonScianaZegar, 11, 36, 1, InputDevice::MCP1, outputForLight(LightId::SalonScianaZegar)},
  {LightId::HolSpoty, 12, 47, 0, InputDevice::MCP1, outputForLight(LightId::HolSpoty)},
  {LightId::SalonSufitRGB, 13, 41, 15, InputDevice::MCP2, outputForLight(LightId::SalonSufitRGB)},
  {LightId::SalonOknoTvPlyta, 14, 40, 14, InputDevice::MCP2, outputForLight(LightId::SalonOknoTvPlyta)},
  {LightId::SalonOczka, 15, 39, 13, InputDevice::MCP2, outputForLight(LightId::SalonOczka)},
  {LightId::KorytarzSchodyRGB, 16, 42, 12, InputDevice::MCP2, outputForLight(LightId::KorytarzSchodyRGB)},
  {LightId::KorytarzHolSpot2x, 17, A13, 11, InputDevice::MCP2, outputForLight(LightId::KorytarzHolSpot2x)},
  {LightId::KorytarzOczkaSufit, 18, 44, 10, InputDevice::MCP2, outputForLight(LightId::KorytarzOczkaSufit)},
  {LightId::Kotlownia, 19, 38, 8, InputDevice::MCP2, outputForLight(LightId::Kotlownia)}
};

const RollerChannelConfig ROLLER_UP_CHANNELS[noRelays3] = {
  {0, 9, 15, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 9, 0, 0}, 30000},
  {1, 27, 12, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 27, 0, 0}, 30000},
  {2, 23, 10, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 23, 0, 0}, 30000},
  {3, 25, 8, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 25, 0, 0}, 30000},
  {4, 11, 7, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 11, 0, 0}, 30000},
  {5, 31, 2, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 31, 0, 0}, 30000},
  {6, 33, 1, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 33, 0, 0}, 30000}
};

const RollerChannelConfig ROLLER_DOWN_CHANNELS[noRelays4] = {
  {0, 10, 14, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 10, 0, 0}, 23000},
  {1, 26, 13, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 26, 0, 0}, 23000},
  {2, 22, 11, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 22, 0, 0}, 23000},
  {3, 24, 9, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 24, 0, 0}, 23000},
  {4, 12, 6, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 12, 0, 0}, 23000},
  {5, 30, 3, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 30, 0, 0}, 23000},
  {6, 32, 0, InputDevice::MCP3, {OutputBackend::MegaLocalPin, 32, 0, 0}, 23000}
};
