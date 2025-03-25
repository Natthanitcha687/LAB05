#include "hal_7segment.h"
#include <string.h>
#include <driver/gpio.h>

static SevenSegmentConfig active_config;

void seven_segment_init(const SevenSegmentConfig *config)
{
    memcpy(&active_config, config, sizeof(SevenSegmentConfig));
    // ตงคาโหมดพนสําหรบเซกเมนต
    for (int i = 0; i < 7; i++)
    {
        gpio_reset_pin(active_config.segment_pins[i]);
        gpio_set_direction(active_config.segment_pins[i], GPIO_MODE_OUTPUT);
    }
    // ตงคาโหมดพนสําหรบหลกตวเลข
    for (int i = 0; i < 2; i++)
    {
        gpio_reset_pin(active_config.digit_pins[i]);
        gpio_set_direction(active_config.digit_pins[i], GPIO_MODE_OUTPUT);
    }
}
void set_segment(uint8_t value)
{
    for (int i = 0; i < 7; i++)
    {
        gpio_set_level(active_config.segment_pins[i], (value >> i) & 0x01);
    }
}

void select_digit(uint8_t pos)
{
    gpio_set_level(active_config.digit_pins[0], pos == 0);
    gpio_set_level(active_config.digit_pins[1], pos == 1);
}