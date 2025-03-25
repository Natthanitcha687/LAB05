#include "hal_7segment.h"
#include "counter_sys.h"
#include "display_task.h"
#include "input_task.h"
#include <esp_log.h>

void app_main()
{
    ESP_LOGI("Main", "Starting application...");

    // Initialize 7-segment display
    SevenSegmentConfig seg_config = {
        .segment_pins = {GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27,
                         GPIO_NUM_14, GPIO_NUM_12, GPIO_NUM_33, GPIO_NUM_32},
        .digit_pins = {GPIO_NUM_18, GPIO_NUM_19}};
    seven_segment_init(&seg_config);

    // Initialize counter system
    static CounterSystem counter; // Ensure the counter object is static or global
    counter_init(&counter);       // Properly initialize the counter system

    // Initialize tasks
    display_task_init(&counter); // Pass the initialized counter to the display task
    input_task_init(&counter);   // Pass the initialized counter to the input task

    ESP_LOGI("Main", "Application started");
}