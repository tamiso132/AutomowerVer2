#include "myuart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <esp_log.h>

#include "stdlib.h"
#include "stdio.h"

typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffffffffUL

#define BASE_GPIO GPIO_NUM_19

uint8_t myuart_init()
{
    const uint8_t uart_num = UART_NUM_1;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };

    uart_param_config(uart_num, &uart_config);
    uart_set_pin(uart_num, GPIO_NUM_23, GPIO_NUM_22, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    const int uart_buffer_size = 128 * 2;

    uart_driver_install(uart_num, uart_buffer_size,
                        uart_buffer_size, 0, NULL, 0);

    return uart_num;
}

// TODO, there can be numerious read after each other instead of using up a cycle
uint8_t myuart_read_time_slot(uint8_t uart_num)
{
    const uint8_t initiate_read = 0xFF; // hold for at least 1 micro second
    uart_write_bytes(uart_num, &initiate_read, 1);
    uart_write_bytes(uart_num, initiate_read, sizeof(initiate_read)); // start bit pulls low for 8
    char buffer[1];
    uart_read_bytes(uart_num, &buffer, sizeof(buffer), portMAX_DELAY); // first bit tells
    return buffer[0];
}

void myuart_write_bytes(uint8_t uart_num, uint8_t *p_byte, size_t length)
{

    uart_write_bytes(uart_num, p_byte, length);
}
