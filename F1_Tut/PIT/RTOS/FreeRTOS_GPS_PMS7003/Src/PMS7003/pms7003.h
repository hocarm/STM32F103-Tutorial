#ifndef _PMS7003_H_
#define _PMS7003_H_

#include "stm32f1xx_hal.h"

/**
 *  define start bit value PMS7003
 */
#define PMS_START_BYTE_1 0x42
#define PMS_START_BYTE_2 0x4d

/**
 *  Comands controls PMS7003 via UART
 */
static const uint8_t wakeup[7] = {0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74};
static const uint8_t sleep[7] =  {0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73};
static const uint8_t active[7] = {0x42, 0x4d, 0xe1, 0x00, 0x01, 0x01, 0x71};

/**
 * Possible return values of the functions
 */
typedef enum{
	PMS7003_OK,
//	PMS7003_ERROR,
//	PMS7003_CRC_ERROR
} PMS7003_RESULT;

/**
 * Describes the state of the sensor
 */
typedef enum{
	PMS7003_RECEIVED,		/*< Data have been received but not yet processed */
	PMS7003_RECEIVING,	/*< Data from sensor are currently being received */
	PMS7003_OFF,
	PMS7003_ON,
	PMS7003_CRC_ERROR,
	PMS7003_ERROR,
} PMS7003_STATE;

/**
 * This structure hold all the variables necessary for communication with the sensor
 */
typedef struct{
	volatile uint8_t 			pm1p0;
	volatile uint8_t 			pm2p5;
	volatile uint8_t 			pm10;
	volatile uint8_t 			pm1p0_ATM;
	volatile uint8_t				pm2p5_ATM;
	volatile uint8_t 			pm10_ATM;
	uint16_t			PMS_gpioPin;
	GPIO_TypeDef*		PMS_gpioPort;
	uint16_t			HEATER_gpioPin;
	GPIO_TypeDef*		HEATER_gpioPort;
	uint8_t				uartNumber;
	UART_HandleTypeDef 	*uart;
	uint8_t 			uartBuf[50];
	uint8_t				countDataToReceive;
	PMS7003_STATE 		state;
} PMS7003_HandleTypeDef;

void HEATHER_on(PMS7003_HandleTypeDef* handle);

void HEATHER_off(PMS7003_HandleTypeDef* handle);

void PMS7003_on(PMS7003_HandleTypeDef* handle);

void PMS7003_off(PMS7003_HandleTypeDef* handle);

void PMS7003_ReceiveStart(PMS7003_HandleTypeDef* handle);

void PMS7003_ReceiveUART(PMS7003_HandleTypeDef* handle);


#endif /* _PMS7003_H_ */
