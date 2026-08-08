#pragma once

#include <stdint.h>

enum class EventType : uint8_t
{
  LightChanged
};

struct Event
{
  EventType type;
  uint8_t id;
  bool state;
};
