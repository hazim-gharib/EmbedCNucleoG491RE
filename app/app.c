#include "app.h"
#include "bsp/bsp_gpio.h"
#include "led.h"
#include "board/g491re/gpio.h"
#include "stm32g4xx_hal.h"

// Simple tick-based periodic scheduler: delay until the next absolute tick time.
// Keeps loop execution at a steady interval and avoids cumulative drift.
static void delay_until_next(uint32_t *next_wake_ms, uint32_t period_ms)
{
    uint32_t now = HAL_GetTick();

    // If this is the first call, initialize next_wake_ms to now
    if (*next_wake_ms == 0)
    {
        *next_wake_ms = now + period_ms;
        HAL_Delay(period_ms);
        return;
    }

    // Compute signed difference to handle 32-bit tick wrap-around
    int32_t dt = (int32_t)(*next_wake_ms - now);
    if (dt > 0)
    {
        // Still time left until next wake
        HAL_Delay((uint32_t)dt);
        *next_wake_ms += period_ms;
    }
    else
    {
        // We missed the deadline; catch up by setting next wake relative to now
        *next_wake_ms = now + period_ms;
    }
}

void app_main(void)
{
    const uint32_t period_ms = 200;
    uint32_t next_wake = 0;

    led_init();
    led_set_blink(GPIO_LED_BLUE_1, true, 100);
    led_set_blink(GPIO_LED_BLUE_2, true, 200);
    led_set_blink(GPIO_LED_BLUE_3, true, 300);
    led_set_blink(GPIO_LED_YELLOW_1, true, 400);
    led_set_blink(GPIO_LED_YELLOW_2, true, 500);
    led_set_blink(GPIO_LED_YELLOW_3, true, 600);
    led_set_blink(GPIO_LED_GREEN_1, true, 700);
    
    while (1)
    {
        led_process();
    }
}