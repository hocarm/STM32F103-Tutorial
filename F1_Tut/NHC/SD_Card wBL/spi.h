#ifndef SPI_H_
#define SPI_H_

#include "stm32f10x.h"

void My_SPI_Init(void);
uint8_t My_SPI_Exchange(uint8_t u8Data);

#endif
