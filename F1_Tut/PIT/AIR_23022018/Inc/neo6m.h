#ifndef _NEO6M_H_
#define _NEO6M_H_

#include "stm32f1xx_hal.h"

#define GPS_BUFFER_SIZE 100
#define GPS_VTG_SIZE 50
static uint32_t lat, lng;
static float velocity;
//Phan cau lenh
int Nmea_Line1 = 1;
int Nmea_Line2 = 0;
char ch;

/*______________Struct_GPS________________*/
struct nmeaMessage_t{
	//Raw Data GPS
	char GPS_RX_byte[2];
	char GPS_Transfer_cplt;
	char GPS_RX_Buffer[GPS_BUFFER_SIZE];
	char GPS_VTG_Buffer[GPS_VTG_SIZE];
	uint8_t GPS_Counter;
	uint8_t GPS_Counter_Tmp;
	uint8_t GPS_Flag;
	
	uint8_t GPS_SCounter;
	uint8_t GPS_SCounter_Tmp;
	uint8_t GPS_SFlag;

};
struct dataGps_t{
		//Data GPS
	char Time[20];
	char Status[2];
	char Latitude[9];
	char S_N[2];
	char Longtitude[10];
	char E_W[2];
	char Speed[20];
	char Dir[20];
	char Date[20];
};
struct statusGps_t{
	unsigned char GPS_ans_stt;
	unsigned char GPS_send_error;
	unsigned char GPS_receive_error;
};
struct point_t {
  double X;       // kinh do
  double Y;       // vi do
};

/*________________________________GPS_Prototype_________________________________*/
void Delete_Char(char s[], int pos);
int Search_Char(unsigned char Char, char *Str, unsigned char Time, int Len);
void CLEAR_GPS_RX_Buffer() ;
int GPS_GetGPRMC();
unsigned char GPS_DeviceInfo(char* time, char* status, char* latitude, char* S_N, 
														 char* longitude, char* E_W, char* speed, char* dir, char* date);
void Scan_for_dots();
void CLEAR_GPS_RX_Buffer(void);
void Processing_$GPGRMC(void);
void Processing_$GPGVTG(void);
void GPS_USART_RX_ISR();

#endif /* _NEO6M_H_ */
