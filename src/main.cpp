 // Pierwsza wersja sterowania lokalnego plus feedback i odczyt z Domoticz
// Działające światła, plus obsługa satela, rolety sterowane prawidłowo
// Kolejna modyfikacja - dołączenie pomiaru swiatła na zewnątrz 18/11/19 22:55
//
// Sterownik_Master_090726 v2.1.0 USB Gateway (Arduino IDE):
// - zachowana dotychczasowa logika działania
// - zachowana konfiguracja MySensors RS485
// - zachowana numeracja pinów i sensorów
// - dodany OutputBackend pod stopniową migrację świateł na Modbus
// - dodane logiczne nazwy LightId według rzeczywistych lokalizacji
// - dodany realny testowy sterownik Waveshare 32CH po Modbus RTU
// - dodany bezpieczny driver Waveshare TX-only bez blokowania MySensors/OpenHAB
// - wszystkie światła przeniesione na Waveshare przez LightMapping.h
// - rolety pozostają na lokalnych wyjściach Mega
// - Mega działa jako bramka MySensors przez USB
// - Serial1 pozostaje dla Modbus, Serial2 dla sieci MySensors RS485
// - używana jest zmodyfikowana biblioteka MySensors z AUTO_DIRECTION bez pinu DE

#include <Arduino.h>

#define MY_GATEWAY_SERIAL
#define MY_BAUD_RATE 115200

#define MY_RS485
//#define MY_RS485_DE_PIN 15
#define MY_RS485_BAUD_RATE 19200
#define MY_RS485_HWSERIAL Serial2
#define MY_RS485_AUTO_DIRECTION

#define MY_TRANSPORT_WAIT_READY_MS 1000

#include <MySensors.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <Bounce2mcp.h>
//#include <Bounce2.h>

#include "Version.h"
#include "ChildIds.h"
#include "HouseConfig.h"
#include "Config.h"
#include "SystemConfig.h"
#include "RelayTypes.h"
#include "OutputBackend.h"
#include "LightId.h"
#include "LightMapping.h"
#include "RollerId.h"
#include "ModbusManager.h"
#include "ModbusRelayDevice.h"
#include "SprinklerController.h"
#include "ModbusMaster.h"
#include "WaveshareRelay32CH.h"
#include "ModbusRelayOutputDriver.h"
#include "SDM630Meter.h"
#include "ModbusTestConsole.h"
#include "WaveshareRawTxTest.h"
#include "WaveshareSafeDriverTest.h"
#include "ChannelConfig.h"
#include "StartupSafety.h"
#include "RelayManager.h"
#include "Mcp23017Manager.h"
#include "LightingContext.h"
#include "RollerContext.h"


Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;

RollerContext rollerContext;
ModbusManager modbusManager;
ModbusMaster modbusMaster;
WaveshareRelay32CH waveshare32ch;
ModbusRelayDevice sprinklerRelay8ch;
SprinklerController sprinklerController;
SDM630Meter sdm630Meter;
ModbusTestConsole modbusTestConsole;
WaveshareRawTxTest waveshareRawTxTest;
WaveshareSafeDriverTest waveshareSafeDriverTest;

//uwaga kolejność inicjalizacji obiektów ma znaczenie, bo niektóre zależą od innych
ModbusRelayOutputDriver modbusRelayOutput;
LightingContext lightingContext;
Mcp23017Manager mcpManager;

// uint32_t SLEEP_TIME = 30 * 1000;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int lastaverage = 0;
MyMessage msg(ChildId::OUTDOOR_LIGHT_SENSOR, V_LIGHT_LEVEL);

// bool detektor = false;
// bool detektor2 = false;

#include "MySensorsGateway.h"
#include "Application.h"

RelayManager relayManager(
  modbusRelayOutput
);


Application application(
  relayManager,
  mcpManager,
  lightingContext,
  rollerContext
);

MySensorsGateway mySensorsGateway(
  relayManager,
  lightingContext
);

void before()
{
  prepareLocalRelayPinsSafeOff();
}

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Druga warstwa zabezpieczenia: utrzymaj wszystkie lokalne przekaźniki OFF
  // zanim zacznie się pełna inicjalizacja MCP, EEPROM i MySensors.
  prepareLocalRelayPinsSafeOff();

#if ENABLE_WAVESHARE_MODBUS
  // Etap 10C: używamy potwierdzonego sprzętowo trybu TX-only.
  // Nie czekamy na odpowiedź Modbus, więc MySensors/OpenHAB nie jest blokowany.
  modbusManager.begin(MODBUS_RTU_SERIAL, MODBUS_RTU_BAUD_RATE);
  waveshare32ch.begin(modbusManager, WAVESHARE_DEFAULT_SLAVE_ID);
  modbusRelayOutput.attach(waveshare32ch);

#if ENABLE_SPRINKLER_MODULE
  sprinklerRelay8ch.begin(modbusManager, SPRINKLER_RELAY_SLAVE_ID, SPRINKLER_ZONE_COUNT);
  sprinklerController.begin(sprinklerRelay8ch);
#endif
#endif

#if ENABLE_SDM630_METER
  sdm630Meter.begin(modbusMaster, SDM630_DEFAULT_SLAVE_ID);
#endif

  application.begin();

#if ENABLE_SPRINKLER_MODULE
  // Po prezentacji MySensors zgłoś do OpenHAB bezpieczny stan początkowy OFF.
  sprinklerController.reportAll();
#endif

  // Testy Modbus startują po inicjalizacji aplikacji, żeby nie wpływać na start MySensors.
  waveshareRawTxTest.begin();
  waveshareSafeDriverTest.begin();
}

void presentation()
{
  mySensorsGateway.presentNode();
}

void loop()
{
  application.update();
  mySensorsGateway.update();
#if ENABLE_SPRINKLER_MODULE
  sprinklerController.update();
#endif
  modbusTestConsole.update();
  waveshareRawTxTest.update();
  waveshareSafeDriverTest.update();
}

void receive(const MyMessage & message)
{
  mySensorsGateway.handleMessage(message);
}
