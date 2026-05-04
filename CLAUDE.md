# ESP32C6 TouchToken

Zigbee point-to-point communication between two Seeed Xiao ESP32-C6 boards,
with the receiver forwarding messages to Unreal Engine via OSC or a native UE plugin.

## Board map

| Role         | COM port | MAC                  | Zigbee role | Partition       |
|--------------|----------|----------------------|-------------|-----------------|
| **sender**   | COM15    | 58:e6:c5:19:c0:08    | End Device  | zigbee.csv      |
| **sender2**  | COM17    | (check boot log)     | End Device  | zigbee.csv      |
| **receiver** | COM16    | 58:e6:c5:1b:9d:04    | Coordinator | zigbee_zczr.csv |

Physical labels on the boards match these roles. COM ports are hardcoded in
each `platformio.ini` so `pio run -t upload` always targets the right board.

## Stack

- **Platform**: pioarduino (`platform-espressif32` fork with ESP32-C6 Arduino support)
- **Framework**: Arduino ESP32 3.3.8
- **Zigbee channel**: 15 (2.425 GHz — sits between WiFi ch1 and ch6)
- **Unreal integration**: UE C++ plugin (`UnrealPlugin/TokenReceiver/`) reads serial
  directly via Win32 COM port API; no Python bridge needed

## Project structure

```
sender/          End Device firmware (Zigbee TX, dummy messages every 1 s)
receiver/        Coordinator firmware (Zigbee RX → USB Serial)
bridge/          Python fallback: serial_to_osc.py (OSC over UDP if plugin not used)
UnrealPlugin/    TokenReceiver UE5 C++ plugin (reads COM16, fires Blueprint events)
```

## Skills (use these instead of raw commands)

| Skill             | When to use |
|-------------------|-------------|
| `/esp32-upload`   | Flash sender, receiver, or both |
| `/esp32-monitor`  | Watch serial output from either board |
| `/esp32-erase`    | Zigbee stuck / switching roles / factory reset |

## Critical Windows quirks

1. **Always use PowerShell** for `pio` commands — `idf_tools.py` rejects MSys/Mingw
2. **Always set** `$env:PYTHONIOENCODING = "utf-8"` before running pio, or cp1252 crashes it
3. **`osc-bridge.exe`** from the Digitracks project auto-starts and holds COM16 —
   kill it before uploading: `Stop-Process -Name "osc-bridge" -Force`
4. **Arduino IDE** serial monitor also locks COM ports — close it before uploading

## Message format

```
2026/04/28 11:33:39 [2079928368] [0 1 0 2] batt:3603mV
                     └─ token id  └─ sensors  └─ mV
```

## OSC address (if using bridge or UE OSC plugin)

```
/digitracks/token  →  [string rawMsg, int32 id, int32 s0..s3, int32 battMv]
```
