#pragma once

#include "Config.h"
#include "HouseConfig.h"
#include "ChannelTypes.h"
#include "OutputConfig.h"

const LightChannelConfig LIGHT_CHANNELS[LIGHT_COUNT] = {
    {LightId::Archiwum,

     13,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 14}},
    {LightId::Biuro,

     12,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 5}},
    {LightId::Sportowy,

     11,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 26}},
    {LightId::Rozdzielnia,

     10,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 24}},
    {LightId::Lazienka,

     8,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 9}},
    {LightId::Garaz,

     7,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 22}},
    {LightId::KuchniaOczka,

     6,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 18}},
    {LightId::KuchniaSufit,

     5,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 13}},
    {LightId::Oswietlenie_Zew_Trojkat,

     4,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 19}},
    {LightId::RezerwaPin7,

     3,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 16}},

    {LightId::SalonStol,

     2,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 25}},
    {LightId::Wykusz,

     1,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 20}},
    {LightId::HolSpoty,

     0,
     InputDevice::MCP1,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 15}},

    {LightId::SalonSufitRGB,

     15,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 2}},
    {LightId::SalonOknoTvPlyta,

     14,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 6}},
    {LightId::SalonOczka,

     13,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 8}},
    {LightId::KorytarzSchodyRGB,

     12,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 1}},
    {LightId::KorytarzHolSpot2x,

     11,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 23}},
    {LightId::KorytarzOczkaSufit,

     10,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 7}},
    {LightId::Kotlownia,

     8,
     InputDevice::MCP2,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 10}},

    {LightId::HolRGB,

     -1,
     InputDevice::None,
     {OutputType::ModbusRelay, 0, HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID, 17}},
};
