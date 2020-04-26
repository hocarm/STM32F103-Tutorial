#include "..\Src\PMS7003\pms7003.h"

void HEATHER_on(PMS7003_HandleTypeDef* handle) {
	HAL_GPIO_WritePin(handle->HEATER_gpioPort, handle->HEATER_gpioPin, SET);
}

void HEATHER_off(PMS7003_HandleTypeDef* handle) {
	HAL_GPIO_WritePin(handle->HEATER_gpioPort, handle->HEATER_gpioPin, RESET);
}

void PMS7003_on(PMS7003_HandleTypeDef* handle) {
	HAL_GPIO_WritePin(handle->PMS_gpioPort, handle->PMS_gpioPin, SET);
	handle->state = PMS7003_ON;
}

void PMS7003_off(PMS7003_HandleTypeDef* handle) {
	HAL_GPIO_WritePin(handle->PMS_gpioPort, handle->PMS_gpioPin, RESET);
	handle->state = PMS7003_OFF;
}

void PMS7003_ReceiveStart(PMS7003_HandleTypeDef* handle) {
	//HAL_UART_Receive_IT(&huart2, handle->uartBuf, 1);

}

void PMS7003_ReceiveUART(PMS7003_HandleTypeDef* handle) {
	//handle->state = PMS7003_RECEIVING;
	if (handle->uartBuf[0] == PMS_START_BYTE_1) { //0x42 first start character
		handle->countDataToReceive = 31; // start receive PMS7003 data
		HAL_UART_Receive_IT(handle->uart, handle->uartBuf, 31);
		handle->state = PMS7003_RECEIVING;
	}
	if (handle->uartBuf[0] == PMS_START_BYTE_2 && handle->state == PMS7003_RECEIVING) {
		int check_code = PMS_START_BYTE_1;
		//uint8_t i = 0;
		//while(i <= 28) {
		//check_code = +handle->uartBuf[i];
		//i++;
		//}
		if (check_code == check_code/*((handle->uartBuf[29] << 8) + handle->uartBuf[30])*/) {
			handle->pm1p0 = ((handle->uartBuf[3] << 8) + handle->uartBuf[4]);
			handle->pm1p0_ATM = ((handle->uartBuf[5] << 8) + handle->uartBuf[6]);
			handle->pm2p5 = ((handle->uartBuf[7] << 8) + handle->uartBuf[8]);
			handle->pm2p5_ATM = ((handle->uartBuf[9] << 8) + handle->uartBuf[10]);
			handle->pm10 = ((handle->uartBuf[11] << 8) + handle->uartBuf[12]);
			handle->pm10_ATM = ((handle->uartBuf[13] << 8) + handle->uartBuf[14]);
			HAL_UART_Receive_IT(handle->uart, handle->uartBuf,1);
			handle->state = PMS7003_RECEIVED;
		}
		else{
			HAL_UART_Receive_IT(handle->uart, handle->uartBuf,1);
			handle->state = PMS7003_CRC_ERROR;
		}
	}
	else HAL_UART_Receive_IT(handle->uart, handle->uartBuf,1);
}

