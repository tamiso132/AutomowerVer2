#include "myuart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "stdlib.h"
#include "stdio.h"

#define ONEWIRE_RESET 0xF0

static const char ONEWIRE_WRITE_ZERO[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char ONEWIRE_WRITE_ONE[] = {0x00};

static const char ONEWIRE_INITATE_READ[] = {0x00};

typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffffffffUL

#define BASE_GPIO GPIO_NUM_19

void test_function()
{
    const uart_port_t uart_num = UART_NUM_0;
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

    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size,
                                        uart_buffer_size, 10, &uart_queue, 0));
}

void ow_init(Ow_t *ow)
{
    const uart_port_t uart_num = UART_NUM_1;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };

    uart_param_config(uart_num, &uart_config);
    gpio_set_level(GPIO_NUM_23, 0);
    uart_set_pin(uart_num, GPIO_NUM_23, GPIO_NUM_22, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    const int uart_buffer_size = 128 * 2;
    //  printf("buffer size %d\n", uart_buffer_size);
    // QUEUE, works FIFO( First in, First out)
    ow->uart_num = uart_num;
    ow->mode = mode_Write;

    uart_driver_install(uart_num, uart_buffer_size,
                        uart_buffer_size, 10, &ow->uart_queue, 0);

    printf("does it come here?\n");
    gpio_set_direction(BASE_GPIO, GPIO_MODE_OUTPUT);
    // char *test_str = "This is a test string.\n";
    // uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
    // gpio_config_t config;
    // gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    // gpio_set_level(GPIO_NUM_19, 1);
}

void loop_write_F()
{
    char *test_str = malloc(10000);
    for (int i = 1; i < 10000; i++)
    {
        i--;
        for (int index = 0; index < 10000; index++)
        {
            test_str[i] = 0x00;
            i++;
        }
    }

    uart_write_bytes(UART_NUM_0, (const char *)test_str, 10000);
    // ESP_ERROR_CHECK(uart_wait_tx_done(UART_NUM_0, pdMS_TO_TICKS(100000)));
    // printf("done writing serial\n");
    free(test_str);
}

void ow_reset_pulse(Ow_t *ow)
{
    uart_set_baudrate(ow->uart_num, 9600);
    fflush(stdout);
    uint8_t write = 0xF0;
    uart_write_bytes(ow->uart_num, &write, 1);

    char *read_buffer = malloc(1);
    int read_bytes = uart_read_bytes(ow->uart_num, read_buffer, 1, portMAX_DELAY);
    printf("\n\nbuffer %x\n", *read_buffer);
    fflush(stdout);
}

// BUFFER WRITES queue
void ow_write_zero(Ow_t *ow)
{
    uart_set_baudrate(ow->uart_num, 115200); // 8.6806 us per bit
    uart_write_bytes(ow->uart_num, (const char *)&WRITE_ZERO, sizeof(WRITE_ZERO));
    uart_wait_tx_done(ow->uart_num, portMAX_DELAY);
}

void ow_uart_read_byte()
{
    // Reset pulse
    //
}