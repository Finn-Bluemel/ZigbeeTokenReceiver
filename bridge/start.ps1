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

# Start the monitor in the background, then open Chrome once it's up
Start-Process -FilePath "$PSScriptRoot\zigbee-monitor.exe" -ArgumentList $Port, $WebPort

# Give the server a moment to bind the port before opening the browser
Start-Sleep -Milliseconds 800
Start-Process "chrome.exe" "http://localhost:$WebPort"
