#include "control_system.h"
#include "encoder.h"
#include "usart.h"

volatile uint32_t millis = 0;

void System_Control(void)
{
    int L_cnt = Read_Encoder(2);
    int R_cnt = Read_Encoder(3);

    // ???? m/s
    float L_speed_mps = (float)L_cnt * WHEEL_CIRCUM / (CNT_PER_ROT * SAMPLE_TIME);
    float R_speed_mps = (float)R_cnt * WHEEL_CIRCUM / (CNT_PER_ROT * SAMPLE_TIME);

    printf("left pulse:%d, left speed:%.3f m/s\r\n", L_cnt, L_speed_mps);
    printf("right pulse:%d, right speed:%.3f m/s\r\n", R_cnt, R_speed_mps);
}

