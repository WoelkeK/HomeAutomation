#pragma once

#include "Config.h"
#include "HouseConfig.h"
#include "ChannelTypes.h"
#include "OutputConfig.h"

const LightChannelConfig LIGHT_CHANNELS[noRelays1] = {
  {
    LightId::Garderoba,
    0,
    13,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 14}
  },
  {
    LightId::Sportowy,
    1,
    12,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 5}
  },
  {
    LightId::Gabinet,
    2,
    11,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 26}
  },
  {
    LightId::Rozdzielnia,
    3,
    10,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 24}
  },
  {
    LightId::Lazienka,
    4,
    8,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 9}
  },
  {
    LightId::Garaz,
    5,
    7,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 22}
  },
  {
    LightId::KuchniaOczka,
    6,
    6,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 18}
  },
  {
    LightId::KuchniaSufit,
    7,
    5,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 13}
  },
  {
    LightId::OswietlenieZewnetrzne1,
    8,
    4,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 19}
  },
  {
    LightId::RezerwaPin7,
    9,
    3,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 20}
  },
  {
    LightId::SalonStol,
    10,
    2,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 25}
  },
  {
    LightId::SalonScianaZegar,
    11,
    1,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 16}
  },
  {
    LightId::HolSpoty,
    12,
    0,
    InputDevice::MCP1,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 15}
  },
  {
    LightId::SalonSufitRGB,
    13,
    15,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 2}
  },
  {
    LightId::SalonOknoTvPlyta,
    14,
    14,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 6}
  },
  {
    LightId::SalonOczka,
    15,
    13,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 8}
  },
  {
    LightId::KorytarzSchodyRGB,
    16,
    12,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 1}
  },
  {
    LightId::KorytarzHolSpot2x,
    17,
    11,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 23}
  },
  {
    LightId::KorytarzOczkaSufit,
    18,
    10,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 7}
  },
  {
    LightId::Kotlownia,
    19,
    8,
    InputDevice::MCP2,
    {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 10}
  }
};
