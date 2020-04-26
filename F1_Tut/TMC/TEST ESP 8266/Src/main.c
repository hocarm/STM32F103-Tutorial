
#include "main.h"
#include "stm32f1xx_hal.h"

unsigned char ssid[] = "KyThuatTuhu";
unsigned char pass[] = "mualinhkien.vn";
unsigned char  add_wifi[50];
int i; //Khai bao bien dem
char buffer[100]; //Khai bao mang buffer 100 phan tu
int len; //Khai bao bien len tuong ung voi chieu dai
char Rx_indx, Rx_Buffer[100], Transfer_cplt; //Khai bao cac bien de nhan du lieu
uint8_t Rx_data[2];
uint8_t ESP8266_AT[]="AT\r\n";
uint8_t ESP8266_RST[]="AT+RST\r\n";
uint8_t ESP8266_MODE[]="AT+CWMODE =\"2\"\r\n";

uint8_t REP_OK[]="OK\r\n";
uint8_t REP_ADD_WIFI[]="WIFI CONNECTED\r\n";
uint8_t ADD_WIFI[]="AT+CWJAP=\"KyThuatTuhu\",\"mualinhkien.vn\"\r\n";
uint8_t REP_OK_COUNT=0;
uint8_t flag_rep_ok=0;
uint8_t REP_ADD_WIFI_COUNT=0;
uint8_t flag_rep_add_wifi=0;



UART_HandleTypeDef huart2;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t i;
	if (huart->Instance == USART2)	//UART hien tai la uart2
		{
		if (Rx_indx==0) {for (i=0;i<100;i++) Rx_Buffer[i]=0;}	//xoa Rx_Buffer truoc khi nhan du lieu	
		
		if (Rx_data[0]!=13)	//Neu du lieu nhan duoc khac voi 13 (13 la ma cua phim enter)
			{
			Rx_Buffer[Rx_indx++]=Rx_data[0];	//them du lieu vao Rx_Buffer
			}
		else			//Neu phim enter duoc an
			{
			Rx_indx=0;	//Dua index ve 0
			Transfer_cplt=1;//Qua trinh truyen hoan tat, du lieu da san sang de doc
			}
	  if(Rx_data[0] == REP_OK[REP_OK_COUNT])
			{
				REP_OK_COUNT++;
				if(REP_OK_COUNT==4)
					  {
						flag_rep_ok=1;
						REP_OK_COUNT=0;
						}
				else
					  {
							flag_rep_ok=0;
						}
			 }
			
			if(Rx_data[0]== REP_ADD_WIFI[REP_ADD_WIFI_COUNT])
				{
					REP_ADD_WIFI_COUNT++;
					if(REP_ADD_WIFI_COUNT==sizeof(REP_ADD_WIFI))
						{
							REP_ADD_WIFI_COUNT=0;
							flag_rep_add_wifi=1;
						}
					else
						{
							flag_rep_add_wifi=0;
						}
				}
			
		

		HAL_UART_Receive_IT(&huart2, Rx_data, 1);	//Kich hoat UART nhan du lieu ngat moi luc
		}

}



int main(void)
{


  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();
  MX_USART2_UART_Init();
  HAL_UART_Receive_IT(&huart2, Rx_data, 1);
  HAL_UART_Transmit(&huart2,ESP8266_RST,sizeof(ESP8266_RST),1000);
  while (1)
  {
	if(flag_rep_ok==0)
	{
	HAL_UART_Transmit(&huart2,ESP8266_MODE,sizeof(ESP8266_MODE),1000);
	HAL_Delay(50);
	if(flag_rep_ok==1)
	{
	flag_rep_ok=0;
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart2,ADD_WIFI,sizeof(ADD_WIFI),1000);
  //sprintf(add_wifi,"AT+CWJAP = \"%s\",\"%s\"\r\n",ssid,pass);
	//HAL_UART_Transmit(&huart2,add_wifi,sizeof(add_wifi),1000);
	Transfer_cplt =0;
	
	}
	}


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RS_Pin|RW_Pin|EN_Pin|D4_Pin 
                          |D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin RW_Pin EN_Pin D4_Pin 
                           D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|EN_Pin|D4_Pin 
                          |D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
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

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
