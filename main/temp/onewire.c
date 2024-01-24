#include "myuart.h"
#include <esp_log.h>

#include "onewire.h"

#define FUNC_TEMP_CONVERT 0x44
#define FUNC_RECALL 0xB8
#define FUNC_READ_POWER_MODE 0xB4

#define FUNC_READ_SCRATCH 0xBE
#define FUNC_WRITE_SCRATCH 0x4E
#define FUNC_COPY_SCRATCH 0x48
#define ROM_READ 0x33
// Match with specific device
#define ROM_MATCH 0x55

// Adress All Devices
#define ROM_SKIP 0xCC
#define ROM_SEARCH 0xF0
#define ROM_ALARM_SEARCH 0xEC

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

#pragma region PRIVATE_REGION

// HELPER
static uint8_t calculate_crc8(const uint8_t *data, size_t length);

// GETTER
static uint8_t get_family(uint64_t data);
static uint64_t get_serial(uint64_t data);

// onewire
static void ow_reset_pulse(const Onewire_t *ow);
static void onewire_write_bytes(const Onewire_t *ow, uint8_t *p_byte, size_t length);

#pragma endregion PRIVATE_REGION

// implement, finding all devices
uint64_t onewire_scan(const Onewire_t *ow)
{

    ow_reset_pulse(ow);

    const uint8_t opcode = ROM_SEARCH;
    myuart_write_bytes(ow, &opcode, sizeof(opcode));

    uint64_t data = 0;
    for (int i = 0; i < 64; i++)
    {
        uint8_t least_significant = ow_uart_read_bit(ow);
        uint8_t most_significant = ow_uart_read_bit(ow);

        uint8_t bit = least_significant & 1;

        if ((most_significant | least_significant) == 0)
        {
            // TODO, Collision, implement later
        }
        else
        {
            data |= (((uint64_t)bit) << i);
            onewire_write_bytes(ow, &bit, sizeof(bit));
        }
    }

    printf("Data 8: %d\n", (uint8_t)(data & 0xFF));

    uint8_t crc = data >> (64 - 8);

    if (calculate_crc8(&data, 7) == crc)
    {
        printf("actually calculated crc %d\n", crc);
    }
    else
    {
        rom_search(ow);
    }

    uint64_t val = data << 8;
    val = val >> 8;
    printf("message: %llu\n", val);

    printf("crc: %d\n", (uint8_t)(data >> 56));

    return data;
}

int ds_get_all_temp(const Onewire_t *ow)
{

    uint8_t command = {ROM_MATCH, FUNC_TEMP_CONVERT};

    ow_reset_pulse(ow);

    onewire_write_bytes(ow, &command, sizeof(command));

    // wait for  read time slot = 1,

    // match all known devices, and check their temp
}

static void ow_reset_pulse(const Onewire_t *ow)
{
    uart_set_baudrate(ow->uart_num, 9600);
    fflush(stdout);
    uint8_t write = 0xF0;
    uart_write_bytes(ow->uart_num, &write, 1);

    char read_buffer[1];
    int read_bytes = uart_read_bytes(ow->uart_num, &read_buffer, 1, portMAX_DELAY);

    fflush(stdout);
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

float calculate_temp(uint16_t temp, EBitRes res)
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

static void onewire_write_bytes(const Onewire_t *ow, uint8_t *p_byte, size_t length)
{
    for (int byte_nr = 0; byte_nr < length; byte_nr++)
    {
        uint8_t byte = p_byte[length];
        for (int i = 0; i < 8; i++)
        {
            uint8_t send_bit = ~((byte >> i) & 1) + 1;
            myuart_write_bytes(ow->uart_num, &send_bit, sizeof(send_bit));
        }
    }
    uart_wait_tx_idle_polling(ow->uart_num);
}
