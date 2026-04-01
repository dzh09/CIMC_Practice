#include "stm32f10x.h"                  // Device header
#include "fputc.h"
#include "stdio.h"
#include "MYUSART.h"
int main(void)
{
	uint16_t Systemtime;
	MYUSART_Init();
	printf("System:Open Successfully");
 	while (1)
	{
		Systemtime += 500;
		printf("Time:%d",Systemtime);
	
	}
	
}



		