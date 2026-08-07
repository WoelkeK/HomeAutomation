#pragma once

struct LightingContext
{
  RelayChannel relays[noRelays1];
  BounceMcp debouncers[noRelays1];
  MyMessage messages[noRelays1];
};
