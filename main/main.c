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
#include "temp/myuart.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

void my_task(void *pvParameters)
{

    while (1)
    {
    }
}

void app_main(void)
{
    printf("hello?\n");
    Ow_t ow;
    printf("hello?\n");
    ow_init(&ow);

    uint64_t device_code = rom_search(&ow);

    printf("family code %llu\n", get_family(device_code));
    printf("Serial code %llu\n", get_serial(device_code));

    while (1)
    {

        // esp_err_t t = e

        // if (t != ESP_OK)
        // {
        //     printf("error trying to reset\n");
        // }
        // else
        // {
        //     printf("so it resets???\n");
        // }
    }
}
