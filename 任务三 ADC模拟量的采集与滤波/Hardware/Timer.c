#include "stm32f10x.h"                  // Device header
#include "SlidingWindow.h"
volatile uint8_t raw = 0;
volatile uint16_t NewAverage;
static uint8_t Count;
volatile uint16_t Print_Ready;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;

	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}
void TIM2_IRQHandler()
{
	while(TIM_GetITStatus(TIM2,TIM_IT_Update)==RESET);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	raw = ADC_GetConversionValue(ADC1);
	NewAverage = UpdateWindow(raw);
	
	Count ++;
	if(Count > WindowSize)
	{
		Count = 0;
		Print_Ready = 1;
		
	}
	

	
}