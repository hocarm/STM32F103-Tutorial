
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pms7003.h"
uint8_t mode_Status = 0; //Mode 1: Nhan tin nhan  Mode 2: Che do GPRS  Mode 3: Thuc hien Goi khan cap
uint8_t alarm_hour= 0, alarm_minute = 0;
/*_______________DEFINE____________________*/
#define GPS_BUFFER_SIZE 100
#define GPS_VTG_SIZE 50
#define HEATER_ON_PIN_Pin GPIO_PIN_13
#define HEATER_ON_PIN_GPIO_Port GPIOC
#define DS3231_ADD 0x68
//_______________SIM_______________
#define true 1
#define false 0
#define bool int
bool retry = false;
char* PhoneNumber = "01216911759";
char readSMS=0;
char count = 0;
char flag_SMS = 0, flag_GPRS = 0;
char Rx_indx = 0, Rx_data[1] ,Rx_temp1[400];
char *token;
int val;
char SIM_Message[400];
char SIM_Latlng[50];
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

osThreadId myTask01Handle;
osThreadId myTask02Handle;

uint16_t ADC_Value[4];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
void StartTask01(void const * argument);
void StartTask02(void const * argument);
osSemaphoreId myBinarySem01Handle;

uint64_t lat, lng;
float velocity;

int Nmea_Line1 = 0;
int Nmea_Line2 = 1;
char ch;
//______________________________SIM_Struct___________________________
struct dataGPRS_t{
	char reply[400];
	char sms_buffer[100];
};
char SendSMS = 0x1A;

/*_______________________________GPS_Struct_____________________________________*/
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
	char Latitude[12];
	char S_N;
	char Longtitude[13];
	char E_W;
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

/*_______________________________DS3231_Struct_____________________________________*/
struct DS3231_DateTime{
	uint8_t receive_data[7];
	uint8_t send_data[7];
	uint8_t second, minute, hour, day, date, month, year;
};
/*________________________________Declaration_Struct________________________________*/
struct nmeaMessage_t 	nmeaMessage;
struct dataGps_t 			dataGps;
struct statusGps_t		statusGps;
PMS7003_HandleTypeDef pms7003;
struct DS3231_DateTime ds3231;
struct dataGPRS_t dataGPRS;


/*________________________________GPS_Prototype_________________________________*/
void Delete_Char(char s[], int pos);
int Search_Char(unsigned char Char, char *Str, unsigned char Time, int Len);
void CLEAR_GPS_RX_Buffer(void) ;
int GPS_GetGPRMC(void);
unsigned char GPS_DeviceInfo(char* time, char* status, char* latitude, char S_N, 
														 char* longitude, char E_W, char* speed, char* dir, char* date);
void Scan_for_dots(void);
void CLEAR_GPS_RX_Buffer(void);
/*______________________________DS3231_Prototype________________________________*/
uint8_t BCD2DEC(uint8_t data);
uint8_t DEC2BCD(uint8_t data);
void DS1307_Set_data(uint8_t second, uint8_t minute, uint8_t hour, 
										 uint8_t day, uint8_t date, uint8_t month, uint8_t year);
/*______________________________SIM800C_Prototype________________________________*/

bool indexOf(char* String, char* Character);
void SIM_Send(char* cmd);
void SIM_sendCommand(char* cmd);
void SIM_Send_Int(unsigned long n);
//-------------------------------------
char* SIM_replyCommand(int delay);
char* SIM_replySMSCommand(int delay);
///------------------------------------
void SIM_DeleteArray(void);
void SIM_DeleteArray1(void);
void SIM_DeleteSMS_Array(void);
//-------------------------------------
void SIM_begin(void);
//GPRS_Function
bool SIM_connectGPRS(void);
void SIM_disconnectGPRS(void);
void SIM_readserverResponse(void);
bool SIM_getValue(void);
void SIM_getContent1(char* _Parameter, uint8_t date, uint8_t month, uint8_t year, 
										uint8_t hour, uint8_t minute, uint8_t second, uint8_t pm1p0, 
										uint8_t pm2p5, uint8_t pm10, uint8_t so2, uint8_t no2, uint8_t co, uint8_t battery);
