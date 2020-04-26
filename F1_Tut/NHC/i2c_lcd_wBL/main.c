#include "stm32f10x.h"
#include "delay.h"
#include "i2c_lcd.h"

void init(void);

int main() {
	uint8_t test = 0;
	
	init();
	Delay_Init();
	
	I2C_LCD_Init();
	I2C_LCD_Clear();
	I2C_LCD_BackLight(1);
	
	while(1) {
		if (test) {
			test = 0;
			I2C_LCD_Clear();
			I2C_LCD_Puts("STM32F103C8T6");
			I2C_LCD_NewLine();
			I2C_LCD_Puts("LCD I2C Test");
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		} else {
			test = 1;
			I2C_LCD_Clear();
			I2C_LCD_Puts("Ngo Hung Cuong");
			I2C_LCD_NewLine();
			I2C_LCD_Puts("LCD I2C Library");
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}
		Delay_Ms(2000);
	}
}

void init(void) {
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);
}
