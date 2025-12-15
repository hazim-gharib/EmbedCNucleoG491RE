#include "gpio.h"

static void enable_gpio_clock(GPIO_TypeDef *port)
{
    if (port == GPIOA && !__HAL_RCC_GPIOA_IS_CLK_ENABLED()) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB && !__HAL_RCC_GPIOB_IS_CLK_ENABLED()) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC && !__HAL_RCC_GPIOC_IS_CLK_ENABLED()) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (port == GPIOD && !__HAL_RCC_GPIOD_IS_CLK_ENABLED()) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if (port == GPIOE && !__HAL_RCC_GPIOE_IS_CLK_ENABLED()) __HAL_RCC_GPIOE_CLK_ENABLE();
    else if (port == GPIOF && !__HAL_RCC_GPIOF_IS_CLK_ENABLED()) __HAL_RCC_GPIOF_CLK_ENABLE();
    else if (port == GPIOG && !__HAL_RCC_GPIOG_IS_CLK_ENABLED()) __HAL_RCC_GPIOG_CLK_ENABLE();
}

#define GPIO_BUILD_LED_ENTRY(name, port, pin, mode, pull, speed) \
    { port, { pin, mode, pull, speed } },

#define GPIO_BUILD_BTN_ENTRY(name, port, pin, mode, pull, speed) \
    { port, { pin, mode, pull, speed } },

const gpioPinConfig gpio_pins[GPIO_MAX] = 
{
    BOARD_LED_LIST(GPIO_BUILD_LED_ENTRY)
    BOARD_BUTTON_LIST(GPIO_BUILD_BTN_ENTRY)
};

#undef GPIO_BUILD_LED_ENTRY
#undef GPIO_BUILD_BTN_ENTRY

void gpio_init(void)
{
    for (uint32_t pin = 0; pin < GPIO_MAX; pin++)
    {
        enable_gpio_clock(gpio_pins[pin].port);
        HAL_GPIO_Init(gpio_pins[pin].port, (GPIO_InitTypeDef *)&gpio_pins[pin].config);
        gpio_reset((gpioPinId)pin);
    }
}

void gpio_set(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_WritePin(gpio_pins[id].port, (uint16_t)gpio_pins[id].config.Pin, GPIO_PIN_SET);
    }
}

void gpio_reset(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_WritePin(gpio_pins[id].port, (uint16_t)gpio_pins[id].config.Pin, GPIO_PIN_RESET);
    }
}

GPIO_PinState gpio_read(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        return HAL_GPIO_ReadPin(gpio_pins[id].port, (uint16_t)gpio_pins[id].config.Pin);
    }
    return GPIO_PIN_RESET;
}

void gpio_toggle(gpioPinId id)
{
    if (id < GPIO_MAX)
    {
        HAL_GPIO_TogglePin(gpio_pins[id].port, (uint16_t)gpio_pins[id].config.Pin);
    }
}
