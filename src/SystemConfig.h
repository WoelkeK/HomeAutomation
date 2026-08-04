#pragma once

#include "HouseConfig.h"

// Aliasy zgodności dla istniejącego kodu i testów.
constexpr byte WAVESHARE_RELAY_SLAVE_ID = HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID;
constexpr byte SDM630_METER_SLAVE_ID = HouseConfig::Modbus::SDM630_SLAVE_ID;
constexpr byte DEYE_INVERTER_SLAVE_ID = 3;

constexpr byte WAVESHARE_RELAY_CHANNEL_MIN = HouseConfig::Modbus::LIGHT_RELAY_CHANNEL_MIN;
constexpr byte WAVESHARE_RELAY_CHANNEL_MAX = HouseConfig::Modbus::LIGHT_RELAY_CHANNEL_MAX;
