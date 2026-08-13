#pragma once

#include "Config.h"
#include "HouseConfig.h"
#include "ChannelTypes.h"

// sensor, przycisk góra, przycisk dół, MCP, wyjście góra, wyjście dół, czas góra, czas dół

const RollerConfig ROLLERS[ROLLER_COUNT] = {
    // Biuro
    {0, 14, 15, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 3}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 4}, 30000, 23000},
    // Roleta Prawa
    {1, 12, 13, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 1}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 2}, 30000, 23000},
    // Salon Środek
    {2, 10, 11, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 7}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 8}, 30000, 23000},
    // Salon okno lewe
    {3, 8, 9, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 5}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 6}, 30000, 23000},
    // salon wykusz
    {4, 7, 6, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 11}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 12}, 30000, 23000},
    // łazienka
    {5, 5, 4, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 9}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 10}, 30000, 23000},
    // kuchnia
    {6, 3, 2, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 13}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 14}, 30000, 23000},
    // Siłownia
    {7, 1, 0, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 15}, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 16}, 30000, 23000}};
