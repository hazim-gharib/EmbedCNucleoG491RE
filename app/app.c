#include "app.h"
#include "board/g491re/gpio.h"

void app_main(void)
{
    led_init();
    led_set_blink(LED_ID_BLUE_1, true, 500);
    led_set_blink(LED_ID_BLUE_2, true, 500);
    led_set_blink(LED_ID_BLUE_3, true, 500);
    led_set_blink(LED_ID_YELLOW_1, true, 300);
    led_set_blink(LED_ID_YELLOW_2, true, 300);
    led_set_blink(LED_ID_YELLOW_3, true, 300);
    led_set_blink(LED_ID_GREEN_1, true, 200);
    
    while (1)
    {
        led_process();
    }
}