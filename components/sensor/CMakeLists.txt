
idf_component_register(SRCS "src/myuart.c" "src/onewire.c" "src/sensor_avoid.c" "src/display_st7735s.c"
                    INCLUDE_DIRS "src"
                    REQUIRES "driver")
