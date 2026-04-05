#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
		Delay_ms(20);
		KeyNum = 1;
		
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0);
		Delay_ms(20);
		KeyNum = 2;
		
	}
		return KeyNum;
}
	