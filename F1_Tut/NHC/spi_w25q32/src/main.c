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

uint8_t spi_exchange(uint8_t u8Data);
void w25q32_sector_erase(uint32_t u32Address);
void w25q32_page_write(uint32_t u32Address, uint8_t *pu8Data);
void w25q32_read(uint32_t u32Address, uint8_t *pu8Data, uint32_t len);

uint8_t spi_exchange(uint8_t u8Data)
{
	
	SPI_I2S_SendData(SPI2, u8Data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
	}
	return SPI_I2S_ReceiveData(SPI2);
}

void w25q32_sector_erase(uint32_t u32Address)
{
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_exchange(0x06);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);

	Delay_Ms(1);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_exchange(0x20);
	spi_exchange((u32Address >> 16));
	spi_exchange((u32Address >> 8));
	spi_exchange((u32Address));
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	Delay_Ms(400);
}

void w25q32_page_write(uint32_t u32Address, uint8_t *pu8Data)
{
	uint16_t i;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_exchange(0x06);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);

	Delay_Ms(1);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_exchange(0x02);
	spi_exchange((u32Address >> 16));
	spi_exchange((u32Address >> 8));
	spi_exchange((u32Address));
	for (i = 0; i < 256; ++i) {
		spi_exchange(pu8Data[i]);
	}
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	Delay_Ms(3);
}

void w25q32_read(uint32_t u32Address, uint8_t *pu8Data, uint32_t len)
{
	uint32_t i;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	spi_exchange(0x03);
	spi_exchange((u32Address >> 16));
	spi_exchange((u32Address >> 8));
	spi_exchange((u32Address));
	for (i = 0; i < len; ++i) {
		pu8Data[i] = spi_exchange(0x00);
	}
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

uint8_t u8Buff[256];
uint8_t u8ReadBuff[256];

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	SPI_InitTypeDef spi2Init;
	uint32_t i;
	
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
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
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
	spi2Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
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
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
	spi_exchange(0x9f);
	u8Buff[0] = spi_exchange(0x00);
	u8Buff[1] = spi_exchange(0x00);
	u8Buff[2] = spi_exchange(0x00);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	if ((u8Buff[0] != 0xef) || (u8Buff[1] != 0x40) || (u8Buff[2] != 0x16)) {
		while (1) {
		}
	}
	
	w25q32_sector_erase(0x00000000);
	
	for (i = 0; i < 256; ++i) {
		u8Buff[i] = i;
	}
	
	w25q32_page_write(0x00000000, u8Buff);
	
	w25q32_read(0x00, u8ReadBuff, 256);
	
	for (i = 0; i < 256; ++i) {
		if (u8Buff[i] != u8ReadBuff[i]) {
			while (1) {
			}
		}
	}
	
	while (1) {
		
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
	}
	
}
