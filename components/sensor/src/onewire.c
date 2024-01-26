#include "myuart.h"
#include <esp_log.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "onewire.h"

const uint8_t FUNC_TEMP_CONVERT = 0x44;
const uint8_t FUNC_RECALL = 0xB8;
const uint8_t FUNC_READ_POWER_MODE = 0xB4;

const uint8_t FUNC_READ_SCRATCH = 0xBE;
const uint8_t FUNC_WRITE_SCRATCH = 0x4E;
const uint8_t FUNC_COPY_SCRATCH = 0x48;
const uint8_t ROM_READ = 0x33;
// Match with specific device
const uint8_t ROM_MATCH = 0x55;

// Adress All Devices
const uint8_t ROM_SKIP = 0xCC;
const uint8_t ROM_SEARCH = 0xF0;
const uint8_t ROM_ALARM_SEARCH = 0xEC;

#define TEMP_LOWEST_FRACTION 0.0625

#define portMAX_DELAY (uint32_t)0xffffffffUL

static uint8_t crc_table[] = {
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35};

// HELPER
static uint8_t calculate_crc8(const uint8_t *data, size_t length);

// GETTER
static uint8_t get_family(uint64_t data);
static uint64_t get_serial(uint64_t data);

// onewire
static void ow_reset_pulse(const onewire_t *ow);
static void ow_read_scratchpad(const onewire_t *ow, uint64_t serial_number, size_t bytes_read, uint8_t *data);

static void onewire_write_bytes(const onewire_t *ow, const uint8_t *p_byte, size_t length);
static void onewire_write_bit(const onewire_t *ow, uint8_t bit);

static void onewire_read_bytes(const onewire_t *ow, size_t length, uint8_t *data_read);
static float calculate_temp(uint16_t temp, EBitRes res);

void onewire_init(onewire_t *ow, uint8_t uart_num, gpio_num_t tx_pin, gpio_num_t rx_pin)
{
    ow->uart_num = myuart_init(uart_num, tx_pin, rx_pin);
}

// implement, finding all devices
uint64_t onewire_scan(onewire_t *ow)
{
    ow_reset_pulse(ow);

    const uint8_t opcode_code = 0xF0;
    onewire_write_bytes(ow, &opcode_code, 1);
    uint64_t data = 0;
    for (int i = 0; i < 64; i++)
    {
        uint8_t least_significant = myuart_read_time_slot(ow->uart_num) & 1;
        uint8_t most_significant = myuart_read_time_slot(ow->uart_num) & 1;

        if (least_significant != most_significant)
        {
            data |= (((uint64_t)least_significant) << i);
            onewire_write_bit(ow, least_significant & 1);
        }
        else if ((least_significant & most_significant) == 0)
        {
            ESP_LOGD("Rom Search", "Collision Detected");
            // TODO, implement collsiion stuff
        }
        else
        {
            ESP_LOGE("Rom Search", "Both 1s");
        }
    }

    uint8_t crc = data >> (64 - 8);
    uint8_t cal_crc = calculate_crc8((const uint8_t *)&data, 7);
    if (cal_crc == crc)
    {
        printf("Serial: %llx\n", data);
    }
    else
    {
        ESP_LOGE("ROM SEARCH", "CRC NOT CORRECT");
        onewire_scan(ow);
    }
    ow->serial_number = data;
    return data;
}

float onewire_get_temp(const onewire_t *ow)
{

    uint8_t *nr = (uint8_t *)&ow->serial_number;
    const uint8_t command[] = {ROM_MATCH, nr[0], nr[1], nr[2], nr[3], nr[4], nr[5], nr[6], nr[7], FUNC_TEMP_CONVERT};

    ow_reset_pulse(ow);

    onewire_write_bytes(ow, command, sizeof(command));

    // match all known devices, and check their temp
    uint8_t bit = (myuart_read_time_slot(ow->uart_num) & 1);
    while (!bit)
    {
        vTaskDelay(750 / portTICK_PERIOD_MS);
        ESP_LOGD("Task delayed", "Task delayed");
        bit = (myuart_read_time_slot(ow->uart_num) & 1);
    }

    uint8_t data[9];

    ow_read_scratchpad(ow, ow->serial_number, sizeof(data), data);

    uint16_t temp = *((uint16_t *)data);

    return calculate_temp(temp, BIT_TWELVE_RES);
}

