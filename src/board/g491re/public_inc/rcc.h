#ifndef RCC_H
#define RCC_H

#ifdef __cplusplus
extern "C" {
#endif

// Configure system clock (HSI, no PLL in current profile)
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif // RCC_H
