/**
 * @file    bsp_crc32.h
 * @author  Deadline039
 * @brief   STM32 硬件 CRC
 * @version 1.0
 * @date    2025-02-28
 */

#ifndef __CRC_H
#define __CRC_H

#include <CSP_Config.h>

void bsp_crc32_init(void);
uint32_t bsp_crc32_calc(uint8_t *data, uint32_t len);

#endif /* __CRC_H */
