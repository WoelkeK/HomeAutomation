#pragma once

#include "Config.h"

// Centralna numeracja kanałów MySensors.
namespace ChildId
{
  constexpr byte LIGHT_FIRST = 0;
  constexpr byte LIGHT_LAST = 19;

  constexpr byte OUTDOOR_LIGHT_SENSOR = 50;

  // Wirtualne kanały sterujące spryskiwaczami z OpenHAB.
  // Nie są powiązane z fizycznymi przyciskami.
  constexpr byte SPRINKLER_FIRST = 60;
  constexpr byte SPRINKLER_LAST = 67;
  constexpr byte SPRINKLER_COUNT =
      SPRINKLER_LAST - SPRINKLER_FIRST + 1;

  constexpr byte FIRMWARE_INFO = 68;
  constexpr byte BUILD_INFO = 69;

  // Rolety
  constexpr byte ROLLER_FIRST = 100;
  constexpr byte ROLLER_LAST =
      ROLLER_FIRST + ROLLER_COUNT - 1;
}
