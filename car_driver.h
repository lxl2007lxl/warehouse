#ifndef __CAR_DRIVER_H
#define __CAR_DRIVER_H

#include "stm32f1xx_hal.h"

/*==================== 【模块1：引脚与参数宏定义模块】 ====================*/
//电机L298N引脚
#define IN1_GPIO_PORT  GPIOA
#define IN1_GPIO_PIN   GPIO_PIN_0

#define IN2_GPIO_PORT  GPIOA
#define IN2_GPIO_PIN   GPIO_PIN_1

#define IN3_GPIO_PORT  GPIOA
#define IN3_GPIO_PIN   GPIO_PIN_2

#define IN4_GPIO_PORT  GPIOA
#define IN4_GPIO_PIN   GPIO_PIN_3

//HC?SR04超声波引脚
#define TRIG_GPIO_PORT GPIOB
#define TRIG_GPIO_PIN  GPIO_PIN_0

#define ECHO_GPIO_PORT GPIOB
#define ECHO_GPIO_PIN  GPIO_PIN_1

//TCRT5000左右黑线传感器引脚
#define IR_L_GPIO_PORT GPIOB
#define IR_L_GPIO_PIN  GPIO_PIN_2

#define IR_R_GPIO_PORT GPIOB
#define IR_R_GPIO_PIN  GPIO_PIN_3

//功能阈值参数
#define OBSTACLE_DIST  30.0f   //障碍物报警距离 单位cm
/*========================================================================*/

/*==================== 函数声明 ====================*/
//电机驱动
void car_forward(void);
void car_backward(void);
void car_left(void);
void car_right(void);
void car_stop(void);

//超声波测距
float get_hcsr04_distance(void);

//黑线检测
//返回：0无黑线；1左黑线；2右黑线；3左右黑线
uint8_t read_black_line(void);

#endif