//SMS_Function
void SIM_deleteMessage(void);
void SIM_smsFormat(void);
void SIM_sendSMS(char* targetNumber, char* message);
void SIM_checkAccount(void);
void SIM_GetSMS(void);
/*______________________________PMS7003_Prototype________________________________*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void PMS7003_ReceiveStart(PMS7003_HandleTypeDef* handle);
static void PMS7003_Init(void);

/*________________________________DS3231_Function__________________________________*/
uint8_t BCD2DEC(uint8_t data){
	return (data>>4)*10 + (data&0x0f);
}
uint8_t DEC2BCD(uint8_t data){
	return (data/10)<<4|(data%10);
}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == hi2c1.Instance){
		ds3231.second = BCD2DEC(ds3231.receive_data[0]);
		ds3231.minute = BCD2DEC(ds3231.receive_data[1]);
		ds3231.hour = BCD2DEC(ds3231.receive_data[2]);
		ds3231.day = BCD2DEC(ds3231.receive_data[3]);
		ds3231.date = BCD2DEC(ds3231.receive_data[4]);
		ds3231.month = BCD2DEC(ds3231.receive_data[5]);
		ds3231.year = BCD2DEC(ds3231.receive_data[6]);
	}
}
void DS1307_Set_data(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	
	ds3231.send_data[0] = DEC2BCD(second);
	ds3231.send_data[1] = DEC2BCD(minute);
	ds3231.send_data[2] = DEC2BCD(hour);
	ds3231.send_data[3] = DEC2BCD(day);
	ds3231.send_data[4] = DEC2BCD(date);
	ds3231.send_data[5] = DEC2BCD(month);
	ds3231.send_data[6] = DEC2BCD(year);
	HAL_I2C_Mem_Write_IT(&hi2c1,DS3231_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds3231.send_data,7);
}

/*________________________________GPS_Function__________________________________*/
// Ham xoa ki tu trong chuoi
void Delete_Char(char s[], int pos)
{
	int n = strlen(s); 
	for(int i = pos + 1; i < n; i++)
	{
		s[i - 1] = s[i];
	}
	s[strlen(s) - 1] = '\0'; // Ki tu ket thuc
}
// Ham tim kiem ki tu trong chuoi
int Search_Char(unsigned char Char, char *Str, unsigned char Time, int Len)
{
    int   i=0;
    int  j=0;
    while((j<Time)&&(i<=Len))
    {
        if(Str[i] == Char)    j++;  
        i++;  
    }
    return i;
}
// Ham clear bo nho dem rx
void CLEAR_GPS_RX_Buffer() 
{
	for (int j=0; j<GPS_BUFFER_SIZE; j++)
	nmeaMessage.GPS_RX_Buffer[j] = 0; //clear Rx_Buffer before receiving new data
	for(int j=0; j< 10; j++)
	dataGps.Latitude[j] = 0;					//clear latitude buffer
	for(int j=0; j< 11; j++)
	dataGps.Longtitude[j] = 0;				//clear longtitude buffer
}
// Ham lay vi tri chuoi $GPRMC
int GPS_GetGPRMC()
{
	int k = 0;
	for(int k=0; k < (GPS_BUFFER_SIZE); k++)
	{
		if( (nmeaMessage.GPS_RX_Buffer[k] == 'M') && (nmeaMessage.GPS_RX_Buffer[k] == 'C') )
		{
			k = k - 5; // get the $
			return k;
		}
	}
	return k;
}
//Ham lay thong tin gps
unsigned char GPS_DeviceInfo(char* time, char* status, char* latitude, char S_N, char* longitude, char E_W, char* speed, char* dir, char* date)
{
  int i = 0;
	int k = 0;
	int Temp1, Temp2;
	
	Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,1,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 1
  // printf("%d\n",Temp1);
	Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,2,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 2
  // printf("%d\n",Temp2);
	if(nmeaMessage.GPS_RX_Buffer[Temp2] == 'V'){
		return 0;
	}
	else{
//-------------------------------------------------------------------------------------------------		
    //LAY VI DO:
		Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,3,GPS_BUFFER_SIZE);	 //Tim vi tri co ',' lan 3
		//printf("%d\n\r",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,5,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 4
	  //printf("%d\n\r",Temp2);
		
		//Tach chuoi vi do
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Latitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
		lat = atoi(dataGps.Latitude);
				if(dataGps.Latitude[11] == 'N') dataGps.S_N = 'N';
	 	else dataGps.E_W = 'S';
		dataGps.Latitude[10] = '\0';
		dataGps.Latitude[11] = '\0';
	
//-------------------------------------------------------------------------------------------------				
    //LAY KINH DO:
		Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,5,GPS_BUFFER_SIZE);	 //Tim vi tri co ',' lan 5
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,7,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 6
		//printf("%d\n",Temp2);
		
		k = 0;
		for(i = Temp1 ; i < Temp2-1; i++){
			dataGps.Longtitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
    lng = atoi(dataGps.Longtitude);
		if(dataGps.Longtitude[12] == 'E')  dataGps.E_W = 'E';
		else dataGps.E_W = 'W';	
//		Delete_Char(dataGps.Longtitude,11);
//		Delete_Char(dataGps.Longtitude,12);
		dataGps.Longtitude[11] = '\0';
    dataGps.Longtitude[12] = '\0';
//-------------------------------------------------------------------------------------------------			
		//LAY VAN TOC:
		Temp1 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,7,GPS_VTG_SIZE);	 //Tim vi tri co ',' lan 7
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,8,GPS_VTG_SIZE);	//Tim vi tri co ',' lan 8
	  //	printf("%d\n",Temp2);
		//Tach chuoi van toc
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Speed[k] = nmeaMessage.GPS_VTG_Buffer[i];
			k++;	
		}
    dataGps.Speed[i] = 0;
		velocity = atof(dataGps.Speed);
		
	return 1;	
	}
}
// Tim kiem dau , trong chuoi GPS
void Scan_for_dots(){
	uint8_t i = 0;
	while (i!=26){
		if (nmeaMessage.GPS_RX_Buffer[i] == ','){
			nmeaMessage.GPS_RX_Buffer[i] = 'y';
		}
		i++;
	}
}
/*________________________________Sim_Function__________________________________*/

