// Zigbee End Device — sends token messages once per second.
// Target: Seeed Xiao ESP32-C6  |  arduino-esp32 3.3.8 (pioarduino)
// Build: -DZIGBEE_MODE_ED  partition: zigbee.csv

#include <Arduino.h>
#include "Zigbee.h"
#include "onewire_manager.h"

#define TOKEN_ENDPOINT    10
#define TOKEN_CLUSTER_ID  0xFC00
#define TOKEN_ATTR_MSG    0x0000

// ── Custom ZigbeeEP: End Device sender ───────────────────────────────────────

class ZigbeeTokenSender : public ZigbeeEP {
public:
    ZigbeeTokenSender(uint8_t ep) : ZigbeeEP(ep) {
        _device_id = ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID;

        esp_zb_basic_cluster_cfg_t basic = {};
        basic.zcl_version  = ESP_ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE;
        basic.power_source = 0x03;
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
        esp_zb_cluster_list_add_custom_cluster(list, attrs, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

        _cluster_list = list;
        _ep_config = {
            .endpoint       = _endpoint,
            .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
            .app_device_id  = ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID,
            .app_device_version = 0
        };
    }

    bool sendPayload(const char* str) {
        uint8_t len = (uint8_t)strnlen(str, 127);
        uint8_t buf[129] = {};
        buf[0] = len;
        memcpy(buf + 1, str, len);

        esp_zb_zcl_custom_cluster_cmd_req_t req = {};
        req.zcl_basic_cmd.src_endpoint          = _endpoint;
        req.zcl_basic_cmd.dst_endpoint          = TOKEN_ENDPOINT;
        req.zcl_basic_cmd.dst_addr_u.addr_short = 0x0000;
        req.address_mode     = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        req.profile_id       = ESP_ZB_AF_HA_PROFILE_ID;
        req.cluster_id       = TOKEN_CLUSTER_ID;
        req.custom_cmd_id    = 0x01;
        req.direction        = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
        req.dis_default_resp = 1;
        req.data.type        = ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING;
        req.data.value       = buf;

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_custom_cluster_cmd_req(&req);
        esp_zb_lock_release();
        return true;
    }
};

// ── Globals ───────────────────────────────────────────────────────────────────

ZigbeeTokenSender zbSender(TOKEN_ENDPOINT);

static int32_t token_id = 0;

void buildMessage(char* buf, size_t buflen) {
    oneWireScan();
    int batt_mv = 3600 + random(-30, 30);
    snprintf(buf, buflen,
        "TOKEN %d [%d %d %d %d] batt:%dmV",
        token_id,
        getSlotNum(0), getSlotNum(1), getSlotNum(2), getSlotNum(3),
        batt_mv);
}

// ── Arduino ───────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    delay(400);
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip   = (uint16_t)(chipid >> 32);
    token_id = (int32_t)((uint32_t)chip << 16 | (uint32_t)(chipid & 0xFFFF));
    Serial.printf("[sender] id=%d\n", token_id);

    Zigbee.addEndpoint(&zbSender);

    if (!Zigbee.begin(ZIGBEE_END_DEVICE)) {
        Serial.println("[sender] Zigbee init failed, resetting NVS...");
        Zigbee.factoryReset();
    }

    oneWireInit();
    Serial.println("[sender] Scanning for coordinator...");
}

void loop() {
    if (!Zigbee.connected()) {
        static unsigned long lastLog = 0;
        if (millis() - lastLog >= 2000) {
            lastLog = millis();
            Serial.println("[sender] waiting for coordinator...");
        }
        delay(100);
        return;
    }

    static unsigned long lastSend = 0;
    if (millis() - lastSend >= 1000) {
        lastSend = millis();
        char msg[128];
        buildMessage(msg, sizeof(msg));
        Serial.printf("[sender] TX: %s\n", msg);
        zbSender.sendPayload(msg);
    }
}
