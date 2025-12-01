#ifndef GPIO_H
#define GPIO_H
#include "bsp_gpio.h"

void mGpio_init(void);
void mGpio_set(tBsp_GpioId id);
void mGpio_reset(tBsp_GpioId id);
GPIO_PinState mGpio_read(tBsp_GpioId id);
void mGpio_toggle(tBsp_GpioId id);

#endif // GPIO_H