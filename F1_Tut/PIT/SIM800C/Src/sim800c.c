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
#include "sim800c.h"
//Cac bien de dung khai bao trong file sim800c.c con struct thi khai bao trong sim800c.h
//De su dung cac bien sim800c.c trong ham main.c thi them tu extern o truoc
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//---------------------------DEFINE------------------------------
#define timeout_1 100
#define timeout_5 500
#define timeout_50 5000
//---------------------------------------------------------------
bool retry = false;
char* PhoneNumber = "01216911759";
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
struct dataGPRS_t dataGPRS;
struct dataSMS_t dataSMS;
struct UARTSim_t UARTSim;
struct dataCALL_t dataCALL;
/**
  * @brief  Interrupt callback routine
	* @param  huart UART handle
	*            
	* @note
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  
{
	//Check UART of Module SIM
    if (huart->Instance == USART1){
			//Check character had received via UART3
			//If it isn't special character
	if (UARTSim.Rx_data[0] >= 32 && UARTSim.Rx_data[0] <= 126) {		
     UARTSim.Rx_temp[UARTSim.Rx_indx++] = UARTSim.Rx_data[0];
   }
		//If it's special character
		//Check variable flagSMS 
	 else{
		 //dataSMS.readSMS = 1
		if(UARTSim.Rx_data[0] == 13 && dataSMS.readSMS){
		UARTSim.Rx_temp[UARTSim.Rx_indx++] = UARTSim.Rx_data[0];
				//CALL
				if(strstr(UARTSim.Rx_temp,"RING")){
				printf("%s",UARTSim.Rx_temp);
				//SIM_sendCommand("ATH");
				SIM_Delete_Reply();
				dataSMS.count_Sc = 0;
				}
//				if(strstr(UARTSim.Rx_temp,"ATH\r\rOK\r")){
//				SIM_Delete_Reply();
//				dataSMS.count_Sc = 0;
//				}
				else{
				dataSMS.count_Sc++;
				if(dataSMS.count_Sc == 2){ 
				dataSMS.count_Sc = 0;
				//SMS
				//Coppy current buf to sms buf for processing
				for(int i = 0; i< strlen(UARTSim.Rx_temp); i++) dataSMS.sms_buffer[i] = UARTSim.Rx_temp[i];
				SIM_Delete_Reply();
				UARTSim.Rx_indx = 0;
				printf("%s\r\n",dataSMS.sms_buffer);
				//Coppy current buf to sms buf for processing	
			}
				}
		}
		//dataSMS.readSMS = 0
		//Response Command with OK
    if ((UARTSim.Rx_data[0] == 13 || UARTSim.Rx_data[0] == 10) && !dataSMS.readSMS){
				UARTSim.Rx_temp[UARTSim.Rx_indx++] = UARTSim.Rx_data[0];
	 
		}
	 }	
	  //Reponse Command without OK 
		if(UARTSim.Rx_Flagres == 0){	 
	 		if((indexOf(UARTSim.Rx_temp,"+FTPPUT: 1,61\r\n")||indexOf(UARTSim.Rx_temp,"+HTTPACTION: 0,200,9\r\n")) && !dataSMS.readSMS){
			for(int i = 0; i < strlen(UARTSim.Rx_temp); i++) dataGPRS.reply[i] = UARTSim.Rx_temp[i];	
			SIM_Delete_Reply();
			UARTSim.Rx_indx = 0;
			}
		}
			if(UARTSim.Rx_Flagres == 1){
			if((indexOf(UARTSim.Rx_temp, UARTSim.Response_ex)) && !dataSMS.readSMS){
			for(int i = 0; i < strlen(UARTSim.Rx_temp); i++) dataGPRS.reply[i] = UARTSim.Rx_temp[i];	
			SIM_Delete_Reply();
			UARTSim.Rx_Flagres = 0;
			UARTSim.Rx_indx = 0;
			}
		}
   HAL_UART_Receive_IT(&huart1,(uint8_t *)UARTSim.Rx_data, 1); 		
				}
   }
/**
  * @brief  Check character in string
	* @param  String: Current string
	*         Character: Character need to find into String       
	* @note
  * @retval status
  */
