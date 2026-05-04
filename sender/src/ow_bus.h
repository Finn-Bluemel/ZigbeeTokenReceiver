#pragma once
// Minimal 1-Wire driver using Arduino digitalWrite/digitalRead.
// Avoids the direct-register GPIO path that breaks on ESP32-C6.

#include <Arduino.h>

// CRC-8 / Dallas-1Wire (poly 0x31)
static inline uint8_t ow_crc8(const uint8_t* data, uint8_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        uint8_t b = data[i];
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t mix = (crc ^ b) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            b >>= 1;
        }
    }
    return crc;
}

static inline bool ow_reset(uint8_t pin) {
    // Reset pulse: hold LOW ≥480µs
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(520);

    // Release and poll for presence pulse (device pulls low within 15–240µs)
    noInterrupts();
    pinMode(pin, INPUT_PULLUP);
    bool present = false;
    for (int i = 0; i < 300; i++) {
        delayMicroseconds(1);
        if (!digitalRead(pin)) { present = true; break; }
    }
    interrupts();

    delayMicroseconds(500);  // wait for presence pulse to end + recovery
    return present;
}

static inline void ow_write_bit(uint8_t pin, bool bit) {
    noInterrupts();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(bit ? 6 : 60);
    pinMode(pin, INPUT_PULLUP);
    delayMicroseconds(bit ? 64 : 10);
    interrupts();
}

static inline bool ow_read_bit(uint8_t pin) {
    noInterrupts();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(3);
    pinMode(pin, INPUT_PULLUP);
    delayMicroseconds(12);  // extra time for weak internal pull-up to charge line
    bool val = digitalRead(pin);
    interrupts();
    delayMicroseconds(48);
    return val;
}

static inline void ow_write_byte(uint8_t pin, uint8_t val) {
    for (int i = 0; i < 8; i++) ow_write_bit(pin, (val >> i) & 1);
}

static inline uint8_t ow_read_byte(uint8_t pin) {
    uint8_t val = 0;
    for (int i = 0; i < 8; i++) if (ow_read_bit(pin)) val |= (1 << i);
    return val;
}

// Read the 64-bit ROM address of the first device on the bus.
// Returns true on success (CRC ok + device present).
static inline bool ow_read_rom(uint8_t pin, uint8_t addr[8]) {
    if (!ow_reset(pin)) return false;
    ow_write_byte(pin, 0x33);  // READ ROM
    for (int i = 0; i < 8; i++) addr[i] = ow_read_byte(pin);
    return ow_crc8(addr, 7) == addr[7];
}

// Select a specific device by ROM address.
static inline bool ow_select(uint8_t pin, uint8_t addr[8]) {
    if (!ow_reset(pin)) return false;
    ow_write_byte(pin, 0x55);  // MATCH ROM
    for (int i = 0; i < 8; i++) ow_write_byte(pin, addr[i]);
    return true;
}
