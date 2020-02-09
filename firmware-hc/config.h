#ifndef CONFIG_H
#define CONFIG_H
#include "types.h"

#define FLASH_MEM_BASE_ADDR (0x8000000)
#define FLASH_MEM_SIZE (0x80000)
#define FLASH_MEM_END_ADDR (FLASH_MEM_BASE_ADD + FLASH_MEM_SIZE - 1)

#define RAW_HID_RX_ENDPOINT 1
#define RAW_HID_TX_ENDPOINT 2

#endif