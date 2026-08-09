#pragma once

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
    constexpr unsigned long TIMEOUT_MS = 250;
    constexpr byte RETRIES = 2;
    constexpr byte DE_PIN = 6;

    constexpr byte LIGHT_RELAY_CHANNEL_MIN = 1;
    constexpr byte LIGHT_RELAY_CHANNEL_MAX = 32;
    constexpr byte SPRINKLER_RELAY_CHANNEL_MIN = 1;
    constexpr byte SPRINKLER_RELAY_CHANNEL_MAX = 8;
    constexpr byte ROLLER_RELAY_CHANNEL_MIN = 1;
    constexpr byte ROLLER_RELAY_CHANNEL_MAX = 16;

    constexpr byte ROLLER_RELAY_CHANNEL_COUNT =
    ROLLER_RELAY_CHANNEL_MAX - ROLLER_RELAY_CHANNEL_MIN + 1;
  }
}
