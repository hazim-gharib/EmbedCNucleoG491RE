#include "gpio.h"
#include "board_layout.h"

static const gpioPinConfig pin_configs[GPIO_MAX] = {
    // Blue LEDs
    [GPIO_LED_BLUE_1] = {
        .port = GPIO_LED_BLUE_1_PORT,
        .config = {
            .Pin = GPIO_LED_BLUE_1_PIN,
            .Mode = GPIO_LED_BLUE_1_MODE,
            .Pull = GPIO_LED_BLUE_1_PULL,
            .Speed = GPIO_LED_BLUE_1_SPEED
        },
    },
    [GPIO_LED_BLUE_2] = {
        .port = GPIO_LED_BLUE_2_PORT,
        .config = {
            .Pin = GPIO_LED_BLUE_2_PIN,
            .Mode = GPIO_LED_BLUE_2_MODE,
            .Pull = GPIO_LED_BLUE_2_PULL,
            .Speed = GPIO_LED_BLUE_2_SPEED
        },
    },
    [GPIO_LED_BLUE_3] = {
        .port = GPIO_LED_BLUE_3_PORT,
        .config = {
            .Pin = GPIO_LED_BLUE_3_PIN,
            .Mode = GPIO_LED_BLUE_3_MODE,
            .Pull = GPIO_LED_BLUE_3_PULL,
            .Speed = GPIO_LED_BLUE_3_SPEED
        },
    },
    [GPIO_LED_YELLOW_1] = {
        .port = GPIO_LED_YELLOW_1_PORT,
        .config = {
            .Pin = GPIO_LED_YELLOW_1_PIN,
            .Mode = GPIO_LED_YELLOW_1_MODE,
            .Pull = GPIO_LED_YELLOW_1_PULL,
            .Speed = GPIO_LED_YELLOW_1_SPEED
        },
    },
    [GPIO_LED_YELLOW_2] = {
        .port = GPIO_LED_YELLOW_2_PORT,
        .config = {
            .Pin = GPIO_LED_YELLOW_2_PIN,
            .Mode = GPIO_LED_YELLOW_2_MODE,
            .Pull = GPIO_LED_YELLOW_2_PULL,
            .Speed = GPIO_LED_YELLOW_2_SPEED
        },
    },
    [GPIO_LED_YELLOW_3] = {
        .port = GPIO_LED_YELLOW_3_PORT,
        .config = {
            .Pin = GPIO_LED_YELLOW_3_PIN,
            .Mode = GPIO_LED_YELLOW_3_MODE,
            .Pull = GPIO_LED_YELLOW_3_PULL,
            .Speed = GPIO_LED_YELLOW_3_SPEED
        },
    },
    [GPIO_LED_GREEN_1] = {
        .port = GPIO_LED_GREEN_1_PORT,
        .config = {
            .Pin = GPIO_LED_GREEN_1_PIN,
            .Mode = GPIO_LED_GREEN_1_MODE,
            .Pull = GPIO_LED_GREEN_1_PULL,
            .Speed = GPIO_LED_GREEN_1_SPEED
        },
    },
    [GPIO_BUTTON_1] = {
        .port = GPIO_BUTTON_1_PORT,
        .config = {
            .Pin = GPIO_BUTTON_1_PIN,
            .Mode = GPIO_BUTTON_1_MODE,
            .Pull = GPIO_BUTTON_1_PULL,
            .Speed = GPIO_BUTTON_1_SPEED
        },
    },
};

void gpio_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    for (uint32_t pin = 0; pin < GPIO_MAX; pin++)
    {
        HAL_GPIO_Init(pin_configs[pin].port, &pin_configs[pin].config);
    }
}

void gpio_set(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_WritePin(pin_configs[id].port, (uint16_t)(pin_configs[id].config.Pin & GPIO_PIN_MASK), GPIO_PIN_SET);
    }
}

void gpio_reset(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_WritePin(pin_configs[id].port, (uint16_t)(pin_configs[id].config.Pin & GPIO_PIN_MASK), GPIO_PIN_RESET);
    }
}

GPIO_PinState gpio_read(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        return HAL_GPIO_ReadPin(pin_configs[id].port, (uint16_t)(pin_configs[id].config.Pin & GPIO_PIN_MASK));
    }
    return GPIO_PIN_RESET;
}

void gpio_toggle(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_TogglePin(pin_configs[id].port, (uint16_t)(pin_configs[id].config.Pin & GPIO_PIN_MASK));
    }
}
