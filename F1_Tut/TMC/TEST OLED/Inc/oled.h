#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
#include "stdlib.h"	  

//////////////////////////////////////////////////////////////////////////////////	 
//Edit by HTpro DevTeam
//info@htpro.vn
// v2.0 03/08/2014
//////////////////////////////////////////////////////////////////////////////////	
   						  
//----------------- OLED PIN Define----------------  					   
/*
#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_5,0) //rST -- B5
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_5,1)

#define OLED_RS_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_6,0)    //D/C  ---B6
#define OLED_RS_Set() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_6,1)

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_3,0) //SClK  ---B3 (SCL)
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_3,1)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_4,0)  //SDIN ----B4 (SDA)
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB,GPIO_Pin_4,1)  */
//================================================================================
 		     
#define OLED_CMD  0	
#define OLED_DATA 1	
//OLED function
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size,unsigned char mode);
void OLED_ShowNum(unsigned char x,unsigned char y,uint32_t num,unsigned char len,unsigned char size);
void OLED_ShowString1206(unsigned char x,unsigned char y,const unsigned char *p);	
void OLED_ShowString1608(unsigned char x,unsigned char y,const unsigned char *p);
#endif  
	 



