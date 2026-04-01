#include "stm32f10x.h"                  // Device header
#include "stdio.h"
int fputc(int ch,FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,(uint8_t)ch);
	
	return ch;
}
 