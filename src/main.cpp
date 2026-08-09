// Sterownik Master
//
// Aktualny układ:
// - światła: Waveshare 32CH po Modbus RTU
// - rolety: Waveshare 16CH po Modbus RTU
// - spryskiwacze: Waveshare 8CH po Modbus RTU
// - wejścia lokalne: MCP23017
// - Mega działa jako bramka MySensors przez USB
// - Serial1: Modbus RTU
// - Serial2: MySensors RS485
// - MySensors z AUTO_DIRECTION bez pinu DE

#include <Arduino.h>

#define MY_GATEWAY_SERIAL
#define MY_BAUD_RATE 115200

#define MY_RS485
#define MY_RS485_BAUD_RATE 19200
#define MY_RS485_HWSERIAL Serial2
#define MY_RS485_AUTO_DIRECTION

#define MY_TRANSPORT_WAIT_READY_MS 1000

#include <MySensors.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <Bounce2mcp.h>
#include "HardwareContext.h"
#include "Version.h"
#include "ChildIds.h"
#include "HouseConfig.h"
#include "Config.h"
#include "SystemConfig.h"
#include "RelayTypes.h"
#include "OutputConfig.h"
#include "LightId.h"
#include "LightMapping.h"
#include "ModbusManager.h"
#include "ModbusRelayDevice.h"
#include "SprinklerController.h"
#include "ModbusMaster.h"
#include "WaveshareRelay32CH.h"
#include "ModbusOutputDriver.h"
#include "SDM630Meter.h"
#include "ChannelConfig.h"
#include "StartupSafety.h"
#include "OutputManager.h"
#include "Mcp23017Manager.h"
#include "LightingContext.h"
#include "RollerContext.h"

Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;

HardwareContext hardware;

RollerContext rollerContext;
LightingContext lightingContext;

SprinklerController sprinklerController;

Mcp23017Manager mcpManager;

#include "MySensorsGateway.h"
#include "Application.h"

OutputManager outputManager(
  hardware.outputDriver
);

Application application(
  outputManager,
  mcpManager,
  lightingContext,
  rollerContext
);

MySensorsGateway mySensorsGateway(
  outputManager,
  lightingContext,
  sprinklerController
);

void before()
{
  prepareLocalRelayPinsSafeOff();
}

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Bezpieczny stan lokalnych wyjść przed pełną inicjalizacją.
  prepareLocalRelayPinsSafeOff();

#if ENABLE_WAVESHARE_MODBUS

  hardware.modbusManager.begin(
    MODBUS_RTU_SERIAL,
    MODBUS_RTU_BAUD_RATE
  );

  // Światła - Waveshare 32CH
  hardware.lightRelay32.begin(
    hardware.modbusManager,
    HouseConfig::Modbus::LIGHT_RELAY_SLAVE_ID
  );

  // Rolety - Waveshare 16CH
  hardware.rollerRelay16.begin(
    hardware.modbusManager,
    HouseConfig::Modbus::ROLLER_RELAY_SLAVE_ID,
    HouseConfig::Modbus::ROLLER_RELAY_CHANNEL_COUNT
  );

  hardware.outputDriver.attachLightModule(
    hardware.lightRelay32
  );

  hardware.outputDriver.attachRollerModule(
    hardware.rollerRelay16
  );

#if ENABLE_SPRINKLER_MODULE

  // Spryskiwacze - Waveshare 8CH
  hardware.sprinklerRelay8.begin(
    hardware.modbusManager,
    HouseConfig::Modbus::SPRINKLER_RELAY_SLAVE_ID,
    SPRINKLER_ZONE_COUNT
  );

  sprinklerController.begin(
    hardware.sprinklerRelay8
  );

#endif
#endif

#if ENABLE_SDM630_METER

  hardware.sdm630Meter.begin(
  hardware.modbusMaster,
  SDM630_DEFAULT_SLAVE_ID
  );

#endif

  application.begin();

#if ENABLE_SPRINKLER_MODULE

  // Bezpieczny stan początkowy wszystkich sekcji.
  sprinklerController.reportAll();

#endif
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
}

void receive(const MyMessage& message)
{
  mySensorsGateway.handleMessage(message);
}
