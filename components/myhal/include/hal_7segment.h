#pragma once
#include <driver/gpio.h>

typedef struct {
    gpio_num_t segment_pins[7];
    gpio_num_t digit_pins[2];
} SevenSegmentConfig;

void seven_segment_init(const SevenSegmentConfig *config);
void set_segment(uint8_t value);
void select_digit(uint8_t pos);