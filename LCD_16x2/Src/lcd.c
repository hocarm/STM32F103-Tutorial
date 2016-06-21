/*
*************************************************************************************************************************************
*															INCLUDED FILES															*
*************************************************************************************************************************************
*/
#include "lcd.h"

/* define macro for debug-------------------------------------------------------------------*/
#define DEBUG_LCD

/*
*************************************************************************************************************************************
*															PRIVATE DEFINE															*
*************************************************************************************************************************************
*/


/*
*************************************************************************************************************************************
*														 	DATA TYPE DEFINE															*
*************************************************************************************************************************************
*/


/*
*************************************************************************************************************************************
*													   		PRIVATE VARIABLES														*
*************************************************************************************************************************************
*/ 


/*
*************************************************************************************************************************************
*							  								LOCAL FUNCTIONS															*
*************************************************************************************************************************************
*/
static void delay(u32 nCount);

/**
  * @brief  	Inserts a delay time with resolution is 1 milisecond.
  * @param  	nCount: specifies the delay time length.
  * @retval 	None
  */
static void delay(uint32_t nCount)
{
	__IO uint32_t index = 0;

	/* default system clock is 168MHz */
	for(index = (500 * nCount); index != 0; index--);

}

// ****** Low-level functions ******
// the following functions are the only ones which deal with the CPU
// memory or port pins directly.  If you decide to use a fundamentally
// different hardware interface to your LCD, only these functions need
// to be changed, after which all the high-level functions will
// work again.
void lcd_data_line_write(u8 data)
{
	// Write only the highest 4 bits!
	//SET_LCD_EN_Line() ; // Disable LCD
	
	//GPIO_Write(LCD_DATA_GPIO_PORT, ( GPIO_ReadOutputData(LCD_DATA_GPIO_PORT) & 0xFFF0 ) |(u16) ((data >> 4)&0x000F));
	LCD_EN_SET;
	if(data&0x80) LCD_D7_SET;
	else LCD_D7_CLEAR;
	if(data&0x40) LCD_D6_SET;
	else LCD_D6_CLEAR;	
	if(data&0x20) LCD_D5_SET;
	else LCD_D5_CLEAR;
	if(data&0x10) LCD_D4_SET;
	else LCD_D4_CLEAR;
	LCD_EN_CLEAR;
	//CLR_LCD_EN_Line() ; // Enable LCD, Create a falling edge
	
	delay(1);
	

// 	SET_LCD_EN_Line() ; // Disable LCD
// 	GPIO_Write(LCD_DATA_GPIO_PORT, (GPIO_ReadInputData(LCD_DATA_GPIO_PORT)&0xFFF0) |(u16)(data&0x000F));
// 	CLR_LCD_EN_Line() ; // Enable LCD, create a falling edge
	LCD_EN_SET;
	if(data&0x08) LCD_D7_SET;
	else LCD_D7_CLEAR;
	if(data&0x04) LCD_D6_SET;
	else LCD_D6_CLEAR;	
	if(data&0x02) LCD_D5_SET;
	else LCD_D5_CLEAR;
	if(data&0x1) LCD_D4_SET;
	else LCD_D4_CLEAR;
	
	LCD_EN_CLEAR;
	//CLR_LCD_EN_Line() ; // Enable LCD, Create a falling edge
	
	delay(1);
	
}

// u8 lcd_data_line_read(void)
// {
// 	u8 HNib, LNib;															
// 	
// 	/* set data I/O lines to input */	
// 	lcd_data_line_conf(Input);
// 	/* set RS to "control" */
// 	CLR_LCD_RS_Line();
// 	/* set R/W to "read" */
// 	SET_LCD_RW_Line();

// 	delay(1);
//   														
// 	/* Read only the lowest 8 bits!*/	
// 	SET_LCD_EN_Line(); 
// 	HNib = (u8)(GPIO_ReadInputData(LCD_DATA_GPIO_PORT) & LCD_DATA_GPIO_PINS);
// 	CLR_LCD_EN_Line() ; // create a falling edge

// 	delay(1);

// 	SET_LCD_EN_Line(); 
// 	LNib = (u8)(GPIO_ReadInputData(LCD_DATA_GPIO_PORT) & LCD_DATA_GPIO_PINS);
// 	CLR_LCD_EN_Line() ; // create a falling edge
// 																			
// 	return (HNib |(LNib >> 4));	
// }

// void lcd_data_line_conf(GPIOConfig_Mode_TypeDef IO_mode)
// {
// 	GPIO_InitTypeDef  GPIO_InitStructure;										  	
// 																			
// 	/* Enable the LCD Data line Clock */											
//   	RCC_APB2PeriphClockCmd(LCD_DATA_GPIO_CLK, ENABLE);					
// 																			
// 	/* Configure the LCD Data lines */											
//   	GPIO_InitStructure.GPIO_Pin = LCD_DATA_GPIO_PINS;  	 					
//   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						
// 	if( IO_mode == Input ){							
//        	/* Configure LCD D0~D7 lines as Input */									
//             	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;				
//       	}																		
//        else if ( IO_mode == Output)						
// 	{																		
//             /* Configure LCD D0~D7 lines in Output Push-Pull mode */					
//             GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;						
//       	}																		
// 																			
//   	GPIO_Init(LCD_DATA_GPIO_PORT, &GPIO_InitStructure);	 					
// }

