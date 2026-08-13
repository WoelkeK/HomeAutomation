# Sterownik_Master_090726 v2.0.1

Główna wersja projektu sterownika domu na Atmega 2560.

## Najważniejsze cechy

- MySensors / OpenHAB zostaje na Gateway `Serial2`.
- Modbus RTU dla modulow Waveshare działa na `Serial1`.
- Wszystkie światła są mapowane na Waveshare 32CH przez `LightConfig.h`.
- Rolety są mapowane w 'RollerConfig.h'
- Przyciski zostają na module 4xMCP23017.
- SafeStart pozostaje aktywny.

## Magistrale

| Funkcja             | Port Mega | Uwagi                                      |
| ------------------- | --------: | ------------------------------------------ |
| MySensors / OpenHAB |   Serial2 | Mega + Raspberry Pi   |
| Modbus RTU          |   Serial1 | Waveshare TTL TO RS485 (C), TX1=18, RX1=19 |

## Modbus

Domyślnie:

- Waveshare 32CH Relay: slave `1`
- SDM630: zarezerwowany slave `2`
- Waveshare 8CH Relay: slave '3'
- Waveshare 16CH Relay: slave `4`
- baudrate: `9600`

## Mapowanie świateł

Cała kolejność przekaźników Waveshare jest w pliku:

```text
LightConfig.h
```

Zmiana przewodów w rozdzielni wymaga zmiany tylko tej tabeli.

## Ważne

W tej wersji wszystkie światła są kierowane na Waveshare. Jeżeli fizycznie dany obwód nadal jest podłączony do lokalnego przekaźnika Mega, nie zadziała, dopóki nie zostanie przepięty na odpowiadający kanał Waveshare.
Application
│
├── Bootstrap
│
├── Gateway
│ └── MySensorsGateway
│
├── Controllers
│ ├── LightingController
│ ├── RollerController
│ ├── SprinklerController
│ └── SensorController
│
├── Services
│ ├── OutputManager
│ ├── ModbusManager
│ ├── Mcp23017Manager
│ └── EEPROMManager
│
├── Hardware
│ ├── ModbusRelayDevice
│ ├── SDM630
│ └── Deye
│
├── Configuration
│ ├── LightConfig
│ ├── RollerConfig
│ ├── SprinklerConfig
│ └── HouseConfig
│
└── Context
├── LightingContext
├── RollerContext
└── SprinklerContext