/*Check character in string*/
bool indexOf(char* String, char* Character){
	char *p = strstr(String, Character);
	if(p == NULL){
		return false;
	}
	
	else{
		return true;
	}
}
/* Sim Send*/
void SIM_Send(char* cmd){
	int i = strlen(cmd);
	HAL_UART_Transmit(&huart3,(uint8_t *) cmd, i, 100);
}
/* SIM Send AT Command*/
void SIM_sendCommand(char* cmd) {
  SIM_Send(cmd);
  SIM_Send("\r\n");
}
void SIM_Send_Int(unsigned long n){
	 unsigned char buffer[16];
   unsigned char i,j;
	 if(n == 0) {
    	HAL_UART_Transmit(&huart2,(uint8_t *)'0', 1, 1000);
          return;
     }
	 for (i = 15; i > 0 && n > 0; i--) {
          buffer[i] = (n%10)+'0';
          n /= 10;
     }
	 for(j = i+1; j <= 15; j++) {
    	HAL_UART_Transmit(&huart3,(uint8_t *)&buffer[j], 1, 1000);
     }
}
/* Sim Send Reply Command*/
char* SIM_replyCommand(int delay){
	osDelay(delay);
	printf("%s",dataGPRS.reply);
  osDelay(delay);
	return dataGPRS.reply;
	
}
char* SIM_replyCommand1(int delay){
	HAL_Delay(delay);
	printf("%s",dataGPRS.reply);
	HAL_Delay(delay);
	return dataGPRS.reply;
	
}
char* SIM_replySMSCommand(int delay){
	 // osDelay(delay);
		printf("%s",dataGPRS.sms_buffer);
	return dataGPRS.sms_buffer;
}

/* Delete Array*/
void SIM_DeleteArray(){
/* _____________________________SIM_GPRS_________________________*/
	int length = strlen(dataGPRS.reply);
	for(int i = 0; i<length; i++){
		dataGPRS.reply[i] = 0;
	}
}

