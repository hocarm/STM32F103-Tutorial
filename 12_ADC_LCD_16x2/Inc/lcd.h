/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/*
*************************************************************************************************************************************
*															INCLUDED FILES															*
*************************************************************************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"


/* LCD Control pins----------------------------------------------------- */
#define LCD_RS_GPIO_PORT            	GPIOB
#define LCD_RS_GPIO_CLK               	RCC_AHB1Periph_GPIOB
#define LCD_RS_GPIO_PIN               	GPIO_Pin_0

// #define LCD_RW_GPIO_PORT            	 GPIOC
// #define LCD_RW_GPIO_CLK               	RCC_APB2Periph_GPIOC // CONNET PIN RW TO GND
// #define LCD_RW_GPIO_PIN               	GPIO_Pin_10

#define LCD_EN_GPIO_PORT            	GPIOB
#define LCD_EN_GPIO_CLK               	RCC_AHB1Periph_GPIOB
#define LCD_EN_GPIO_PIN               	GPIO_Pin_1
//XXXXXXXXXXXXXXXXXXXXXXXX DATA D4..7
#define LCD_D4_GPIO_PORT            	GPIOC
#define LCD_D4_GPIO_CLK               	RCC_AHB1Periph_GPIOC
#define LCD_D4_GPIO_PIN               	GPIO_Pin_0

#define LCD_D5_GPIO_PORT            	GPIOC
#define LCD_D5_GPIO_CLK               	RCC_AHB1Periph_GPIOC
#define LCD_D5_GPIO_PIN               	GPIO_Pin_1

#define LCD_D6_GPIO_PORT            	GPIOC
#define LCD_D6_GPIO_CLK               	RCC_AHB1Periph_GPIOC
#define LCD_D6_GPIO_PIN               	GPIO_Pin_2

#define LCD_D7_GPIO_PORT            	GPIOC
#define LCD_D7_GPIO_CLK               	RCC_AHB1Periph_GPIOC
#define LCD_D7_GPIO_PIN               	GPIO_Pin_3

//XXXXXXXXXXXXXXXXXXXXXXXXX
#define LCD_RS_SET LCD_RS_GPIO_PORT->ODR|=LCD_RS_GPIO_PIN
#define LCD_RS_CLEAR LCD_RS_GPIO_PORT->ODR&=~LCD_RS_GPIO_PIN

#define LCD_EN_SET LCD_EN_GPIO_PORT->ODR|=LCD_EN_GPIO_PIN
#define LCD_EN_CLEAR LCD_EN_GPIO_PORT->ODR&=~LCD_EN_GPIO_PIN

#define LCD_D4_SET LCD_D4_GPIO_PORT->ODR|=LCD_D4_GPIO_PIN
#define LCD_D4_CLEAR LCD_D4_GPIO_PORT->ODR&=~LCD_D4_GPIO_PIN

#define LCD_D5_SET LCD_D5_GPIO_PORT->ODR|=LCD_D5_GPIO_PIN
#define LCD_D5_CLEAR LCD_D5_GPIO_PORT->ODR&=~LCD_D5_GPIO_PIN

#define LCD_D6_SET LCD_D6_GPIO_PORT->ODR|=LCD_D6_GPIO_PIN
#define LCD_D6_CLEAR LCD_D6_GPIO_PORT->ODR&=~LCD_D6_GPIO_PIN

#define LCD_D7_SET LCD_D7_GPIO_PORT->ODR|=LCD_D7_GPIO_PIN
#define LCD_D7_CLEAR LCD_D7_GPIO_PORT->ODR&=~LCD_D7_GPIO_PIN


/* LCD Data pins----------------------------------------------------- */
/* No need because of 4 bits mode b*/
#define LCD_D4                   			GPIO_Pin_0
#define LCD_D5                   			GPIO_Pin_1
#define LCD_D6                   			GPIO_Pin_2
#define LCD_D7                   			GPIO_Pin_3
#define LCD_DATA_GPIO_PINS         			(LCD_D4|LCD_D5|LCD_D6|LCD_D7)
#define LCD_DATA_GPIO_PORT 					GPIOE
#define LCD_DATA_GPIO_CLK					RCC_APB2Periph_GPIOE


/**
 * @brief LCD command for HD44780U
 */

/* LCD memory map */
#define LCD_LINE0_ADDR 				0x00 		// Start of line 0 in the DD-Ram
#define LCD_LINE1_ADDR 				0x40 		// Start of line 1 in the DD-Ram
#define LCD_LINE2_ADDR 			0x14 		// Only for LCD 20x4: start of line 2 in the DD-Ram
#define LCD_LINE3_ADDR 			0x54 		// Only for LCD 20x4: start of line 3 in the DD-Ram