bool indexOf(char* String, char* Character){
	char *p = strstr(String, Character);
	if(p == NULL){
		return false;
	}
	else{
		return true;
	}
}
/**
  * @brief  sim send command
	* @param  cmd: command
	*               
	* @note
  * @retval status
  */
void SIM_Send(char* cmd){
	int i = strlen(cmd);
	HAL_UART_Transmit(&huart3,(uint8_t *) cmd, i, 100);
}
/**
  * @brief  sim send at command
	* @param  cmd: command
	*               
	* @note
  * @retval none
  */
void SIM_sendCommand(char* cmd) {
  SIM_Send(cmd);
  SIM_Send("\r\n");
}
/**
  * @brief  sim send at command
	* @param  cmd: command
	*               
	* @note
  * @retval none
  */
void SIM_sendCommandResponse(char* cmd, char* response_expected) {
  SIM_Send(cmd);
  SIM_Send("\r\n");
	strcpy(UARTSim.Response_ex, response_expected);
	UARTSim.Rx_Flagres = 1;
}
/**
  * @brief  sim send int
	* @param  cmd: command
	*               
	* @note
  * @retval none
  */
void SIM_Send_Int(unsigned long n){
	 unsigned char buffer[16];
   unsigned char i,j;
	 if(n == 0) {
    	HAL_UART_Transmit(&huart3,(uint8_t *)'0', 1, 1000);
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
/**
  * @brief  sim reply AT command response
	* @param  _timeout: time to get response
	*               
	* @note
  * @retval buf data Rx
  */
char* SIM_replyCommand(int _timeout){
	uint32_t t = HAL_GetTick();
	do{
		if(strstr(UARTSim.Rx_temp, "\r\nOK\r\n") ||strstr(UARTSim.Rx_temp, "OK\r\n") ||strstr(UARTSim.Rx_temp, "ERROR\r\n")||strstr(UARTSim.Rx_temp, "operation not allowed\r\n")){
			break;
		}
	}
	while(HAL_GetTick() - t < _timeout);
	printf("%s",UARTSim.Rx_temp);
	return UARTSim.Rx_temp;
}
/**
  * @brief  sim reply another AT command
	* @param  _timeout: time to get response
	*               
	* @note
  * @retval buf data Rx
  */
char* SIM_replyCommandResponse(int _timeout, char* expected_answer){
			uint32_t t = HAL_GetTick();
	do{
		if(strstr(dataGPRS.reply, expected_answer)){
			printf("---------------------------------------\r\n");
			break;
		}
	}
	while(HAL_GetTick() - t < _timeout);
	printf("%s",dataGPRS.reply);
	return dataGPRS.reply;
}
/**
  * @brief  sim reply SMS
	* @param  _timeout: time to get response
	*               
	* @note
  * @retval buf data Rx
  */
char* SIM_replySMSCommand(int _timeout){
	uint32_t t = HAL_GetTick();
	while(HAL_GetTick() - t < _timeout){};
	printf("%s",dataSMS.sms_buffer);
	return dataSMS.sms_buffer;
}
/**
  * @brief  delete array Rx_temp
	* @param  none
	*            
	* @note
  * @retval None
  */
void SIM_Delete_Reply(){
	int length = strlen(UARTSim.Rx_temp);
	for(int i = 0; i<length; i++){
		UARTSim.Rx_temp[i] = 0;
	}
	UARTSim.Rx_indx = 0;
}
/**
  * @brief  delete array Response_ex
	* @param  none
	*            
	* @note
  * @retval None
  */
void SIM_Delete_ResponseEx(){
	int length = strlen(UARTSim.Response_ex);
	for(int i = 0; i<length; i++){
		UARTSim.Response_ex[i] = 0;
	}
}
/**
  * @brief  delete array sim reply
	* @param  none
	*            
	* @note
  * @retval None
  */
void SIM_Delete_BufReply(){
	int length = strlen(dataGPRS.reply);
	for(int i = 0; i<length; i++){
		dataGPRS.reply[i] = 0;
	}
}
/**
  * @brief  delete array sim sms_buffer
	* @param  none
	*            
	* @note
  * @retval None
  */
void SIM_Delete_BufSMS(){
	int length = strlen(dataSMS.sms_buffer);
	for(int i = 0; i<length; i++){
		dataSMS.sms_buffer[i] = 0;
	}
}
/**
  * @brief  initial sim800c with at command
	* @param  none
	*            
	* @note
  * @retval None
  */
void SIM_begin(void){
	dataSMS.readSMS = 0;
	do{
		SIM_Delete_Reply();
		SIM_sendCommand("AT+CREG?");	
	}while(!(indexOf(SIM_replyCommand(timeout_50),"0,1")));
	SIM_Delete_Reply();
 //SIM available SleepMode1
	SIM_sendCommand("AT+CSCLK=0");SIM_replyCommand(timeout_5);SIM_Delete_Reply();
	//Turn off USSD
	SIM_sendCommand("AT+CUSD=0");SIM_replyCommand(timeout_5);SIM_Delete_Reply();
	SIM_sendCommand("AT&F0");SIM_replyCommand(timeout_5);SIM_Delete_Reply();
	SIM_sendCommand("AT+CMEE=2");SIM_replyCommand(timeout_5);SIM_Delete_Reply();
	//Set GSM
	SIM_sendCommand("AT+CSCS=\"GSM\"");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
	//Enable USSD
  SIM_sendCommand("AT+CMGF=1");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
	//Enable response command
  SIM_sendCommand("ATE1");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
	dataSMS.readSMS = 1;
}

/**
  * @brief  function connect gprs
	* @param  none
	*            
	* @note
  * @retval true or fall
  */
bool SIM_connectGPRS(){
	dataSMS.readSMS = 0;
	SIM_sendCommand("AT+CGATT=1");	
	if(indexOf(SIM_replyCommand(timeout_50),"ERROR")){ SIM_Delete_Reply(); return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");	
	if(indexOf(SIM_replyCommand(timeout_50),"ERROR")){ SIM_Delete_Reply(); return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+SAPBR=3,1,\"APN\",\"internet\"");	
	if(indexOf(SIM_replyCommand(timeout_50),"ERROR")) {SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+SAPBR=1,1");
	if(indexOf(SIM_replyCommand(timeout_50),"ERROR:")) {SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+SAPBR=2,1");
	if(indexOf(SIM_replyCommand(timeout_50),"ERROR")){ SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	dataSMS.readSMS = 1;
	return true;
}
/**
  * @brief  function initial HTTP to transfer data by GET protocol
	* @param  none
	*            
	* @note
  * @retval true or fall
  */
bool SIM_initHTTP(void){
	dataSMS.readSMS = 0;
	SIM_sendCommand("AT+HTTPINIT");
	if(indexOf(SIM_replyCommand(timeout_5),"ERROR")){ SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+HTTPPARA=CID,1");
	if(indexOf(SIM_replyCommand(timeout_5),"ERROR")){ SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	dataSMS.readSMS = 1;
	return true;
}
/**
  * @brief  function disconnect gprs
	* @param  none
	*            
	* @note
  * @retval true or fall
  */
bool SIM_disconnectGPRS(){
	dataSMS.readSMS = 0;
	SIM_sendCommand("AT+HTTPTERM");
  SIM_replyCommand(timeout_5);SIM_Delete_Reply();
	SIM_sendCommand("AT+SAPBR=0,1");
	if(indexOf(SIM_replyCommand(10000),"ERROR")){ SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	SIM_sendCommand("AT+CGATT=0");
	if(indexOf(SIM_replyCommand(10000),"ERROR")){ SIM_Delete_Reply();return false;}
	SIM_Delete_Reply();
	dataSMS.readSMS = 1;
	return true;
}
/**
  * @brief  function read server response after request by GET protocol
	* @param  none
	*            
	* @note
  * @retval none
  */
void SIM_readserverResponse(void){
	dataSMS.readSMS = 0;
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	dataSMS.readSMS = 1;
}
/**
  * @brief  function transfer data by GET protocol
	* @param  Location: 1603.61665xNx10814.32328xE
	*					date, month, year, hour, minute, second, pm1p0, pm2p5, pm10, so2, no2, co, baterry
	*            
	* @note
  * @retval none
  */
void SIM_getHTTP(char* _Parameter, uint8_t date, uint8_t month, uint8_t year, 
										uint8_t hour, uint8_t minute, uint8_t second, uint8_t pm1p0, 
										uint8_t pm2p5, uint8_t pm10, uint8_t so2, uint8_t no2, uint8_t co, uint8_t battery){
							
		/*______________GET_______________*/
	dataSMS.readSMS = 0 ;										
	SIM_Send("AT+HTTPPARA=URL,http://nckhbkdn.tapit.vn/Content/web2/get_location.php?raw_var=");
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
	SIM_Send("&co=");
	SIM_Send_Int(co);

	SIM_Send("&battery=");
	SIM_Send_Int(battery);
	SIM_Send("\r\n");
											
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	
	SIM_sendCommand("AT+HTTPACTION=0");
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	
	
	SIM_replyCommandResponse(timeout_50,"+HTTPACTION: 0,200,9\r\n");SIM_Delete_BufReply();
	
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	
	dataSMS.readSMS = 1 ;
	
}
/**
  * @brief  delete all message in sim800c
	* @param  
	*            
	* @note
  * @retval none
  */
void SIM_deleteMessage() {
	dataSMS.readSMS = 0;
	
  SIM_sendCommand("AT+CMGD=1,4"); //delete all message on SIM
  SIM_replyCommand(100);
	SIM_Delete_Reply();
	
	dataSMS.readSMS = 1;
}
/**
  * @brief  configure sms format 
	* @param  
	*            
	* @note
  * @retval none
  */
void SIM_smsFormat() {
	dataSMS.readSMS = 0;
	
  SIM_sendCommand("AT+CSCS=\"GSM\"");
  SIM_replyCommand(500);
  SIM_Delete_Reply();
	
  SIM_sendCommand("AT+CMGF=1");
  SIM_replyCommand(500);
  SIM_Delete_Reply();
	
  SIM_sendCommand("ATE1");//debug respone
  SIM_replyCommand(500);
	SIM_Delete_Reply();
	dataSMS.readSMS = 1;
}
/**
  * @brief  send SMS by sim800c 
	* @param  targetNumber: number to send sms
	*       	message     : content message
	* @note
  * @retval none
  */
void SIM_sendSMS(char* targetNumber, char* message){
	dataSMS.readSMS = 0;
	
	dataSMS.sendSMS = 0x1A;
	SIM_sendCommand("AT+CMGS=\"01216911759\"");
	SIM_replyCommand(1000);
	SIM_Delete_Reply();

	SIM_sendCommand(message);
	HAL_Delay(300);
	HAL_UART_Transmit(&huart3,(uint8_t *)&dataSMS.sendSMS, 1, 1000);
	SIM_replyCommand(5000);
	SIM_Delete_Reply();
	
	SIM_sendCommand("AT");
	SIM_replyCommand(1000);
	SIM_Delete_Reply();

	
	dataSMS.readSMS = 1;
	
}
/**
  * @brief  check account of sim by USSD *101#
	* @param  
	*       	
	* @note
  * @retval none
  */
void SIM_checkAccount(){
	dataSMS.readSMS = 0;
	printf("Check Account\n\r");

			SIM_sendCommand("AT+CMGF=1");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
			SIM_sendCommand("AT+CUSD=1");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
			SIM_sendCommand("AT+CSCS=\"GSM\"");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
			SIM_sendCommandResponse("AT+CUSD=1,\"*101#\"",", 15");SIM_replyCommand(timeout_1);SIM_Delete_Reply();
			if(indexOf(SIM_replyCommandResponse(10000,", 15"),"ERROR")) {
      printf("-----------> Reset Module SIM-----");
      SIM_sendCommand("AT+CFUN=1,1");
      SIM_begin();
    }		
			SIM_Delete_ResponseEx();
			SIM_Delete_BufReply();
			SIM_sendCommand("AT+CUSD=0");
		  SIM_replyCommand(timeout_1);
			SIM_Delete_Reply();
			dataSMS.readSMS = 1;
}
/**
  * @brief  get id new of message and read content of message
	* @param  
	*       	
	* @note
  * @retval none
  */
void SIM_GetSMS(void){
	
	   if(strstr(dataSMS.sms_buffer,"+CMTI: \"SM\"")){
			 dataSMS.token = strtok(dataSMS.sms_buffer,",");
       dataSMS.token = strtok(NULL,",");
			 dataSMS.val = atoi(dataSMS.token);
		   dataSMS.readSMS = 0;
			 SIM_Send("AT+CMGR=");
			 SIM_Send_Int(dataSMS.val);
			 SIM_Send("\r\n");
			 SIM_replyCommand(timeout_50);
			 SIM_Delete_Reply();
  		 dataSMS.readSMS = 1;
		 }
		 SIM_Delete_BufSMS();
	
}
/**
  * @brief  file transfer protocol to server
	* @param  
	*       	
	* @note
  * @retval none
  */
void SIM_SendFTP(void){
	dataSMS.readSMS = 0;
	SIM_sendCommand("AT+FTPCID=1");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPSERV=\"nckhbkdn.tapit.vn\"");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPUN=\"ngocthuong\"");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPPW=\"02081996\"");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPPUTNAME=\"999k.txt\"");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPPUTPATH=\"/public_html/\"");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	//Ham 1,1,1360
	SIM_sendCommandResponse("AT+FTPPUT=1", "+FTPPUT: 1,1,1360\r\n");
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	SIM_replyCommandResponse(timeout_50,"+FTPPUT: 1,1,1360\r\n");
	SIM_Delete_BufReply();
	SIM_Delete_ResponseEx();
	//Ham 2,10
	SIM_sendCommandResponse("AT+FTPPUT=2,10","+FTPPUT: 2,10\r\n");
  SIM_replyCommandResponse(timeout_50,"+FTPPUT: 2,10\r\n");
	SIM_Delete_BufReply();
	SIM_Delete_ResponseEx();

	//Ham goi aaa
	SIM_sendCommandResponse("aazzaaazz","+FTPPUT: 1,1,1360\r\n");
	SIM_replyCommand(timeout_50);
	SIM_Delete_Reply();
	SIM_replyCommandResponse(10000, "+FTPPUT: 1,1,1360\r\n");
	SIM_Delete_ResponseEx();
	SIM_Delete_BufReply();
	HAL_Delay(1000);
	SIM_Delete_Reply();
	SIM_sendCommand("AT+FTPPUT=2,0");SIM_replyCommand(timeout_50);SIM_Delete_Reply();
	SIM_replyCommandResponse(timeout_50,"+FTPPUT: 1,0\r\n");SIM_Delete_BufReply();
	dataSMS.readSMS = 1;
}
/**
  * @brief  finish process send file transfer protocol
	* @param  
	*       	
	* @note
  * @retval none
  */
void SIM_FinishFTP(void){
		dataSMS.readSMS = 0;
		SIM_sendCommand("AT+FTPQUIT");
		SIM_replyCommand(timeout_5);
		SIM_Delete_Reply();
		SIM_replyCommandResponse(timeout_50,"+FTPPUT: 1,61");
		SIM_Delete_BufReply();
		SIM_sendCommand("AT+CIPSHUT");
		SIM_replyCommand(timeout_50);
		SIM_Delete_Reply();
		dataSMS.readSMS = 1;
}
