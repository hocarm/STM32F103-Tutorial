
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdio.h>
/* Define --------------------------------------------------------------------*/
#define true 1
#define false 0
#define bool int
bool retry = false;
char* PhoneNumber = "01216911759";
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/*__________________________________________________-*/
bool indexOf(char* String, char* Character);
void SIM_Send(char* cmd);
void SIM_sendCommand(char* cmd);
char* SIM_replyCommand(int delay);
void SIM_DeleteArray();
void SIM_begin();
//GPRS_Function
bool SIM_connectGPRS();
void SIM_disconnectGPRS();
void SIM_readserverResponse();
bool SIM_getValue();
void SIM_getContent();
//SMS_Function
void SIM_deleteMessage();
void SIM_sendSMS();
void SIM_smsFormat();
void SIM_checkAccount();

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE  
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return ch;
}
struct dataGPRS_t{
	char reply[100];
};
char SendSMS = 26;


struct dataGPRS_t dataGPRS;
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
	HAL_UART_Transmit(&huart2,(uint8_t *) cmd, i, 1000);
}
/* SIM Send AT Command*/
void SIM_sendCommand(char* cmd) {
  SIM_Send(cmd);
  SIM_Send("\r\n");
}
/* Sim Send Reply Command*/
char* SIM_replyCommand(int delay){
		HAL_UART_Receive(&huart2, (uint8_t *)dataGPRS.reply, 100, 1000);
		printf("%s\n",dataGPRS.reply);
		HAL_Delay(delay);
	return dataGPRS.reply;
}
/* Delete Array*/
void SIM_DeleteArray(){
/* _____________________________SIM_GPRS_________________________*/
	int length = strlen(dataGPRS.reply);
	for(int i = 0; i<length; i++){
		dataGPRS.reply[i] = 0;
	}
}
/* _____________________________SIM_GPRS_________________________*/
bool SIM_connectGPRS(){
	
	SIM_sendCommand("AT+SAPBR=1,1");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+SAPBR=2,1");
	if(!(indexOf(SIM_replyCommand(1000),"1,1"))) return false;
	SIM_DeleteArray();

	SIM_sendCommand("AT+HTTPINIT");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();

	SIM_sendCommand("AT+HTTPPARA=CID,1");
	if(indexOf(SIM_replyCommand(1000),"ERROR")) return false;
	SIM_DeleteArray();
	return true;
}

void SIM_disconnectGPRS(){
	SIM_sendCommand("AT+HTTPTERM");
	SIM_replyCommand(500);
	SIM_DeleteArray();
	SIM_sendCommand("AT+SAPBR=0,1");
	SIM_replyCommand(500);
	SIM_DeleteArray();
}

void SIM_readserverResponse(){
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(1000);
}


void SIM_getContent(char* _Parameter){
		/*______________GET_______________*/
	SIM_Send("AT+HTTPPARA=URL,http://www.vmig2016.16mb.com/get_location.php?raw_var=");
	SIM_sendCommand(_Parameter);
	SIM_replyCommand(500);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+HTTPACTION=0");
	SIM_replyCommand(5000);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+HTTPREAD");
	SIM_replyCommand(500);
	
	printf("-----------------RETRY (before HTTPACTION):  ");
	char* r = retry == true ? "true-----" : "false-----";
	printf("%s\n",r);
	
		 
	if(indexOf(dataGPRS.reply, "httpaction") || indexOf(dataGPRS.reply, "error")){
		printf("Retry later!\n");
    retry = true;
	};
	
//	
//	SIM_readserverResponse();
	/*______________POST_______________*/
//	SIM_sendCommand("AT+HTTPPARA=URL,http://posttestserver.com/post.php?dir=mattmiller22");
//	SIM_replyCommand(1000);
//	SIM_DeleteArray();
//	
//	SIM_sendCommand("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
//	SIM_replyCommand(1000);
//	SIM_DeleteArray();
//	
//	int i = strlen(_Parameter);
//	SIM_Send("AT+HTTPDATA=");
//	SIM_Send((char *)i);
//	SIM_sendCommand(",10000");
//	
//	SIM_sendCommand(_Parameter);
//	SIM_replyCommand(1000);
//	SIM_DeleteArray();
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
/* _____________________________SIM_SMS_________________________*/
void SIM_deleteMessage() {
  SIM_sendCommand("AT+CMGD=1,4"); //delete all message on SIM
  SIM_replyCommand(100);
	SIM_DeleteArray();
}
void SIM_smsFormat() {
  SIM_sendCommand("AT+CSCS=\"GSM\""); //Chon che do GSM
  SIM_replyCommand(100);
	SIM_DeleteArray();
  SIM_sendCommand("AT+CMGF=1");
  SIM_replyCommand(100);
	SIM_DeleteArray();
  SIM_sendCommand("ATE1");//debug respone
  SIM_replyCommand(100);
  SIM_DeleteArray();
}

void SIM_sendSMS(char* targetNumber, char* message){
	
	printf("|%s|\n|%s|", targetNumber, message);
//	SIM_Send("AT+CMGS=\"");
//	SIM_Send(targetNumber);
//	SIM_Send("\"\r\n");
	SIM_sendCommand("AT+CMGS=\"01216911759\"");
//	SIM_Send("AT+CMGS=\"");
//	SIM_Send(targetNumber);
//	SIM_Send("\"\r\n");
	HAL_Delay(500);
	SIM_sendCommand(message);
	HAL_Delay(300);
	HAL_UART_Transmit(&huart2,(uint8_t *)&SendSMS, 1, 1000);
	HAL_Delay(300);
	HAL_UART_Transmit(&huart2,(uint8_t *)&SendSMS, 1, 1000);
	
}
/*______________________________SIM_ACCOUNT____________________*/
void SIM_checkAccount(){
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
	
//	account = getUSSDMessage(data);
//  SIM_sendCommand("AT+CUSD=0");
//  SIM_buffer_flush();
//  delay(100);
}

/* _____________________________SIM_BEGIN________________________ */
void SIM_begin(){
	HAL_Delay(1000);
	do{
		SIM_sendCommand("AT+CREG?");	
	}while(!(indexOf(SIM_replyCommand(500),"0,1")));
	SIM_DeleteArray();
	//Turn off USSD
	SIM_sendCommand("AT+CUSD=0");
	SIM_replyCommand(100);
	SIM_DeleteArray();
	
	SIM_deleteMessage();
	
	SIM_sendCommand("AT&F0");
	SIM_replyCommand(100);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+CMEE=2");
	SIM_replyCommand(100);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+SAPBR=3,1,CONTYPE,GPRS");
	SIM_replyCommand(300);
	SIM_DeleteArray();
	
	SIM_sendCommand("AT+SAPBR=3,1,APN,internet");
	SIM_replyCommand(300);
	SIM_DeleteArray();
	
	SIM_smsFormat();
}



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
	
	SIM_disconnectGPRS();
	SIM_begin();
  SIM_sendSMS(PhoneNumber, "Thuongdeptrai");
//	if(SIM_connectGPRS()) {
//	printf("Dung\n");
//	//	SIM_getContent("1605.61665xNx10814.32328xE");
//	}
//	else printf("Sai\n");

	
  while (1)
  {
//	printf("Thuong\r");
//		HAL_Delay(1000);

  }


}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/* USART2 init function */
void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : Led1_Pin */
  GPIO_InitStruct.Pin = Led1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(Led1_GPIO_Port, &GPIO_InitStruct);

}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

