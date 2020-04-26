#include "myspi.h"

void spi_init(void)
{
	GPIO_InitTypeDef gpioInit;
	SPI_InitTypeDef spi2Init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* PB10 - RESET */
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	
	/* PB11 - A0 */
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_11;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	
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
	spi2Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spi2Init.SPI_CPHA = SPI_CPHA_2Edge;
	spi2Init.SPI_CPOL = SPI_CPOL_High;
	spi2Init.SPI_DataSize = SPI_DataSize_8b;
	spi2Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi2Init.SPI_FirstBit = SPI_FirstBit_MSB;
	spi2Init.SPI_Mode = SPI_Mode_Master;
	spi2Init.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPI2, &spi2Init);
	
	SPI_Cmd(SPI2, ENABLE);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

uint8_t spi_exchange(uint8_t u8Data)
{
	
	SPI_I2S_SendData(SPI2, u8Data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
	}
	return SPI_I2S_ReceiveData(SPI2);
}
