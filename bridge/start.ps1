# start.ps1 — launch Zigbee token monitor
# Usage:  .\start.ps1              (uses COM16)
#         .\start.ps1 COM18        (custom port)
#         .\start.ps1 COM16 9001   (custom port + web port)

param(
    [string]$Port    = "COM16",
    [string]$WebPort = "9001"
)

Stop-Process -Name "zigbee-monitor" -Force -ErrorAction SilentlyContinue
Start-Sleep -Milliseconds 200

Write-Host "Starting Zigbee Monitor  ->  http://localhost:$WebPort  (serial: $Port)"
& "$PSScriptRoot\zigbee-monitor.exe" $Port $WebPort
