#include "gpio.h"
#include "stm32g4xx_hal.h"

void mGpio_init(void)
{
    for (size_t i = 0; i < BSP_GPIO_MAX; i++)
    {
        if (bsp_gpio_list[i].clkEnableFunc)
        {
            bsp_gpio_list[i].clkEnableFunc();
        }
        HAL_GPIO_Init(bsp_gpio_list[i].port, &bsp_gpio_list[i].config);
    }
}

void mGpio_set(tBsp_GpioId id)
{
    if (id < BSP_GPIO_MAX)
    {
        HAL_GPIO_WritePin(bsp_gpio_list[id].port, bsp_gpio_list[id].config.Pin, GPIO_PIN_SET);
    }
}

void mGpio_reset(tBsp_GpioId id)
{
    if (id < BSP_GPIO_MAX)
    {
        HAL_GPIO_WritePin(bsp_gpio_list[id].port, bsp_gpio_list[id].config.Pin, GPIO_PIN_RESET);
    }
}

GPIO_PinState mGpio_read(tBsp_GpioId id)
{
    if (id < BSP_GPIO_MAX)
    {
        return HAL_GPIO_ReadPin(bsp_gpio_list[id].port, bsp_gpio_list[id].config.Pin);
    }
    return GPIO_PIN_RESET;
}

void mGpio_toggle(tBsp_GpioId id)
{
    if (id < BSP_GPIO_MAX)
    {
        HAL_GPIO_TogglePin(bsp_gpio_list[id].port, bsp_gpio_list[id].config.Pin);
    }
}
