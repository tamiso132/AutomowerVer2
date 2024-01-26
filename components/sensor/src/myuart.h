#pragma once

#include <string.h>
#include "driver/uart.h"
#include "driver/gpio.h"

uint8_t myuart_init(uint8_t uart_port, gpio_num_t tx, gpio_num_t rx);
uint8_t myuart_read_time_slot(uint8_t uart_num);
void myuart_write_bytes(uint8_t uart_num, const uint8_t *p_byte, size_t length);
