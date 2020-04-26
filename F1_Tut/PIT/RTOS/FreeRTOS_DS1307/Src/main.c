
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#define DS1307_ADD 0x68
struct DS1307_t{
	uint8_t receive_data[7];
	uint8_t send_data[7];
	uint8_t second, minute, hour, day, date, month, year;
	
};
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;

osThreadId defaultTaskHandle;
uint8_t BCD2DEC(uint8_t data);
uint8_t DEC2BCD(uint8_t data);

uint8_t BCD2DEC(uint8_t data){
	return (data<<4)*10 + (data&0x0f);
}
uint8_t DEC2BCD(uint8_t data){
	return (data/10)>>4|(data%10);
}
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
void StartDefaultTask(void const * argument);

struct DS1307_t ds1307;
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();

  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  osKernelStart();

  while (1)
  {
		
  }


}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }


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


  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);


  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
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

static void MX_DMA_Init(void) 
{
  __HAL_RCC_DMA1_CLK_ENABLE();

  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

static void MX_GPIO_Init(void)
{


  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

void StartDefaultTask(void const * argument)
{

  for(;;)
  {
   HAL_I2C_Mem_Read_DMA(&hi2c1,DS1307_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds1307.receive_data,7);
		osDelay(100);
  }

}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c->Instance == hi2c1.Instance){
		ds1307.second = BCD2DEC(ds1307.receive_data[0]);
		ds1307.minute = BCD2DEC(ds1307.receive_data[1]);
		ds1307.hour = BCD2DEC(ds1307.receive_data[2]);
		ds1307.day = BCD2DEC(ds1307.receive_data[3]);
		ds1307.date = BCD2DEC(ds1307.receive_data[4]);
		ds1307.month = BCD2DEC(ds1307.receive_data[5]);
		ds1307.year = BCD2DEC(ds1307.receive_data[6]);
		
	}
}
void DS1307_Set_data(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	ds1307.send_data[0] = DEC2BCD(second);
	ds1307.send_data[1] = DEC2BCD(minute);
	ds1307.send_data[2] = DEC2BCD(hour);
	ds1307.send_data[3] = DEC2BCD(day);
	ds1307.send_data[4] = DEC2BCD(date);
	ds1307.send_data[5] = DEC2BCD(month);
	ds1307.send_data[6] = DEC2BCD(year);
	HAL_I2C_Mem_Write_DMA(&hi2c1,DS1307_ADD<<1,0,I2C_MEMADD_SIZE_8BIT,ds1307.send_data,7);
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


