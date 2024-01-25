#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum EBitRes
{
    BIT_TWELVE_RES = 0,
    BIT_ELEVEN_RES = 1,
    BIT_TEN_RES = 2,
    BIT_NINE_RES = 3,

} EBitRes;

typedef struct Onewire_t
{
    uint8_t uart_num;
    uint64_t serial_number;

} Onewire_t;

typedef struct Temp_t
{
    size_t length;
    int data;
} Temp_t;

void onewire_init(Onewire_t *ow);
uint64_t onewire_scan(Onewire_t *ow);
float ds_get_all_temp(const Onewire_t *ow);