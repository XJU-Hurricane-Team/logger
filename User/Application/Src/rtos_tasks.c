/**
 * @file    rtos_tasks.c
 * @author  Deadline039
 * @brief   RTOS tasks.
 * @version 1.0
 * @date    2024-01-31
 */

#include "includes.h"

#include <logger/logger.h>

static TaskHandle_t start_task_handle;
void start_task(void *pvParameters);

static TaskHandle_t task1_handle;
void task1(void *pvParameters);

static TaskHandle_t task2_handle;
void task2(void *pvParameters);

static TaskHandle_t task3_handle;
void task3(void *pvParameters);

/*****************************************************************************/

/**
 * @brief FreeRTOS start up.
 *
 */
void freertos_start(void) {
    xTaskCreate(start_task, "start_task", 128, NULL, 2, &start_task_handle);
    vTaskStartScheduler();
}

/**
 * @brief Start up task.
 *
 * @param pvParameters Start parameters.
 */
void start_task(void *pvParameters) {
    UNUSED(pvParameters);
    taskENTER_CRITICAL();

    xTaskCreate(task1, "task1", 128, NULL, 2, &task1_handle);
    xTaskCreate(task2, "task2", 128, NULL, 2, &task2_handle);
    xTaskCreate(task3, "task3", 128, NULL, 2, &task3_handle);

    log_init(LOG_INFO);

    vTaskDelete(start_task_handle);
    taskEXIT_CRITICAL();
}

/**
 * @brief Task1: Blink.
 *
 * @param pvParameters Start parameters.
 */
void task1(void *pvParameters) {
    UNUSED(pvParameters);

    LED0_OFF();
    LED1_ON();

    while (1) {
        LED0_TOGGLE();
        LED1_TOGGLE();
        vTaskDelay(1000);
    }
}

/**
 * @brief Task2: print running time.
 *
 * @param pvParameters Start parameters.
 */
void task2(void *pvParameters) {
    UNUSED(pvParameters);

    while (1) {
        log_message(
            LOG_INFO,
            "STM32F4xx FreeRTOS project template. Running time: %d ms. ",
            xTaskGetTickCount());
        vTaskDelay(1000);
    }
}

/**
 * @brief Task3: Scan the key and print which key pressed.
 *
 * @param pvParameters Start parameters.
 */
void task3(void *pvParameters) {
    UNUSED(pvParameters);

    key_press_t key = KEY_NO_PRESS;

    while (1) {
        key = key_scan(0);
        switch (key) {
            case WKUP_PRESS: {
                log_message(LOG_INFO, "WKUP Pressed, set log level to FATAL. ");
                log_set_level(LOG_FATAL);
            } break;

            case KEY0_PRESS: {
                log_set_level(LOG_INFO);
                log_message(LOG_INFO, "KEY0 Pressed, set log level to INFO. ");
            } break;

            case KEY1_PRESS: {
                log_message(LOG_WARNING, "KEY1 Pressed! ");
            } break;

            case KEY2_PRESS: {
                log_message(LOG_FATAL, "KEY2 Pressed! ");
            } break;

            default: {
            } break;
        }
        vTaskDelay(10);
    }
}
