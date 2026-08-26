#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "colorful_led.h"
extern u8 count;
int main(void)
  { 
		RCC->CSR |=1<<24;
		Stm32_Clock_Init(9);						//Íâ²¿Ê±ÖÓ8Mhz 9±¶Æµ  8*9= 72mhz±¶Æµ72mhz
		MY_NVIC_PriorityGroupConfig(2);	//=====ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é		
		uart_init(115200);	            //=====´®¿Ú³õÊ¼»¯Îª115200
		JTAG_Set(JTAG_SWD_DISABLE);     //=====¹Ø±ÕJTAG½Ó¿Ú
		JTAG_Set(SWD_ENABLE);           //=====´ò¿ªSWD½Ó¿Ú ¿ÉÒÔÀûÓÃÖ÷°åµÄSWD½Ó¿Úµ÷ÊÔ
    PWM_Init(7199,9);
		colorful_led_Init();            //=====ìÅ²ÊµÆ³õÊ¼»¯

		printf("QSTÇàÈí\r\n");
		/**Ö÷Òª³ÌÐò**/
	while(1)
	{
		Set_Pwm(2500,2500);
		delay_ms(100);
	}
}
	

