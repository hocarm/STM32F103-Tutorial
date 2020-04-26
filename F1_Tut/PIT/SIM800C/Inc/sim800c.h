/*
	 HUYNH NGOC THUONG
	 DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY
	 Last modified: 15/05/2018 - Version 2
	 **Describe: 
	 +SIM800c with AT command and STM32F103C8T6
	 +In this project i had used: 
	 +Comunicate protocol: UART to transfer data from mcu to sim800c
	 +										 UART to receive response from sim800c to mcu
	 +Keilc 5 Debug: observation data. 
 *Facebook: ngocthuong0208 - huynhngocthuong0208@gmail.com - 01216911759
*/
#ifndef _SIM800C_H_
#define _SIM800C_H_

#include "stm32f1xx_hal.h"
/* Define --------------------------------------------------------------------*/
#define true 1
#define false 0
#define bool int
//--------------------------------------------
struct UARTSim_t{
	char Rx_temp[400];
	char Rx_indx;
	char Rx_data[1];
	char Response_ex[128];
	uint8_t Rx_Flagres;
};
struct dataGPRS_t{
	char reply[256];
};
struct dataCALL_t{
	char call_buffer[128];
};
struct dataSMS_t{
	char sms_buffer[128];
	char ussd[256];
	int  count_Sc;	//Count special char
	char readSMS;
	char sendSMS;		//Last character send SMS
	char *token;
	int val;				//Position of messeage
};
//--------------------------------------------
bool indexOf(char* String, char* Character);
void SIM_Send(char* cmd);
void SIM_sendCommand(char* cmd);
void SIM_sendCommandResponse(char* cmd, char* response_expected);
void SIM_Send_Int(unsigned long n);
//-------------------------------------
char* SIM_replyCommand(int _timeout);
char* SIM_replySMSCommand(int delay);
void SIM_sendCommandResponse(char* cmd, char* response_expected);
///------------------------------------
void SIM_Delete_Reply(void);
void SIM_Delete_BufReply(void);
void SIM_Delete_BufSMS(void);
void SIM_Delete_ResponseEx(void);
//-------------------------------------
void SIM_begin(void);
bool SIM_connectGPRS(void);
bool SIM_disconnectGPRS(void);
bool SIM_initHTTP(void);
void SIM_readserverResponse(void);
void SIM_getHTTP(char* _Parameter, uint8_t date, uint8_t month, uint8_t year, 
										uint8_t hour, uint8_t minute, uint8_t second, uint8_t pm1p0, 
										uint8_t pm2p5, uint8_t pm10, uint8_t so2, uint8_t no2, uint8_t co, uint8_t battery);
//SMS_Function
void SIM_deleteMessage(void);
void SIM_smsFormat(void);
void SIM_sendSMS(char* targetNumber, char* message);
void SIM_checkAccount(void);
void SIM_GetSMS(void);
void SIM_SendFTP(void);
void SIM_FinishFTP(void);
#endif /* _NEO6M_H_ */
