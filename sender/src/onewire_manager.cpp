// Direct 1-Wire for DS2431 (family 0x2D) — READ ONLY.
// Uses portSET_INTERRUPT_MASK_FROM_ISR() to disable all interrupt levels
// (including Zigbee MAC ISR) for timing-critical µs windows.

#include "onewire_manager.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "soc/gpio_struct.h"

#define DS2431_FAMILY  0x2D

static const uint8_t OW_PIN[NUM_OW_BUSES] = {PIN_OW1, PIN_OW2, PIN_OW3, PIN_OW4};

static String  busID[NUM_OW_BUSES];
static uint8_t busSlot[NUM_OW_BUSES];
static bool    anyPresent = false;

// ── GPIO helpers ───────────────────────────────────────────────────────────────

static inline IRAM_ATTR void owDriveLow(uint8_t pin) {
    GPIO.out_w1tc.val    = (1UL << pin);
    GPIO.enable_w1ts.val = (1UL << pin);
}
static inline IRAM_ATTR void owRelease(uint8_t pin) {
    GPIO.enable_w1tc.val = (1UL << pin);
}
static inline IRAM_ATTR int owReadPin(uint8_t pin) {
    return (int)((GPIO.in.val >> pin) & 1U);
}

// ── 1-Wire primitives ──────────────────────────────────────────────────────────

static bool IRAM_ATTR owReset(uint8_t pin) {
    owDriveLow(pin);
    esp_rom_delay_us(500);
    UBaseType_t saved = portSET_INTERRUPT_MASK_FROM_ISR();
    owRelease(pin);
    esp_rom_delay_us(70);
    int v = owReadPin(pin);
    portCLEAR_INTERRUPT_MASK_FROM_ISR(saved);
    esp_rom_delay_us(410);
    return (v == 0);
}

static void IRAM_ATTR owWriteBit(uint8_t pin, int bit) {
    UBaseType_t saved = portSET_INTERRUPT_MASK_FROM_ISR();
    owDriveLow(pin);
    if (bit) {
        esp_rom_delay_us(5);
        owRelease(pin);
        portCLEAR_INTERRUPT_MASK_FROM_ISR(saved);
        esp_rom_delay_us(60);
    } else {
        esp_rom_delay_us(65);
        owRelease(pin);
        portCLEAR_INTERRUPT_MASK_FROM_ISR(saved);
        esp_rom_delay_us(5);
    }
}

static int IRAM_ATTR owReadBit(uint8_t pin) {
    UBaseType_t saved = portSET_INTERRUPT_MASK_FROM_ISR();
    owDriveLow(pin);
    esp_rom_delay_us(3);
    owRelease(pin);
    esp_rom_delay_us(10);
    int v = owReadPin(pin);
    portCLEAR_INTERRUPT_MASK_FROM_ISR(saved);
    esp_rom_delay_us(53);
    return v;
}

static void owWriteByte(uint8_t pin, uint8_t b) {
    for (int i = 0; i < 8; i++) { owWriteBit(pin, b & 1); b >>= 1; }
}
static uint8_t owReadByte(uint8_t pin) {
    uint8_t r = 0;
    for (int i = 0; i < 8; i++) r |= (owReadBit(pin) << i);
    return r;
}

static uint8_t crc8(const uint8_t* d, int len) {
    uint8_t crc = 0;
    for (int i = 0; i < len; i++) {
        uint8_t b = d[i];
        for (int j = 0; j < 8; j++) {
            if ((crc ^ b) & 1) crc = (crc >> 1) ^ 0x8C;
            else               crc >>= 1;
            b >>= 1;
        }
    }
    return crc;
}

static String addrToHex(const uint8_t addr[8]) {
    String s;
    for (int i = 1; i < 7; i++) {
        if (addr[i] < 0x10) s += '0';
        s += String(addr[i], HEX);
    }
    s.toUpperCase();
    return s;
}

// ── Public API ─────────────────────────────────────────────────────────────────

void oneWireInit() {
    for (int b = 0; b < NUM_OW_BUSES; b++) {
        gpio_reset_pin((gpio_num_t)OW_PIN[b]);
        gpio_set_direction((gpio_num_t)OW_PIN[b], GPIO_MODE_INPUT);
    }
}

void oneWireScan() {
    anyPresent = false;
    for (int b = 0; b < NUM_OW_BUSES; b++) {
        uint8_t p = OW_PIN[b];
        busID[b]   = "";
        busSlot[b] = 0;
        for (int attempt = 0; attempt < 3; attempt++) {
            if (!owReset(p)) continue;
            owWriteByte(p, 0x33);   // READ_ROM
            uint8_t rom[8];
            for (int j = 0; j < 8; j++) rom[j] = owReadByte(p);
            if (crc8(rom, 7) != rom[7])  continue;
            if (rom[0] != DS2431_FAMILY) continue;
            busID[b]   = addrToHex(rom);
            anyPresent = true;
            // Read slot number from EEPROM address 0x00
            if (owReset(p)) {
                owWriteByte(p, 0xCC);  // SKIP_ROM
                owWriteByte(p, 0xF0);  // READ_MEMORY
                owWriteByte(p, 0x00);  owWriteByte(p, 0x00);
                busSlot[b] = owReadByte(p);
            }
            break;
        }
    }
}

String  getSlotId(int slotIndex)  { return (slotIndex >= 0 && slotIndex < NUM_OW_BUSES) ? busID[slotIndex]            : ""; }
uint8_t getSlotNum(int slotIndex) { return (slotIndex >= 0 && slotIndex < NUM_OW_BUSES) ? busSlot[slotIndex] : 0; }
bool    oneWireDevicesPresent()   { return anyPresent; }
