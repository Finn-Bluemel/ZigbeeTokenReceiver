// Zigbee Coordinator — receives token messages, prints to USB Serial.
// Also programs DS2431 chips: scans SS1-SS4 for 20 s after boot and writes
// the slot number (1-4) to EEPROM address 0x00 if not already set.
//
// Target: Seeed Xiao ESP32-C6  |  arduino-esp32 3.3.8 (pioarduino)
// Build: -DZIGBEE_MODE_ZCZR  partition: zigbee_zczr.csv

#include <Arduino.h>
#include "Zigbee.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "soc/gpio_struct.h"

#define TOKEN_ENDPOINT    10
#define TOKEN_CLUSTER_ID  0xFC00
#define TOKEN_ATTR_MSG    0x0000

// ── SS connector GPIO mapping (same XIAO ESP32-C6 pinout as sender) ───────────
#define PIN_SS1   1
#define PIN_SS2   2
#define PIN_SS3  22
#define PIN_SS4  23

static const uint8_t OW_PIN[4] = {PIN_SS1, PIN_SS2, PIN_SS3, PIN_SS4};

#define DS2431_FAMILY  0x2D

// ── Thread-safe queue (Zigbee task → main loop) ───────────────────────────────

#define Q_SIZE  8
#define MSG_MAX 128

static volatile int q_head = 0, q_tail = 0;
static char q_buf[Q_SIZE][MSG_MAX];

static void qPush(const char* s) {
    int next = (q_head + 1) % Q_SIZE;
    if (next != q_tail) {
        strlcpy(q_buf[q_head], s, MSG_MAX);
        q_head = next;
    }
}
static bool qPop(char* out) {
    if (q_tail == q_head) return false;
    strlcpy(out, q_buf[q_tail], MSG_MAX);
    q_tail = (q_tail + 1) % Q_SIZE;
    return true;
}

// ── Custom ZigbeeEP: Coordinator receiver ─────────────────────────────────────

