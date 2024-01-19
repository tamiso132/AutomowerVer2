#pragma once
/* UART 1-wire (OneWire) Free RTOS Periherial OW_UART Driver
 *
 * Created by Stanislav Lakhtin on 06.01.2020.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include "driver/uart.h"
#include "esp_private/periph_ctrl.h"
#include "hal/gpio_types.h"
#include "hal/uart_hal.h"

typedef enum mode_e
{
    Read,
    Write,
}

typedef struct Ow_t
{
    uart_port_t uart_num;
    mode_e mode;

} Ow_t;
