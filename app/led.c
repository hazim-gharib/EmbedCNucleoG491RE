#include "led.h"
#include "stm32g4xx_hal.h"
#include <string.h>

#define LED_TO_GPIO(name, port, pin, mode, pull, speed) GPIO_LED_##name,
static const gpioPinId led_to_gpio[LED_ID_MAX] = { BOARD_LED_LIST(LED_TO_GPIO) };
#undef LED_TO_GPIO

typedef struct {
    bool is_on;
	bool is_blinking;
    bool prev_state;
	uint32_t period_ms;
	uint32_t last_blink_tick;
} ledState;

static ledState led_states[LED_ID_MAX];

static inline bool valid_id(ledId id)
{
    return (uint32_t)id < (uint32_t)LED_ID_MAX;
}

void led_init(void)
{
    for (ledId id = 0; id < LED_ID_MAX; id++)
    {
        led_states[id].is_on = false;
        led_states[id].is_blinking = false;
        led_states[id].prev_state = false;
        led_states[id].period_ms = 0;
        led_states[id].last_blink_tick = 0;
        gpio_reset(led_to_gpio[id]);
    }
}

void led_set(ledId id, bool state)
{
    if (valid_id(id)) {
        led_states[id].is_blinking = false;
        led_states[id].is_on = state;
        led_states[id].prev_state = !state;
    }
}

void led_toggle(ledId id)
{
	if (valid_id(id)) {
        led_states[id].is_blinking = false;
		led_states[id].is_on = !led_states[id].is_on;
        led_states[id].prev_state = !led_states[id].is_on;
	}
}

void led_set_blink(ledId id, bool blink, uint32_t period_ms)
{
	if (valid_id(id) && period_ms != 0) {
        if(blink)
        {
            led_states[id].is_blinking = true;
            led_states[id].is_on = true;
            led_states[id].prev_state = false;
            led_states[id].period_ms = period_ms;
            led_states[id].last_blink_tick = HAL_GetTick();
        }
        else
        {
            led_states[id].is_blinking = false;
        }
    }
}

void led_process(void)
{
    uint32_t current_tick = HAL_GetTick();
    for (ledId id = 0; id < LED_ID_MAX; id++)
    {
        ledState *state = &led_states[id];
        if (state->is_blinking && state->period_ms > 0)
        {
            if ((uint32_t)(current_tick - state->last_blink_tick) >= (uint32_t)(state->period_ms / 2))
            {
                state->is_on = !state->is_on;
                state->last_blink_tick = current_tick;
            }
        }
        
        if (state->is_on != state->prev_state) 
        {
            // Handle non-blinking LED state changes
            if(state->is_on)
            {
                gpio_set(led_to_gpio[id]);
            } 
            else 
            {
                gpio_reset(led_to_gpio[id]);
            }
            state->prev_state = state->is_on;
        }
    }
}
