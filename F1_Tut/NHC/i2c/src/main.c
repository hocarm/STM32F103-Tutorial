#include "stm32f10x.h"

void Delay1Ms(void);
void Delay_Ms(uint32_t u32DelayInMs);
void delay_us(uint32_t delay);

void Delay1Ms(void)
{
	
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
}

void delay_us(uint32_t delay)
{
	
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < delay) {
	}
}

void Delay_Ms(uint32_t u32DelayInMs)
{
	
	while (u32DelayInMs) {
		Delay1Ms();
		--u32DelayInMs;
	}
}

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_write(uint8_t u8Data);
uint8_t i2c_read(uint8_t u8Ack);

#define SDA_0 GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define SDA_1 GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define SCL_0 GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define SCL_1 GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define SDA_VAL (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))

void i2c_init(void)
{
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	SDA_1;
	SCL_1;
}

void i2c_start(void)
{
	
	SCL_1;
	delay_us(3);
	SDA_1;
	delay_us(3);
	SDA_0;
	delay_us(3);
	SCL_0;
	delay_us(3);
}

void i2c_stop(void)
{
	
	SDA_0;
	delay_us(3);
	SCL_1;
	delay_us(3);
	SDA_1;
	delay_us(3);
}

uint8_t i2c_write(uint8_t u8Data)
{
	uint8_t i;
	uint8_t u8Ret;
	
	for (i = 0; i < 8; ++i) {
		if (u8Data & 0x80) {
			SDA_1;
		} else {
			SDA_0;
		}
		delay_us(3);
		SCL_1;
		delay_us(5);
		SCL_0;
		delay_us(2);
		u8Data <<= 1;
	}
	
	SDA_1;
	delay_us(3);
	SCL_1;
	delay_us(3);
	if (SDA_VAL) {
		u8Ret = 0;
	} else {
		u8Ret = 1;
	}
	delay_us(2);
	SCL_0;
	delay_us(5);
	
	return u8Ret;
}

uint8_t i2c_read(uint8_t u8Ack)
{
	uint8_t i;
	uint8_t u8Ret;
	
	SDA_1;
	delay_us(3);
	
	for (i = 0; i < 8; ++i) {
		u8Ret <<= 1;
		SCL_1;
		delay_us(3);
		if (SDA_VAL) {
			u8Ret |= 0x01;
		}
		delay_us(2);
		SCL_0;
		delay_us(5);
	}
	
	if (u8Ack) {
		SDA_0;
	} else {
		SDA_1;
	}
	delay_us(3);
	
	SCL_1;
	delay_us(5);
	SCL_0;
	delay_us(5);
	
	return u8Ret;
}

uint8_t at24c32_read(uint16_t u16Address, uint16_t u16Num, uint8_t *pu8Data);
uint8_t at24c32_write(uint16_t u16Address, uint8_t u16Num, uint8_t *pu8Data);

uint8_t at24c32_read(uint16_t u16Address, uint16_t u16Num, uint8_t *pu8Data)
{
	uint16_t i;
	
	i2c_start();
	if (i2c_write(0xa0) == 0) {
		i2c_stop();
		return 0;
	}
	
	if (i2c_write(u16Address >> 8) == 0) {
		i2c_stop();
		return 0;
	}
	
	if (i2c_write(u16Address) == 0) {
		i2c_stop();
		return 0;
	}
	
	i2c_start();
	
	if (i2c_write(0xa1) == 0) {
		i2c_stop();
		return 0;
	}
	
	for (i = 0; i < u16Num - 1; ++i) {
		pu8Data[i] = i2c_read(1);
	}
	
	pu8Data[i] = i2c_read(0);
	
	i2c_stop();
	
	return 1;
}

uint8_t at24c32_write(uint16_t u16Address, uint8_t u16Num, uint8_t *pu8Data)
{
	uint16_t i;
	
	for (i = 0; i < u16Num; ++i) {
		i2c_start();
		if (i2c_write(0xa0) == 0) {
			i2c_stop();
			return 0;
		}
		if (i2c_write((u16Address + i) >> 8) == 0) {
			i2c_stop();
			return 0;
		}
		
		if (i2c_write(u16Address + i) == 0) {
			i2c_stop();
			return 0;
		}
		if (i2c_write(pu8Data[i]) == 0) {
			i2c_stop();
			return 0;
		}
		i2c_stop();
		Delay_Ms(10);
	}
	
	return 1;
}

uint8_t u8Data[4] = {0x14, 0x12, 0x19, 0x86};
uint8_t u8Tmp[4] = {0x00, 0x00, 0x00, 0x00};

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_0;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpioInit);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
	
	i2c_init();
	
	if (at24c32_write(0x0000, 4, u8Data) == 0) {
		while (1) {
		}
	}
	
	while (1) {
		if (at24c32_read(0x0000, 4, u8Tmp) == 0) {
			while (1) {
			}
		}
		if ((u8Tmp[0] != 0x14) || (u8Tmp[1] != 0x12) || (u8Tmp[2] != 0x19) || (u8Tmp[3] != 0x86)) {
			while (1) {
			}
		}
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		Delay_Ms(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		Delay_Ms(500);
	}
	
}
