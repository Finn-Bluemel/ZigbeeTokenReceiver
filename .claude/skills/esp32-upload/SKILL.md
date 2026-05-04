---
name: esp32-upload
description: >
  Upload firmware to the ESP32-C6 TouchToken boards via PlatformIO.
  Use this skill whenever the user wants to flash, upload, build-and-upload,
  or deploy firmware to the sender board, receiver board, or both.
  Also triggers on phrases like "push firmware", "flash the board",
  "upload to COM15/COM16", or "update the token boards".
  IMPORTANT: Always use PowerShell for pio commands — bash/MSys fails on Windows
  because idf_tools.py rejects the Mingw environment.
---

# ESP32-C6 TouchToken Upload

## Board map

| Role     | COM port | Partition table  | Zigbee build flag |
|----------|----------|------------------|-------------------|
| sender   | COM15    | zigbee.csv       | -DZIGBEE_MODE_ED  |
| receiver | COM16    | zigbee_zczr.csv  | -DZIGBEE_MODE_ZCZR|

Each `platformio.ini` already has `upload_port` hardcoded, so pio always
targets the right board automatically.

## Project path

```
C:\Users\finn\Documents\Claude\ESP32C6_TouchToken\
  sender\    ← End Device (token transmitter)
  receiver\  ← Coordinator (USB serial to PC)
```

## PlatformIO executable

```powershell
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
```

## Upload procedure

Parse the user's request to decide which target(s) to flash:
- "sender" / "COM15" / "end device" → sender only
- "receiver" / "COM16" / "coordinator" → receiver only
- "both" / no qualifier / "all" → sender first, then receiver

### Preamble — always include these two lines first

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
```

Without them, pio's progress output triggers a cp1252 UnicodeEncodeError on
Windows, causing a false failure even when the flash succeeded.

### Single board (PowerShell)

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
$PROJECT = "C:\Users\finn\Documents\Claude\ESP32C6_TouchToken\<sender|receiver>"
Set-Location $PROJECT
& $PIO run -t upload
```

### Both boards (PowerShell — sequential, sender first)

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
$BASE = "C:\Users\finn\Documents\Claude\ESP32C6_TouchToken"

Set-Location "$BASE\sender"
& $PIO run -t upload
if ($LASTEXITCODE -ne 0) { Write-Error "Sender upload failed"; exit 1 }

Set-Location "$BASE\receiver"
& $PIO run -t upload
```

## Pre-upload: free the COM port

Before uploading, kill any process holding the target COM port.
Common offenders on this machine:

```powershell
# osc-bridge from the Digitracks project often holds COM16
Stop-Process -Name "osc-bridge" -Force -ErrorAction SilentlyContinue
# stale pio / esptool processes from a previous failed upload
Stop-Process -Name "platformio","esptool" -Force -ErrorAction SilentlyContinue
```

Confirm the port is free before proceeding:

```powershell
try {
    $p = New-Object System.IO.Ports.SerialPort "COM16"  # or COM15
    $p.Open(); $p.Close()
    Write-Host "Port is free"
} catch { Write-Host "Still locked — check Arduino IDE / VS Code serial monitor" }
```

## Reporting build errors

If the build fails, extract the actual compiler errors (lines containing
`error:` or `fatal error:`) and show them clearly — don't dump the full log.
Offer to fix obvious issues (missing members, wrong types, missing files)
directly before asking the user to retry.

## After a successful upload

Tell the user:
- Which board(s) were flashed
- The COM port each board is on
- Next step: open monitor with `/esp32-monitor` if they want to watch serial output
