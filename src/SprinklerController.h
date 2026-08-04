#pragma once

#include "ModbusRelayDevice.h"

// Sterownik ośmiu sekcji spryskiwaczy.
// Harmonogram pozostaje w OpenHAB; Mega realizuje polecenia i zabezpieczenia.
class SprinklerController
{
  public:
    SprinklerController()
      : _device(nullptr)
    {
      for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++) {
        _states[zone] = false;
        _startedAt[zone] = 0;
      }
    }

    void begin(ModbusRelayDevice& device)
    {
      _device = &device;
      stopAll(false);
    }

    void update()
    {
      const unsigned long now = millis();

      for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++) {
        if (_states[zone] &&
            static_cast<unsigned long>(now - _startedAt[zone]) >= SPRINKLER_MAX_RUNTIME_MS) {
          setZone(zone, false, true);
        }
      }
    }

    bool setZone(byte zone, bool state, bool reportState)
    {
      if (_device == nullptr || zone >= SPRINKLER_ZONE_COUNT) {
        return false;
      }

#if SPRINKLER_ALLOW_MULTIPLE_ZONES == 0
      if (state) {
        for (byte other = 0; other < SPRINKLER_ZONE_COUNT; other++) {
          if (other != zone && _states[other]) {
            setZone(other, false, reportState);
          }
        }
      }
#endif

      if (!_device->writeChannel(zone + 1, state)) {
        return false;
      }

      _states[zone] = state;
      _startedAt[zone] = state ? millis() : 0;

      if (reportState) {
        report(zone);
      }
      return true;
    }

    void stopAll(bool reportState)
    {
      if (_device == nullptr) {
        return;
      }

      for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++) {
        _device->writeChannel(zone + 1, false);
        _states[zone] = false;
        _startedAt[zone] = 0;

        if (reportState) {
          report(zone);
        }
      }
    }

    bool state(byte zone) const
    {
      return zone < SPRINKLER_ZONE_COUNT && _states[zone];
    }

    void reportAll()
    {
      for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++) {
        report(zone);
      }
    }

  private:
    ModbusRelayDevice* _device;
    bool _states[SPRINKLER_ZONE_COUNT];
    unsigned long _startedAt[SPRINKLER_ZONE_COUNT];

    void report(byte zone)
    {
      MyMessage message(ChildId::SPRINKLER_FIRST + zone, V_STATUS);
      send(message.set(_states[zone]));
    }
};