void SIM_DeleteArray1(){
/* _____________________________SIM_GPRS_________________________*/
	int length = strlen(Rx_temp1);
	for(int i = 0; i<length; i++){
		Rx_temp1[i] = 0;
	}
}
void SIM_DeleteSMS_Array(){
/* _____________________________SIM_GPRS_________________________*/
	int length = strlen(dataGPRS.sms_buffer);
	for(int i = 0; i<length; i++){
		dataGPRS.sms_buffer[i] = 0;
	}
}
/* _____________________________SIM_BEGIN________________________ */
void SIM_begin(){
	readSMS = 0;
	do{
		SIM_sendCommand("AT+CREG?");	
	}while(!(indexOf(SIM_replyCommand1(500),"0,1")));
	SIM_DeleteArray();	
	//Turn off USSD
	SIM_sendCommand("AT+CUSD=0");
	SIM_replyCommand1(500);
  SIM_DeleteArray();
	
	//SIM_deleteMessage();
	
	SIM_sendCommand("AT&F0");
	SIM_replyCommand1(500);
  SIM_DeleteArray();
	
	SIM_sendCommand("AT+CMEE=2");
	SIM_replyCommand1(500);

	SIM_DeleteArray();
	SIM_sendCommand("AT+SAPBR=3,1,CONTYPE,GPRS");
	SIM_replyCommand1(500);
  SIM_DeleteArray();
	
	SIM_sendCommand("AT+SAPBR=3,1,APN,internet");
	SIM_replyCommand1(500);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+CSCS=\"GSM\""); //Chon che do GSM
  SIM_replyCommand1(500);
  SIM_DeleteArray();
	
  SIM_sendCommand("AT+CMGF=1");
  SIM_replyCommand1(500);
  SIM_DeleteArray();
	
  SIM_sendCommand("ATE1");//debug respone
  SIM_replyCommand1(500);
	SIM_DeleteArray();
	

	readSMS = 1;
}

/* _____________________________SIM_GPRS_________________________*/
bool SIM_connectGPRS(){
	readSMS = 0;
	
		SIM_sendCommand("AT+SAPBR=1,1");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();
	
//		SIM_sendCommand("AT+SAPBR=2,1");
// if(!(indexOf(SIM_replyCommand(2000),"ERROR"))) return false;
//	SIM_DeleteArray();

	SIM_sendCommand("AT+HTTPINIT");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();
	


	
	SIM_sendCommand("AT+HTTPPARA=CID,1");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();


	

	
	readSMS = 1;
	return true;
}

void SIM_disconnectGPRS(){
	readSMS = 0;
	

	SIM_sendCommand("AT+HTTPTERM");
	SIM_replyCommand(1000);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+SAPBR=0,1");
	SIM_replyCommand(1000);
	SIM_DeleteArray();
	

	readSMS = 1;

}

void SIM_readserverResponse(){
	readSMS = 0;
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(1000);
	SIM_DeleteArray();
	readSMS = 1;
}

