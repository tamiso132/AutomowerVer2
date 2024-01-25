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

void app_main(void)
{
    Onewire_t ow;
    onewire_init(&ow);

    onewire_scan(&ow);

    float temp = ds_get_all_temp(&ow);

    printf("temperature: %f\n", temp);

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
