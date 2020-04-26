#include "delay.h"

static void Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	uint16_t PrescalerValue = 0;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void Delay_Init(void)
{
	Timer_Init();
}

void Delay_Us(uint32_t u32DelayInUs)
{
	TIM_SetCounter(TIM3, 0);
	while(TIM_GetCounter(TIM3) < u32DelayInUs);
}

void Delay_Ms(uint32_t u32DelayInMs)
{
	while (u32DelayInMs) {
		Delay_Us(1000);
		--u32DelayInMs;
	}
}
