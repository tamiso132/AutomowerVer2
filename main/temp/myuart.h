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
#include "esp_private/periph_ctrl.h"
#include "hal/gpio_types.h"
#include "driver/uart.h"

typedef enum mode_e
{
    mode_Read,
    mode_Write,
} mode_e;

typedef struct Ow_t
{
    uart_port_t uart_num;
    mode_e mode;
    QueueHandle_t uart_queue;

} Ow_t;

void ow_init(Ow_t *ow);
void ow_reset_pulse(Ow_t *ow);

void loop_write_F();
