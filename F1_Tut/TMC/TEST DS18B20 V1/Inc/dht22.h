/*
 * dht22.h
 *
 *  Created on: Jan 3, 2015
 *      Author: peter
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include "stm32f1xx_hal.h"

/**
 * Possible return values of the functions
 */
typedef enum{
	DHT22_OK,
	DHT22_ERROR,
	DHT22_CRC_ERROR
} DHT22_RESULT;

/**
 * Describes the state of the sensor
 */
typedef enum{
	DHT22_RECEIVED,		/*< Data have been received but not yet processed */
	DHT22_RECEIVING,	/*< Data from sensor are currently being received */
	DHT22_READY	/*< The sensor has finished all operations and is in wait state */
} DHT22_STATE;

/**
 * This structure hold all the variables necessary for communication with the sensor
 */
typedef struct{
	uint8_t				bitsRX[5];
	float 				temp;
	float				hum;
	uint8_t				crcErrorFlag;
	DHT22_STATE			state;
	TIM_HandleTypeDef	timHandle;
	TIM_IC_InitTypeDef	timICHandle;
	uint32_t			timChannel;
	uint16_t			gpioPin;
	GPIO_TypeDef*		gpioPort;
	int					bitPos;
	IRQn_Type			timerIRQn;
	uint32_t			gpioAlternateFunction;
	uint16_t			lastVal;
	void				(*errorCallback)(DHT22_RESULT);
} DHT22_HandleTypeDef;

/**
 * Initializes the DHT22 communication
 * @param	handle - a pointer to the DHT22 handle
 * @return	whether the function was successful or not
 */
DHT22_RESULT DHT22_Init(DHT22_HandleTypeDef* handle);

/**
 * Deinitializes the DHT22 communication
 * @param	handle - a pointer to the DHT22 handle
 * @return	whether the function was successful or not
 */
DHT22_RESULT DHT22_DeInit(DHT22_HandleTypeDef* handle);

/**
 * Reads the current temperature and humidity from the sensor
 * @param	handle - a pointer to the DHT22 handle
 * @return	whether the function was successful or not
 */
DHT22_RESULT DHT22_ReadData(DHT22_HandleTypeDef* handle);

/**
 * Handles the pin interrupt
 * @param	handle - a pointer to the DHT22 handle
 */
void DHT22_InterruptHandler(DHT22_HandleTypeDef* handle);

/**
 * Initiates a transfer of sensor data
 * @param	handle - a pointer to the DHT22 handle
 */
DHT22_RESULT DHT22_InitiateTransfer(DHT22_HandleTypeDef* handle);

/**
 * Sets up the pin as an output
 * @param	handle - a pointer to the DHT22 handle
 */
void DHT22_SetPinOUT(DHT22_HandleTypeDef* handle);

/**
 * Sets up the pin as an input
 * @param	handle - a pointer to the DHT22 handle
 */
void DHT22_SetPinIN(DHT22_HandleTypeDef* handle);

#endif /* INC_DHT22_H_ */
