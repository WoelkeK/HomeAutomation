#pragma once

struct RollerContext
{
  TimedRelayChannel upRelays[noRelays3];
  TimedRelayChannel downRelays[noRelays4];

  BounceMcp upDebouncers[noRelays3];
  BounceMcp downDebouncers[noRelays4];

  MyMessage upMessages[noRelays3];
  MyMessage downMessages[noRelays4];
};
