#pragma once

#include <stdint.h>

class DiagnosticsManager
{
  public:
    void onLightChanged()
    {
      lightEvents++;
    }

    uint32_t getLightEvents() const
    {
      return lightEvents;
    }

  private:
    uint32_t lightEvents = 0;
};
