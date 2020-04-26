#include "stm32f10x.h"
#include "mydelay.h"
#include "myspi.h"
#include "lcd.h"
#include "bmp1.c"
#include "bmp2.c"

/******************************************************************
					TFT 1.8 ST7735
	STM32F103C8T6 --------------------------- 	TFT
	3v3		----------------------------------	VCC
	GND		----------------------------------	GND
	PB12	----------------------------------	CS
	PB10	----------------------------------	RESET
	PB11	----------------------------------	A0
	PB15	----------------------------------	SDA
	PB13	----------------------------------	SCK
	3v3		----------------------------------	LED
*******************************************************************/

void xianshi(void);//????  
void showqq(void);

void xianshi(void)//????
{ 
	//BACK_COLOR=WHITE;
	POINT_COLOR=RED;   
	//??32*32??
	//showhanzi32(0,0,0);	 //?
	//showhanzi32(40,0,1);	 //?
	//showhanzi32(80,0,2);    //?
	//??16*16??
	//showhanzi16(0,35,0);	  //?
	//showhanzi16(20,35,1);	  //?
	//showhanzi16(40,35,2);	  //?
	//showhanzi16(60,35,3);	  //?
	//showhanzi16(80,35,4);	  //?
	//showhanzi16(100,35,5);	  //?	   
	LCD_ShowString(0,55,200,16,16,"1.8 TFT SPI");
}

void showqq(void)
{ 
	u16 x,y; 
	x=0;
	y=0;//75;
	
	while(y<lcddev.height-39)
	{
		x=0;
		while(x<lcddev.width-39)
		{
			//showimage(x,y);	
			showimage_DMA(x,y);	
			x+=40;
		}
		y+=40;
	 }
}

int main(void)
{
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_1;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpioInit);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	
	delay_init();
	
	spi_init();	//SPI1???
	LCD_Init();	  			
 	POINT_COLOR=RED;//??????? 
	//xianshi();	   //????
	//showqq();	   //??QQ
	
	while (1) {
		/*
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		LCD_Clear_DMA(BLUE);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		BACK_COLOR=BLUE;
		//xianshi();	   //????
		showqq();	   //??QQ
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		LCD_Clear_DMA(GREEN);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		BACK_COLOR=GREEN;
		//xianshi();	   //????
		showqq();	   //??QQ
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(100);
		*/
		/*
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		//LCD_Clear_DMA(WHITE);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		BACK_COLOR=WHITE;
		xianshi();	   //????
		delay_ms(40);
		showqq();	   //??QQ
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		//GPIO_SetBits(GPIOC, GPIO_Pin_13);
		//delay_ms(100);
		//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		//delay_ms(100);
		delay_ms(10);
		*/
		/*
		LCD_Clear_DMA2(RED);
		delay_ms(1000);
		LCD_Clear_DMA2(GREEN);
		delay_ms(1000);
		LCD_Clear_DMA2(BLUE);
		delay_ms(1000);
		*/
		show_img1();
		delay_ms(1000);
		show_img2();	   //??QQ
		delay_ms(1000);
	}
}
