#include "RTC.h"
DS3231_t DS3231;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
/**
  * @brief  Binary code decimal to decimal
  * @param 	uint8_t c
  * @retval return value had changed
  */
uint8_t RTC_BCD2DEC(uint8_t c)
{
		return (c>>4)*10 + (c&0x0f);
}
/**
  * @brief  Decimal to binary code decimal
  * @param  uint8_t c
  * @retval return value had changed
  */
uint8_t RTC_DEC2BCD(uint8_t c)
{
	return (c/10)<<4|(c%10);
}
/**
  * @brief  Write buffer to register of DS3231
  * @param  I2C_HandleTypeDef hi 	I2C1 had used
	*					uint8_t DEV_ADDR			address DS3231
	*					uint8_t sizebuf				size of bufer
  * @retval None
  */
void I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Transmit(&hi, (uint16_t) DEV_ADDR, (uint8_t*) &DS3231.I2C_Buffer, (uint16_t) sizebuf, (uint32_t)1000)!=HAL_OK)
	{
			if(HAL_I2C_GetError(&hi)!=HAL_I2C_ERROR_AF)
			{
				printf("Buffer error\r\n");
			}
	}
}
/**
  * @brief  Read buffer to register of DS3231
  * @param  I2C_HandleTypeDef hi 	I2C1 had used
	*					uint8_t DEV_ADDR			address DS3231
	*					uint8_t sizebuf				size of bufer
  * @retval	None
  */
void I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Receive(&hi, (uint16_t) DEV_ADDR, (uint8_t*) &DS3231.I2C_Buffer, (uint16_t) sizebuf, (uint32_t)1000)!=HAL_OK)
	{
			if(HAL_I2C_GetError(&hi)!=HAL_I2C_ERROR_AF)
			{
				printf("Buffer error\r\n");
			}
	}
}
/**
  * @brief  Write byte to register of DS3231
  * @param  I2C_HandleTypeDef hi 	I2C1 had used
	*					uint8_t DEV_ADDR			address DS3231
	*					uint8_t addr					address register need to write data
	*					uint8_t data					data to write
	*					uint8_t sizebuf				size of bufer
  * @retval	HAL status
  */
uint8_t I2C_WriteByte(I2C_HandleTypeDef hi,uint8_t DEV_ADDR, uint8_t addr, uint8_t data)
{
	uint8_t buf[] = {addr, data};
  uint8_t d;
  while (HAL_I2C_GetState(&hi) != HAL_I2C_STATE_READY);
  d = HAL_I2C_Master_Transmit(&hi, (uint16_t) DEV_ADDR, buf, 2, (uint32_t) 10000);
  if ( d != HAL_OK) {
			printf("Byte error\r\n");
      return d;
  }
  return HAL_OK;
}
/**
  * @brief  Read byte to register of DS3231
  * @param  I2C_HandleTypeDef hi 	I2C1 had used
	*					uint8_t DEV_ADDR			address DS3231
	*					uint8_t addr					address register need to read data
  * @retval	HAL status
  */
uint8_t I2C_ReadByte(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t addr)
{
  uint8_t data = 0;
  uint8_t d;
  while (HAL_I2C_GetState(&hi) != HAL_I2C_STATE_READY);
  d = HAL_I2C_Master_Transmit(&hi, (uint16_t) DEV_ADDR, &addr, 1, (uint32_t) 10000);
  if ( d != HAL_OK) {
			printf("Byte error\r\n");
      return d;
  }
  while (HAL_I2C_GetState(&hi) != HAL_I2C_STATE_READY);
  d = HAL_I2C_Master_Receive(&hi, (uint16_t) DEV_ADDR, &data, 1, (uint32_t) 10000);
  if ( d != HAL_OK) {
      return d;
  }
  return data;
}
/**
  * @brief  Function get time current
  * @param  None
  * @retval None
  */
void RTC_GetTime(void){
	//Bat dau qua trinh nhan du lieu tu thanh ghi 0x00
	DS3231.I2C_Buffer[0]=0x00;
	I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,1);
	while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
	I2C_ReadBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,7);

	DS3231.day = RTC_BCD2DEC(DS3231.I2C_Buffer[3]);
	
	DS3231.date = RTC_BCD2DEC(DS3231.I2C_Buffer[4]);
	DS3231.month = RTC_BCD2DEC(DS3231.I2C_Buffer[5]);
	DS3231.year = RTC_BCD2DEC(DS3231.I2C_Buffer[6]);

	DS3231.sec = RTC_BCD2DEC(DS3231.I2C_Buffer[0]);
	DS3231.min = RTC_BCD2DEC(DS3231.I2C_Buffer[1]);
	DS3231.hour = RTC_BCD2DEC(DS3231.I2C_Buffer[2]);
}
/**
  * @brief  Function set time
  * @param  hour, min, sec, month, year to set
  * @retval None
  */
void RTC_SetTime(uint8_t hour, uint8_t min, uint16_t sec, uint8_t date, uint8_t month, uint8_t year){
	
   DS3231.I2C_Buffer[0] = 0x00;
   DS3231.I2C_Buffer[1] = RTC_DEC2BCD(sec);  
   DS3231.I2C_Buffer[2] = RTC_DEC2BCD(min); 
   DS3231.I2C_Buffer[3] = RTC_DEC2BCD(hour);
	
   DS3231.I2C_Buffer[5] = RTC_DEC2BCD(date);  
   DS3231.I2C_Buffer[6] = RTC_DEC2BCD(month); 
   DS3231.I2C_Buffer[7] = RTC_DEC2BCD(year);  

   I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,8);
   HAL_Delay(100);   
}
/**
  * @brief  Enable or disable alarm1 A1IE
  * @param  True or False
  * @retval None
  */
