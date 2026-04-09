#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "fputc.h"
#include "stdio.h"
#include "MYUSART.h"
#include "MYADC.h"
#include "TIMER.h"
#include "SlidingWindow.h"
#include "OLED.h"
int main(void)
{
	//MYUSART_Init();
	MYADC_Init();
	OLED_Init();
	OLED_ShowString(1,1,"ADC");
	SlidingWindow_Init();
	Timer_Init();
	while(1)
	{	
		OLED_ShowNum(1,5,NewAverage,4);
		if(Print_Ready == 1)
		{
			Print_Ready = 0;
			float percent = NewAverage * 100.0f/ 4095.0f;
			 printf("[Sensor] Raw: %4d, Filtered: %4d, Value: %.2f%%\r\n",raw, NewAverage, percent);
		}
	}
	
	
}






		