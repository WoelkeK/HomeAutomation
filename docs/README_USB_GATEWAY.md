# Sterownik Master v2.1.0 USB Gateway — Arduino IDE

Konfiguracja portów:

- `Serial` / USB — bramka MySensors do Raspberry Pi / OpenHAB
- `Serial1` — Modbus RTU Waveshare 32CH
- `Serial2` — sieć MySensors RS485
- `Serial3` — wolny

Wymagania:

- Arduino Mega 2560
- zmodyfikowana biblioteka MySensors z obsługą `MY_RS485_AUTO_DIRECTION` bez `MY_RS485_DE_PIN`
- biblioteki `Adafruit_MCP23017` i `Bounce2mcp`

Najważniejsze definicje w pliku głównym:

```cpp
#define MY_GATEWAY_SERIAL
#define MY_BAUD_RATE 115200
#define MY_RS485
#define MY_RS485_BAUD_RATE 19200
#define MY_RS485_HWSERIAL Serial2
#define MY_RS485_AUTO_DIRECTION
#define MY_TRANSPORT_WAIT_READY_MS 1000
```

Nie używaj zwykłych `Serial.print()` podczas pracy bramki, ponieważ USB przenosi protokół MySensors.
