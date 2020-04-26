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

void spi_send(uint8_t u8Data);

void spi_send(uint8_t u8Data)
{
	
	SPI_I2S_SendData(SPI2, u8Data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
	}
}

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	SPI_InitTypeDef spi2Init;
	uint32_t count = 0;
	
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
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
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
	spi2Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	spi2Init.SPI_CPHA = SPI_CPHA_1Edge;
	spi2Init.SPI_CPOL = SPI_CPOL_Low;
	spi2Init.SPI_DataSize = SPI_DataSize_8b;
	spi2Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi2Init.SPI_FirstBit = SPI_FirstBit_MSB;
	spi2Init.SPI_Mode = SPI_Mode_Master;
	spi2Init.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI2, &spi2Init);
	
	SPI_Cmd(SPI2, ENABLE);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
	
	/* chon che do giai ma */
	/* giai ma led 7 doan tat ca 8 led */
	spi_send(0x09);
	spi_send(0xff);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* chon do sang 7 / 32 */
	spi_send(0x0a);
	spi_send(0x03);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* hien thi 8 led */
	spi_send(0x0b);
	spi_send(0x07);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* che do hoat dong binh thuong */
	spi_send(0x0c);
	spi_send(0x01);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* che do hoat dong binh thuong */
	spi_send(0x0f);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 0 */
	spi_send(0x01);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 1 */
	spi_send(0x02);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 2 */
	spi_send(0x03);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 3 */
	spi_send(0x04);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 4 */
	spi_send(0x05);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 5 */
	spi_send(0x06);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 6 */
	spi_send(0x07);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	/* led 7 */
	spi_send(0x08);
	spi_send(0x00);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	while (1) {
		
		/* led 0 */
		spi_send(0x01);
		spi_send(count % 10);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		
		/* led 1 */
		spi_send(0x02);
		spi_send((count / 10) % 10);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		
		Delay_Ms(500);
		++count;
	}
	
}
