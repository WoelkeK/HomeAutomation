# Spryskiwacze Modbus RTU 8CH

## Konfiguracja

- magistrala Modbus: `Serial1`, 9600 bps
- moduł świateł 32CH: adres 1
- SDM630: adres 2 (obecnie wyłączony w konfiguracji)
- moduł spryskiwaczy 8CH: adres 3
- kanały MySensors/OpenHAB: 60-67

## Mapowanie

| Child ID | Kanał modułu 8CH |
|---:|---:|
| 60 | 1 |
| 61 | 2 |
| 62 | 3 |
| 63 | 4 |
| 64 | 5 |
| 65 | 6 |
| 66 | 7 |
| 67 | 8 |

## Zasady działania

- brak fizycznych przycisków dla spryskiwaczy
- sterowanie wyłącznie z OpenHAB przez MySensors USB
- harmonogram pozostaje w OpenHAB
- jednocześnie działa maksymalnie jedna sekcja
- włączenie nowej sekcji wyłącza poprzednią
- maksymalny awaryjny czas pracy jednej sekcji: 45 minut
- po restarcie Mega wszystkie sekcje są wyłączane
