#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "stm32g4xx_hal.h"

typedef enum
{
    // Blue LEDs
    BSP_LED_BLUE1 = 0, // PA5
    BSP_LED_BLUE2,     // PA6
    BSP_LED_BLUE3,     // PA7

    // Yellow LEDs
    BSP_LED_YELLOW1, // PB6
    BSP_LED_YELLOW2, // PC7
    BSP_LED_YELLOW3, // PA9

    // Green LED
    BSP_LED_GREEN, // PA8

    // User button
    BSP_BUTTON1, // PB10

    BSP_GPIO_MAX
} t_bsp_gpio_id;

typedef struct
{
    GPIO_TypeDef *port;
    GPIO_InitTypeDef config;
    void (*clkEnableFunc)(void);
} t_bsp_gpio_config;

extern const t_bsp_gpio_config bsp_gpio_list[BSP_GPIO_MAX];

#endif // BSP_GPIO_H