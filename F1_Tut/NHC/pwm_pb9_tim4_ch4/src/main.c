#include "stm32f10x.h"

void delay_ms(uint32_t u32DelayInMs);

void delay_ms(uint32_t u32DelayInMs)
{
	
	while (u32DelayInMs) {
		TIM_SetCounter(TIM4, 0);
		while (TIM_GetCounter(TIM4) < 1000) {
		}
		--u32DelayInMs;
	}
}

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef tim4Init;
	TIM_OCInitTypeDef pwmInit;
	
	/* clock PB */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* PB9 out */
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_9;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInit);
	
	/* timer 4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	tim4Init.TIM_Prescaler = 18 - 1;
	tim4Init.TIM_CounterMode = TIM_CounterMode_Up;
	tim4Init.TIM_Period = 8 - 1;//0xffff;
	tim4Init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &tim4Init);
	TIM_Cmd(TIM4, ENABLE);
	
	pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
	pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
	pwmInit.TIM_OutputState = TIM_OutputState_Enable;
	pwmInit.TIM_Pulse = 6;
	
	TIM_OC4Init(TIM4, &pwmInit);
	
	while (1) {
		/*
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		delay_ms(100);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_ms(200);
		*/
	}
}
