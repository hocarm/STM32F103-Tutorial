#include "stm32f10x.h"

void delay(void);

void delay(void)
{
	uint32_t i;
	
	for (i = 0; i < 0xfffff; ++i) {
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
	
	while (1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay();
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay();
	}
	
}
