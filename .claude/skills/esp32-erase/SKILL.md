---
name: esp32-erase
description: >
  Erase the flash / NVS of an ESP32-C6 TouchToken board and re-upload firmware.
  Use this when: Zigbee won't connect, coordinator keeps rejecting joins, board
  is stuck in a bad network state, "nvs" errors in serial output, first-time
  setup of a board, or switching a board between coordinator and end-device roles.
  Triggers on: "erase", "factory reset the board", "Zigbee stuck", "clear NVS",
  "board won't join", "reset zigbee state", "start fresh".
---

# ESP32-C6 TouchToken Flash Erase

Zigbee stores its network credentials in NVS (non-volatile storage). If a board
gets stuck — won't join, keeps re-forming a stale network, or was previously a
coordinator and is being reflashed as an end device — a full erase is the fix.

## When to erase vs. just re-upload

| Symptom | Action |
|---------|--------|
| New code, same role | `/esp32-upload` only |
| Zigbee won't connect after reflash | Erase + upload |
| Switching coordinator ↔ end device | Erase + upload |
| Serial shows NVS errors | Erase + upload |
| First flash on a brand-new board | Upload only (NVS is already blank) |

## Board map

| Role     | COM port |
|----------|----------|
| sender   | COM15    |
| receiver | COM16    |

## esptool path

```
C:\Users\finn\.platformio\packages\tool-esptoolpy\esptool.py
```

Use PlatformIO's bundled Python to run it:
```
C:\Users\finn\.platformio\penv\Scripts\python.exe
```

## Erase procedure (PowerShell)

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PY      = "$env:USERPROFILE\.platformio\penv\Scripts\python.exe"
$ESPTOOL = "$env:USERPROFILE\.platformio\packages\tool-esptoolpy\esptool.py"
$PORT    = "COM15"   # or COM16

& $PY $ESPTOOL --port $PORT erase_flash
```

After erase, immediately re-upload the firmware — otherwise the board boots
into a blank flash and may behave unexpectedly:

```powershell
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
$PROJECT = "C:\Users\finn\Documents\Claude\ESP32C6_TouchToken\<sender|receiver>"
Set-Location $PROJECT
& $PIO run -t upload
```

## Erase both boards

Erase receiver first (coordinator), then sender (end device), then reflash both:

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PY      = "$env:USERPROFILE\.platformio\penv\Scripts\python.exe"
$ESPTOOL = "$env:USERPROFILE\.platformio\packages\tool-esptoolpy\esptool.py"
$PIO     = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
$BASE    = "C:\Users\finn\Documents\Claude\ESP32C6_TouchToken"

& $PY $ESPTOOL --port COM16 erase_flash
& $PY $ESPTOOL --port COM15 erase_flash

Set-Location "$BASE\sender";   & $PIO run -t upload
Set-Location "$BASE\receiver"; & $PIO run -t upload
```

## After erase + upload

- Power-cycle both boards (unplug/replug USB)
- Receiver coordinator starts and opens the network for 180 s via `Zigbee.openNetwork(180)`
- Sender scans and joins — expect 5–30 s for first join
- Watch receiver serial for incoming messages