bool SIM_getValue(){
	printf("-------------------- -Start g----------------------\n");
  char check_connect = 0;
  while (!SIM_connectGPRS()) { 
     check_connect++;
     SIM_begin();
      if(check_connect==3){ 
		//	SIM_sendSMS(PhoneNumber, "SYNTAX ERROR! \n ID: \""+ (String)measuring_point_id+"\"\n Sim800 connect GPRS fail !! \n check your module:\n ");
			return false;
			}		
//	String date_of_value = (String)yearr+"-"+(String)mon +"-" +(String)dayy ;
//  Serial.println(date_of_value);
//  String hour_of_value = (String)hh1+":"+(String)mm1 +":" +(String)ss1;;
//  Serial.println(hour_of_value);
//  SIM_getContent( "action=index&measuring_point_id=" + (String)measuring_point_id + "&date="+ date_of_value + "&time="+ hour_of_value+ "&value1=" + (String)temp1 + "&value2=" + (String)temp2 + "&value3=" + (String)temp3 + "&account="+ account + "&battery="+(String)battery);
//  SIM_readserverResponse();
  SIM_disconnectGPRS();
  SIM_smsFormat();
  printf("-------------------- -Get finished---------------------- -");
return true;
			
}
}
void SIM_getContent1 (char* _Parameter, uint8_t date, uint8_t month, uint8_t year, 
										uint8_t hour, uint8_t minute, uint8_t second, uint8_t pm1p0, 
										uint8_t pm2p5, uint8_t pm10, uint8_t so2, uint8_t no2, uint8_t co, uint8_t battery){
							
		/*______________GET_______________*/
	readSMS = 0 ;										
	SIM_Send("AT+HTTPPARA=URL,http://www.vmig2016.16mb.com/get_location1.php?raw_var=");
	SIM_Send(_Parameter);
											
	SIM_Send("&date_time=");
	SIM_Send_Int(year);
	SIM_Send("-");
	SIM_Send_Int(month);
	SIM_Send("-");
  SIM_Send_Int(date);
	SIM_Send(" ");
	SIM_Send_Int(hour);
	SIM_Send(":");
	SIM_Send_Int(minute);
	SIM_Send(":");
	SIM_Send_Int(second);
  
	SIM_Send("&pms1p0=");
	SIM_Send_Int(pm1p0);
  SIM_Send("&pms2p5=");
	SIM_Send_Int(pm2p5);
	SIM_Send("&pms10=");
	SIM_Send_Int(pm10);
	
	SIM_Send("&so2=");
	SIM_Send_Int(so2);
	SIM_Send("&no2=");
	SIM_Send_Int(no2);
	SIM_Send("&co2=");
	SIM_Send_Int(co);

	SIM_Send("&battery=");
	SIM_Send_Int(battery);
	SIM_Send("\r\n");
											
	SIM_replyCommand(5000);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+HTTPACTION=0");
	SIM_replyCommand(5000);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(5000);
	SIM_DeleteArray();
	
	readSMS = 1 ;
	
}
/* _____________________________SIM_SMS_________________________*/
void SIM_deleteMessage() {
	readSMS = 0;
	
  SIM_sendCommand("AT+CMGD=1,4"); //delete all message on SIM
  SIM_replyCommand(100);
	SIM_DeleteArray();
	
	readSMS = 1;
}
void SIM_smsFormat() {
	readSMS = 0;
	
  SIM_sendCommand("AT+CSCS=\"GSM\""); //Chon che do GSM
  SIM_replyCommand(500);
  SIM_DeleteArray();
	
  SIM_sendCommand("AT+CMGF=1");
  SIM_replyCommand(500);
  SIM_DeleteArray();
	
  SIM_sendCommand("ATE1");//debug respone
  SIM_replyCommand(500);
	SIM_DeleteArray();
	readSMS = 1;
}

void SIM_sendSMS(char* targetNumber, char* message){
	readSMS = 0;
	
	SIM_sendCommand("AT+CMGS=\"01216911759\"");
	SIM_replyCommand(1000);
	SIM_DeleteArray();

	SIM_sendCommand(message);
	osDelay(300);
	HAL_UART_Transmit(&huart3,(uint8_t *)&SendSMS, 1, 500);
	SIM_replyCommand(5000);
	SIM_DeleteArray();
	
	readSMS = 1;
	
}
/*______________________________SIM_ACCOUNT____________________*/
void SIM_checkAccount(){
	readSMS = 0;
	printf("Check Account\n");
	do{
			SIM_sendCommand("AT+CUSD=1,\"*101#\"");

		  if(indexOf(SIM_replyCommand(300),"ERROR")) {
      printf("-------------------------> Reset Module SIM-----");
      //SIM_sendCommand("AT+CFUN=1,1"); //Reset luon;
      SIM_begin();
    }
			
	}while(!(indexOf(SIM_replyCommand(300),"+CUSD")));
	SIM_replyCommand(300);
	SIM_DeleteArray();
	SIM_sendCommand("AT+CUSD=0");
	readSMS = 1;
}


