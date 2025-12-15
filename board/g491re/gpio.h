#ifndef GPIO_H
#define GPIO_H

#include "stm32g4xx_hal.h"
#include "board_layout.h"

#define GPIO_DECLARE_LED_ID(name, port, pin, mode, pull, speed) GPIO_LED_##name,
#define GPIO_DECLARE_BTN_ID(name, port, pin, mode, pull, speed) GPIO_BTN_##name,

typedef enum {
    BOARD_LED_LIST(GPIO_DECLARE_LED_ID)
    BOARD_BUTTON_LIST(GPIO_DECLARE_BTN_ID)
    GPIO_MAX
} gpioPinId;

#undef GPIO_DECLARE_LED_ID
#undef GPIO_DECLARE_BTN_ID

typedef struct
{
    GPIO_TypeDef *port;
    GPIO_InitTypeDef config;
} gpioPinConfig;

extern const gpioPinConfig gpio_pins[GPIO_MAX];

void gpio_init(void);
void gpio_set(gpioPinId id);
void gpio_reset(gpioPinId id);
GPIO_PinState gpio_read(gpioPinId id);
void gpio_toggle(gpioPinId id);

#endif // GPIO_H