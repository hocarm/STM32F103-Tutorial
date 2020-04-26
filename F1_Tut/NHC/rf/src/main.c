#include "stm32f10x.h"

void Delay1Ms(void);
void Delay_Ms(uint32_t u32DelayInMs);
uint32_t rf_decode(void);

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

#define RF_IN (GPIO_ReadInputData(GPIOB) & (1 << 10))
#define SYNC_MAX 11000
#define SYNC_MIN 9000
#define BIT_S_MIN 200
#define BIT_S_MAX 400
#define BIT_L_MIN 900
#define BIT_L_MAX 1100

uint32_t rf_decode(void)
{
	uint32_t timeOut = 0;
	uint32_t count = 0;
	uint32_t timeValue = 0;
	uint32_t result = 0;
	
	if (RF_IN) {
		return 0;
	}
	
	timeOut = 1;
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < SYNC_MAX) {
		if (RF_IN) {
			timeOut = 0;
			break;
		}
	}
	if (timeOut) {
		return 0;
	}
	if (TIM_GetCounter(TIM2) < SYNC_MIN) {
		return 0;
	}
	
	count = 0;
	while (count < 24) {
		timeOut = 1;
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < BIT_L_MAX) {
			if (!RF_IN) {
				timeOut = 0;
				break;
			}
		}
		if (timeOut) {
			return 0;
		}
		
		timeValue = TIM_GetCounter(TIM2);
		if ((timeValue > BIT_S_MIN) && (timeValue < BIT_S_MAX)) {
			/* bit 0 */
			timeOut = 1;
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < BIT_L_MAX) {
				if (RF_IN) {
					timeOut = 0;
					break;
				}
			}
			if (timeOut) {
				return 0;
			}
			timeValue = TIM_GetCounter(TIM2);
			if ((timeValue > BIT_L_MIN) && (timeValue < BIT_L_MAX)) {
				result <<= 1;
				++count;
			} else {
				return 0;
			}
		} else if ((timeValue > BIT_L_MIN) && (timeValue < BIT_L_MAX)) {
			/* bit 1 */
			timeOut = 1;
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < BIT_L_MAX) {
				if (RF_IN) {
					timeOut = 0;
					break;
				}
			}
			if (timeOut) {
				return 0;
			}
			timeValue = TIM_GetCounter(TIM2);
			if ((timeValue > BIT_S_MIN) && (timeValue < BIT_S_MAX)) {
				result <<= 1;
				result |= 1;
				++count;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	}
	
	return result;
}

#define BUTTON_A 0x6d7ee4

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	uint32_t led = 0;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	
	while (1) {
		if (rf_decode() == BUTTON_A) {
			if (led) {
				led = 0;
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			} else {
				led = 1;
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
			}
			Delay_Ms(500);
		}
	}
}