/**
  * @brief  	initializes I/O pins connected to LCD.
  * @param  	None
  * @retval 	None
  */
void lcd_Init_HW(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clocks for LCD control pins */
	//RCC_APB2PeriphClockCmd(LCD_RS_GPIO_CLK | LCD_RW_GPIO_CLK | LCD_EN_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(LCD_RS_GPIO_CLK | LCD_EN_GPIO_CLK|LCD_D4_GPIO_CLK|LCD_D5_GPIO_CLK|LCD_D6_GPIO_CLK|LCD_D7_GPIO_CLK, ENABLE);
	

	
	/* initialize LCD control lines to output */
	GPIO_InitStructure.GPIO_Pin 	= LCD_RS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure); 
	
	//GPIO_Init(LCD_RW_GPIO_PORT, &GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin 	= LCD_EN_GPIO_PIN;
	GPIO_Init(LCD_EN_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin 	= LCD_D4_GPIO_PIN;
	GPIO_Init(LCD_D4_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= LCD_D5_GPIO_PIN;
	GPIO_Init(LCD_D5_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= LCD_D6_GPIO_PIN;
	GPIO_Init(LCD_D6_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= LCD_D7_GPIO_PIN;
	GPIO_Init(LCD_D7_GPIO_PORT, &GPIO_InitStructure);	
}

/**
  * @brief  	waits until LCD is not busy.
  * @param  	None
  * @retval 	None
  */
// void lcd_Busy_Wait(void)
// {
// 	 u8 status;

//   	do  {
//     	status = lcd_data_line_read();
//   	}  while (status & 0x80);             /* Wait for busy flag */
// }

/**
  * @brief  writes a control command to the LCD.
  * @param  data: Specifies the control command to the LCD. 
  *   This parameter can be one of following parameters:
  *     @arg LCD_DD_RAM_PTR		: Address Display Data RAM pointer
  *     @arg LCD_CLEAR_DISPLAY		: Clear entire display and set Display Data Address to 0
  *     @arg LCD_RETRN_HOME		: sets DDRAM address 0 and returns display from being shifted to original position.
  *     @arg LCD_DISP_INIT			: 8 bit data length and 2 lines
  *     @arg LCD_INC_MODE			: Entry mode is display Data RAM pointer incremented after write
  *     @arg LCD_DISP_ON			: Sets entire display on, cursor on and blinking of cursor position character
  *     @arg LCD_DISP_OFF			: Sets entire display off, cursor off
  *     @arg LCD_CURSOR_ON		: turn on cursor
  *     @arg LCD_CURSOR_OFF		: turn off cursor
  *     @arg LCD_CUR_MOV_LEFT		: Cursor move and shift to left
  *     @arg LCD_CUR_MOV_RIGHT	: Cursor move and shift to right
  * @retval None
  */
void lcd_Control_Write(u8 data)
{
	/* write the control byte to the display controller */
	/* wait until LCD not busy */
	//lcd_Busy_Wait();		
	/* set RS to "control" */
	//CLR_LCD_RS_Line();
	LCD_RS_CLEAR;
	/* set R/W to "write" */
	//CLR_LCD_RW_Line();
	
	/* set data I/O lines to output (8bit) */
	//lcd_data_line_conf(Output);
	
	/* output data, 8bits */
	lcd_data_line_write(data);
		
	/* leave data lines in input mode to save power consumption */
	/* set data I/O lines to input (8bit) */	
	//lcd_data_line_conf(Input);
}

/**
  * @brief  	read the control status from the LCD.
  * @param  	None
  * @retval 	8 bits value from LCD
  */
// u8 lcd_Control_Read(void)
// {
// 	/* read the control byte from the display controller */
// 	register u8 data;

// 	/* wait until LCD not busy */
// 	lcd_Busy_Wait();	

// 	/* set data I/O lines to input (8bit) */
// 	lcd_data_line_conf(Input);
// 	
// 	/* set RS to "control" */
// 	CLR_LCD_RS_Line();

// 	/* set R/W to "read" */
// 	SET_LCD_RW_Line();

// 	/*  input data, 8bits */
// 	data = lcd_data_line_read();
// 	
// 	
// 	/* leave data lines in input mode to save power consumption */
// 	/* set data I/O lines to input (8bit) */
// 	lcd_data_line_conf(Input);

// 	return data;
// }

/**
  * @brief  writes a data byte to the LCD screen at the current position.
  * @param  data: data is writed to the LCD. 
  *   This parameter is ASCII code or user data:
  * @retval None
  */
void lcd_Data_Write(u8 data)
{
	/* write a data byte to the display */
	/* wait until LCD not busy */
	//lcd_Busy_Wait();		
	/* set RS to "data" */
	//SET_LCD_RS_Line();
	LCD_RS_SET;
	/* set R/W to "write" */
	//CLR_LCD_RW_Line();// hw can connect mass
	
	/* set data I/O lines to output (8bit) */
	//lcd_data_line_conf(Output);
	/* output data, 8bits */
	lcd_data_line_write(data);
	
	/* leave data lines in input mode to save power consumption */
	/* set data I/O lines to input (8bit) */	
	//lcd_data_line_conf(Input);
	
	delay(20);
}

/**
  * @brief  	reads the data byte on the LCD screen at the current position.
  * @param  	None 
  * @retval 	8 bits value from LCD
  */
// u8 lcd_Data_Read(void)
// {
// 	/* read a data byte from the display */
// 	register u8 data;

// 	/* wait until LCD not busy */
// 	lcd_Busy_Wait();	

// 	/* set data I/O lines to input (8bit) */
// 	lcd_data_line_conf(Input);
// 	
// 	/* set RS to "data" */
// 	SET_LCD_RS_Line();

// 	/* set R/W to "read" */
// 	SET_LCD_RW_Line();
// 		
// 	/*  input data, 8bits */
// 	data = lcd_data_line_read();

// 	/* leave data lines in input mode to save power consumption */
// 	/* set data I/O lines to input (8bit) */			
// 	lcd_data_line_conf(Input);

// 	return data;
// }

/*
*************************************************************************************************************************************
*															GLOBAL FUNCTIONS														*
*************************************************************************************************************************************
*/
/**
  * @brief  	Initializes the LCD.
  * @param  	None
  * @retval 	None
  */
void lcd_Init(void)
{
	/* initialize hardware */
	lcd_Init_HW();

	/* Set 4-bits interface */
	lcd_Control_Write(0x33);		 
	delay(100);
	lcd_Control_Write(0x32);

	delay(500);

	/* Start to set LCD function */
	lcd_Control_Write(LCD_DISP_INIT);
		delay(500);
	
	/* clear LCD */
	lcd_Control_Write(LCD_CLEAR_DISPLAY);
		delay(500);
	/* wait 60ms */
	
	/* set entry mode */
	lcd_Control_Write(LCD_INC_MODE);	delay(500);
	
	/* set display to on */	
	lcd_Control_Write(LCD_DISP_ON);		delay(500);
	
	/* move cursor to home and set data address to 0 */
	lcd_Control_Write(LCD_RETRN_HOME);	delay(500);
}

/**
  * @brief  	moves the cursor/position to Home (upper left corner).
  * @param  	None
  * @retval 	None
  */
void lcd_Home(void)
{
	// move cursor to home
	lcd_Control_Write(LCD_RETRN_HOME);
	delay(5);
}

/**
  * @brief  	clears the LCD display.
  * @param  	None
  * @retval 	None
  */
void lcd_Clear(void)
{	
	lcd_Control_Write(LCD_CLEAR_DISPLAY);
	delay(200);
}

/**
  * @brief  moves the cursor/position to the row,col requested,
  *			this may not be accurate for all displays.
  * @param  x: the position of row of the LCD. 
  *   This parameter can be one of following parameters:
  *     @arg 0-1		: the LCD has 2 row
  * @param  y: the position of column of the LCD. 
  *   This parameter can be one of following parameters:
  *     @arg 0-15		: the LCD has 16 column
  * @retval None
  */
void lcd_Goto(u8 x, u8 y)
{
	__IO u8 DDRAMAddr;

	// remap lines into proper order
	switch(x)
	{
	case 0: DDRAMAddr = LCD_LINE0_ADDR+y; break;
	case 1: DDRAMAddr = LCD_LINE1_ADDR+y; break;
	case 2: DDRAMAddr = LCD_LINE2_ADDR+y; break;	// for LCD 16x4 or 20x4 only
	case 3: DDRAMAddr = LCD_LINE3_ADDR+y; break;
	default: DDRAMAddr = LCD_LINE0_ADDR+y;
	}

	// set data address
	lcd_Control_Write(LCD_DD_RAM_PTR | DDRAMAddr);
	delay(10);
}

/**
  * @brief  prints a series of bytes/characters to the display.
  * @param  data: data or characters is writed to LCD. 
  *   This parameter can be one of following parameters:
  *     @arg 8bits data value		
  * @param  nBytes: number of data or character that's writed to LCD. 
  *   This parameter can be one of following parameters:
  *     @arg 0-255		
  * @retval None
  */
// void lcd_Print_Data(char* data, u8 nBytes)
// {
// 	register u8 i;

// 	/* check to make sure we have a good pointer */
// 	if (!data) return;

// 	/* print data */
// 	for(i=0; i<nBytes; i++)
// 	{
// 		lcd_Data_Write(data[i]);
// 		delay(5);
// 	}
// }

void lcd_Print_Data(char* data)
{
	while(*data++)
		lcd_Data_Write(*data);
}

