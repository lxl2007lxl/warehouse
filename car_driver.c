#include "car_driver.h"

/*==================== 【模块2：电机驱动动作函数模块】 ====================*/
void car_forward(void)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT,IN1_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN2_GPIO_PORT,IN2_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN3_GPIO_PORT,IN3_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN4_GPIO_PORT,IN4_GPIO_PIN,GPIO_PIN_RESET);
}

void car_backward(void)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT,IN1_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_GPIO_PORT,IN2_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN3_GPIO_PORT,IN3_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_GPIO_PORT,IN4_GPIO_PIN,GPIO_PIN_SET);
}

void car_left(void)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT,IN1_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_GPIO_PORT,IN2_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN3_GPIO_PORT,IN3_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN4_GPIO_PORT,IN4_GPIO_PIN,GPIO_PIN_RESET);
}

void car_right(void)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT,IN1_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN2_GPIO_PORT,IN2_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN3_GPIO_PORT,IN3_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_GPIO_PORT,IN4_GPIO_PIN,GPIO_PIN_SET);
}

void car_stop(void)
{
    HAL_GPIO_WritePin(IN1_GPIO_PORT,IN1_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_GPIO_PORT,IN2_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN3_GPIO_PORT,IN3_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_GPIO_PORT,IN4_GPIO_PIN,GPIO_PIN_RESET);
}
/*========================================================================*/

/*==================== 【模块3：HC?SR04超声波测距模块】 ====================*/
float get_hcsr04_distance(void)
{
    uint32_t time_us;
    //输出10us触发脉冲
    HAL_GPIO_WritePin(TRIG_GPIO_PORT, TRIG_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_PORT, TRIG_GPIO_PIN, GPIO_PIN_RESET);

    //等待ECHO高电平开始
    while(HAL_GPIO_ReadPin(ECHO_GPIO_PORT,ECHO_GPIO_PIN)==GPIO_PIN_RESET);
    time_us = HAL_GetTick();
    //等待ECHO高电平结束
    while(HAL_GPIO_ReadPin(ECHO_GPIO_PORT,ECHO_GPIO_PIN)==GPIO_PIN_SET);
    time_us = HAL_GetTick() - time_us;

    return (float)time_us / 58.0f;
}
/*========================================================================*/

/*==================== 【模块4：TCRT5000黑线检测模块】 ====================*/
/*
返回值说明
0：地面白色，无黑线
1：左侧传感器压到黑线
2：右侧传感器压到黑线
3：左右都压到黑线
TCRT5000：检测黑线输出低电平GPIO_PIN_RESET；白色输出高电平GPIO_PIN_SET
*/
uint8_t read_black_line(void)
{
    uint8_t left  = HAL_GPIO_ReadPin(IR_L_GPIO_PORT, IR_L_GPIO_PIN);
    uint8_t right = HAL_GPIO_ReadPin(IR_R_GPIO_PORT, IR_R_GPIO_PIN);
    uint8_t flag = 0;

    if(left  == GPIO_PIN_RESET) flag |= 1;
    if(right == GPIO_PIN_RESET) flag |= 2;
    return flag;
}
/*========================================================================*/

