---
name: esp32-monitor
description: >
  Open the USB serial monitor for a TouchToken ESP32-C6 board.
  Triggers on: "monitor", "serial output", "watch COM15/COM16",
  "show serial", "read the board", "what is the board printing",
  "open terminal for the receiver/sender".
  Default board is receiver (COM16) since that's where Zigbee messages appear.
  Uses PowerShell — never bash — to invoke pio.
---

# ESP32-C6 TouchToken Serial Monitor

## Board map

| Role     | COM port | What you'll see |
|----------|----------|-----------------|
| receiver | COM16    | Incoming Zigbee messages (one per line, ready for OSC bridge) |
| sender   | COM15    | TX log: dummy messages being sent |

## PlatformIO executable

```powershell
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
```

## Open monitor (PowerShell)

```powershell
$env:PYTHONIOENCODING = "utf-8"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PIO = "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe"
$PROJECT = "C:\Users\finn\Documents\Claude\ESP32C6_TouchToken\<sender|receiver>"
Set-Location $PROJECT
& $PIO device monitor
```

`monitor_port` and `monitor_speed` are already set in each `platformio.ini`
so no extra flags are needed.

## Default behaviour

- If the user doesn't specify a board, open the **receiver** monitor (COM16),
  because that's where the Zigbee → serial output appears.
- If both are requested, remind the user that two monitors need two terminals
  and suggest opening one in a separate PowerShell window.

## Exit

`Ctrl+C` exits the monitor. The board keeps running.
