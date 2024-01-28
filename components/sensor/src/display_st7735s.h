#include "driver/gpio.h"
#include "driver/spi_master.h"
// Using SPI protocol

// SCL -> SPI CLOCK
// SDA -> SPI DATA

// CS -> Chip Select
// RST -> Screen Reset
// Rs/Ds -> Register Select (tells if data or command)
//  BLK -> Back Light Led

// how SPI usually works,

// when CS is low, it means communication, otherwise no communication
// Usually there is a SDO for slave sending information, in this case, no info is sent out, only input

// ESP32 SPI

// Has Three Spi Interfaces, (HSPI/VSPI/SPI)  SPI is used with Flash memory, the other can be used.

// V-SPI LAYOUT, GPIO NUMBER

// MISO (19) -> Master In Slave Out
// MOSI (23) -> Master Out Slave In
// CLK  (18) -> CLOCK
// CS   (5) -> Chip Select (Enable/Disable communication)

// H-SPI LAYOUT, GPIO NUMBER

/// MISO (12) -> Master In Slave Out
// MOSI (13) -> Master Out Slave In
// CLK  (14) -> CLOCK
// CS   (15) -> Chip Select (Enable/Disable communication)

// rst --> GPIO_16
// DC --> GPIO_17

// Serial Timing Interface, 4 line

// write, 16 mhz

struct display_t
{
    gpio_num_t rst;
    gpio_num_t ds;
    gpio_num_t cs;
    spi_host_device_t spi_host;
};

void init_display();