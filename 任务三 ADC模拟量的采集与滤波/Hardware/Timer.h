#ifndef __TIMER_H_
#define __TIMER_H_
void Timer_Init(void);
void TIM2_IRQHandler();
extern volatile uint8_t raw;
extern volatile uint16_t NewAverage;
extern volatile uint16_t Print_Ready;
#endif
