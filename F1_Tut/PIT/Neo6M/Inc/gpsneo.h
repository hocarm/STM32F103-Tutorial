/*
	 HUYNH NGOC THUONG
	 DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY
	 Last modified: 1/05/2018 - Version 2
	 **Describe: 
	 +SDcard by module SD and STM32F103C8T6
	 +In this project i had used: 
	 +Thirt party: FreeRTOS
	 +Thirt party: FATFS
	 +Comunicate protocol: UART1 - Rx for receive data from GPS Neo-Ulbox
												 UART2 - Tx for transfer data from MCU to PC for observation
 *Facebook: ngocthuong0208 - huynhngocthuong0208@gmail.com - 01216911759
*/
#ifndef _GPSNEO_H_
#define _GPSNEO_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//------------------------------------Define-----------------------------------//
//-----------------------------------------------------------------------------//
#define GPS_BUFFER_SIZE 200
//------------------------------------Struct-----------------------------------//
//-----------------------------------------------------------------------------//
struct nmeaMessage_t{
	//Raw Data GPS
	char GPS_RX_Buffer[GPS_BUFFER_SIZE];
	uint8_t GPS_Counter;
	uint8_t GPS_Counter_Tmp;
	uint8_t GPS_Flag;
};
struct dataGps_t{
		//Data GPS
	char Status[2];
	char Time[20];
	char Latitude[10];
	char S_N[2];
	char Longtitude[11];
	char E_W[2];
	char Speed[20];
	char Date[20];
	float Velocity;
};
struct statusGps_t{
	unsigned char GPS_ans_stt;
	unsigned char GPS_send_error;
	unsigned char GPS_receive_error;
};
/*________________________________GPS_Prototype_________________________________*/
 /*____________________________________________________________________________*/
unsigned char GPS_Data(char* time, char* status, char* latitude, char* S_N, 
														 char* longitude, char* E_W, char* speed, char* date);
void GPS_ClearData(void);
void GPS_ClearRxBuffer(void);
int  GPS_SearchChar(unsigned char Char, char *Str, unsigned char Time, int Len);
void GPS_DeleteChar(char s[], int pos);
void GPS_RawData(void);
void GPS_Knot2Kmh(char * knot, float * km_h);
#endif /* _GPSNEO_H_ */