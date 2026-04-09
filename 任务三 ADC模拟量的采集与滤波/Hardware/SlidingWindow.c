#include "stm32f10x.h"                  // Device header
#define WindowSize 100
static uint8_t ADC_Buffer[WindowSize];
static uint16_t Temp;
static uint32_t Sum;
static uint16_t AverageValue;
static uint16_t index = 0;
void SlidingWindow_Init(void)
{
	uint8_t i = 0;
	for(i=0;i<WindowSize;i++)
	{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)== RESET);
		Temp = ADC_GetConversionValue(ADC1);
		ADC_Buffer[i]=Temp;
		Sum += Temp;
	}
	AverageValue = Sum / WindowSize;
	
}
int UpdateWindow(uint8_t NewValue)
{
	Sum -= ADC_Buffer[index];
	ADC_Buffer[index]=NewValue;
	Sum += ADC_Buffer[index];
	index = (index + 1)%WindowSize;
	AverageValue = Sum / WindowSize;
	return AverageValue;
}