class ZigbeeTokenReceiver : public ZigbeeEP {
public:
    ZigbeeTokenReceiver(uint8_t ep) : ZigbeeEP(ep) {
        _device_id = ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID;

        esp_zb_basic_cluster_cfg_t basic = {};
        basic.zcl_version  = ESP_ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE;
        basic.power_source = 0x01;
        esp_zb_cluster_list_t* list = esp_zb_zcl_cluster_list_create();
        esp_zb_cluster_list_add_basic_cluster(
            list, esp_zb_basic_cluster_create(&basic), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

        esp_zb_identify_cluster_cfg_t ident = {};
        esp_zb_cluster_list_add_identify_cluster(
            list, esp_zb_identify_cluster_create(&ident), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

        static uint8_t empty[2] = {0, 0};
        esp_zb_attribute_list_t* attrs = esp_zb_zcl_attr_list_create(TOKEN_CLUSTER_ID);
        esp_zb_custom_cluster_add_custom_attr(
            attrs, TOKEN_ATTR_MSG,
            ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING,
            ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE,
            empty);
        esp_zb_cluster_list_add_custom_cluster(list, attrs, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

        _cluster_list = list;
        _ep_config = {
            .endpoint       = _endpoint,
            .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
            .app_device_id  = ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID,
            .app_device_version = 0
        };
    }

    void zbCustomClusterCommand(const esp_zb_zcl_custom_cluster_command_message_t* msg) override {
        if (msg->info.cluster != TOKEN_CLUSTER_ID) return;
        const uint8_t* data = static_cast<const uint8_t*>(msg->data.value);
        uint16_t size = msg->data.size;
        if (!data || size < 1) return;
        uint8_t len = data[0];
        if (len >= MSG_MAX) len = MSG_MAX - 1;
        if (len > size - 1) len = (uint8_t)(size - 1);
        char str[MSG_MAX] = {};
        memcpy(str, data + 1, len);
        qPush(str);
    }
};

// ── DS2431 1-Wire — exact copy of sender's onewire_manager.cpp ────────────────
// Direct GPIO registers + portSET_INTERRUPT_MASK_FROM_ISR, IRAM_ATTR.
// Called before Zigbee.begin() so radio is off during all 1-Wire operations.

static inline IRAM_ATTR void owDriveLow(uint8_t p) {
    GPIO.out_w1tc.val    = (1UL << p);
    GPIO.enable_w1ts.val = (1UL << p);
}
static inline IRAM_ATTR void owDriveHigh(uint8_t p) {
    GPIO.out_w1ts.val    = (1UL << p);
    GPIO.enable_w1ts.val = (1UL << p);
}
static inline IRAM_ATTR void owRelease(uint8_t p) {
    GPIO.enable_w1tc.val = (1UL << p);
}
static inline IRAM_ATTR int owReadPin(uint8_t p) {
    return (int)((GPIO.in.val >> p) & 1U);
}

static bool IRAM_ATTR owReset(uint8_t p) {
    owDriveLow(p);
    esp_rom_delay_us(500);
    UBaseType_t s = portSET_INTERRUPT_MASK_FROM_ISR();
    owRelease(p);
    esp_rom_delay_us(70);
    int v = owReadPin(p);
    portCLEAR_INTERRUPT_MASK_FROM_ISR(s);
    esp_rom_delay_us(410);
    return (v == 0);
}

static void IRAM_ATTR owWriteBit(uint8_t p, int bit) {
    UBaseType_t s = portSET_INTERRUPT_MASK_FROM_ISR();
    owDriveLow(p);
    if (bit) { esp_rom_delay_us(5);  owRelease(p); portCLEAR_INTERRUPT_MASK_FROM_ISR(s); esp_rom_delay_us(60); }
    else     { esp_rom_delay_us(65); owRelease(p); portCLEAR_INTERRUPT_MASK_FROM_ISR(s); esp_rom_delay_us(5);  }
}

static int IRAM_ATTR owReadBit(uint8_t p) {
    UBaseType_t s = portSET_INTERRUPT_MASK_FROM_ISR();
    owDriveLow(p);
    esp_rom_delay_us(3);
    owRelease(p);
    esp_rom_delay_us(10);
    int v = owReadPin(p);
    portCLEAR_INTERRUPT_MASK_FROM_ISR(s);
    esp_rom_delay_us(53);
    return v;
}

static void owWriteByte(uint8_t p, uint8_t b) {
    for (int i = 0; i < 8; i++) { owWriteBit(p, b & 1); b >>= 1; }
}
static uint8_t owReadByte(uint8_t p) {
    uint8_t r = 0;
    for (int i = 0; i < 8; i++) r |= (owReadBit(p) << i);
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

// Read one byte from DS2431 EEPROM at address
static uint8_t ds2431ReadByte(uint8_t p, uint16_t addr) {
    if (!owReset(p)) return 0xFF;
    owWriteByte(p, 0xCC);             // SKIP_ROM
    owWriteByte(p, 0xF0);             // READ_MEMORY
    owWriteByte(p, addr & 0xFF);
    owWriteByte(p, (addr >> 8) & 0xFF);
    return owReadByte(p);
}

// Write value to DS2431 address 0x00 (full page 0, 8 bytes).
// Drives pin HIGH for 12 ms as strong pull-up during EEPROM programming.
static bool ds2431WriteSlot(uint8_t p, uint8_t value) {
    // Write Scratchpad
    if (!owReset(p)) return false;
    owWriteByte(p, 0xCC);  owWriteByte(p, 0x0F);  // SKIP_ROM, WRITE_SP
    owWriteByte(p, 0x00);  owWriteByte(p, 0x00);  // TA1, TA2
    owWriteByte(p, value);
    for (int i = 1; i < 8; i++) owWriteByte(p, 0x00);

    // Read Scratchpad — get authorization bytes
    if (!owReset(p)) return false;
    owWriteByte(p, 0xCC);  owWriteByte(p, 0xAA);  // SKIP_ROM, READ_SP
    uint8_t ta1 = owReadByte(p);
    uint8_t ta2 = owReadByte(p);
    uint8_t es  = owReadByte(p);
    uint8_t d0  = owReadByte(p);
    for (int i = 1; i < 8; i++) owReadByte(p);

    if (ta1 != 0x00 || ta2 != 0x00 || d0 != value) return false;

    // Copy Scratchpad + strong pull-up for tPROG
    if (!owReset(p)) return false;
    owWriteByte(p, 0xCC);  owWriteByte(p, 0x55);  // SKIP_ROM, COPY_SP
    owWriteByte(p, ta1);   owWriteByte(p, ta2);   owWriteByte(p, es);
    owDriveHigh(p);
    esp_rom_delay_us(12000);   // 12 ms strong pull-up
    owRelease(p);

    delayMicroseconds(2000);
    return (ds2431ReadByte(p, 0x00) == value);
}

// Scan all 4 SS slots: if DS2431 present and slot not yet written, write it.
static void ds2431ProgramScan() {
    for (int b = 0; b < 4; b++) {
        uint8_t p = OW_PIN[b];
        // READ_ROM — check family
        bool found = false;
        for (int attempt = 0; attempt < 3 && !found; attempt++) {
            if (!owReset(p)) continue;
            owWriteByte(p, 0x33);   // READ_ROM
            uint8_t rom[8];
            for (int j = 0; j < 8; j++) rom[j] = owReadByte(p);
            if (crc8(rom, 7) != rom[7])  continue;
            if (rom[0] != DS2431_FAMILY) continue;
            found = true;
        }
        uint8_t slotNum = (uint8_t)(b + 1);
        if (!found) {
            Serial.printf("[prog] SS%d GPIO%02d no chip\n", b + 1, p);
            continue;
        }

        uint8_t current = ds2431ReadByte(p, 0x00);
        if (current == slotNum) {
            Serial.printf("[prog] SS%d slot=%d already set\n", b + 1, slotNum);
        } else {
            bool ok = ds2431WriteSlot(p, slotNum);
            Serial.printf("[prog] SS%d wrote slot=%d (was 0x%02X) %s\n",
                b + 1, slotNum, current, ok ? "OK" : "FAIL");
        }
    }
}

// ── Globals ───────────────────────────────────────────────────────────────────

ZigbeeTokenReceiver zbReceiver(TOKEN_ENDPOINT);

// ── Arduino ───────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    delay(400);

    // ── Phase 1: program DS2431 chips BEFORE Zigbee starts ───────────────────
    // Single pass — fast (~50 ms). Radio off so no ISR interference.
    for (int b = 0; b < 4; b++) {
        gpio_reset_pin((gpio_num_t)OW_PIN[b]);
        gpio_set_direction((gpio_num_t)OW_PIN[b], GPIO_MODE_INPUT);
        gpio_set_pull_mode((gpio_num_t)OW_PIN[b], GPIO_PULLUP_ONLY);
    }
    ds2431ProgramScan();

    // ── Phase 2: start Zigbee coordinator ────────────────────────────────────
    Zigbee.addEndpoint(&zbReceiver);
    if (!Zigbee.begin(ZIGBEE_COORDINATOR)) {
        Serial.println("[receiver] Zigbee init failed — halting");
        for (;;) delay(1000);
    }
    Zigbee.openNetwork(254);
    Serial.println("[receiver] ready");
}

void loop() {
    // Permit-join refresh
    static unsigned long lastOpen = 0;
    if (millis() - lastOpen >= 120000) {
        lastOpen = millis();
        Zigbee.openNetwork(254);
    }

    // Forward received Zigbee messages to USB serial
    char msg[MSG_MAX];
    while (qPop(msg)) {
        Serial.println(msg);
    }
    delay(10);
}
