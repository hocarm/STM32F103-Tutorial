/*
	 HUYNH NGOC THUONG
	 DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY
	 Last modified: 05/08/2018 - Version 2
	 **Describe: 
	 +RTC by module DS3231 with MCU:STM32F103C8T6
	 +In this project i had used: 
	 +External interrupt: Ex_IR to catch pulse from INT/SQW when alarm1 occur
	 +Comunicate protocol: I2C1 with Standard mode, clock speed: 100000Hz
	 +UART: UART1 for observation data from RTC - Baudrate: 9600
 *Facebook: ngocthuong0208 - huynhngocthuong0208@gmail.com - 01216911759
*/

#ifndef RTC_H_
#define RTC_H_
#include "stm32f1xx_hal.h"
#include <stdbool.h>

#define DS3231_ADDRESS              (0x68<<1)
#define DS3231_REG_TIME             (0x00)
#define DS3231_REG_ALARM_1          (0x07)
#define DS3231_REG_ALARM_2          (0x0B)
#define DS3231_REG_CONTROL          (0x0E)
#define DS3231_REG_STATUS           (0x0F)
#define DS3231_REG_TEMPERATURE      (0x11)

typedef __packed struct {
		uint8_t sec;
		uint8_t min;
		uint8_t hour;
		uint8_t day;
		uint8_t date;
		uint8_t month;
		uint8_t year;
		uint8_t I2C_Buffer[8];
		char nameofday[7][12];
}DS3231_t;

typedef struct{
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}DS3231AlarmTime;

typedef enum{
    DS3231_EVERY_SECOND   = 0x0F,
    DS3231_MATCH_S        = 0x0E,
    DS3231_MATCH_M_S      = 0x0C,
    DS3231_MATCH_H_M_S    = 0x08,
    DS3231_MATCH_DT_H_M_S = 0x00,
    DS3231_MATCH_DY_H_M_S = 0x10
} DS3231_alarm1_t;

typedef struct{
    uint8_t control;
    uint8_t status;
}DS3231Control;

uint8_t RTC_BCD2DEC(uint8_t c);
uint8_t RTC_DEC2BCD(uint8_t c);
void I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);
void I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);
uint8_t I2C_WriteByte(I2C_HandleTypeDef hi,uint8_t DEV_ADDR,uint8_t addr, uint8_t data);
uint8_t I2C_ReadByte(I2C_HandleTypeDef hi,uint8_t DEV_ADDR,uint8_t addr);


void RTC_GetTime(void);
void RTC_SetTime(uint8_t hour, uint8_t min, uint16_t sec, uint8_t date, uint8_t month, uint8_t year);

void RTC_SetAlarm1(uint8_t dydw, uint8_t hour, uint8_t minute, uint8_t second, DS3231_alarm1_t mode, bool armed);
void RTC_ArmedAlarm1(bool armed);
void RTC_ClearAlarm1(void);
DS3231AlarmTime RTC_GetAlarm1(void);
DS3231Control RTC_GetControl(void);

float RTC_readTemperature(void);

#endif /* RTC_H_ */
