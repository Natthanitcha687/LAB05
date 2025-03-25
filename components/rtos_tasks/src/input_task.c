#include "input_task.h"
#include "counter_sys.h"
#include <driver/gpio.h>
#include <freertos/task.h>
#include <esp_log.h>

#define BUTTON_PIN GPIO_NUM_5
static const char *TAG = "InputTask";

static CounterSystem *counter;

static void input_task(void *params)
{
    ESP_LOGI(TAG, "Input task started");
    counter = (CounterSystem *)params; // Assign the passed CounterSystem object

    uint8_t last_state = 1;
    while (1)
    {
        if (counter == NULL || counter->queue == NULL) {
            ESP_LOGE(TAG, "CounterSystem or queue not initialized");
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        uint8_t current_state = gpio_get_level(BUTTON_PIN);
        if (last_state == 1 && current_state == 0) {
            ESP_LOGI(TAG, "Button pressed");
            counter_increment(counter);
        }
        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void input_task_init(void *params)
{
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    xTaskCreate(input_task, "InputTask", 2048, params, 1, NULL);
}