void SIM_GetSMS(){
	
	   if(strstr(dataGPRS.sms_buffer,"+CMTI: \"SM\"")|| strstr(dataGPRS.sms_buffer,"+CMTI: \"ME\"")){
			 token = strtok(dataGPRS.sms_buffer,",");
       token = strtok(NULL,",");
			 val = atoi(token);
			
				readSMS = 0;
			 SIM_Send("AT+CMGR=");
			 SIM_Send_Int(val);
			 SIM_Send("\r\n");
			// SIM_replyCommand(500);
			 if(indexOf(SIM_replyCommand(500), "GETDATA")){
			flag_SMS = 1;
    	flag_GPRS = 0;
			 }
		 SIM_DeleteArray();  
     readSMS = 1;			 
		 }
		 SIM_DeleteSMS_Array();
}
/*________________________________PMS7003_Function__________________________________*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART2){
 PMS7003_ReceiveUART(&pms7003);
	}
	if (huart->Instance == USART3)  //xem thu uart hien tai co phai la uart 1 khong
        {
			//Rx_temp1[Rx_indx1++] = Rx_data[0];
	if (Rx_data[0] >= 32 && Rx_data[0] <= 126) 
   {			
     Rx_temp1[Rx_indx++] = Rx_data[0];
   }
	 else{
			if(Rx_data[0] == 13 && readSMS){
		Rx_temp1[Rx_indx++] = Rx_data[0];
			count++;
			if(count == 2){
				count = 0;
//				flag_SMS=1;
//				flag_GPRS=0;
				for(int i =0; i< strlen(Rx_temp1); i++) dataGPRS.sms_buffer[i] = Rx_temp1[i];
				SIM_DeleteArray1();
				Rx_indx = 0;
				printf("%s",dataGPRS.sms_buffer);
			}
		}
    if ((Rx_data[0] == 13 || Rx_data[0] == 10) && !readSMS)
				Rx_temp1[Rx_indx++] = Rx_data[0];
	 }
	 		if((indexOf(Rx_temp1,"\r\nOK\r\n") || indexOf(Rx_temp1,"allowed") || indexOf(Rx_temp1,"0,200,5")) && !readSMS){
			for(int i =0; i< strlen(Rx_temp1); i++) dataGPRS.reply[i] = Rx_temp1[i];	
	  	SIM_DeleteArray1();
			Rx_indx = 0;
		}
   HAL_UART_Receive_IT(&huart3,(uint8_t *)Rx_data, 1); 		
				}
}
void PMS7003_ReceiveStart(PMS7003_HandleTypeDef* handle) {
	HAL_UART_Receive_IT(pms7003.uart, pms7003.uartBuf, pms7003.countDataToReceive);
}
static void PMS7003_Init(void){
	pms7003.uart = &huart2;
	pms7003.uartNumber = 2;
	pms7003.countDataToReceive = 1;
	pms7003.HEATER_gpioPin = GPIO_PIN_13;
	pms7003.HEATER_gpioPort = GPIOC;
}
/*_____________________________________________________________________________________________*/

int main(void)



{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
	PMS7003_Init();
	HAL_UART_Receive_IT(&huart3, (uint8_t*)&Rx_data, 1);
  SIM_begin();		
	osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);
	osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 128);
  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);
	osThreadDef(myTask02, StartTask02, osPriorityLow, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);
  osKernelStart();

  while (1)
  {

  }
}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 3;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 5, 0);
	
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

	
}


static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