EBitRes get_res_state(const onewire_t *ow)
{
    uint64_t data;
    ow_read_scratchpad(ow, ow->serial_number, sizeof(data), (uint8_t *)&data);
    uint8_t config = ((uint8_t *)&data)[4] & 0xFF;
    uint8_t R = (config >> 5) | ((config >> 6) << 1);

    // R = 3, 12
    // R = 2, 11
    // R = 1, 10
    // R = 0, 9
    return (EBitRes)(3 - R);
}

static void ow_reset_pulse(const onewire_t *ow)
{
    uart_set_baudrate(ow->uart_num, 9600);
    fflush(stdout);
    uint8_t write = 0xF0;
    uart_write_bytes(ow->uart_num, &write, 1);

    char read_buffer[1];
    uart_read_bytes(ow->uart_num, &read_buffer, 1, portMAX_DELAY);

    uart_set_baudrate(ow->uart_num, 115200);

    ESP_LOGD("Reset Pulse", "%x", read_buffer[0]);
    fflush(stdout);
}

static void ow_read_scratchpad(const onewire_t *ow, uint64_t serial_number, size_t bytes_read, uint8_t *data)
{
    ow_reset_pulse(ow);
    uint8_t *serial = (uint8_t *)&serial_number;

    printf("serial number %llx\n", *(uint64_t *)serial);

    const uint8_t command[] = {ROM_MATCH,
                               serial[0], serial[1], serial[2], serial[3], serial[4], serial[5], serial[6], serial[7],
                               FUNC_READ_SCRATCH};

    onewire_write_bytes(ow, command, sizeof(command));

    onewire_read_bytes(ow, bytes_read, data);
}

static uint8_t get_family(uint64_t data)
{
    return (uint8_t)(data & 0xFF);
}
static uint64_t get_serial(uint64_t data)
{
    data = (data << 8);  // delete CRC
    data = (data >> 16); // delete family
    return data;
}

static uint8_t calculate_crc8(const uint8_t *data, size_t length)
{
    uint8_t crc = 0x00;
    for (size_t i = 0; i < length; i++)
        crc = crc_table[crc ^ data[i]];
    return crc;
}

static float calculate_temp(uint16_t temp, EBitRes res)
{

    float temp_celsius = 0;

    uint8_t signed_bits = (temp >> 11);
    uint8_t sign_bit = signed_bits & 1;

    uint8_t whole_number_bits = (uint8_t)(temp >> 4);

    uint16_t signed_bits_extend = signed_bits | (signed_bits << 3);

    uint16_t whole_value = whole_number_bits ^ signed_bits_extend;

    /// Fraction value depending on resolution
    /// 0.0625, 0.125,  0.25, 0.5
    float fraction = ((float)((temp & 0x00F))) / (1 << (4 - res)) - (signed_bits & 1);

    temp_celsius += (float)whole_value;
    *(uint32_t *)&temp_celsius ^= ((uint32_t)sign_bit) << (31);
    temp_celsius += fraction;

    return temp_celsius;
}

static void onewire_write_bytes(const onewire_t *ow, const uint8_t *p_byte, size_t length)
{
    uint8_t r[length * 8];
    for (int byte_nr = 0; byte_nr < length; byte_nr++)
    {
        uint8_t byte = p_byte[byte_nr];
        for (int i = 0; i < 8; i++)
        {
            uint8_t send_bit = ~((byte >> i) & 1) + 1;

            myuart_write_bytes(ow->uart_num, &send_bit, 1);
        }
    }
    uart_read_bytes(ow->uart_num, &r, sizeof(r), portMAX_DELAY);
}

static void onewire_write_bit(const onewire_t *ow, uint8_t bit)
{
    uint8_t send_bit = ~bit + 1;
    uint8_t r = 0;
    uart_write_bytes(ow->uart_num, &send_bit, 1);
    uart_read_bytes(ow->uart_num, &r, 1, portMAX_DELAY);
}

static void onewire_read_bytes(const onewire_t *ow, size_t length, uint8_t *data_read)
{
    for (size_t byte_nr = 0; byte_nr < length; byte_nr++)
    {
        uint8_t byte = 0;
        for (size_t bit_nr = 0; bit_nr < 8; bit_nr++)
        {
            byte |= (myuart_read_time_slot(ow->uart_num) & 1) << bit_nr;
        }
        data_read[byte_nr] = byte;
    }
}

// alternative temp conversion
float calcf(uint16_t input)
{
    bool s = ((input >> 11) != 0);
    float fraction = 1 - (float)(input & 0b1111) / 16;
    float integer = (uint8_t)((s ? ~input : input) >> 4);
    return (integer + fraction) * (s ? -1 : 1);
}
