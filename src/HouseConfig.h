#pragma once

#include <Arduino.h>

// Centralna konfiguracja sprzętowa domu.
namespace HouseConfig
{
  namespace Modbus
  {
    constexpr byte LIGHT_RELAY_SLAVE_ID = 1;
    constexpr byte SDM630_SLAVE_ID = 2;
    constexpr byte SPRINKLER_RELAY_SLAVE_ID = 3;
    constexpr byte ROLLER_RELAY_SLAVE_ID = 4;

    constexpr unsigned long BAUD_RATE = 9600;

    constexpr byte LIGHT_RELAY_CHANNEL_COUNT = 32;
    constexpr byte ROLLER_RELAY_CHANNEL_COUNT = 16;
  }
}
