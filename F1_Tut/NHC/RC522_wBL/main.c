#include "stm32f10x.h"
#include "delay.h"
#include "mfrc522.h"
#include "i2c_lcd.h"
#include <stdio.h>

void My_GPIO_Init(void);

uint8_t CardID[5];
char szBuff[100];

int main() {
	Delay_Init();
	My_GPIO_Init();
	TM_MFRC522_Init();
	I2C_LCD_Init();
	I2C_LCD_Clear();
	I2C_LCD_BackLight(1);
	I2C_LCD_Puts("STM32 - MFRC522");
	I2C_LCD_NewLine();
	I2C_LCD_Puts("vidieukhien.org");
	
	while(1) {
		if (TM_MFRC522_Check(CardID) == MI_OK) {
			sprintf(szBuff, "ID: 0x%02X%02X%02X%02X%02X", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
			I2C_LCD_Clear();
			I2C_LCD_Puts("STM32 - MFRC522");
			I2C_LCD_NewLine();
			I2C_LCD_Puts(szBuff);
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(2000);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
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
