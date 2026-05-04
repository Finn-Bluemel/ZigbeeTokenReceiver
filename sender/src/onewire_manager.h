#pragma once
#include <Arduino.h>

void    oneWireInit();
void    oneWireScan();

String  getSlotId(int slotIndex);
uint8_t getSlotNum(int slotIndex);

bool    oneWireDevicesPresent();
