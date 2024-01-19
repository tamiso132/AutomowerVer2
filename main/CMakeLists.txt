idf_component_register(SRCS "main.c" "temp/myuart.c"
                    INCLUDE_DIRS "temp" "${IDF_PATH}/components/freertos/esp_additions/include/freertos" "${IDF_PATH}/components/driver/uart/include/")
