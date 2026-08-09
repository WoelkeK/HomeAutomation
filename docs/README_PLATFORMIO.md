# Sterownik Master v2.3.0 — migracja do PlatformIO

Ta wersja nie zmienia logiki sterownika. Pliki źródłowe v2.3.0 zostały przeniesione do `src/`.

## Wymagane biblioteki niestandardowe

Projekt korzysta z:

1. zmodyfikowanej biblioteki `MySensors` obsługującej `MY_RS485_AUTO_DIRECTION`,
2. biblioteki `Bounce2mcp`.

Skopiuj całe katalogi bibliotek używanych przez działający Arduino IDE do:

```text
lib/MySensors_CUSTOM/
lib/Bounce2mcp_CUSTOM/
```

W katalogu każdej biblioteki musi znajdować się jej kod źródłowy, np. `MySensors.h` albo `Bounce2mcp.h`.

## Kompilacja

W VS Code użyj `PlatformIO: Build` albo terminala:

```powershell
pio run
```

Plik wynikowy:

```text
.pio/build/megaatmega2560/firmware.hex
```

## Przekazanie firmware do Raspberry Pi

Uruchom z PowerShell:

```powershell
.\scripts\deploy-to-openhab.ps1
```

Skrypt kopiuje firmware jako `/home/openhabian/firmware/current.hex`, a następnie uruchamia `~/bin/updateMega.sh`.

Przed pierwszym użyciem sprawdź nazwę hosta w skrypcie.
