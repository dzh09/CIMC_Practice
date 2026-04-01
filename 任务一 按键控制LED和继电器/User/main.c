#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "fputc.h"
#include "stdio.h"
#include "MYUSART.h"
uint8_t KeyNum;
int main(void)
{
	
	LED_Init();
	MYUSART_Init();
	
 	while (1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			LED1_Invert();
			printf("YES,kEY1");
				
		}
		if(KeyNum == 2)
		{
			LED2_Invert();
			printf("YES,kEY2");
		}
	 }
	
}



		