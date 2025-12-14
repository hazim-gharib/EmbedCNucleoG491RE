#ifndef GPIO_H
#define GPIO_H

#include "stm32g4xx_hal.h"

typedef enum
{
    // Blue LEDs
    GPIO_LED_BLUE_1 = 0,
    GPIO_LED_BLUE_2,
    GPIO_LED_BLUE_3,

    // Yellow LEDs
    GPIO_LED_YELLOW_1,
    GPIO_LED_YELLOW_2,
    GPIO_LED_YELLOW_3,

    // Green LED
    GPIO_LED_GREEN_1,

    // User button
    GPIO_BUTTON_1,

    GPIO_MAX
} gpioPinId;

typedef struct
{
    GPIO_TypeDef *port;
    GPIO_InitTypeDef config;
} gpioPinConfig;


void gpio_init(void);
void gpio_set(gpioPinId id);
void gpio_reset(gpioPinId id);
GPIO_PinState gpio_read(gpioPinId id);
void gpio_toggle(gpioPinId id);
#endif // GPIO_H