#ifndef _PMS7003_H_
#define _PMS7003_H_

#include "stm32f1xx_hal.h"
/**
 *  Dinh nghia gia tri bit bat dau cua PMS7003
 */
#define PMS_START_BYTE_1 0x42
#define PMS_START_BYTE_2 0x4d

/**
 *  Cac lenh dieu khien PMS7003 
 */
static  uint8_t wakeup[7] = {0x42, 0x4D, 0xE4, 0x00, 0x01, 0x01, 0x74};
static  uint8_t active[7] = {0x42, 0x4d, 0xe1, 0x00, 0x01, 0x01, 0x71};
static  uint8_t sleep[7] =  {0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73};
static uint8_t passive[] = { 0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70 };
static uint8_t rpassive[] = { 0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71 };

/**
 * Mo ta trang thai hien tai cua Sensor
 */
typedef enum{
	PMS7003_RECEIVED,		/*< Trang thai da nhan duoc du lieu nhung chua xu ly */
	PMS7003_RECEIVING,	/*< Trang thai du lieu cam bien da duoc nhan va xu ly xong*/
	PMS7003_OFF,
	PMS7003_ON,
	PMS7003_CRC_ERROR, /*< Trang thai nhan du lieu bi loi*/
	PMS7003_ERROR,
} PMS7003_STATE;

/**
 * Struct chua tat ca cac bien can de giao tiep voi cam bien
 */
struct PMS7003_Data{
	volatile uint8_t 			frame;
	volatile uint8_t 			checksum;
	volatile uint8_t 			pm1p0;
	volatile uint8_t 			pm2p5;
	volatile uint8_t 			pm10;
	volatile uint8_t 			pm1p0_ATM;
	volatile uint8_t			pm2p5_ATM;
	volatile uint8_t 			pm10_ATM;
	uint8_t 			Buf;
	uint8_t 			uartBuf[31];
	uint8_t				countDataToReceive;
	PMS7003_STATE 		state;
};

void PMS7003_ReceiveStart_IT(UART_HandleTypeDef* handle);
void PMS7003_TransferData(UART_HandleTypeDef* handle);
void PMS7003_ReceiveData_IT(UART_HandleTypeDef* handle);
int PMS7003_ReceiveData(UART_HandleTypeDef* handle);

#endif /* _PMS7003_H_ */
