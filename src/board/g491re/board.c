#include "stm32g4xx_hal.h"
#include "board/g491re/public_inc/board.h"
#include "board/g491re/public_inc/gpio.h"

#define HAL_CHECK(expr) do { if ((expr) != HAL_OK) Error_Handler(__FILE__, __LINE__); } while(0)

static void SystemClock_Config(void);

void board_init(void)
{
    HAL_Init();               // Initialize HAL + SysTick
    SystemClock_Config();     // Configure system clock (HSI + PLL to 170 MHz)
    mGpio_init();             // Initialize GPIOs
}

static void Error_Handler(const char* file, int line)
{
    (void)file; (void)line;
    while (1) { /* optional: toggle LED for fault indication */ }
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    /* Enable PWR clock and set voltage scaling for high frequency */
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_CHECK(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1));

    /* Oscillator: HSI on, PLL on, source HSI */
    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState = RCC_PLL_ON;
    osc.PLL.PLLSource = RCC_PLLSOURCE_HSI;    // 16 MHz
    /* PLL configuration to reach 170 MHz on PLLR output with valid VCO range:
     * Use M = 4 so PLL input = 16 / 4 = 4 MHz
     * VCO = 4 * 85 = 340 MHz (within spec)
     * R = 2 => SYSCLK = 340 / 2 = 170 MHz
     */
    osc.PLL.PLLM = RCC_PLLM_DIV4;   // 4 MHz to PLL input
    osc.PLL.PLLN = 85;              // VCO = 4 * 85 = 340 MHz
    osc.PLL.PLLR = RCC_PLLR_DIV2;   // SYSCLK = 340 / 2 = 170 MHz
    osc.PLL.PLLP = RCC_PLLP_DIV2;   // not used for SYSCLK
    osc.PLL.PLLQ = RCC_PLLQ_DIV2;   // for peripherals if needed

    HAL_CHECK(HAL_RCC_OscConfig(&osc));

    /* Clocks: switch SYSCLK to PLL, set bus dividers */
    clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;   // HCLK = 170 MHz
    clk.APB1CLKDivider = RCC_HCLK_DIV2;    // PCLK1 = 85 MHz
    clk.APB2CLKDivider = RCC_HCLK_DIV2;    // PCLK2 = 85 MHz

    /* Flash latency must match frequency & voltage scale */
    HAL_CHECK(HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_4));
}
