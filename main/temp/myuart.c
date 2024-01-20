#include "myuart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#include "stdlib.h"
#include "stdio.h"
void test_function()
{
    const uart_port_t uart_num = UART_NUM_1;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, GPIO_NUM_4, GPIO_NUM_4, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    const int uart_buffer_size = 1024 * 1; // 1kib
    QueueHandle_t uart_queue;

    // QUEUE, works FIFO( First in, First out)

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, uart_buffer_size,
                                        uart_buffer_size, 10, &uart_queue, 0));

    char *test_str = "This is a test string.\n";
    uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
}

void ow_init(Ow_t *ow)
{
    const uart_port_t uart_num = UART_NUM_0;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, GPIO_NUM_23, U0RXD_GPIO_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    const int uart_buffer_size = 128 * 2;
    //  printf("buffer size %d\n", uart_buffer_size);
    // QUEUE, works FIFO( First in, First out)
    ow->uart_num = uart_num;
    ow->mode = mode_Write;

    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size,
                                        0, 10, NULL, 0));

    // char *test_str = "This is a test string.\n";
    // uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
}

void loop_write_F()
{
    char *test_str = malloc(10000);

    for (int i = 1; i < 10000; i++)
    {
        i--;
        for (int index = 0; index < 10000; index++)
        {
            test_str[i] = 0xFF;
            i++;
        }
        // for (int index = 0; index < 5000; index++)
        // {
        //     test_str[i] = 0x00;
        //     i++;
        // }
    }

    uart_write_bytes(UART_NUM_0, (const char *)test_str, 10000);
    // ESP_ERROR_CHECK(uart_wait_tx_done(UART_NUM_0, pdMS_TO_TICKS(100000)));
    // printf("done writing serial\n");
    free(test_str);
}

// BUFFER WRITES queue
void ow_write_zero()
{
    // baudrate 115200 , 8.68055555556 us
}

void ow_reset_pulse()
{
    // baudrate 9600 , 104.166666667

    // tx, write a 0, for 5 bits --> 520 us
    // go into rx mode, read for 1 bit, 102 us
}

void ow_uart_read_byte()
{
    // Reset pulse
    //
}