# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# compile C with /home/tom/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
C_DEFINES = -DESP_LWIP_COMPONENT_BUILD -DESP_PLATFORM -DIDF_VER=\"v5.1.2\" -DSOC_MMU_PAGE_SIZE=CONFIG_MMU_PAGE_SIZE -D_GNU_SOURCE -D_POSIX_READER_WRITER_LOCKS

C_INCLUDES = -I/home/tom/projects/automower/build/config -I/home/tom/esp/esp-idf/components/lwip/include -I/home/tom/esp/esp-idf/components/lwip/include/apps -I/home/tom/esp/esp-idf/components/lwip/include/apps/sntp -I/home/tom/esp/esp-idf/components/lwip/lwip/src/include -I/home/tom/esp/esp-idf/components/lwip/port/include -I/home/tom/esp/esp-idf/components/lwip/port/freertos/include -I/home/tom/esp/esp-idf/components/lwip/port/esp32xx/include -I/home/tom/esp/esp-idf/components/lwip/port/esp32xx/include/arch -I/home/tom/esp/esp-idf/components/newlib/platform_include -I/home/tom/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include -I/home/tom/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include -I/home/tom/esp/esp-idf/components/freertos/esp_additions/include/freertos -I/home/tom/esp/esp-idf/components/freertos/esp_additions/include -I/home/tom/esp/esp-idf/components/freertos/esp_additions/arch/xtensa/include -I/home/tom/esp/esp-idf/components/esp_hw_support/include -I/home/tom/esp/esp-idf/components/esp_hw_support/include/soc -I/home/tom/esp/esp-idf/components/esp_hw_support/include/soc/esp32 -I/home/tom/esp/esp-idf/components/esp_hw_support/port/esp32/. -I/home/tom/esp/esp-idf/components/esp_hw_support/port/esp32/private_include -I/home/tom/esp/esp-idf/components/heap/include -I/home/tom/esp/esp-idf/components/log/include -I/home/tom/esp/esp-idf/components/soc/include -I/home/tom/esp/esp-idf/components/soc/esp32 -I/home/tom/esp/esp-idf/components/soc/esp32/include -I/home/tom/esp/esp-idf/components/hal/esp32/include -I/home/tom/esp/esp-idf/components/hal/include -I/home/tom/esp/esp-idf/components/hal/platform_port/include -I/home/tom/esp/esp-idf/components/esp_rom/include -I/home/tom/esp/esp-idf/components/esp_rom/include/esp32 -I/home/tom/esp/esp-idf/components/esp_rom/esp32 -I/home/tom/esp/esp-idf/components/esp_common/include -I/home/tom/esp/esp-idf/components/esp_system/include -I/home/tom/esp/esp-idf/components/esp_system/port/soc -I/home/tom/esp/esp-idf/components/esp_system/port/include/private -I/home/tom/esp/esp-idf/components/xtensa/include -I/home/tom/esp/esp-idf/components/xtensa/esp32/include -I/home/tom/esp/esp-idf/components/vfs/include -I/home/tom/esp/esp-idf/components/esp_eth/include -I/home/tom/esp/esp-idf/components/esp_event/include -I/home/tom/esp/esp-idf/components/driver/include -I/home/tom/esp/esp-idf/components/driver/deprecated -I/home/tom/esp/esp-idf/components/driver/analog_comparator/include -I/home/tom/esp/esp-idf/components/driver/dac/include -I/home/tom/esp/esp-idf/components/driver/gpio/include -I/home/tom/esp/esp-idf/components/driver/gptimer/include -I/home/tom/esp/esp-idf/components/driver/i2c/include -I/home/tom/esp/esp-idf/components/driver/i2s/include -I/home/tom/esp/esp-idf/components/driver/ledc/include -I/home/tom/esp/esp-idf/components/driver/mcpwm/include -I/home/tom/esp/esp-idf/components/driver/parlio/include -I/home/tom/esp/esp-idf/components/driver/pcnt/include -I/home/tom/esp/esp-idf/components/driver/rmt/include -I/home/tom/esp/esp-idf/components/driver/sdio_slave/include -I/home/tom/esp/esp-idf/components/driver/sdmmc/include -I/home/tom/esp/esp-idf/components/driver/sigma_delta/include -I/home/tom/esp/esp-idf/components/driver/spi/include -I/home/tom/esp/esp-idf/components/driver/temperature_sensor/include -I/home/tom/esp/esp-idf/components/driver/touch_sensor/include -I/home/tom/esp/esp-idf/components/driver/twai/include -I/home/tom/esp/esp-idf/components/driver/uart/include -I/home/tom/esp/esp-idf/components/driver/usb_serial_jtag/include -I/home/tom/esp/esp-idf/components/driver/touch_sensor/esp32/include -I/home/tom/esp/esp-idf/components/esp_pm/include -I/home/tom/esp/esp-idf/components/esp_ringbuf/include

C_FLAGS = -mlongcalls -Wno-frame-address  -fdiagnostics-color=always -ffunction-sections -fdata-sections -Wall -Werror=all -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=unused-but-set-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare -Wno-enum-conversion -gdwarf-4 -ggdb -Og -fmacro-prefix-map=/home/tom/projects/automower=. -fmacro-prefix-map=/home/tom/esp/esp-idf=/IDF -fstrict-volatile-bitfields -fno-jump-tables -fno-tree-switch-conversion -DconfigENABLE_FREERTOS_DEBUG_OCDAWARE=1 -std=gnu17 -Wno-old-style-declaration -Wno-address -Wno-format

# Custom flags: esp-idf/lwip/CMakeFiles/__idf_lwip.dir/lwip/src/core/tcp.c.obj_FLAGS = -Wno-type-limits

# Custom flags: esp-idf/lwip/CMakeFiles/__idf_lwip.dir/lwip/src/netif/ppp/chap_ms.c.obj_FLAGS = -Wno-array-parameter

# Custom flags: esp-idf/lwip/CMakeFiles/__idf_lwip.dir/lwip/src/netif/ppp/pppos.c.obj_FLAGS = -Wno-type-limits

