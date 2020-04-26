#include "pms7003.h"
struct PMS7003_Data pms7003;
extern UART_HandleTypeDef huart2;
/**
  * @brief  Bat dau ngat nhan 1 ki tu
  * @param  handle : UART handle
  * @retval Khong
  */
void PMS7003_ReceiveStart_IT(UART_HandleTypeDef* handle){
	HAL_UART_Receive_IT(&huart2, pms7003.uartBuf, 1);
}
/**
  * @brief  Ngat nhan du lieu PMS7003
  * @param  handle : UART handle
  * @retval Khong
  */
void PMS7003_ReceiveData_IT(UART_HandleTypeDef* handle){
	//0x42 ki tu dau tien
	if (pms7003.uartBuf[0] == PMS_START_BYTE_1){ 
		pms7003.countDataToReceive = 31;
	// bat dau nhan du lieu PMS7003		
		HAL_UART_Receive_IT(handle, pms7003.uartBuf, 31);
		pms7003.state = PMS7003_RECEIVING;
	}
	if (pms7003.uartBuf[0] == PMS_START_BYTE_2 && pms7003.state == PMS7003_RECEIVING) {
			pms7003.frame = ((pms7003.uartBuf[1] << 8) + pms7003.uartBuf[2]);
			pms7003.pm1p0 = ((pms7003.uartBuf[3] << 8) + pms7003.uartBuf[4]);
			pms7003.pm2p5 = ((pms7003.uartBuf[5] << 8) + pms7003.uartBuf[6]);
			pms7003.pm10 = ((pms7003.uartBuf[7] << 8) + pms7003.uartBuf[8]);
			pms7003.pm1p0_ATM = ((pms7003.uartBuf[9] << 8) + pms7003.uartBuf[10]);
			pms7003.pm2p5_ATM = ((pms7003.uartBuf[11] << 8) + pms7003.uartBuf[12]);
			pms7003.pm10_ATM = ((pms7003.uartBuf[13] << 8) + pms7003.uartBuf[14]);
			pms7003.checksum = ((pms7003.uartBuf[29] << 8) + pms7003.uartBuf[30]);
			HAL_UART_Receive_IT(handle, pms7003.uartBuf,1);
			pms7003.state = PMS7003_RECEIVED;
		}
		else{ 
			HAL_UART_Receive_IT(handle, pms7003.uartBuf, 1);
		pms7003.state = PMS7003_CRC_ERROR;
		}
}
/**
  * @brief  Nhan du lieu PMS7003
  * @param  handle : UART handle
  * @retval Khong
  */
int PMS7003_ReceiveData(UART_HandleTypeDef* handle){
		HAL_UART_Receive(handle, pms7003.uartBuf, 1, 1000);
		if(pms7003.uartBuf[0] == PMS_START_BYTE_1){
		pms7003.countDataToReceive = 31;
		HAL_UART_Receive(handle, pms7003.uartBuf, pms7003.countDataToReceive, 1000);
		pms7003.state = PMS7003_RECEIVING;
	 }
		if(pms7003.uartBuf[0] == PMS_START_BYTE_2 && pms7003.state == PMS7003_RECEIVING){
			pms7003.frame = ((pms7003.uartBuf[1] << 8) + pms7003.uartBuf[2]);
			pms7003.pm1p0 = ((pms7003.uartBuf[3] << 8) + pms7003.uartBuf[4]);
			pms7003.pm2p5 = ((pms7003.uartBuf[5] << 8) + pms7003.uartBuf[6]);
			pms7003.pm10 = ((pms7003.uartBuf[7] << 8) + pms7003.uartBuf[8]);
			pms7003.pm1p0_ATM = ((pms7003.uartBuf[9] << 8) + pms7003.uartBuf[10]);
			pms7003.pm2p5_ATM = ((pms7003.uartBuf[11] << 8) + pms7003.uartBuf[12]);
			pms7003.pm10_ATM = ((pms7003.uartBuf[13] << 8) + pms7003.uartBuf[14]);
			pms7003.checksum = ((pms7003.uartBuf[29] << 8) + pms7003.uartBuf[30]);
			for(int i = 0; i < 31; i++){
				pms7003.uartBuf[i] = 0;
			}
		pms7003.state = PMS7003_RECEIVED;
		}
		else{ 
			pms7003.state = PMS7003_CRC_ERROR;
		}
		return pms7003.state;
}
