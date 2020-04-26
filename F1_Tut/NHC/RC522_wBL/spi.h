#include "stm32f10x.h"

/*=======================================================================
Ngo Hung Cuong
http://vidieukhien.org
ngohungcuong@gmail.com
0989696971
=======================================================================*/

#ifndef KT_SPI_H_
#define KT_SPI_H_

void TM_SPI_Init(void);

uint8_t TM_SPI_Send(uint8_t data);

extern void TM_MFRC522_InitPins(void);

#define MFRC522_CS_LOW					GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define MFRC522_CS_HIGH					GPIO_SetBits(GPIOB, GPIO_Pin_12)

#endif
