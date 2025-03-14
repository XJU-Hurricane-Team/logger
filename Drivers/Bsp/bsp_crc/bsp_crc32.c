/**
 * @file    bsp_crc32.c
 * @author  Deadline039
 * @brief   STM32 硬件 CRC
 * @version 1.0
 * @date    2025-02-28
 */

#include "bsp_crc32.h"

#include <string.h>

/**
 * @brief 初始化 CRC32
 * 
 */
void bsp_crc32_init(void) {
    __HAL_RCC_CRC_CLK_ENABLE();
}

/**
 * @brief 计算 CRC32
 * 
 * @param data 数据
 * @param len 数据长度
 * @return 校验结果
 */
uint32_t bsp_crc32_calc(uint8_t *data, uint32_t len) {
    uint32_t index = 0;
    uint32_t temp = 0U;
    index = len >> 2;
 
    /* 重置 CRC 计算值 */
    CRC->CR |= CRC_CR_RESET;

    while (index--) {
        CRC->DR = __RBIT(*(uint32_t *)data);
        data += 4;
    }
    temp = __RBIT(CRC->DR);

    index = len & 0x03;

    while (index--) {
        temp ^= (uint32_t)*data++;
        for (uint32_t i = 0; i < 8; ++i) {
            if (temp & 0x01) {
                temp = (temp >> 1) ^ 0xEDB88320;
            } else {
                temp = (temp >> 1);
            }
        }
    }

    return temp ^ 0xFFFFFFFF;
}
