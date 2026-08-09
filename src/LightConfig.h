#pragma once

#include "Config.h"
#include "ChannelTypes.h"
#include "LightMapping.h"

const LightChannelConfig LIGHT_CHANNELS[noRelays1] = {
  {LightId::Garderoba, 0, 13, InputDevice::MCP1, outputForLight(LightId::Garderoba)},
  {LightId::Sportowy, 1, 12, InputDevice::MCP1, outputForLight(LightId::Sportowy)},
  {LightId::Gabinet, 2, 11, InputDevice::MCP1, outputForLight(LightId::Gabinet)},
  {LightId::Rozdzielnia, 3, 10, InputDevice::MCP1, outputForLight(LightId::Rozdzielnia)},
  {LightId::Lazienka, 4, 8, InputDevice::MCP1, outputForLight(LightId::Lazienka)},
  {LightId::Garaz, 5, 7, InputDevice::MCP1, outputForLight(LightId::Garaz)},
  {LightId::KuchniaOczka, 6, 6, InputDevice::MCP1, outputForLight(LightId::KuchniaOczka)},
  {LightId::KuchniaSufit, 7, 5, InputDevice::MCP1, outputForLight(LightId::KuchniaSufit)},
  {LightId::OswietlenieZewnetrzne1, 8, 4, InputDevice::MCP1, outputForLight(LightId::OswietlenieZewnetrzne1)},
  {LightId::RezerwaPin7, 9, 3, InputDevice::MCP1, outputForLight(LightId::RezerwaPin7)},
  {LightId::SalonStol, 10, 2, InputDevice::MCP1, outputForLight(LightId::SalonStol)},
  {LightId::SalonScianaZegar, 11, 1, InputDevice::MCP1, outputForLight(LightId::SalonScianaZegar)},
  {LightId::HolSpoty, 12, 0, InputDevice::MCP1, outputForLight(LightId::HolSpoty)},
  {LightId::SalonSufitRGB, 13, 15, InputDevice::MCP2, outputForLight(LightId::SalonSufitRGB)},
  {LightId::SalonOknoTvPlyta, 14, 14, InputDevice::MCP2, outputForLight(LightId::SalonOknoTvPlyta)},
  {LightId::SalonOczka, 15, 13, InputDevice::MCP2, outputForLight(LightId::SalonOczka)},
  {LightId::KorytarzSchodyRGB, 16, 12, InputDevice::MCP2, outputForLight(LightId::KorytarzSchodyRGB)},
  {LightId::KorytarzHolSpot2x, 17, 11, InputDevice::MCP2, outputForLight(LightId::KorytarzHolSpot2x)},
  {LightId::KorytarzOczkaSufit, 18, 10, InputDevice::MCP2, outputForLight(LightId::KorytarzOczkaSufit)},
  {LightId::Kotlownia, 19, 8, InputDevice::MCP2, outputForLight(LightId::Kotlownia)}
};
