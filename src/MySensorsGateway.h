#pragma once

class MySensorsGateway
{
  public:
    void presentNode()
    {
      sendSketchInfo(FIRMWARE_NAME, FIRMWARE_VERSION);
      present(ChildId::OUTDOOR_LIGHT_SENSOR, S_LIGHT_LEVEL);

      for (int i = 0; i < noRelays1; i++) {
        present(ChildId::LIGHT_FIRST + i, S_LIGHT);
      }

#if ENABLE_SPRINKLER_MODULE
      for (byte zone = 0; zone < SPRINKLER_ZONE_COUNT; zone++) {
        present(ChildId::SPRINKLER_FIRST + zone, S_BINARY, "Spryskiwacz");
      }
#endif
    }

    void handleMessage(const MyMessage& message)
    {
      if ((message.type == V_LIGHT || message.type == V_STATUS) &&
          message.sensor >= ChildId::LIGHT_FIRST &&
          message.sensor <= ChildId::LIGHT_LAST) {
        const byte lightIndex = message.sensor - ChildId::LIGHT_FIRST;
        relayManager.writeLight(lightIndex, Relays1[lightIndex], message.getBool());
        saveState(lightIndex, Relays1[lightIndex].relayState);
        return;
      }

#if ENABLE_SPRINKLER_MODULE
      if ((message.type == V_STATUS || message.type == V_LIGHT) &&
          message.sensor >= ChildId::SPRINKLER_FIRST &&
          message.sensor <= ChildId::SPRINKLER_LAST) {
        const byte zone = message.sensor - ChildId::SPRINKLER_FIRST;
        sprinklerController.setZone(zone, message.getBool(), true);
      }
#endif
    }
};
