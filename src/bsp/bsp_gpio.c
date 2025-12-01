#include "bsp_gpio.h"

// Per-port clock enables (can be shared across multiple pins on same port)
static inline void GPIOA_CLK_ENABLE(void) { __HAL_RCC_GPIOA_CLK_ENABLE(); }
static inline void GPIOB_CLK_ENABLE(void) { __HAL_RCC_GPIOB_CLK_ENABLE(); }
static inline void GPIOC_CLK_ENABLE(void) { __HAL_RCC_GPIOC_CLK_ENABLE(); }

// Array of GPIO configurations
const tGpio_Config bsp_gpio_list[BSP_GPIO_MAX] = {
    // Blue LEDs
    [BSP_LED_BLUE1] = {
        .port = GPIOA,
        .config = {
            .Pin = GPIO_PIN_5,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOA_CLK_ENABLE
    },
    [BSP_LED_BLUE2] = {
        .port = GPIOA,
        .config = {
            .Pin = GPIO_PIN_6,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOA_CLK_ENABLE
    },
    [BSP_LED_BLUE3] = {
        .port = GPIOA,
        .config = {
            .Pin = GPIO_PIN_7,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOA_CLK_ENABLE
    },

    // Yellow LEDs
    [BSP_LED_YELLOW1] = {
        .port = GPIOB,
        .config = {
            .Pin = GPIO_PIN_6,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOB_CLK_ENABLE
    },
    [BSP_LED_YELLOW2] = {
        .port = GPIOC,
        .config = {
            .Pin = GPIO_PIN_7,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOC_CLK_ENABLE
    },
    [BSP_LED_YELLOW3] = {
        .port = GPIOA,
        .config = {
            .Pin = GPIO_PIN_9,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOA_CLK_ENABLE
    },

    // Green LED
    [BSP_LED_GREEN] = {
        .port = GPIOA,
        .config = {
            .Pin = GPIO_PIN_8,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        },
        .clkEnableFunc = GPIOA_CLK_ENABLE
    },

    // Button (input with pull-up)
    [BSP_BUTTON1] = {
        .port = GPIOB,
        .config = {
            .Pin = GPIO_PIN_10,
            .Mode = GPIO_MODE_INPUT,
            .Pull = GPIO_PULLUP,
            .Speed = GPIO_SPEED_FREQ_LOW
        },
        .clkEnableFunc = GPIOB_CLK_ENABLE
    }
};