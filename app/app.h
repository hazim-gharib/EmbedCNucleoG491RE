#ifndef APP_H
#define APP_H

#include "bsp/bsp_gpio.h"
#include "led.h"
#include "board/g491re/gpio.h"
#include "stm32g4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);

#ifdef __cplusplus
}
#endif

#endif // APP_H
