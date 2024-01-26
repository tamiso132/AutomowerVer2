#include "sensor_avoid.h"
#include "esp_intr_alloc.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static QueueHandle_t gpio_evt_queue = NULL;

static void gpio_task_example(void *arg)
{
    uint32_t io_num;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
        {
            printf("SOMETHING\n");
        }
    }
}

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void init_sensor(sensor_avoid_t *sensor_info, gpio_num_t gpio_num)
{

    sensor_info->gpio_pin = gpio_num;
    gpio_config_t io_conf;

    io_conf.pin_bit_mask = 1 << gpio_num;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;

    ESP_ERROR_CHECK(gpio_config(&io_conf));

    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_num, gpio_isr_handler, (void *)gpio_num);

    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
}
