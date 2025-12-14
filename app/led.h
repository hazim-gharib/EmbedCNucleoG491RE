#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>
#include "board/g491re/gpio.h"

typedef gpioPinId ledId;

#ifdef __cplusplus
extern "C" {
#endif

// Initialize LED module (clears internal state). Safe to call multiple times.
void led_init(void);

// Direct control (immediate)
void led_set(ledId id, bool state);
void led_toggle(ledId id);

// Blink control: period_ms is full on+off period in milliseconds.
// led_blink_start makes the LED start blinking (non-blocking). Call led_process()
// periodically from the main loop to drive the blinking logic.
void led_set_blink(ledId id, bool blink, uint32_t period_ms);

// Call frequently from main loop (or from a periodic task) to update blinking LEDs.
void led_process(void);

#ifdef __cplusplus
}
#endif

#endif // LED_H