void StartTask01(void const * argument)
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Value,4);
  PMS7003_ReceiveStart(&pms7003);
  HAL_UART_Receive_IT(&huart3,(uint8_t *)Rx_data, 1); 
  HAL_I2C_Mem_Read_DMA(&hi2c1,DS3231_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds3231.receive_data,7);\
	osDelay(100);
	alarm_hour = ds3231.hour;
	alarm_minute = ds3231.minute;
  for(;;)
  {	
			SIM_GetSMS();
		//Mode 1 : mode GPRS
		if(flag_GPRS){
				
		HAL_I2C_Mem_Read_DMA(&hi2c1,DS3231_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds3231.receive_data,7);
		if(alarm_hour == ds3231.hour){
			//Check thoi gian +5'
				if(ds3231.minute < (alarm_minute + 5) && ds3231.minute >= alarm_minute){
					alarm_minute += 5;			
	      	xSemaphoreGive( myBinarySem01Handle );
		    	osDelay(1000);
		    	xSemaphoreGive( myBinarySem01Handle );
		    	osDelay(1000);
					statusGps.GPS_ans_stt = GPS_DeviceInfo(dataGps.Time, dataGps.Status, dataGps.Latitude, dataGps.S_N, 
																  dataGps.Longtitude, dataGps.E_W, dataGps.Speed, dataGps.Dir, dataGps.Date);				
					sprintf(SIM_Latlng,"%sx%cx%sx%c",dataGps.Latitude, dataGps.S_N,dataGps.Longtitude, dataGps.E_W);
		    	//printf("%s\r\n", SIM_Latlng);	
					
					//Kiem tra gps nhan dung du lieu roi moi goi GPRS
					if(statusGps.GPS_ans_stt){
							SIM_connectGPRS();
							osDelay(1000);
						  SIM_getContent1(SIM_Latlng,ds3231.date,ds3231.month,ds3231.year,ds3231.hour,ds3231.minute,ds3231.second,
						  pms7003.pm1p0,pms7003.pm2p5,pms7003.pm10,ADC_Value[0],ADC_Value[1],ADC_Value[2],ADC_Value[3]);
						  osDelay(1000);
						  SIM_disconnectGPRS();
					}
				// Neu khong thi send tin nhan
					else{
						SIM_smsFormat();
						osDelay(1000);
						printf("Fail to connect GPRS!!!\r\n");
						//SIM_sendSMS("01216911759","Fail to connect GPRS!!!");
					}
				}
				//Check thoi gian tang gio +1	
				if( alarm_minute > 60){
					alarm_hour += 1;
					alarm_minute = alarm_minute - 60;
					if(alarm_hour == 24) alarm_hour = 0;
				}
		}
}
//End of flag_GPRS

//Mode 2 : Goi tin nhan 
				
		if(flag_SMS){
			HAL_I2C_Mem_Read_DMA(&hi2c1,DS3231_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds3231.receive_data,7);
		//	printf("%d %d %d \r\n",ds3231.day, ds3231.month, ds3231.year);
		//	printf("%d:%d:%d\r\n", ds3231.hour, ds3231.minute, ds3231.second);
		//	printf("PM1.0: %d PM2.5: %d PM10:  %d\r\n",pms7003.pm1p0, pms7003.pm2p5, pms7003.pm10);
		//	printf("ADC_Channel0: %d ADC_Channel0: %d ADC_Channel0: %d ADC_Channel0: %d\r\n",ADC_Value[0],ADC_Value[1],ADC_Value[2],ADC_Value[3]);
		
			xSemaphoreGive( myBinarySem01Handle );
			osDelay(1000);
			xSemaphoreGive( myBinarySem01Handle );
			osDelay(1000);
			
			statusGps.GPS_ans_stt = GPS_DeviceInfo(dataGps.Time, dataGps.Status, dataGps.Latitude, dataGps.S_N, 
																				 dataGps.Longtitude, dataGps.E_W, dataGps.Speed, dataGps.Dir, dataGps.Date);
//			
//			printf("%s %s %s\r\n",dataGps.Latitude,dataGps.Longtitude,dataGps.Speed);	
//			printf("%c %c \r\n",dataGps.S_N,dataGps.E_W);	
		sprintf(SIM_Message,"%d:%d:20%d %d:%d:%d\r\nLat:%s %c Lng:%s %c Vel:%s \r\nBattery:%d",ds3231.date,ds3231.month,ds3231.year, ds3231.hour, ds3231.minute, ds3231.second
			, dataGps.Latitude, dataGps.S_N, dataGps.Longtitude, dataGps.E_W, dataGps.Speed, ADC_Value[0]);
		//	sprintf(SIM_Message,"%d:%d:%d %d:%d:%d\r\nLat:%s  Lng:%s  Vel:%s S_N: %c E_W: %c\r\nBattery:%d ",ds3231.date,ds3231.month,ds3231.year, ds3231.hour, ds3231.minute, ds3231.second
		//	, dataGps.Latitude, dataGps.Longtitude, dataGps.Speed, dataGps.S_N, dataGps.E_W, ADC_Value[0]);
		// printf("%s\r\n",SIM_Message);
			if(statusGps.GPS_ans_stt)
	  SIM_sendSMS("01216911759",SIM_Message);
			osDelay(1000);
			flag_SMS = 0 ;
			flag_GPRS = 1;
		}
//End of flag_SMS		
		osDelay(100);
	} 
}