/* LCD Commands */
#define LCD_DD_RAM_PTR 				0x80 		// Address Display Data RAM pointer
#define LCD_CG_RAM_PTR 				0x40 		// Address Character Generator RAM pointer
#define LCD_CLEAR_DISPLAY 			0x01 		// Clear entire display and set Display Data Address to 0
#define LCD_RETRN_HOME 				0x02 		// sets DDRAM address 0 and returns display from being shifted to original position.
#define LCD_DISP_INIT 				0x28 		// function set is 4 bit data length and 2 lines
#define LCD_INC_MODE 				0x06 		// Entry mode is display Data RAM pointer incremented after write
#define LCD_DISP_ON					0x0C		// Sets entire display on, cursor on and blinking of cursor position character
#define LCD_DISP_OFF				0x08   		// Sets entire display off, cursor off
#define LCD_CURSOR_ON				0x04		// turn on cursor
#define LCD_CURSOR_OFF				0x00    		// turn off cursor
#define LCD_CUR_MOV_LEFT			0x10		// Cursor move and shift to left
#define LCD_CUR_MOV_RIGHT			0x14		// Cursor move and shift to right
#define LCD_BUSY            		0x80      		// LCD is busy

/*
*************************************************************************************************************************************
*															PRIVATE TYPE	DEFINE														*
*************************************************************************************************************************************
*/
/* GPIO configuration mode */
typedef enum {
   	Input = 0,
   	Output
} GPIOConfig_Mode_TypeDef;

/*
*************************************************************************************************************************************
*															PRIVATE MACRO															*
*************************************************************************************************************************************
*/
#define SET_LCD_RS_Line()				GPIO_SetBits(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN)
#define CLR_LCD_RS_Line()				GPIO_ResetBits(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN)
#define SET_LCD_RW_Line()				GPIO_SetBits(LCD_RW_GPIO_PORT, LCD_RW_GPIO_PIN)
#define CLR_LCD_RW_Line()				GPIO_ResetBits(LCD_RW_GPIO_PORT, LCD_RW_GPIO_PIN)
#define SET_LCD_EN_Line()				GPIO_SetBits(LCD_EN_GPIO_PORT, LCD_EN_GPIO_PIN)
#define CLR_LCD_EN_Line()				GPIO_ResetBits(LCD_EN_GPIO_PORT, LCD_EN_GPIO_PIN)

/*
*************************************************************************************************************************************
*															PRIVATE VARIABLES														*
*************************************************************************************************************************************
*/


/*
*************************************************************************************************************************************
*															PRIVATE FUNCTION PROTOTYPES												*
*************************************************************************************************************************************
*/
// ****** Low-level functions ******
// the following functions are the only ones which deal with the CPU
// memory or port pins directly.  If you decide to use a fundamentally
// different hardware interface to your LCD, only these functions need
// to be changed, after which all the high-level functions will
// work again.
void lcd_data_line_write(u8 data);
//u8 lcd_data_line_read(void);
//void lcd_data_line_conf(GPIOConfig_Mode_TypeDef IO_mode);
// initializes I/O pins connected to LCD
void lcd_Init_HW(void);
// waits until LCD is not busy
//void lcd_Busy_Wait(void);
// writes a control command to the LCD
void lcd_Control_Write(u8 data);
// read the control status from the LCD
//u8 lcd_Control_Read(void);
// writes a data byte to the LCD screen at the current position
void lcd_Data_Write(u8 data);
// reads the data byte on the LCD screen at the current position
//u8 lcd_Data_Read(void);


 /*
*************************************************************************************************************************************
*							  						   		GLOBAL FUNCTION PROTOTYPES												*
*************************************************************************************************************************************
*/

// ****** High-levlel functions ******
// these functions provide the high-level control of the LCD
// such as clearing the display, setting cursor positions,
// displaying text and special characters

// initializes the LCD display (gets it ready for use)
void lcd_Init(void);
// moves the cursor/position to Home (upper left corner)
void lcd_Home(void);
// clears the LCD display
void lcd_Clear(void);
// moves the cursor/position to the row,col requested
// ** this may not be accurate for all displays
void lcd_Goto(u8 row, u8 col);
// prints a series of bytes/characters to the display
void lcd_Print_Data(char* data);

#ifdef __cplusplus
}
#endif


#endif /* __LCD_H */


