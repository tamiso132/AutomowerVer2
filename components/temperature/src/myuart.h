#pragma once

#include <string.h>
#include "driver/uart.h"

uint8_t myuart_init();
uint8_t myuart_read_time_slot(uint8_t uart_num);
void myuart_write_bytes(uint8_t uart_num, const uint8_t *p_byte, size_t length);
