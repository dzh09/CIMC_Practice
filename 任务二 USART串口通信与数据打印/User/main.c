#include "stm32f10x.h"                  // Device header
#include "fputc.h"
#include "stdio.h"
#include "MYUSART.h"
#include "Delay.h"
int main(void)
{
	uint16_t Systemtime = 0;
	MYUSART_Init();
	printf("System:Open Successfully\r\n");
	
 	while (1)
	{
	Systemtime += 500;
	Delay_ms(500);
	printf("Time:%d\r\n",Systemtime);
	
	}
	
}



		