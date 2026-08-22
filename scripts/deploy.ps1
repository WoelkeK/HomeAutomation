
$ErrorActionPreference = "Stop"

$PiHost = "192.168.5.163"
$PiUser = "openhabian"

$ProjectRoot = Split-Path -Parent $PSScriptRoot
$PlatformIO = "$env:USERPROFILE\.platformio\penv\Scripts\platformio.exe"

$FirmwareLocal = Join-Path `
    $ProjectRoot `
    ".pio\build\megaatmega2560\firmware.hex"

$FirmwareRemote = "/home/openhabian/firmware/current.hex"
$UpdateScript = "/home/openhabian/bin/updateMega.sh"

Write-Host ""
Write-Host "================================="
Write-Host " Sterownik Master - wdrozenie"
Write-Host "================================="
Write-Host ""

Set-Location $ProjectRoot

Write-Host "[1/4] Kompilacja PlatformIO..."

if (-not (Test-Path $PlatformIO)) {
    Write-Error "Nie znaleziono PlatformIO: $PlatformIO"
    exit 1
}

& $PlatformIO run

if ($LASTEXITCODE -ne 0) {
    Write-Error "Kompilacja nie powiodla sie."
    exit 1
}

if (-not (Test-Path $FirmwareLocal)) {
    Write-Error "Nie znaleziono firmware: $FirmwareLocal"
    exit 1
}

Write-Host ""
Write-Host "[2/4] Kopiowanie firmware na Raspberry Pi..."

scp `
    $FirmwareLocal `
    "${PiUser}@${PiHost}:${FirmwareRemote}"

if ($LASTEXITCODE -ne 0) {
    Write-Error "Kopiowanie firmware nie powiodlo sie."
    exit 1
}

Write-Host ""
Write-Host "[3/4] Wgrywanie firmware do Arduino Mega..."

ssh `
    "${PiUser}@${PiHost}" `
    $UpdateScript

if ($LASTEXITCODE -ne 0) {
    Write-Error "Wgrywanie firmware nie powiodlo sie."
    exit 1
}

Write-Host ""
Write-Host "[4/4] Sprawdzanie OpenHAB..."

ssh `
    "${PiUser}@${PiHost}" `
    "systemctl is-active openhab"

if ($LASTEXITCODE -ne 0) {
    Write-Error "OpenHAB nie jest aktywny."
    exit 1
}

Write-Host ""
Write-Host "================================="
Write-Host " Wdrozenie zakonczone poprawnie"
Write-Host "================================="
