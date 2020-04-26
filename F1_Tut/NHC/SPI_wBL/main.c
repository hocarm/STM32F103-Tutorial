#include "stm32f10x.h"
#include "delay.h"
#include "spi.h"

void My_GPIO_Init(void);

int main() {
	Delay_Init();
	My_SPI_Init();
	My_GPIO_Init();
	
	while(1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(100);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		My_SPI_Exchange(0x19);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(100);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		My_SPI_Exchange(0x86);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
}

void My_GPIO_Init(void) {
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);
}
