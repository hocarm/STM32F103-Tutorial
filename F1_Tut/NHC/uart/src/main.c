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
	USART_InitTypeDef uartInit;
	uint8_t u8Data;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* PB10 TX */
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* PB11 RX */
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_11;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	uartInit.USART_BaudRate = 9600;
	uartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uartInit.USART_Parity = USART_Parity_No;
	uartInit.USART_StopBits = USART_StopBits_1;
	uartInit.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &uartInit);
	
	USART_Cmd(USART3, ENABLE);
	
	while (1) {
		if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
			u8Data = USART_ReceiveData(USART3);
			USART_SendData(USART3, u8Data);
			while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET) {
			}
		}
		/*
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		USART_SendData(USART3, 0x19);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET) {
		}
		Delay_Ms(100);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		USART_SendData(USART3, 0x86);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET) {
		}
		Delay_Ms(200);
		*/
	}
	
}
