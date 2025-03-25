#include "counter_sys.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <esp_log.h>

static const char *TAG = "CounterSystem";

void counter_init(CounterSystem *counter)
{
    if (counter == NULL) {
        ESP_LOGE(TAG, "CounterSystem is NULL");
        return;
    }

    counter->value = 0; // Initialize the counter value
    counter->queue = xSemaphoreCreateMutex(); // Create a mutex for thread safety
    if (counter->queue == NULL) {
        ESP_LOGE(TAG, "Failed to create mutex");
    }
}

void counter_increment(CounterSystem *counter)
{
    if (counter == NULL || counter->queue == NULL) {
        ESP_LOGE(TAG, "CounterSystem or queue not initialized");
        return;
    }

    if (xSemaphoreTake(counter->queue, portMAX_DELAY)) {
        counter->value++;
        if (counter->value > 99) { // Reset to 0 if the value exceeds 99
            counter->value = 0;
        }
        ESP_LOGI(TAG, "Counter value: %02d", counter->value); // Log the counter value
        xSemaphoreGive(counter->queue);
    } else {
        ESP_LOGE(TAG, "Failed to take mutex");
    }
}

uint8_t counter_get_value(CounterSystem *counter)
{
    if (counter == NULL || counter->queue == NULL) {
        ESP_LOGE(TAG, "CounterSystem or queue not initialized");
        return 0; // Return a default value
    }

    uint8_t value = 0;
    if (xSemaphoreTake(counter->queue, portMAX_DELAY)) {
        value = counter->value;
        xSemaphoreGive(counter->queue);
    } else {
        ESP_LOGE(TAG, "Failed to take mutex");
    }
    return value;
}