#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <driver/gpio.h>

typedef enum EBitRes
{
    BIT_TWELVE_RES = 0,
    BIT_ELEVEN_RES = 1,
    BIT_TEN_RES = 2,
    BIT_NINE_RES = 3,

} EBitRes;

typedef struct onewire_t
{
    uint8_t uart_num;
    uint64_t serial_number;

} onewire_t;

typedef struct temp_t
{
    size_t length;
    int data;
} temp_t;

void onewire_init(onewire_t *ow, uint8_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin);
uint64_t onewire_scan(onewire_t *ow);
float onewire_get_temp(const onewire_t *ow);