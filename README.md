# TouchToken — Zigbee Physical Token System

A wireless physical-token system built on **Seeed XIAO ESP32-C6** boards and the **Zigbee** protocol. Small sender tokens carry DS2431 1-Wire EEPROM chips in snap connectors; a USB receiver forwards all token readings to a PC, where a live web monitor and an Unreal Engine 5 plugin consume the data in real time.

```
┌─────────────────────┐        Zigbee         ┌──────────────────────┐
│   Sender Token      │ ─────────────────────▶ │   Receiver (USB)     │
│   ESP32-C6          │                        │   ESP32-C6           │
│   4× DS2431 slots   │    TOKEN 436135512     │                      │
│   battery monitor   │    [1 2 0 4] 3600mV    │   Serial ──▶ PC      │
└─────────────────────┘                        └──────────┬───────────┘
                                                          │ USB Serial
                     ┌────────────────────────────────────┴────────────────────────────┐
                     │                                                                  │
           ┌─────────▼──────────┐                                          ┌───────────▼─────────┐
           │  zigbee-monitor    │                                          │  TokenReceiver       │
           │  Web UI + Firmware │                                          │  UE5 Plugin          │
           │  Installer         │                                          │  Blueprint Events    │
           └────────────────────┘                                          └─────────────────────┘
```

---

## Hardware

| Board | Role | Zigbee | COM Port | Partition |
|-------|------|--------|----------|-----------|
| Seeed XIAO ESP32-C6 | **Sender** (token) | End Device | COM15 | `zigbee.csv` |
| Seeed XIAO ESP32-C6 | **Receiver** (USB bridge) | Coordinator | COM16 | `zigbee_zczr.csv` |

Each sender PCB has four **SS1–SS4** snap connectors, each wired to a dedicated 1-Wire bus. Plugging a **DS2431 EEPROM chip** into a connector identifies that physical slot. The receiver programs each chip with its slot number (1–4) on first contact — the slot ID is permanently stored in EEPROM and survives power cycles.

**Zigbee channel:** 15 (2.425 GHz — sits cleanly between Wi-Fi channels 1 and 6)

---

## Repository structure

```
sender/                     ESP32-C6 End Device firmware
  src/main.cpp              Zigbee TX loop — builds and sends TOKEN messages
  src/onewire_manager.cpp   1-Wire scan — reads DS2431 ROM + EEPROM slot number
  src/config.h              Pin assignments (PIN_OW1–OW4, NUM_OW_BUSES)
  platformio.ini            Build config (pioarduino, zigbee.csv partition)

receiver/                   ESP32-C6 Coordinator firmware
  src/main.cpp              Programs DS2431 chips on boot, then forwards
                            Zigbee messages to USB serial

bridge/                     PC-side tooling
  zigbee-monitor/           Go source for the monitor binary
    main.go                 Serial reader → SSE broker → HTTP server
    ui/index.html           Web UI: firmware installer + live token monitor
  firmware/
    sender/                 Flattened .bin files + manifest.json (esp-web-tools)
    receiver/               Flattened .bin files + manifest.json (esp-web-tools)
  start.ps1                 One-click launcher (Windows PowerShell)

UnrealPlugin/
  TokenReceiver/            UE5 plugin — drop into your project's Plugins/ folder
```

---

## Message format

Every sender transmits once per second over Zigbee. The receiver prints each message to USB serial:

```
TOKEN 436135512 [1 2 0 4] batt:3600mV
      │          │         └─ battery voltage in millivolts
      │          └─ DS2431 slot numbers for SS1 SS2 SS3 SS4 (0 = connector empty)
      └─ unique chip ID derived from the ESP32-C6 MAC address
```

Slot values are written to DS2431 EEPROM by the receiver and are persistent — a chip always reports the same slot number regardless of which sender board it is inserted into.

---

## Zigbee Monitor & Firmware Installer

`bridge/zigbee-monitor.exe` is a single self-contained Windows binary that:

- Reads the receiver's USB serial port
- Parses TOKEN messages in real time
- Serves a web UI at **http://localhost:9001** with two sections:
  - **Firmware installer** — flash Sender or Receiver firmware directly from the browser via Web Serial (Chrome / Edge required)
  - **Live token monitor** — one card per active sender, showing slot occupancy and battery percentage; cards fade out automatically 5 seconds after a sender goes silent

### Starting the monitor

```powershell
cd bridge
.\start.ps1              # defaults to COM16, port 9001
.\start.ps1 COM16 9001   # explicit
.\zigbee-monitor.exe COM16 9001
```

Then open **http://localhost:9001** in Chrome or Edge.

### Flashing firmware from the browser

1. Plug the board in via USB-C (data cable, not charge-only)
2. Open http://localhost:9001
3. Toggle **Sender** or **Receiver**
4. Click **Install** and follow the browser prompt to select the COM port

> Firmware files live in `bridge/firmware/sender/` and `bridge/firmware/receiver/`. To update firmware after a PlatformIO build, copy the new `.bin` files from `.pio/build/<env>/` into the appropriate folder.

### Building from source

```bash
cd bridge/zigbee-monitor
go build -o ../zigbee-monitor.exe .
```

