
#pragma once

#include "Config.h"
#include "HouseConfig.h"
#include "ChannelTypes.h"

const RollerChannelConfig ROLLER_UP_CHANNELS[noRelays3] = {
  {0, 15, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 1}, 30000},
  {1, 12, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 3}, 30000},
  {2, 10, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 5}, 30000},
  {3, 8, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 7}, 30000},
  {4, 7, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 9}, 30000},
  {5, 2, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 11}, 30000},
  {6, 1, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 13}, 30000}
};

const RollerChannelConfig ROLLER_DOWN_CHANNELS[noRelays4] = {
  {0, 14, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 2}, 23000},
  {1, 13, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 4}, 23000},
  {2, 11, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 6}, 23000},
  {3, 9, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 8}, 23000},
  {4, 6, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 10}, 23000},
  {5, 3, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 12}, 23000},
  {6, 0, InputDevice::MCP3, {OutputType::ModbusRelay, 0, HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID, 14}, 23000}
};
