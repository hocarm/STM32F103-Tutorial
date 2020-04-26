/*
 * dht22.c
 *
 *  Created on: Jan 3, 2015
 *      Author: peter
 */

#include "dht22.h"

#define DHT22_StartIT()	if(HAL_TIM_IC_Start_IT(&handle->timHandle, handle->timChannel) != HAL_OK) return DHT22_ERROR
#define DHT22_StopIT()	if(HAL_TIM_IC_Stop_IT(&handle->timHandle, handle->timChannel) != HAL_OK) return DHT22_ERROR

void DHT22_SetPinOUT(DHT22_HandleTypeDef* handle) {
	HAL_NVIC_DisableIRQ(handle->timerIRQn);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = handle->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(handle->gpioPort, &GPIO_InitStruct);
}

void DHT22_SetPinIN(DHT22_HandleTypeDef* handle) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = handle->gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = handle->gpioAlternateFunction;
	HAL_GPIO_Init(handle->gpioPort, &GPIO_InitStruct);
	HAL_NVIC_EnableIRQ(handle->timerIRQn);
	HAL_NVIC_SetPriority(handle->timerIRQn, 0, 0);
}

DHT22_RESULT DHT22_Init(DHT22_HandleTypeDef* handle) {
	handle->timHandle.Init.Period = 0xFFFF;
	handle->timHandle.Init.Prescaler = 0;
	handle->timHandle.Init.ClockDivision = 0;
	handle->timHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	if (HAL_TIM_IC_Init(&handle->timHandle) != HAL_OK) {
		return DHT22_ERROR;
	}
	handle->timICHandle.ICPolarity = TIM_ICPOLARITY_FALLING;
	handle->timICHandle.ICSelection = TIM_ICSELECTION_DIRECTTI;
	handle->timICHandle.ICPrescaler = TIM_ICPSC_DIV1;
	handle->timICHandle.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&handle->timHandle, &handle->timICHandle,
			handle->timChannel) != HAL_OK) {
		return DHT22_ERROR;
	}
	return DHT22_OK;
}

DHT22_RESULT DHT22_DeInit(DHT22_HandleTypeDef* handle) {
	return DHT22_OK;
}

DHT22_RESULT DHT22_InitiateTransfer(DHT22_HandleTypeDef* handle) {

	DHT22_SetPinOUT(handle);
	HAL_GPIO_WritePin(handle->gpioPort, handle->gpioPin, GPIO_PIN_RESET);
	HAL_Delay(2);
	DHT22_SetPinIN(handle);

	handle->bitPos = -1;
	for (int i = 0; i < 5; i++) {
		handle->bitsRX[i] = 0;
	}
	handle->state = DHT22_RECEIVING;
	DHT22_StartIT();

	return DHT22_OK;
}

void DHT22_InterruptHandler(DHT22_HandleTypeDef* handle) {

	uint16_t val = HAL_TIM_ReadCapturedValue(&handle->timHandle,
			handle->timChannel);

	uint32_t freq = HAL_RCC_GetPCLK2Freq();

	uint16_t val2;
	if (val > handle->lastVal)
		val2 = val - handle->lastVal;
	else
		val2 = 65535 + val - handle->lastVal;

	handle->lastVal = val;

	float time = 1000000.0 * val2 / freq;

	if (handle->bitPos < 0) {
		if (time > 155.0 && time < 165.0) {
			handle->bitPos = 0;
		}
	} else if (handle->bitPos >= 0 && handle->bitPos < 40) {
		if (time > 78.0 && time < 97.0) {
			handle->bitsRX[handle->bitPos / 8] &= ~(1
					<< (7 - handle->bitPos % 8));
			handle->bitPos++;
		} else if (time > 120.0 && time < 145.0) {
			handle->bitsRX[handle->bitPos / 8] |= 1 << (7 - handle->bitPos % 8);
			handle->bitPos++;
		} else {
			handle->bitPos = -1;
			HAL_TIM_IC_Stop_IT(&handle->timHandle, handle->timChannel);
			handle->state = DHT22_READY;
		}
	}

	if(handle->bitPos==40){
		handle->bitPos = -1;
		HAL_TIM_IC_Stop_IT(&handle->timHandle, handle->timChannel);
		uint8_t sum = 0;
		for (int i = 0; i < 4; i++) {
			sum += handle->bitsRX[i];
		}
		if (sum == handle->bitsRX[4]) {
			handle->crcErrorFlag = 0;

			int16_t temp10 = 0;
			if ((handle->bitsRX[2] & 0x80) == 0x80) {
				temp10 |= (handle->bitsRX[2] & 0x7F) << 8;
				temp10 |= handle->bitsRX[3];
				temp10 *= -1;
			} else {
				temp10 |= handle->bitsRX[2] << 8;
				temp10 |= handle->bitsRX[3];
			}
			handle->temp = 0.1 * temp10;

			int16_t hum10 = 0;
			if ((handle->bitsRX[0] & 0x80) == 0x80) {
				hum10 |= (handle->bitsRX[0] & 0x7F) << 8;
				hum10 |= handle->bitsRX[1];
				hum10 *= -1;
			} else {
				hum10 |= handle->bitsRX[0] << 8;
				hum10 |= handle->bitsRX[1];
			}
			handle->hum = 0.1 * hum10;
		} else {
			handle->crcErrorFlag = 1;
		}
		handle->state = DHT22_RECEIVED;
	}

}

DHT22_RESULT DHT22_ReadData(DHT22_HandleTypeDef* handle) {

	DHT22_InitiateTransfer(handle);
	uint32_t startTick=HAL_GetTick();
	while (handle->state == DHT22_RECEIVING && HAL_GetTick()-startTick<1000);
	if(handle->crcErrorFlag==1){
		return DHT22_CRC_ERROR;
	}
	if(handle->state!=DHT22_RECEIVED){
		return DHT22_ERROR;
	}else{
		handle->state=DHT22_READY;
	}
	return DHT22_OK;
}
