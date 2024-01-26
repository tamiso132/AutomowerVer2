#pragma once
#include "driver/gpio.h"

typedef enum e_obstacle_state
{
    OBSTACLE_FOUND = 0,
    OBSTACLE_FREE = 1
} e_obstacle_state;

typedef struct sensor_avoid_t
{
    gpio_num_t gpio_pin;
    gpio_isr_handle_t high_edge_handle;
    e_obstacle_state state;

} sensor_avoid_t;

void init_sensor(sensor_avoid_t *sensor_info, gpio_num_t gpio_num);