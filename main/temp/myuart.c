#include "myuart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <esp_log.h>

#include "stdlib.h"
#include "stdio.h"

#define ONEWIRE_RESET 0xF0

typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffffffffUL

#define BASE_GPIO GPIO_NUM_19

#define MASK_FAMILY 0xFF

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
                        uart_buffer_size, 0, NULL, 0);

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

void ow_reset_pulse(const Ow_t *ow)
{
    uart_set_baudrate(ow->uart_num, 9600);
    fflush(stdout);
    uint8_t write = 0xF0;
    uart_write_bytes(ow->uart_num, &write, 1);

    char read_buffer[1];
    int read_bytes = uart_read_bytes(ow->uart_num, &read_buffer, 1, portMAX_DELAY);

    printf("Reset pulse: %d\n", read_buffer[0]);
    fflush(stdout);
}

// BUFFER WRITES queue
// TODO, CAN WRITE MULTPLE AT SAME TIME, OPTIMIZATION
uint8_t ow_write_zero(const Ow_t *ow)
{
    static const char write_zero[] = {0x00};
    uint8_t x = 0;
    uart_set_baudrate(ow->uart_num, 115200); // 8.6806 us per bit
    uart_write_bytes(ow->uart_num, (const char *)&write_zero, sizeof(write_zero));
    uart_read_bytes(ow->uart_num, &x, 1, portMAX_DELAY);
    return x;
}

uint8_t ow_write_one(const Ow_t *ow)
{
    static const char write_one[] = {0xFF};
    uint8_t x = 0;
    uart_set_baudrate(ow->uart_num, 115200); // 8.6806 us per bit
    uart_write_bytes(ow->uart_num, (const char *)&write_one, sizeof(write_one));
    uart_read_bytes(ow->uart_num, &x, 1, portMAX_DELAY);
    return x;
}

// TODO, there can be numerious read after each other instead of using up a cycle
uint8_t ow_uart_read_bit(const Ow_t *ow)
{
    const char initiate_read[] = {0xFF}; // hold for at least 1 micro second

    uart_set_baudrate(ow->uart_num, 115200);                              // 8.6806 us per bit
    uart_write_bytes(ow->uart_num, initiate_read, sizeof(initiate_read)); // start bit pulls low for 8
    char buffer[1];
    uart_read_bytes(ow->uart_num, &buffer, sizeof(buffer), portMAX_DELAY); // first bit tells
    ESP_LOGD("Read value", "%x", buffer[0]);
    return buffer[0];
}

void ow_write_bytes(const Ow_t *ow, uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        uint8_t send_bit = byte & 1;
        if (send_bit == 0)
        {
            uint8_t x = ow_write_zero(ow);
            ESP_LOGD("Write-0", "%d", x);
        }
        else
        {
            uint8_t x = ow_write_one(ow);
            ESP_LOGD("Write-1", "%d", x);
        }
        byte >>= 1;
    }
}

uint64_t rom_search(const Ow_t *ow)
{
    uint8_t device_collision = 0;

    ow_reset_pulse(ow);

    const uint8_t opcode = 0xF0;

    ow_write_bytes(ow, opcode);

    printf("########################################################\n");

    uint64_t data = 0;
    for (int i = 0; i < 63; i++)
    {
        uint8_t least_significant = ow_uart_read_bit(ow);
        uint8_t most_significant = ow_uart_read_bit(ow);

        uint8_t bit = least_significant & 1;

        printf("Least: %d\n", bit);

        if (bit == 1)
        {
            data |= (1 << i);
            printf("i value: %d\n", i);
            printf("8 bits: %d\n", (uint8_t)(data & 0xFF));
            ow_write_one(ow);
        }
        else if (bit == 0)
        {
            printf("zero time\n");
            ow_write_zero(ow);
        }
    }

    printf("Data 8: %d\n", (uint8_t)(data & 0xFF));
    return data;
}

uint8_t get_family(uint64_t data)
{
    uint8_t print[8];
    for (int i = 0; i < 8; i++)
    {
        print[i] = (data >> i) & 1;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%d", print[7 - i]);
    }
    printf("\n");
    return (uint8_t)(data & 0xFF);
}
uint64_t get_serial(uint64_t data)
{
    data = (data << 8);  // delete CRC
    data = (data >> 16); // delete family
    return data;
}
