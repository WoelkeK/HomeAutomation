# Sterownik_Master_090726 v2.0.1

Główna wersja projektu sterownika domu na Arduino Mega 2560.

## Najważniejsze cechy

- MySensors / OpenHAB zostaje na RS485 `Serial2`.
- Modbus RTU dla Waveshare 32CH działa na `Serial1`.
- Wszystkie światła są mapowane na Waveshare 32CH przez `LightMapping.h`.
- Rolety zostają na lokalnych wyjściach Arduino Mega.
- Przyciski zostają na MCP23017.
- SafeStart pozostaje aktywny.

## Magistrale

| Funkcja | Port Mega | Uwagi |
|---|---:|---|
| MySensors / OpenHAB | Serial2 | obecna bramka Arduino Uno + Raspberry Pi |
| Modbus RTU | Serial1 | Waveshare TTL TO RS485 (C), TX1=18, RX1=19 |

## Modbus

Domyślnie:

- Waveshare 32CH Relay: slave `1`
- SDM630: zarezerwowany slave `2`
- Deye: zarezerwowany slave `3`
- baudrate: `9600`

## Mapowanie świateł

Cała kolejność przekaźników Waveshare jest w pliku:

```text
LightMapping.h
```

Zmiana przewodów w rozdzielni wymaga zmiany tylko tej tabeli.

## Ważne

W tej wersji wszystkie światła są kierowane na Waveshare. Jeżeli fizycznie dany obwód nadal jest podłączony do lokalnego przekaźnika Mega, nie zadziała, dopóki nie zostanie przepięty na odpowiadający kanał Waveshare.
