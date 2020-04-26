

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "PMS7003/pms7003.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define GPS_BUFFER_SIZE 200
#define GPS_VTG_SIZE 50
#define HEATER_ON_PIN_Pin GPIO_Pin_13
#define HEATER_ON_PIN_GPIO_Port GPIOC

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

osThreadId myTask01Handle;
osThreadId myTask02Handle;

PMS7003_HandleTypeDef pms7003;
uint8_t DataToSend[40]; 

/* Private function prototypes -----------------------------------------------*/
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

/*PMS7003*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
 PMS7003_ReceiveUART(&pms7003);
}
static void PMS7003_Init(void){
	printf("""");
	pms7003.uart = &huart2;
	pms7003.uartNumber = 2;
	pms7003.countDataToReceive = 1;
	pms7003.HEATER_gpioPin = GPIO_PIN_13;
	pms7003.HEATER_gpioPort = GPIOC;
//	pms7003.PMS_gpioPin = PMS_ON_PIN_Pin;
//	pms7003.PMS_gpioPort = PMS_ON_PIN_GPIO_Port;
}
/*_____________FreeRTOS_Queue___________________*/
osMessageQDef(Longtitude, 16, int); 
osMessageQId Longtitude;

osMessageQDef(Latitude, 16, int); 
osMessageQId Latitude;
/*Bien tach chuoi*/
int Tlat,Tlng,Tvelocity;
int Tlat1,Tlng1,Tvelocity1;
//------------
uint32_t lat, lng, velocity;

int Nmea_Line1 = 1;
int Nmea_Line2 = 0;
char ch;
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
//Struct
struct nmeaMessage_t 	nmeaMessage;
struct dataGps_t 			dataGps;
struct statusGps_t		statusGps;
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
unsigned char GPS_DeviceInfo(char* time, char* status, char* latitude, char* S_N, char* longitude, char* E_W, char* speed, char* dir, char* date)
{
  int i = 0;
	int k = 0;
	int Temp1, Temp2;
	Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,1,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 2
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
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,4,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 4
	  //	printf("%d\n",Temp2);
		//Tach chuoi vi do
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Latitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
    dataGps.Latitude[i] = 0;
		
		Delete_Char(dataGps.Latitude,4);	
		lat = atoi(dataGps.Latitude);
//-------------------------------------------------------------------------------------------------				
    //LAY KINH DO:
		Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,5,GPS_BUFFER_SIZE);	 //Tim vi tri co ',' lan 5
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,6,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 6
		//printf("%d\n",Temp2);
		k = 0;
		for(i = Temp1 ; i < Temp2-1; i++){
			dataGps.Longtitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
		dataGps.Longtitude[i] = 0;
		
		Delete_Char(dataGps.Longtitude,5);
    lng = atoi(dataGps.Longtitude);
//-------------------------------------------------------------------------------------------------			
		//LAY VAN TOC:
		Temp1 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,7,GPS_VTG_SIZE);	 //Tim vi tri co ',' lan 3
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,8,GPS_VTG_SIZE);	//Tim vi tri co ',' lan 4
	  //	printf("%d\n",Temp2);
		//Tach chuoi van toc
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Speed[k] = nmeaMessage.GPS_VTG_Buffer[i];
			k++;	
		}
    dataGps.Speed[i] = 0;
		velocity = atoi(dataGps.Speed);
		
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
/*_____________________________________________________________________________________________*/

void Processing_$GPGRMC(){
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
			statusGps.GPS_ans_stt = GPS_DeviceInfo(dataGps.Time, dataGps.Status, dataGps.Latitude, dataGps.S_N, 
																				 dataGps.Longtitude, dataGps.E_W, dataGps.Speed, dataGps.Dir, dataGps.Date);
			if(statusGps.GPS_ans_stt){
				//printf("Kinh do string: %s\n", dataGps.Latitude);
				//printf("Vi do string: %s\n", dataGps.Longtitude);
				//printf("Toc do: %s\n",dataGps.Speed);
				osMessagePut(Longtitude, lng, osWaitForever);
				osMessagePut(Latitude,lat, osWaitForever);
				osDelay(100);
			}
			//printf("%s\n", nmeaMessage.GPS_RX_Buffer);
			Nmea_Line1 = 0; 
			Nmea_Line2 = 1;
			}
		nmeaMessage.GPS_Flag = 0;
		nmeaMessage.GPS_Counter = 0;
	}

	if (0 < nmeaMessage.GPS_Counter && nmeaMessage.GPS_Counter < 200){
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


void Processing_$GPVTG(){
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
			//printf("%s\n", nmeaMessage.GPS_VTG_Buffer);
			Nmea_Line1 = 1;
			Nmea_Line2 = 0;
		}
		nmeaMessage.GPS_SFlag = 0;
		nmeaMessage.GPS_SCounter = 0;
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
	}
	//Ham ngat Uart1 de nhan gia tri GPS
void GPS_USART_RX_ISR(){
	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET){
		ch = (uint8_t)((&huart1)->Instance->DR & (uint8_t)0x00FF);
		Processing_$GPGRMC();
	  Processing_$GPVTG();
	}
}
int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  /* Create the thread(s) */
  /* definition and creation of myTask01 */
	PMS7003_Init();
	//PMS7003_off(&pms7003);
	//PMS7003_ReceiveStart(&pms7003);
	//HAL_UART_Receive_IT(pms7003.uart, pms7003.uartBuf, pms7003.countDataToReceive);
  osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 128);
  myTask01Handle = osThreadCreate(osThread(myTask01), &myTask01Handle);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), &myTask02Handle);
	
	Longtitude = osMessageCreate(osMessageQ(Longtitude), NULL);
	
	Latitude = osMessageCreate(osMessageQ(Latitude), NULL);
  /* Start scheduler */
  osKernelStart();
  
  while (1)
  {
  }


}

/** System Clock Configuration
*/
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

/* ADC1 init function */
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
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
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

/* USART1 init function */
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

/* USART2 init function */
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

/* USART3 init function */
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

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
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

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}


/* StartTask01 function */
void StartTask01(void const * argument)
{
	
  for(;;)
  {
   	GPS_USART_RX_ISR();
  }

}

/* StartTask02 function */
void StartTask02(void const * argument)
{
 
  double F_lng, F_lat;
	osEvent evt;
	osEvent evt1;
	HAL_UART_Receive_IT(pms7003.uart, pms7003.uartBuf, pms7003.countDataToReceive);
  for(;;)
  {
	evt = osMessageGet(Longtitude, 10);
	if(evt.status == osEventMessage){
		lng = evt.value.v;
		F_lng = 1.0*lng;
	  F_lng /= 100000;
		//printf("Nhan duoc kinh do:%d\n",lng);
	  printf("Nhan duoc la: %f\r\n",F_lng);
		}

		evt1 = osMessageGet(Latitude, 10);
	if(evt1.status == osEventMessage){
		lat = evt1.value.v;
		F_lat = 1.0*lat;
	  F_lat /= 100000;
		//printf("Nhan duoc vi do: %d\n",lat);
		printf("Nhan duoc la: %f\r\n",F_lat);
		printf("PM1.0: %d ",pms7003.pm1p0);
		printf("PM2.5: %d ",pms7003.pm2p5);
		printf("PM10: %d\r\n",pms7003.pm10);
		}
	
	
		osDelay(1000);
  }
	//osThreadTerminate(NULL);
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

  while(1) 
  {
  }

}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
