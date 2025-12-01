#include "stm32g4xx_hal.h"
#include "board/g491re/public_inc/board.h"  // Provides prototype for board_init
#include "board/g491re/public_inc/rcc.h"
#include "board/g491re/public_inc/gpio.h"

void board_init(void)
{
    HAL_Init();               // Initialize HAL + SysTick
    SystemClock_Config();     // Configure system clock (HSI + PLL to 170 MHz)
    mGpio_init();             // Initialize GPIOs
}