void RTC_ArmedAlarm1(bool armed){
	uint8_t value;
	value = RTC_BCD2DEC(I2C_ReadByte(hi2c1,(uint16_t) DS3231_ADDRESS, DS3231_REG_CONTROL));
	 if (armed)
    {
        value |= 0x01;
    } else
    {
        value &= 0xFE;
    }
	I2C_WriteByte(hi2c1,(uint16_t)DS3231_ADDRESS, DS3231_REG_CONTROL, RTC_DEC2BCD(value));
}
/**
  * @brief  Clear flag alarm1 A1F
  * @param  None
  * @retval None
  */
void RTC_ClearAlarm1(void){
		uint8_t value;
    value = RTC_BCD2DEC(I2C_ReadByte(hi2c1,(uint16_t) DS3231_ADDRESS, DS3231_REG_STATUS));
    value &= 0xFE;
    I2C_WriteByte(hi2c1,(uint16_t)DS3231_ADDRESS, DS3231_REG_STATUS, RTC_DEC2BCD(value));
}
/**
  * @brief  Function set time to alarm
  * @param  dayofweek, hour, minute, second, mode alarm, armed
  * @retval None
  */
void RTC_SetAlarm1(uint8_t dayofweek, uint8_t hour, uint8_t minute, uint8_t second, DS3231_alarm1_t mode, bool armed){

		second = RTC_DEC2BCD(second);
    minute = RTC_DEC2BCD(minute);
    hour = RTC_DEC2BCD(hour);
    dayofweek = RTC_DEC2BCD(dayofweek);
	 switch(mode)
    {
        case DS3231_EVERY_SECOND:
            second |= 0x80;
            minute |= 0x80;
            hour |= 0x80;
            dayofweek |= 0x80;
            break;

        case DS3231_MATCH_S:
            second &= 0x7F;
            minute |= 0x80;
            hour |= 0x80;
            dayofweek |= 0x80;
            break;

        case DS3231_MATCH_M_S:
            second &= 0x7F;
            minute &= 0x7F;
            hour |= 0x80;
            dayofweek |= 0x80;
            break;

        case DS3231_MATCH_H_M_S:
            second &= 0x7F;
            minute &= 0x7F;
            hour &= 0x7F;
            dayofweek |= 0x80;
            break;

        case DS3231_MATCH_DT_H_M_S:
            second &= 0x7F;
            minute &= 0x7F;
            hour &= 0x7F;
            dayofweek &= 0x7F;
            break;

        case DS3231_MATCH_DY_H_M_S:
            second &= 0x7F;
            minute &= 0x7F;
            hour &= 0x7F;
            dayofweek &= 0x7F;
            dayofweek |= 0x80;
            break;
    }
		DS3231.I2C_Buffer[0] = DS3231_REG_ALARM_1;
		DS3231.I2C_Buffer[1] = second;
		DS3231.I2C_Buffer[2] = minute;
		DS3231.I2C_Buffer[3] = hour;
		DS3231.I2C_Buffer[4] = dayofweek;
		I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,5);
		HAL_Delay(100);
		RTC_ArmedAlarm1(armed);
    RTC_ClearAlarm1();
}
/**
  * @brief  Function get time alarm1
  * @param 	None
  * @retval Struct alarm1
  */
DS3231AlarmTime RTC_GetAlarm1(void){
  DS3231AlarmTime alarm1;
	DS3231.I2C_Buffer[0]= DS3231_REG_ALARM_1;
	I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,1);
	while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
	I2C_ReadBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,4);
	alarm1.second = RTC_BCD2DEC(DS3231.I2C_Buffer[0]);
	alarm1.minute = RTC_BCD2DEC(DS3231.I2C_Buffer[1]);
	alarm1.hour = RTC_BCD2DEC(DS3231.I2C_Buffer[2]);
	alarm1.day = RTC_BCD2DEC(DS3231.I2C_Buffer[3]);
	printf("Hen gio: %d %d:%d:%d\r\n",alarm1.day,alarm1.hour,alarm1.minute,alarm1.second);
	return alarm1;
}
/**
  * @brief  Function get infor from control register
  * @param  None
  * @retval Struct check 
  */
DS3231Control RTC_GetControl(void){
	DS3231Control check;
	DS3231.I2C_Buffer[0]= DS3231_REG_CONTROL;
	I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,1);
	while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
	I2C_ReadBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,2);
	check.control = RTC_BCD2DEC(DS3231.I2C_Buffer[0]);
	check.status = RTC_BCD2DEC(DS3231.I2C_Buffer[1]);
	printf("Control:%d Status:%d\r\n", check.control, check.status);
	return check;
}
/**
  * @brief  Function read temperature
  * @param  None
  * @retval Tempertature
  */
float RTC_readTemperature(void){
	uint8_t msb, lsb;
	DS3231.I2C_Buffer[0]= DS3231_REG_TEMPERATURE;
	I2C_WriteBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,1);
	while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
	I2C_ReadBuffer(hi2c1,(uint16_t)DS3231_ADDRESS,2);
	msb = RTC_BCD2DEC(DS3231.I2C_Buffer[0]);
	lsb = RTC_BCD2DEC(DS3231.I2C_Buffer[1]);
	return ((((short)msb << 8) | (short)lsb) >> 6) / 4.0;
}