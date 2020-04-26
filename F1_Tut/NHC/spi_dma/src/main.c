#include "stm32f10x.h"

void Delay1Ms(void);
void Delay_Ms(uint32_t u32DelayInMs);

void Delay1Ms(void)
{
	
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
}

void Delay_Ms(uint32_t u32DelayInMs)
{
	
	while (u32DelayInMs) {
		Delay1Ms();
		--u32DelayInMs;
	}
}

void spi_send(uint8_t *pu8Data, uint32_t u32Len);

void spi_send(uint8_t *pu8Data, uint32_t u32Len)
{
	uint32_t i;
	
	for (i = 0; i < u32Len; ++i) {
		SPI_I2S_SendData(SPI2, pu8Data[i]);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET) {
		}
	}
}

uint8_t u8Buff[8 * 1024];

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	SPI_InitTypeDef spi2Init;
	DMA_InitTypeDef dmaInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	/* PB12 - CS */
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_12;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* PB13 - SCK */
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* PB14 - MISO */
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_14;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* PB15 - MOSI */
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_15;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* SPI2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	spi2Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spi2Init.SPI_CPHA = SPI_CPHA_1Edge;
	spi2Init.SPI_CPOL = SPI_CPOL_Low;
	spi2Init.SPI_DataSize = SPI_DataSize_8b;
	spi2Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi2Init.SPI_FirstBit = SPI_FirstBit_LSB;
	spi2Init.SPI_Mode = SPI_Mode_Master;
	spi2Init.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI2, &spi2Init);
	
	SPI_Cmd(SPI2, ENABLE);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay_Ms(1);
	
	/* gui du lieu khong dung DMA */
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_send(u8Buff, 8 * 1024);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	Delay_Ms(10);
	
	/* gui du lieu dung DMA */
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* cau hinh DMA */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	dmaInit.DMA_BufferSize = 8 * 1024;
	dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
	dmaInit.DMA_M2M = DMA_M2M_Disable;
	dmaInit.DMA_MemoryBaseAddr = (uint32_t)u8Buff;
	dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaInit.DMA_Mode = DMA_Mode_Normal;
	dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaInit.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel5, &dmaInit);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
	}
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	while (1) {
		
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
	}
	
}
