#include "display_task.h"
#include "hal_7segment.h"
#include "counter_sys.h"
#include <freertos/task.h>
#include <esp_log.h>

static const char *TAG = "DisplayTask";

static const uint8_t SEGMENT_MAP[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,
    0b01100110, 0b01101101, 0b01111101, 0b00000111,
    0b01111111, 0b01101111};

static CounterSystem *counter;

static void display_task(void *params)
{
    ESP_LOGI(TAG, "Display task started");
    counter = (CounterSystem *)params; // Assign the passed CounterSystem object

    while (1)
    {
        if (counter == NULL || counter->queue == NULL) {
            ESP_LOGE(TAG, "CounterSystem or queue not initialized");
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        uint8_t value = counter_get_value(counter);
        uint8_t tens = value % 10;
        uint8_t units = value / 10;

        // Display tens digit
        set_segment(SEGMENT_MAP[tens]);
        select_digit(1);
        vTaskDelay(pdMS_TO_TICKS(10));

        // Display units digit
        set_segment(SEGMENT_MAP[units]);
        select_digit(0);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void display_task_init(void *params)
{
    xTaskCreate(display_task, "DisplayTask", 2048, params, 2, NULL);
}