#pragma once
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

typedef struct {
    uint8_t value;               // Counter value
    SemaphoreHandle_t queue;     // Mutex for thread safety
} CounterSystem;

void counter_init(CounterSystem *sys);
void counter_increment(CounterSystem *sys);
uint8_t counter_get_value(CounterSystem *sys);