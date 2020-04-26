#ifndef __GPHONE_H
#define __GPHONE_H
#include "stm32f1xx_hal.h"

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define CS_Port	GPIOA //Chip Select
#define SDA_Port	GPIOA //Serial Data Pin
#define AO_Port	GPIOA //Command/Data Select Pin(C/D)
#define SCK_Port GPIOA //Serial Clock Pin

void lcd_write(unsigned char cd, unsigned char byte);
void lcd_gotoxy(unsigned char x, unsigned char y);
void glcd_gotoxy(unsigned char x, unsigned char y);
void lcd_clear(void);
void lcd_init(void);
void lcd_putc(char dat);
void lcd_puts(char *s);
void lcd_image(char x1, char y1, char array[],char x2,char y2);

#endif
