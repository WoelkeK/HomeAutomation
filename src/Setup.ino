void inicjalizacja(){


  // initialize all the readings to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;

    
  
  mcpManager.begin();

  
// Initialize Relays1 with corresponding buttons
  for (int i = 0; i < noRelays1; i++) {
    
    Relays1[i].buttonPin = LIGHT_CHANNELS[i].buttonPin;              // assign physical pins
    Relays1[i].relayPin = LIGHT_CHANNELS[i].relayPin;
    msg1[i].sensor = LIGHT_CHANNELS[i].sensorId;                                   // initialize messages
    msg1[i].type = V_LIGHT;
    
    mcpManager.configureInput(LIGHT_CHANNELS[i].buttonDevice, Relays1[i].buttonPin);
    debouncer1[i] = BounceMcp();                        // initialize debouncer
    debouncer1[i].attach(mcpManager.device(LIGHT_CHANNELS[i].buttonDevice), Relays1[i].buttonPin, 100);
    debouncer1[i].interval(50);

    // Bezpieczny start: najpierw wymuszamy OFF, dopiero potem ewentualnie odtwarzamy stan.
    relayManager.safeOff(LIGHT_CHANNELS[i].output);

#if RESTORE_LIGHTS_FROM_EEPROM_ON_BOOT
    Relays1[i].relayState = loadState(i);
#else
    Relays1[i].relayState = false;
#endif

    relayManager.writeLight(i, Relays1[i], Relays1[i].relayState);
    send(msg1[i].set(Relays1[i].relayState ? true : false));                 // make controller aware of last status

    }
    

   



  //-------------------------------------------------------------------------------------------------------------------------------

  // Initialize Relays3 Rolety Góra
  for (int k = 0; k < noRelays3; k++) {
    Relays3[k].buttonPin = ROLLER_UP_CHANNELS[k].buttonPin;              // assign physical pins
    Relays3[k].relayPin = ROLLER_UP_CHANNELS[k].relayPin;
    Relays3[k].turnOffDelay = ROLLER_UP_CHANNELS[k].turnOffDelay;
    msg3[k].sensor = ROLLER_UP_CHANNELS[k].sensorId;                                   // initialize messages
    msg3[k].type = V_LIGHT;

    mcpManager.configureInput(ROLLER_UP_CHANNELS[k].buttonDevice, Relays3[k].buttonPin);

 //   wait(100);
    relayManager.safeOff(Relays3[k].relayPin);
    relayManager.writeRoller(Relays3[k], true); // OFF dla ACTIVE LOW
    send(msg3[k].set(Relays3[k].relayState ? true : false));                 // make controller aware of last status
//    wait(50);

    debouncer3[k] = BounceMcp();                        // initialize debouncer
    debouncer3[k].attach(mcpManager.device(ROLLER_UP_CHANNELS[k].buttonDevice), Relays3[k].buttonPin, 100);
    debouncer3[k].interval(50);
  }


  // Initialize Relays4 Rolety dół
  for (int k = 0; k < noRelays4; k++) {
    Relays4[k].buttonPin = ROLLER_DOWN_CHANNELS[k].buttonPin;              // assign physical pins
    Relays4[k].relayPin = ROLLER_DOWN_CHANNELS[k].relayPin;
    Relays4[k].turnOffDelay = ROLLER_DOWN_CHANNELS[k].turnOffDelay;
    msg4[k].sensor = ROLLER_DOWN_CHANNELS[k].sensorId;                                   // initialize messages
    msg4[k].type = V_LIGHT;

    mcpManager.configureInput(ROLLER_DOWN_CHANNELS[k].buttonDevice, Relays4[k].buttonPin);

 //   wait(100);
    relayManager.safeOff(Relays4[k].relayPin);
    relayManager.writeRoller(Relays4[k], true); // OFF dla ACTIVE LOW
    send(msg4[k].set(Relays4[k].relayState ? true : false));                 // make controller aware of last status
 //   wait(50);

    debouncer4[k] = BounceMcp();                        // initialize debouncer
    debouncer4[k].attach(mcpManager.device(ROLLER_DOWN_CHANNELS[k].buttonDevice), Relays4[k].buttonPin, 100);
    debouncer4[k].interval(50);
  }
}
  