void StartTask02(void const * argument)
{
for(;;)
  {
		if(xSemaphoreTake(myBinarySem01Handle, ( TickType_t ) 0xFFFFFFFF )){
			while(1){
		   if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET){
				ch = (uint8_t)((&huart1)->Instance->DR & (uint8_t)0x00FF);
				 
			 if(Nmea_Line2 == 1){
	if (ch == '$'){
		nmeaMessage.GPS_SCounter = 1;
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = '$';
	}
	if (nmeaMessage.GPS_SCounter == 2){
		if (ch == 'G'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'G';
		}
	}
	if (nmeaMessage.GPS_SCounter == 3){
		if (ch == 'P'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'P';
		}
	}
	if (nmeaMessage.GPS_SCounter == 4){
		if (ch == 'V'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'V';
		nmeaMessage.GPS_SFlag++;
		}	
	}
	if (nmeaMessage.GPS_SCounter == 5){


		if (ch == 'T'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'T';
		nmeaMessage.GPS_SFlag++;	
		}
	}
	if (nmeaMessage.GPS_SCounter == 6){
		if (ch == 'G'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'G';
		nmeaMessage.GPS_SFlag++;
		}
	}
	if (ch == '*'){
		if (nmeaMessage.GPS_SFlag == 3){
		nmeaMessage.GPS_SFlag = 0;
		nmeaMessage.GPS_SCounter = 0;
		//printf("Xong1\r\n");
		Nmea_Line1 = 1;
		Nmea_Line2 = 0;
		break;
		}

	}
	if (0 < nmeaMessage.GPS_SCounter && nmeaMessage.GPS_SCounter < 50){
			if (nmeaMessage.GPS_SFlag == 3){
				nmeaMessage.GPS_SCounter_Tmp = nmeaMessage.GPS_SCounter-1;
				nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter_Tmp] = ch;
				nmeaMessage.GPS_SCounter++;
			}
			else {
				nmeaMessage.GPS_SCounter++;
		}
	}
}
		if(Nmea_Line1 == 1){
	if (ch == '$'){
		nmeaMessage.GPS_Counter = 1;
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = '$';
	}
	if (nmeaMessage.GPS_Counter == 2){
		if (ch == 'G'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'G';
		}
	}
	if (nmeaMessage.GPS_Counter == 3){
		if (ch == 'P'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'P';
		}
	}
	if (nmeaMessage.GPS_Counter == 4){
		if (ch == 'R'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'R';
		nmeaMessage.GPS_Flag++;
		}
	}
	if (nmeaMessage.GPS_Counter == 5){
		if (ch == 'M'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'M';
		nmeaMessage.GPS_Flag++;
			
		}
	}
	if (nmeaMessage.GPS_Counter == 6){
		if (ch == 'C'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'C';
		nmeaMessage.GPS_Flag++;
		}
	}
if (ch == '*'){
		if (nmeaMessage.GPS_Flag == 3){
			nmeaMessage.GPS_Flag = 0;
	    nmeaMessage.GPS_Counter = 0;
			//printf("Xong2\r\n");
			Nmea_Line1 = 0; 
			Nmea_Line2 = 1;
			break;
			}
	}

	if (0 < nmeaMessage.GPS_Counter && nmeaMessage.GPS_Counter < 100){
			if (nmeaMessage.GPS_Flag == 3){
				nmeaMessage.GPS_Counter_Tmp = nmeaMessage.GPS_Counter-1;
				nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter_Tmp] = ch;
				nmeaMessage.GPS_Counter++;
			}
			else {
				nmeaMessage.GPS_Counter++;
		}
	}
		
/*-------------------------------------------------------------------*/	
}		 		 
			}
    }
			
/*___________________________________________*/		
  }
	}
}

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	

PUTCHAR_PROTOTYPE  
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return ch;
}

void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

