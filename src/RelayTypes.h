#pragma once

// Stan zwykłego kanału przekaźnikowego.
class RelayChannel
{
  public:
    boolean relayState;
};

// Wspólny typ dla kanałów roletowych.
// Stan kanału rolety wraz z informacjami czasowymi.
class TimedRelayChannel : public RelayChannel
{
  public:
    bool ROLReady = false;
    unsigned long buttonPushedMillis;
    unsigned long ledTurnedOnAt;
    unsigned long turnOnDelay = 500;
    unsigned long turnOffDelay;
};
