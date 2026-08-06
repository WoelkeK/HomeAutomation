# v2.1.0 USB Gateway

- Mega zmieniona z noda `1` na bramkę MySensors przez USB.
- Zachowano `Serial1` dla Modbus.
- Zachowano `Serial2` dla MySensors RS485.
- Zachowano `MY_RS485_AUTO_DIRECTION` bez pinu DE. Wymaga zmodyfikowanej biblioteki MySensors
- Wyłączono `MY_DEBUG` na USB.
- Usunięto aktywne `Serial.print()` mogące zakłócać protokół bramki.
- Skrócono oczekiwanie na transport do 1000 ms.
