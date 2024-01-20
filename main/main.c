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

void my_task(void *pvParameters)
{
    while (1)
    {
    }
}

void app_main(void)
{

    esp_task_wdt_add(NULL);
    Ow_t ow;
    ow_init(&ow);
    loop_write_F();

    while (1)
    {
        loop_write_F();
        esp_task_wdt_reset();
    }
}
