#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "colorful_led.h"
#include "Delay.h"

#include "motor.h"
#include "encoder.h"
#include "control_system.h"
#define SPEED  5000 
extern u8 count;
int main(void)
  {
		
		
		Motor_Init();
		RCC->CSR |=1<<24;
		Stm32_Clock_Init(9);						//Íâ²¿Ê±ÖÓ8Mhz 9±¶Æµ  8*9= 72mhz±¶Æµ72mhz
		MY_NVIC_PriorityGroupConfig(2);	//=====ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é		
		uart_init(115200);	            //=====´®¿Ú³õÊ¼»¯Îª115200
		JTAG_Set(JTAG_SWD_DISABLE);     //=====¹Ø±ÕJTAG½Ó¿Ú
		JTAG_Set(SWD_ENABLE);           //=====´ò¿ªSWD½Ó¿Ú ¿ÉÒÔÀûÓÃÖ÷°åµÄSWD½Ó¿Úµ÷ÊÔ
    PWM_Init(7199,9);
		
		colorful_led_Init();            //=====ìÅ²ÊµÆ³õÊ¼»¯
//Encoder_Init_TIM2();  //???TIM2 PA0 PA1
   // Encoder_Init_TIM3(); 
//SysTick_Config(72000000/1000); 		
		printf("QSTÇàÈí\r\n");
		/**Ö÷Òª³ÌÐò**/
	
	
while(1)
{
  Set_Pwm(5000, 5000);
		delay_ms(7000);
		
		//??
		Set_Pwm(0,0);
		delay_ms(100);
		
		//??5?
		Set_Pwm(-2500, -2500
	
	);
		delay_ms(7000);
		
		//??
		Set_Pwm(0,0);
		delay_ms(100);


   // static int last_L = 0;
   // static int last_R = 0;

   // int left_enc = Encoder_Get_TIM2();
   // int right_enc = Encoder_Get_TIM3();

  //  if(left_enc != last_L || right_enc != last_R)
