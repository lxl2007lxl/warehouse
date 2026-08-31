#include "oled_ssd1306.h"
#include "hi_task.h"

void oled_demo_task(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0,0,(uint8_t*)"Hello OpenHarmony");
}

APP_FEATURE_INIT(oled_demo_task);