Requires Go 1.21+. The only external dependency is [`go.bug.st/serial`](https://github.com/bugst/go-serial).

---

## Sender firmware

Built with [pioarduino](https://github.com/pioarduino/platform-espressif32) (Arduino ESP32 3.3.8).

**Startup sequence:**
1. Reads the ESP32-C6 eFuse MAC and derives a stable 32-bit token ID
2. Initialises four 1-Wire buses on the SS connector pins
3. Connects to the Zigbee coordinator (retries until found)

**Loop (every 1 second):**
1. Scans all four SS connectors — reads DS2431 ROM for presence check, then reads EEPROM byte 0 for the slot number
2. Samples battery voltage (simulated in firmware, replace with ADC read for production)
3. Transmits a ZCL custom cluster message to the coordinator

**1-Wire implementation** uses direct GPIO register writes (`GPIO.out_w1tc`, `GPIO.enable_w1ts`) and `portSET_INTERRUPT_MASK_FROM_ISR()` to block the Zigbee MAC ISR during timing-critical windows. No Arduino library dependency.

---

## Receiver firmware

**Startup sequence:**
1. **Programs DS2431 chips (radio off)** — scans all four SS connectors; any chip not yet programmed receives its slot number (1–4) written to EEPROM address 0x00
2. **Starts Zigbee coordinator** — opens the network with `openNetwork(254)`, refreshed every 2 minutes
3. Ready — forwards incoming ZCL messages to USB serial via a thread-safe queue

> All DS2431 programming happens before `Zigbee.begin()`. The Zigbee radio interferes with 1-Wire timing even before the stack is fully running, so this ordering is critical. Programming takes ~50 ms and only runs once at boot.

---

## UE5 Plugin — TokenReceiver

Drop `UnrealPlugin/TokenReceiver/` into your project's `Plugins/` directory and reopen the project. UE5 will detect the new plugin and prompt to rebuild.

### Requirements

- Unreal Engine 5.5 or newer
- Windows (auto-detect uses Win32 SetupAPI; other platforms compile but serial reads are no-ops)
- Receiver board plugged in via USB

### Blueprint setup

1. On `BeginPlay`, get the **Token Data Subsystem** node (Game Instance Subsystem)
2. Call **Open Port** — Port Name: `COM16`, Baud Rate: `115200`
3. **Bind Event to On Token Received** and create a custom event
4. In the event handler, **Break FTokenData** and use the fields

> If multiple Espressif boards are plugged in simultaneously, use `OpenPort("COM16", 115200)` explicitly. **Auto Open Port** picks the first `VID_303A` device it finds, which may be a sender board.

### FTokenData fields

| Field | Type | Description |
|-------|------|-------------|
| `RawMessage` | `FString` | Full raw serial line |
| `TokenId` | `int32` | Unique sender chip ID (from MAC) |
| `Slot0` | `int32` | DS2431 EEPROM value at SS1 (0 = empty) |
| `Slot1` | `int32` | DS2431 EEPROM value at SS2 (0 = empty) |
| `Slot2` | `int32` | DS2431 EEPROM value at SS3 (0 = empty) |
| `Slot3` | `int32` | DS2431 EEPROM value at SS4 (0 = empty) |
| `BatteryMv` | `int32` | Battery voltage in millivolts |

### C++ example

```cpp
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    UTokenDataSubsystem* Sub = GetGameInstance()->GetSubsystem<UTokenDataSubsystem>();
    Sub->OpenPort(TEXT("COM16"), 115200);
    Sub->OnTokenReceived.AddDynamic(this, &AMyActor::HandleToken);
}

void AMyActor::HandleToken(const FTokenData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("Token %d  slots: %d %d %d %d  batt: %d mV"),
        Data.TokenId,
        Data.Slot0, Data.Slot1, Data.Slot2, Data.Slot3,
        Data.BatteryMv);
}
```

### TokenSlotComponent

For Blueprint-only projects, add a **Token Slot Component** to any actor. It handles port opening on `BeginPlay` and exposes a single delegate:

```
OnTokenData(TokenId, Slot0, Slot1, Slot2, Slot3, BatteryMv)
```

Set `FilterTokenId` to receive events from one specific sender only, or leave it at `-1` to receive from all senders.

### Testing without hardware

```cpp
Sub->StartDummyMode(1.0f, 99);   // fires fake token events every 1 s with ID 99
Sub->StopDummyMode();
```

Also available as **Start Dummy Mode** / **Stop Dummy Mode** Blueprint nodes.

---

## Building & flashing with PlatformIO

```bash
# Flash sender (COM15)
cd sender && pio run -t upload

# Flash receiver (COM16)
cd receiver && pio run -t upload
```

After flashing, the receiver opens the Zigbee network automatically. Senders scan for the coordinator and join within a few seconds, then begin transmitting every second.

---

## Technical notes

**NVS corruption recovery** — if Zigbee NVS is corrupted (e.g. from a partition table mismatch after flashing the wrong firmware), `Zigbee.factoryReset()` is called automatically on init failure. To recover a hard bootlooping board: hold BOOT while pressing RESET to enter download mode, then flash `firmware.factory.bin` directly via esptool at offset `0x0`.

**Pull-up resistors** — the receiver PCB requires 4.7 kΩ external pull-ups on each SS connector data line. `GPIO_PULLUP_ONLY` is also set in firmware as a software backup, but external resistors are required for reliable reads.

**Interrupt masking** — 1-Wire timing windows of 3–500 µs require blocking all interrupts including the Zigbee MAC ISR. `portSET_INTERRUPT_MASK_FROM_ISR()` / `portCLEAR_INTERRUPT_MASK_FROM_ISR()` bracket every timing-critical section. All 1-Wire functions are marked `IRAM_ATTR` so they execute from IRAM and are immune to flash cache misses during the critical window.
