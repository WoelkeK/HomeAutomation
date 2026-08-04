$ErrorActionPreference = "Stop"

$HostName = "openhabian@openhabian"
$Firmware = Join-Path $PSScriptRoot "..\.pio\build\megaatmega2560\firmware.hex"
$RemoteFirmware = "/home/openhabian/firmware/current.hex"

$Firmware = (Resolve-Path $Firmware).Path

Write-Host "Kompiluję projekt..."
pio run

Write-Host "Kopiuję firmware na Raspberry Pi..."
scp $Firmware "${HostName}:${RemoteFirmware}"

Write-Host "Uruchamiam updateMega.sh..."
ssh $HostName "~/bin/updateMega.sh"
