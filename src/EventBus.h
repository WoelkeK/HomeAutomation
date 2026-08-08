#pragma once

#include <stdint.h>

#include "Event.h"
#include "IEventListener.h"

class EventBus
{
  public:
    bool subscribe(IEventListener& listener)
    {
      if (listenerCount >= MAX_LISTENERS) {
        return false;
      }

      listeners[listenerCount++] = &listener;
      return true;
    }

    void publish(const Event& event)
    {
      for (uint8_t i = 0; i < listenerCount; i++) {
        listeners[i]->onEvent(event);
      }
    }

  private:
    static constexpr uint8_t MAX_LISTENERS = 8;

    IEventListener* listeners[MAX_LISTENERS] = {};
    uint8_t listenerCount = 0;
};
