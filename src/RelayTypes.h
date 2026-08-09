#pragma once

// ETAP 2:
// Wspólny typ dla zwykłych kanałów przekaźnikowych.
// Zastępuje wcześniejsze Relay1 / Relay2, które różniły się tylko nazwami pól.
class RelayChannel
{
  public:
    boolean relayState;
};

// Wspólny typ dla kanałów roletowych.
// Zastępuje wcześniejsze Relay3 / Relay4, zachowując te same dane czasowe.
class TimedRelayChannel : public RelayChannel
{
  public:
    bool ROLReady = false;
    unsigned long buttonPushedMillis;
    unsigned long ledTurnedOnAt;
    unsigned long turnOnDelay = 500;
    unsigned long turnOffDelay;
};
