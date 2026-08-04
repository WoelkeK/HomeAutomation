void swiatla () {



  for (byte i = 0; i < noRelays1; i++) {

    if (debouncer1[i].update()) {

      int value1 = debouncer1[i].read();

      if ( value1 == LOW) {
        relayManager.toggleLight(i, Relays1[i]);
        send(msg1[i].set(Relays1[i].relayState ? true : false));
        // save sensor state in EEPROM (location == sensor number)
        saveState( i, Relays1[i].relayState );

      }
    }
  }
}
