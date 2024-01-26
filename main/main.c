/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_task_wdt.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

#include "onewire.h"
#include "sensor_avoid.h"

void app_main(void)
{
    // onewire_t ow;
    // onewire_init(&ow, 1, GPIO_NUM_23, GPIO_NUM_22);

    // onewire_scan(&ow);

    // float temp = onewire_get_temp(&ow);

    // printf("temperature: %f\n", temp);
    sensor_avoid_t avoid;
    init_sensor(&avoid, GPIO_NUM_15);

    int cnt = 0;
    while (1)
    {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
