#pragma once

// ── OneWire bus count ────────────────────────────────────────────────────────
#define NUM_OW_BUSES  4

// ── GPIO pin mapping (XIAO ESP32-C6 SMD pads → GPIO numbers) ────────────────
// PCB netlist: SS1=U1.2=D1, SS2=U1.3=D2, SS3=U1.5=D4, SS4=U1.6=D5
// Verify against your board's pinout if readings look wrong.
#define PIN_OW1   1   // SS1 — GPIO1_A1_D1  (U1 pin 2)
#define PIN_OW2   2   // SS2 — GPIO2_A2_D2  (U1 pin 3)
#define PIN_OW3  22   // SS3 — GPIO22_D4    (U1 pin 5)
#define PIN_OW4  23   // SS4 — GPIO23_D5    (U1 pin 6)

// ── DS2413 family code ───────────────────────────────────────────────────────
#define DS2413_FAMILY_CODE   0x3A
#define DS2413_CMD_READ_PIO  0xF5

// ── Coral type encoding via DS2413 PIO channels ──────────────────────────────
// Each coral piece has a DS2413 with PIOA and PIOB pulled low via resistors to
// encode its type (2 bits → 4 values):
//   PIOB=0 PIOA=0 → type 1
//   PIOB=0 PIOA=1 → type 2
//   PIOB=1 PIOA=0 → type 3
//   PIOB=1 PIOA=1 → type 4
// No device on bus → type 0 (empty slot)
