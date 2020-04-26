#include "stm32f10x.h"

void Delay_1_Ms(void);
void Delay_Ms(uint32_t u32Delay);

void Delay_1_Ms(void)
{
	
	SysTick->LOAD = 72 * 1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	while (!(SysTick->CTRL & (1 << 16))) {
	}
}

void Delay_Ms(uint32_t u32Delay)
{
	
	while (u32Delay) {
		Delay_1_Ms();
		--u32Delay;
	}
}

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	while (1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		Delay_Ms(100);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		Delay_Ms(200);
	}
	
}
