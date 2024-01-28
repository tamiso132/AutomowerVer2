#include "esp_intr_alloc.h"

#include "display_st7735s.h"

void init_display()
{
    spi_bus_config_t spi_config = {
        .sclk_io_num = GPIO_NUM_18,
        .mosi_io_num = GPIO_NUM_23,
        .miso_io_num = -1,
        .quadhd_io_num = -1,
        .quadwp_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(SPI3_HOST, &spi_config, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    spi_device_interface_config_t interface = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = 80 * 1000 * 1000,
        .duty_cycle_pos = 128,
        .mode = 0,
        .spics_io_num = GPIO_NUM_5,
        .cs_ena_posttrans = 3,
        .queue_size = 3,
    };

    spi_device_handle_t handle;
    ret = spi_bus_add_device(SPI3_HOST, &interface, &handle);
    // int freq = 0;
    // spi_device_get_actual_freq(handle, &freq);

    // printf("Clock Frequency = %dkhz", freq);
}


void write_bytes(){
    
}