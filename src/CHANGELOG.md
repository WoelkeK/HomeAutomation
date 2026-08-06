# CHANGELOG

## v2.0.1 - 2026-07-09

### Dodano

- `SystemConfig.h` z centralną konfiguracją sprzętową.
- `LightMapping.h` jako jedyne miejsce mapowania świateł na przekaźniki Waveshare.

### Zmieniono

- Wszystkie światła zostały przeniesione na `OutputBackend::ModbusRelay32CH`.
- `ChannelConfig.h` korzysta teraz z `outputForLight(LightId::...)`.
- Rolety pozostają na lokalnych pinach Mega.
- MySensors/OpenHAB bez zmian.

### Mapowanie Waveshare

- Kotłownia → relay 1
- Garaż → relay 2
- Łazienka → relay 3
- Garderoba → relay 4
- Sportowy → relay 5
- Gabinet → relay 6
- Rozdzielnia → relay 7
- Kuchnia oczka → relay 8
- Kuchnia sufit → relay 9
- Oświetlenie zewnętrzne 1 → relay 10
- Salon stół → relay 11
- Salon ściana zegar → relay 12
- Hol spoty → relay 13
- Salon sufit RGB → relay 14
- Salon okno TV + płyta TV → relay 15
- Salon oczka → relay 16
- Korytarz schody RGB → relay 17
- Korytarz oczka sufit → relay 18
- Korytarz/Hol spot 2x → relay 19
- Rezerwa pin 7 → relay 20

## 2.2.0 - fundament konfiguracji i Modbus

- dodano `Version.h` i prezentację wersji przez `sendSketchInfo()`,
- dodano centralne `HouseConfig.h` oraz `ChildIds.h`,
- dodano wspólny nieblokujący `ModbusManager`,
- przeniesiono aktywny sterownik Waveshare 32CH na `ModbusManager`,
- zachowano dotychczasowy tryb TX-only i istniejącą numerację MySensors,
- zarezerwowano adres Modbus 3 i Child ID 60-67 pod przyszłe spryskiwacze,
- spryskiwacze nie są jeszcze prezentowane ani obsługiwane w tej wersji.

## 2.3.1 - start migracji z Arduino IDE na projekt C++ VSCode

- dodano repozytorium GIT
- dodano do głównej pętli programu presents Child 68/69 firmware vesrion i build time.
- zmodyfikowano klasę LightSensorController - przeniesiono kod z pomiary.ino
