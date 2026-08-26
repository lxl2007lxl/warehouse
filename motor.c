#include "motor.h"

u16 PWM_A = 0;
u16 PWM_B = 0;
u32 myabs(long int a)
{
    u32 temp;
    if(a < 0) temp = -a;
    else temp = a;
    return temp;
}


void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_3; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_3);
}
void PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  
    TIM_TimeBaseStructure.TIM_Period = arr; 
    TIM_TimeBaseStructure.TIM_Prescaler = psc; 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    //   (PB6)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
    TIM_OC1Init(TIM4, &TIM_OCInitStructure); 

    
    TIM_OC2Init(TIM4, &TIM_OCInitStructure); 

    
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
    
    TIM_ARRPreloadConfig(TIM4, ENABLE); 
    TIM_Cmd(TIM4, ENABLE);  
}


void Set_Pwm(int moto1, int moto2)
{
    
    if(moto1 > 0) {
        
        GPIO_ResetBits(GPIOB, GPIO_Pin_13); // AIN1 = 0
        GPIO_SetBits(GPIOB, GPIO_Pin_14);   
        PWM_A = myabs(moto1);
    } else {
        
        GPIO_SetBits(GPIOB, GPIO_Pin_13);   // AIN1 = 1
        GPIO_ResetBits(GPIOB, GPIO_Pin_14); // AIN2 = 0
        PWM_A = myabs(moto1);
    }
    
    
    if(PWM_A > 7199) PWM_A = 7199;
    
    
    TIM_SetCompare1(TIM4, PWM_A);


    
    if(moto2 > 0) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15); // BIN1 = 0
        GPIO_SetBits(GPIOB, GPIO_Pin_3);    // BIN2 = 1
        PWM_B = myabs(moto2);
    } else {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);   // BIN1 = 1
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);  // BIN2 = 0
        PWM_B = myabs(moto2);
    }

    if(PWM_B > 7199) PWM_B = 7199;

    
    TIM_SetCompare2(TIM4, PWM_B);
}
