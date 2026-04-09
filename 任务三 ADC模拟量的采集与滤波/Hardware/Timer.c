#include "stm32f10x.h"                  // Device header
#include "SlidingWindow.h"
#include "Delay.h"
volatile uint8_t raw;
volatile uint16_t NewAverage;
static uint8_t Count;
volatile uint16_t Print_Ready;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	
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
	// 中断内翻转
   
    // ... 原有代码
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		
		if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_5)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		
	}
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		raw = ADC_GetConversionValue(ADC1);
		NewAverage = UpdateWindow(raw);
		
		Count ++;
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}
	if(Count > WindowSize)
	{
		Count = 0;
		Print_Ready = 1;
		
	}
	
}

