
#include "main.h"
#include "stm32f1xx_hal.h"


void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void quet(unsigned char x)
{
int i,temp;
for(i=0;i<8;i++)
{
temp=x;//gan bien
temp=temp&0x80;//lay ra bit dau tien (bit 7)
if(temp==0x80)//so sanh bit
HAL_GPIO_WritePin(DATA_7SEG_GPIO_Port,DATA_7SEG_Pin,1);  //bang 1 thi xuat vao chip =1
else
HAL_GPIO_WritePin(DATA_7SEG_GPIO_Port,DATA_7SEG_Pin,0);     //nguoc lai bang 0
x*=2;  //dich bit lay bit trong so thap

HAL_GPIO_WritePin(CLK_7SEG_GPIO_Port,CLK_7SEG_Pin,0); //tao xung tren chan 11
HAL_GPIO_WritePin(CLK_7SEG_GPIO_Port,CLK_7SEG_Pin,1);   //1 xung dua vào 1 bít
}

HAL_GPIO_WritePin(LAT_7SEG_GPIO_Port,LAT_7SEG_Pin,0);  //xuat du lieu ra output
HAL_GPIO_WritePin(LAT_7SEG_GPIO_Port,LAT_7SEG_Pin,1);
}


int main(void)
{
	unsigned int i, k=0;
  unsigned char ma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//ma led 7

  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();

 
  while (1)
  {
	HAL_GPIO_WritePin(GPIOC, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin,1);
  for(i=0;i<10;i++)
    {
     quet(ma[i]);
     HAL_Delay(1000);
    }

  }
 

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DATA_7SEG_Pin|CLK_7SEG_Pin|LAT_7SEG_Pin|SEG0_Pin 
                          |SEG1_Pin|SEG2_Pin|SEG3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : DATA_7SEG_Pin CLK_7SEG_Pin LAT_7SEG_Pin SEG0_Pin 
                           SEG1_Pin SEG2_Pin SEG3_Pin */
  GPIO_InitStruct.Pin = DATA_7SEG_Pin|CLK_7SEG_Pin|LAT_7SEG_Pin|SEG0_Pin 
                          |SEG1_Pin|SEG2_Pin|SEG3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
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
