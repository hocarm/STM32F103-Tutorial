#ifndef MY_SPI_H_
#define MY_SPI_H_

#include "stm32f10x.h"

void spi_init(void);
uint8_t spi_exchange(uint8_t u8Data);

#endif
