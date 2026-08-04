# v2.3.0 - Modbus 8CH Sprinklers

- Dodano moduł przekaźnikowy Modbus RTU 8CH pod adresem 3.
- Dodano wirtualne kanały MySensors 60-67 dla OpenHAB.
- Dodano klasę `ModbusRelayDevice` dla modułów o dowolnej liczbie kanałów.
- Dodano `SprinklerController`.
- Harmonogram pozostaje po stronie OpenHAB.
- Domyślnie może działać tylko jedna sekcja jednocześnie.
- Włączenie kolejnej sekcji wyłącza poprzednią.
- Maksymalny awaryjny czas pracy sekcji wynosi 45 minut.
- Po starcie firmware wysyłane są polecenia OFF dla wszystkich ośmiu kanałów.
- Zachowano nieblokujący tryb Modbus TX-only i istniejącą obsługę modułu 32CH.
