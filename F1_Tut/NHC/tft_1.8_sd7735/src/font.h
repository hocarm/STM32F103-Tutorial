#ifndef __FONT_H
#define __FONT_H 	   


//32*32������ģ
const unsigned char hanzi32[]={			  
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x30,0xC0,0x01,0x00,0xE0,0xE0,0x01,0x00,0xC0,0xE1,0x00,0x00,0xC0,0x61,0x00,0x18,0x80,0xF1,0xFF,0x3F,0x00,0x70,0x00,0x18,0x00,0x3E,0x00,0x18,0x04,0xDA,0x01,0x18,0x1C,0xEE,0x01,0x18,0x38,0x6F,0x60,0x18,0x78,0xF7,0xFF,0x18,0x70,0x31,0x86,0x18,0xB0,0x19,0x06,0x18,0x80,0x09,0x06,0x18,0x80,0x05,0x86,0x19,0xC0,0xFE,0xFF,0x1B,0xC0,0x00,0x06,0x1A,0xC0,0x30,0x66,0x18,0xE0,0x70,0xE6,0x19,0x7C,0x30,0xE6,0x18,0x70,0x30,0xE6,0x18,0x60,0x30,0xE6,0x18,0x70,0xF8,0xFF,0x1C,0x70,0x30,0xE0,0x1C,0x70,0x00,0x00,0x1C,0x70,0x00,0xF0,0x1F,0x70,0x00,0x80,0x0F,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,//��
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x0E,0xC0,0x01,0x00,0xFE,0xFF,0x03,0x00,0x0E,0xC0,0x01,0x00,0x0E,0xC0,0x01,0x00,0x0E,0xC0,0x01,0x00,0xFE,0xFF,0x01,0x00,0x0E,0xC0,0x01,0x00,0x0E,0xC0,0x01,0x00,0x0E,0xC0,0x01,0x00,0xFE,0xFF,0x01,0x00,0x0E,0xC0,0x01,0x00,0x06,0x40,0x00,0x00,0x00,0x00,0x00,0x30,0x70,0x0C,0x18,0xF0,0xFF,0xFC,0x3F,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0xF0,0x7F,0xFC,0x1F,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0x70,0x70,0x0C,0x18,0xF0,0x7F,0xFC,0x1F,0x70,0x70,0x0C,0x18,0x10,0x00,0x04,0x00,0x00,0x00,0x00,0x00,//��
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x00,0x1C,0x70,0x00,0xFC,0x1F,0x70,0x00,0x00,0x8C,0x71,0x00,0x20,0x8C,0x77,0x00,0xE0,0x8C,0x73,0x04,0xF0,0x8E,0x73,0x1E,0x70,0x8E,0xF3,0x1F,0x70,0x8E,0xFB,0x0C,0x70,0x8E,0x7F,0x0C,0x70,0xFE,0x73,0x0C,0x30,0x86,0x73,0x0C,0x30,0x86,0x73,0x0C,0x30,0x96,0x73,0x0C,0xF8,0xBF,0x73,0x0C,0x38,0xF8,0x73,0x0C,0x00,0xB8,0x73,0x0C,0x00,0xB8,0xF3,0x0F,0x00,0xBE,0x73,0x06,0xE0,0x9B,0x73,0x30,0x7E,0x98,0x73,0x30,0x1C,0x98,0x13,0x30,0x08,0x9C,0x03,0x30,0x00,0x9C,0x03,0x30,0x00,0x8C,0x03,0x78,0xE0,0x0F,0xFF,0x7F,0x80,0x07,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,//��
};
//16*16������ģ
const unsigned char hanzi16[]={			  
0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x40,0x00,0x40,0x00,0xFF,0x7F,0x20,0x00,0x10,0x00,0xF0,0x0F,0x00,0x08,0x00,0x04,0x60,0x02,0x80,0x01,0x00,0x02,0x00,0x04,//ר
0x00,0x01,0x04,0x02,0x08,0x00,0xE8,0x3F,0x01,0x02,0x02,0x02,0x02,0x02,0x08,0x02,0xC8,0x3F,0x04,0x02,0x07,0x02,0x04,0x02,0x04,0x02,0x04,0x02,0xF4,0x7F,0x00,0x00,//ע
0x00,0x00,0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x20,0x02,0x22,0x22,0x24,0x22,0x28,0x12,0x28,0x0A,0x20,0x02,0xFF,0x7F,0x00,0x00,//��
0x00,0x00,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x88,0x08,0x88,0x10,0x84,0x20,0x82,0x40,0x81,0x40,0xA0,0x00,0x40,0x00,//ʾ
0x40,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x20,0x00,0x20,0x00,0x20,0x00,0xE0,0x0F,0x20,0x08,0x20,0x08,0x20,0x08,0x10,0x08,0x10,0x08,0x08,0x08,0x04,0x05,0x02,0x02,//��
0x80,0x00,0xFE,0x3F,0x02,0x20,0x20,0x00,0xFF,0x7F,0x10,0x04,0x78,0x02,0xC0,0x03,0x3C,0x1C,0x80,0x00,0xFF,0x7F,0xA0,0x02,0x90,0x04,0x8C,0x18,0x83,0x60,0x80,0x00,//��
};
//QQͼ��
const unsigned char qqimage[3200]={ /* 0X00,0X10,0X28,0X00,0X28,0X00,0X01,0X1B,*/
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0X7D,0XEF,
0XBA,0XD6,0XB6,0XB5,0XF3,0X9C,0XB2,0X94,0XB3,0X9C,0XB2,0X94,0X34,0XA5,0XF7,0XBD,
0XFB,0XDE,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XFB,0XDE,0XF3,0X9C,0XCB,0X5A,
0XC7,0X39,0X04,0X21,0X82,0X10,0X42,0X10,0X42,0X10,0X41,0X08,0X83,0X18,0X45,0X29,
0XC7,0X39,0X0C,0X63,0X75,0XAD,0X3C,0XE7,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3C,0XE7,0XB2,0X94,0X08,0X42,0XC3,0X18,0X82,0X10,
0X04,0X21,0X45,0X29,0X86,0X31,0X86,0X31,0X86,0X31,0X86,0X31,0X45,0X29,0X04,0X21,
0X82,0X10,0X41,0X08,0XC3,0X18,0X08,0X42,0XF3,0X9C,0X3C,0XE7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFB,0XDE,0X0C,0X63,0XC3,0X18,0XC3,0X18,0X45,0X29,0XC7,0X39,
0X08,0X42,0X08,0X42,0X08,0X42,0X08,0X42,0X08,0X42,0X08,0X42,0XC7,0X39,0XC7,0X39,
0X86,0X31,0X86,0X31,0X04,0X21,0X41,0X08,0X82,0X10,0XCB,0X5A,0XBA,0XD6,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFB,0XDE,0XCB,0X5A,0X82,0X10,0X45,0X29,0XC7,0X39,0X08,0X42,0X08,0X42,
0X09,0X4A,0X49,0X4A,0X49,0X4A,0X49,0X4A,0X49,0X4A,0X49,0X4A,0X08,0X42,0XC7,0X39,
0XC7,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0X83,0X18,0X00,0X00,0XC8,0X41,0X38,0XC6,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X7D,0XEF,0X8E,0X73,0X82,0X10,0X45,0X29,0XC7,0X39,0X08,0X42,0X09,0X4A,0X8A,0X52,
0X30,0X84,0XCF,0X7B,0X8A,0X52,0X49,0X4A,0X4A,0X52,0X49,0X4A,0XCB,0X5A,0XCF,0X7B,
0X0C,0X63,0X08,0X42,0XC7,0X39,0X86,0X31,0X45,0X29,0XC3,0X18,0X00,0X00,0X49,0X4A,
0XBA,0XD6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF3,0X9C,0XC3,0X18,0X04,0X21,0XC7,0X39,0X08,0X42,0X49,0X4A,0X49,0X4A,0X72,0X94,
0X7D,0XEF,0X7D,0XEF,0XB2,0X94,0X4A,0X52,0X49,0X4A,0X8A,0X52,0X75,0XAD,0XBE,0XF7,
0XBA,0XD6,0X4D,0X6B,0XC7,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0XC3,0X18,0X41,0X08,
0XCF,0X7B,0X7C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBA,0XD6,
0X08,0X42,0X82,0X10,0XC7,0X39,0X08,0X42,0X49,0X4A,0X49,0X4A,0X8E,0X73,0XFB,0XDE,
0XFF,0XFF,0XBE,0XF7,0XBA,0XD6,0X8E,0X73,0X08,0X42,0X30,0X84,0X3C,0XE7,0X7D,0XEF,
0XFF,0XFF,0XB6,0XB5,0X49,0X4A,0XC7,0X39,0X86,0X31,0X45,0X29,0X04,0X21,0X41,0X08,
0X45,0X29,0XB6,0XB5,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0X71,0X8C,
0X41,0X08,0X45,0X29,0X08,0X42,0X49,0X4A,0X49,0X4A,0X4A,0X52,0XB2,0X94,0XBE,0XF7,
0XBE,0XF7,0XB2,0X94,0XCF,0X7B,0XCF,0X7B,0X49,0X4A,0XB6,0XB5,0XF3,0X9C,0X0C,0X63,
0X38,0XC6,0XBA,0XD6,0X0C,0X63,0X87,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0XC3,0X18,
0X41,0X08,0X30,0X84,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3C,0XE7,0XCB,0X5A,
0X41,0X08,0XC7,0X39,0X08,0X42,0X49,0X4A,0X4A,0X52,0X8A,0X52,0XF3,0X9C,0XFF,0XFF,
0X7D,0XEF,0XC7,0X39,0XC3,0X18,0X0C,0X63,0XCB,0X5A,0XB6,0XB5,0XB2,0X94,0XCB,0X5A,
0X75,0XAD,0XFA,0XD6,0X4D,0X6B,0X87,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0X04,0X21,
0X41,0X08,0X8A,0X52,0X79,0XCE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X38,0XC6,0X86,0X31,
0X04,0X21,0XC8,0X41,0X49,0X4A,0X49,0X4A,0X4A,0X52,0X49,0X4A,0XB1,0X8C,0XBE,0XF7,
0XBE,0XF7,0XB2,0X94,0XCF,0X7B,0XCF,0X7B,0X49,0X4A,0X74,0XA5,0X7D,0XEF,0X7C,0XE7,
0XBE,0XF7,0X79,0XCE,0X0C,0X63,0XC7,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0X04,0X21,
0X82,0X10,0X45,0X29,0X75,0XAD,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X34,0XA5,0X82,0X10,
0X86,0X31,0X08,0X42,0X49,0X4A,0X49,0X4A,0X8A,0X52,0X49,0X4A,0X4D,0X6B,0XBA,0XD6,
0XFF,0XFF,0XFF,0XFF,0X79,0XCE,0X0D,0X63,0XC7,0X39,0XCF,0X7B,0X7D,0XEF,0XFF,0XFF,
0XFF,0XFF,0X75,0XAD,0X08,0X42,0X86,0X31,0XC7,0X39,0X86,0X31,0X45,0X29,0X45,0X29,
0XC3,0X18,0XC3,0X18,0XB2,0X94,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XB2,0X8C,0X41,0X08,
0XC7,0X39,0X08,0X42,0X49,0X4A,0X49,0X4A,0X8A,0X52,0X8A,0X52,0X4A,0X4A,0XD0,0X7B,
0X7A,0XC6,0X7B,0XBE,0X90,0X6B,0XC9,0X39,0X88,0X31,0XC9,0X39,0XB3,0X84,0XBB,0XC6,
0XF8,0XB5,0XCC,0X5A,0X86,0X31,0XC7,0X39,0XC7,0X39,0X86,0X31,0X45,0X29,0X45,0X29,
0XC4,0X20,0X41,0X08,0X30,0X84,0X3C,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3C,0XE7,0X8A,0X4A,0XC3,0X10,
0XC7,0X39,0X08,0X42,0X49,0X4A,0X49,0X4A,0X4A,0X4A,0X4A,0X42,0X09,0X3A,0X08,0X4A,
0X09,0X6B,0X49,0X7B,0XC6,0X7A,0X05,0X83,0X46,0X83,0XC5,0X7A,0XC6,0X72,0X09,0X7B,
0X48,0X5A,0X87,0X31,0X88,0X21,0X88,0X29,0X86,0X31,0X86,0X31,0X45,0X29,0X45,0X29,
0X04,0X21,0X41,0X08,0X4A,0X4A,0XBA,0XD6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XC5,0X82,0X50,0X05,0X41,
0XC7,0X29,0X08,0X42,0X49,0X4A,0X4A,0X42,0X49,0X4A,0X09,0X7B,0X88,0X9B,0XC6,0XB3,
0X21,0XD4,0XA0,0XDC,0XE1,0XE4,0X61,0XED,0X61,0XED,0X21,0XED,0XA0,0XE4,0X20,0XDC,
0X80,0XCB,0X43,0XAB,0XC4,0X82,0X06,0X5A,0X47,0X21,0X46,0X29,0X45,0X29,0X04,0X29,
0X04,0X19,0X82,0X10,0X82,0X18,0XF3,0X9C,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0X4D,0X93,0X00,0XA0,0X82,0XB8,
0XC7,0X31,0X09,0X32,0X49,0X4A,0X86,0X7A,0X43,0XC3,0X6B,0XED,0XF4,0XF6,0XEB,0XFD,
0X20,0XFD,0X20,0XFD,0X60,0XFD,0XA0,0XFD,0XA0,0XFD,0X60,0XFD,0X60,0XFD,0X20,0XFD,
0XE0,0XFC,0XA0,0XFC,0X60,0XF4,0XC1,0XDB,0X83,0X9A,0XC5,0X49,0X45,0X29,0X04,0X19,
0XC4,0X20,0X82,0X38,0X00,0X50,0XCB,0X6A,0XBA,0XD6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0XEE,0X04,0XA1,0X00,0XC0,0X00,0XF0,
0XC3,0XA0,0XC8,0X41,0X49,0X42,0X05,0X9B,0X20,0XFC,0XA4,0XFC,0X69,0XFD,0XE8,0XFD,
0X63,0XFD,0X20,0XFD,0X60,0XFD,0X60,0XFD,0X60,0XFD,0X20,0XFD,0X20,0XFD,0XE0,0XFC,
0XE0,0XFC,0XA0,0XFC,0X60,0XFC,0X20,0XFC,0X41,0XD3,0XC5,0X49,0X45,0X19,0XC4,0X38,
0X82,0X68,0X41,0X88,0X00,0X70,0X49,0X5A,0X79,0XCE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0XF6,0X82,0XC0,0X00,0XD0,0X86,0XC1,
0X46,0XF1,0X41,0XC8,0X45,0X79,0X89,0X52,0X88,0X62,0X86,0X6A,0XC6,0X7A,0XC4,0XBB,
0XE1,0XFC,0X60,0XFD,0X60,0XFD,0XA0,0XFD,0XA0,0XFD,0X60,0XFD,0X60,0XFD,0XE0,0XFC,
0X60,0XE4,0X03,0X93,0X84,0X72,0X44,0X6A,0XC5,0X41,0X45,0X29,0XC3,0X58,0X41,0XA8,
0X40,0X98,0X00,0XB0,0X00,0X60,0X0C,0X6B,0X79,0XCE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0XCE,0X83,0X82,0X88,0X00,0XF8,0XC4,0XD8,
0X0C,0XF3,0X8A,0XFA,0X82,0XE8,0X82,0XB0,0X45,0X69,0XC7,0X51,0X08,0X42,0X08,0X3A,
0X86,0X5A,0X83,0X9B,0XA2,0XBC,0X22,0XCD,0X21,0XCD,0XA1,0XC4,0X22,0XB4,0XC4,0X7A,
0X06,0X3A,0X86,0X29,0X45,0X29,0X05,0X31,0XC4,0X50,0X41,0X90,0X00,0XC0,0X00,0XA8,
0X00,0XA0,0X00,0XA8,0X00,0X30,0X4A,0X4A,0XBA,0XD6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0X8E,0X73,0XC3,0X18,0X05,0X39,0X82,0XA8,0X00,0XF8,
0XC3,0XF8,0X4D,0XFB,0X4D,0XFB,0XC7,0XF9,0XC3,0XF0,0X82,0XD8,0XC3,0XB0,0X04,0X81,
0X45,0X61,0X46,0X51,0X86,0X49,0X86,0X49,0X46,0X41,0X45,0X41,0X45,0X41,0X45,0X41,
0X05,0X49,0X04,0X61,0X82,0X90,0X41,0XB0,0X00,0XD0,0X00,0XC8,0X00,0XA8,0X00,0XA8,
0X00,0XB8,0X41,0X58,0X82,0X10,0X82,0X10,0XB2,0X94,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XBE,0XF7,0XCF,0X7B,0X82,0X10,0X04,0X21,0X86,0X29,0X86,0X41,0X04,0X99,
0X40,0XE8,0X41,0XF8,0X86,0XF9,0XCB,0XFA,0X49,0XFA,0X82,0XF8,0X00,0XF8,0X00,0XF0,
0X00,0XE8,0X41,0XD8,0X41,0XD0,0X41,0XC0,0X41,0XC0,0X41,0XC0,0X41,0XC0,0X41,0XC8,
0X00,0XD0,0X00,0XE0,0X00,0XE0,0X00,0XD8,0X00,0XD0,0X00,0XB8,0X00,0XA8,0X41,0X88,
0X82,0X48,0X82,0X10,0X82,0X10,0X00,0X00,0X45,0X29,0X79,0XCE,0XFF,0XFF,0XFF,0XFF,
0XBE,0XF7,0XF3,0X9C,0X82,0X10,0XC3,0X18,0X45,0X29,0X86,0X31,0XC7,0X31,0X30,0X7C,
0XF3,0XDC,0X86,0XE1,0X00,0XF0,0X00,0XF8,0X41,0XF8,0X41,0XF8,0X00,0XF8,0X00,0XF8,
0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,
0X00,0XE8,0X00,0XE0,0X00,0XE0,0X00,0XD8,0X00,0XC8,0X41,0XA0,0X8A,0X9A,0X0C,0X63,
0X04,0X11,0X82,0X10,0X82,0X10,0X41,0X08,0X00,0X00,0X4D,0X6B,0X7D,0XEF,0XFF,0XFF,
0XFB,0XDE,0X08,0X42,0X42,0X10,0X45,0X29,0X86,0X31,0X86,0X31,0X49,0X4A,0X38,0XBE,
0XFF,0XFF,0X38,0XD6,0X86,0XA9,0X00,0XC8,0X00,0XE0,0X00,0XF0,0X00,0XF8,0X00,0XF8,
0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF8,0X00,0XF0,0X00,0XF0,
0X00,0XE8,0X00,0XE0,0X00,0XD0,0XC3,0X98,0X8A,0X8A,0XB2,0XA4,0XBA,0XC6,0XF7,0XB5,
0X08,0X42,0X41,0X08,0X82,0X10,0X41,0X08,0X00,0X00,0X45,0X29,0XF7,0XBD,0XFF,0XFF,
0X71,0X8C,0X41,0X08,0X04,0X21,0X45,0X29,0X86,0X31,0X86,0X31,0X0C,0X63,0X3C,0XE7,
0XFF,0XFF,0X79,0XD6,0X46,0XB9,0X00,0XE0,0X42,0XC8,0X82,0XA8,0X82,0XB0,0X41,0XD8,
0X82,0XE8,0X82,0XF0,0X41,0XE8,0X41,0XE8,0X41,0XE8,0X41,0XF0,0X41,0XE8,0X41,0XD8,
0X04,0XC1,0X08,0X92,0X4D,0X8B,0X34,0XA5,0XFB,0XC6,0XFB,0XD6,0XBA,0XCE,0X3C,0XE7,
0X30,0X84,0XC3,0X18,0X41,0X08,0X41,0X08,0X00,0X00,0X41,0X08,0XCF,0X7B,0X7D,0XEF,
0X49,0X4A,0X00,0X00,0X04,0X21,0X45,0X29,0X46,0X31,0X86,0X31,0X30,0X84,0XFF,0XFF,
0XFF,0XF7,0XF7,0XDD,0X09,0XDA,0X83,0XF8,0X01,0XF0,0X42,0XC0,0X82,0X98,0X49,0X9A,
0XF3,0XB4,0XF3,0XCC,0X71,0XBC,0X8E,0XBB,0X8E,0XBB,0X30,0XBC,0X71,0XBC,0XF3,0XBC,
0XB6,0XBD,0XFB,0XCE,0XBE,0XE7,0X7D,0XE7,0X3B,0XDF,0XBA,0XD6,0X79,0XCE,0XFB,0XDE,
0X75,0XAD,0X86,0X31,0X41,0X08,0X41,0X08,0X00,0X00,0X00,0X00,0X49,0X4A,0XFB,0XDE,
0X04,0X21,0X41,0X08,0X04,0X21,0X45,0X29,0X45,0X29,0X87,0X39,0XB2,0X94,0XFF,0XFF,
0XBE,0XF7,0X34,0XDD,0X0C,0XEB,0X09,0XFA,0X00,0XF0,0X01,0XD8,0X00,0XD8,0X8B,0XD2,
0X7D,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XBE,0XFF,0X7D,0XEF,0XFB,0XDE,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0XBA,0XD6,
0X78,0XC6,0XC7,0X39,0X00,0X00,0X41,0X08,0X00,0X00,0X00,0X00,0XC7,0X39,0X79,0XCE,
0X00,0X00,0X82,0X10,0XC3,0X18,0X04,0X21,0X05,0X29,0X86,0X31,0XB3,0X9C,0XFF,0XFF,
0XFF,0XF7,0X75,0XDD,0XC7,0XE9,0XC7,0XF9,0X01,0XF8,0X01,0XF0,0X00,0XE8,0X49,0XE2,
0XFB,0XEE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XBE,0XF7,0X7D,0XEF,0XFB,0XDE,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0XBA,0XD6,
0XB9,0XCE,0X08,0X42,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC7,0X39,0X38,0XC6,
0X00,0X00,0X82,0X10,0X82,0X10,0X04,0X21,0X04,0X21,0X45,0X29,0X30,0X84,0XFF,0XFF,
0XFF,0XFF,0X38,0XDE,0XC4,0XD0,0X00,0XF0,0X01,0XF8,0X00,0XF8,0X00,0XF0,0X08,0XD2,
0XFB,0XE6,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XBE,0XF7,0X7D,0XEF,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0X79,0XCE,0XBA,0XD6,
0X79,0XCE,0XC7,0X39,0X41,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X86,0X31,0X38,0XC6,
0X00,0X00,0X00,0X00,0XC3,0X18,0XCB,0X5A,0X86,0X31,0XC3,0X18,0XCB,0X5A,0X7D,0XEF,
0XFF,0XFF,0X7D,0XEF,0XCF,0XBB,0XC3,0XB0,0X41,0XD0,0X41,0XD0,0X82,0XB8,0X4D,0XB3,
0X7D,0XE7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XBE,0XF7,0XBE,0XF7,0X3D,0XEF,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0X79,0XCE,0XFA,0XD6,
0XF7,0XBD,0X04,0X21,0X86,0X31,0X04,0X21,0X00,0X00,0X00,0X00,0X86,0X31,0X38,0XC6,
0X86,0X31,0XC3,0X18,0XCB,0X5A,0X75,0XAD,0XCF,0X7B,0X41,0X08,0X86,0X31,0XF7,0XBD,
0XFF,0XFF,0XFF,0XFF,0XBE,0XEF,0X74,0XB5,0X30,0X9C,0X30,0X9C,0X72,0XA4,0XBB,0XD6,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XBE,0XF7,0X7D,0XEF,0X3C,0XE7,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0X79,0XCE,0X3C,0XE7,
0X71,0X8C,0X81,0X08,0X0C,0X63,0XCF,0X7B,0X82,0X10,0X00,0X00,0X8A,0X52,0X38,0XC6,
0X75,0XAD,0X71,0X8C,0XB6,0XB5,0X3C,0XE7,0XFB,0XDE,0XC7,0X39,0X00,0X00,0XCF,0X73,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,
0X7D,0XEF,0X7D,0XEF,0X3B,0XDF,0XFA,0XD6,0X79,0XCE,0X79,0XCE,0XFB,0XDE,0XB9,0XCE,
0XC7,0X39,0XC4,0X20,0X71,0X8C,0XBA,0XD6,0X71,0X8C,0XCB,0X5A,0XB2,0X94,0XBA,0XD6,
0XFF,0XFF,0X7D,0XEF,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XB6,0XB5,0X46,0X29,0X05,0X19,
0X75,0XA5,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,
0X7D,0XEF,0X3C,0XE7,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0XBA,0XD6,0XFC,0XDE,0X4E,0X63,
0X42,0X08,0X0C,0X63,0XF7,0XBD,0XBE,0XF7,0XFF,0XFF,0XFB,0XDE,0XFB,0XDE,0XBE,0XF7,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0X9C,0X04,0X21,
0X05,0X21,0XB6,0XA5,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0X7D,0XEF,
0X3C,0XE7,0XFB,0XDE,0XBA,0XD6,0X79,0XCE,0XFB,0XDE,0XBB,0XD6,0XD1,0X73,0X83,0X18,
0X86,0X39,0X34,0X9D,0XBD,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XFF,0X35,0XD6,0XEB,0XCC,0X43,0XB3,
0X40,0X51,0X05,0X19,0XF5,0X8C,0XBE,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0X7D,0XEF,0X7D,0XEF,0X3C,0XE7,
0XFB,0XDE,0XBA,0XDE,0XBA,0XD6,0X3C,0XDF,0X3A,0XBE,0X4F,0X63,0X82,0X49,0X40,0XA3,
0X23,0XB4,0XCC,0X83,0X3A,0XBE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XF7,0XB5,0XBD,0X82,0X92,0X20,0XF4,0XA0,0XFC,
0X60,0XE4,0X40,0X82,0X84,0X41,0X8F,0X6B,0X77,0XAD,0X3D,0XE7,0XFF,0XFF,0XFF,0XFF,
0XFE,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0X7D,0XEF,0X7D,0XEF,0X3C,0XE7,0XFB,0XDE,
0XFB,0XDE,0X3D,0XE7,0XBB,0XCE,0X36,0X9D,0X0B,0X6B,0X41,0X6A,0X60,0XC4,0X20,0XFE,
0X60,0XF5,0X00,0X8B,0XC7,0X6A,0X38,0XC6,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0X4B,0X7B,0X80,0XB2,0XA0,0XFC,0XA0,0XFC,
0XE0,0XFC,0XE0,0XFC,0XC0,0XCB,0XC1,0X8A,0X45,0X62,0X4D,0X6B,0XB3,0X94,0XF7,0XBD,
0X3D,0XDF,0XFF,0XF7,0XFF,0XFF,0XBE,0XF7,0X7D,0XEF,0X7D,0XEF,0X7D,0XE7,0X3D,0XDF,
0XBA,0XC6,0X75,0XA5,0X8D,0X7B,0X84,0X7A,0X40,0XB3,0XE0,0XEC,0XE0,0XFD,0XE0,0XFD,
0X60,0XF5,0X20,0XE5,0XA0,0XD4,0X0A,0X6B,0XFB,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0XEF,0XCC,0X93,0X40,0XEB,0X60,0XFC,0XA0,0XFC,
0XE0,0XFC,0X20,0XFD,0X60,0XFD,0X20,0XF5,0XA0,0XD4,0XC0,0XBB,0X42,0X9B,0X45,0X8B,
0X6B,0X9C,0XAE,0X9C,0X71,0X8C,0XB3,0X94,0X33,0X9D,0X34,0XA5,0XF2,0XA4,0XF0,0XB4,
0XCA,0X9B,0X04,0X9B,0X40,0XBB,0X20,0XE4,0X20,0XFD,0XA0,0XFD,0XA0,0XFD,0XE0,0XFD,
0XE0,0XFD,0XE0,0XFD,0X20,0XC4,0X88,0X5A,0X38,0XBE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X78,0XD6,0X46,0XAB,0X40,0XDB,0X20,0XF4,
0X60,0XFC,0XA0,0XFC,0XE0,0XFC,0X60,0XFD,0XA0,0XFD,0X60,0XFD,0X20,0XF5,0XA0,0XDC,
0XC0,0XB3,0XC0,0X51,0X86,0X29,0X0D,0X63,0X8F,0X7B,0X0D,0X5B,0XC7,0X41,0X01,0X82,
0X00,0XC3,0XC0,0XE3,0X60,0XFC,0XA0,0XFC,0XE0,0XFC,0XE0,0XFC,0X60,0XF5,0X60,0XF5,
0X20,0XE5,0X80,0X9B,0X86,0X62,0X30,0X84,0X79,0XCE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X38,0XC6,0X2D,0X9C,0X05,0X93,
0X43,0XA3,0X82,0XB3,0XC2,0XBB,0XC2,0XBB,0X22,0XB4,0X82,0XA3,0X42,0X93,0XC3,0X7A,
0X85,0X62,0X0B,0X63,0X71,0X84,0XB6,0XB5,0X79,0XCE,0X79,0XC6,0XB5,0XAD,0X70,0X94,
0X4A,0X8B,0X06,0X83,0X04,0X93,0X04,0X9B,0X43,0X9B,0X43,0X9B,0X43,0X93,0X04,0X83,
0X08,0X73,0X8D,0X73,0XB3,0X94,0X79,0XCE,0X7D,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3C,0XDF,0X38,0XBE,
0X75,0XB5,0X33,0XA5,0X33,0XA5,0XF3,0X9C,0XF3,0X9C,0XF3,0X9C,0XF3,0X94,0XF3,0X9C,
0X35,0XA5,0XF8,0XBD,0XFB,0XDE,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7E,0XEF,
0XBB,0XD6,0XF8,0XBD,0XB6,0XAD,0X75,0XAD,0X34,0XA5,0X33,0X9D,0X34,0X9D,0X35,0XA5,
0XB7,0XAD,0X79,0XC6,0X3C,0XE7,0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};
const unsigned char asc2_1206[95][12]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0x3F,0x40,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
{0x00,0x00,0x30,0x00,0x40,0x00,0x30,0x00,0x40,0x00,0x00,0x00},/*""",2*/
{0x09,0x00,0x0B,0xC0,0x3D,0x00,0x0B,0xC0,0x3D,0x00,0x09,0x00},/*"#",3*/
{0x18,0xC0,0x24,0x40,0x7F,0xE0,0x22,0x40,0x31,0x80,0x00,0x00},/*"$",4*/
{0x18,0x00,0x24,0xC0,0x1B,0x00,0x0D,0x80,0x32,0x40,0x01,0x80},/*"%",5*/
{0x03,0x80,0x1C,0x40,0x27,0x40,0x1C,0x80,0x07,0x40,0x00,0x40},/*"&",6*/
{0x10,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x20,0x40,0x40,0x20},/*"(",8*/
{0x00,0x00,0x40,0x20,0x20,0x40,0x1F,0x80,0x00,0x00,0x00,0x00},/*")",9*/
{0x09,0x00,0x06,0x00,0x1F,0x80,0x06,0x00,0x09,0x00,0x00,0x00},/*"*",10*/
{0x04,0x00,0x04,0x00,0x3F,0x80,0x04,0x00,0x04,0x00,0x00,0x00},/*"+",11*/
{0x00,0x10,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*",",12*/
{0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*".",14*/
{0x00,0x20,0x01,0xC0,0x06,0x00,0x38,0x00,0x40,0x00,0x00,0x00},/*"/",15*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"0",16*/
{0x00,0x00,0x10,0x40,0x3F,0xC0,0x00,0x40,0x00,0x00,0x00,0x00},/*"1",17*/
{0x18,0xC0,0x21,0x40,0x22,0x40,0x24,0x40,0x18,0x40,0x00,0x00},/*"2",18*/
{0x10,0x80,0x20,0x40,0x24,0x40,0x24,0x40,0x1B,0x80,0x00,0x00},/*"3",19*/
{0x02,0x00,0x0D,0x00,0x11,0x00,0x3F,0xC0,0x01,0x40,0x00,0x00},/*"4",20*/
{0x3C,0x80,0x24,0x40,0x24,0x40,0x24,0x40,0x23,0x80,0x00,0x00},/*"5",21*/
{0x1F,0x80,0x24,0x40,0x24,0x40,0x34,0x40,0x03,0x80,0x00,0x00},/*"6",22*/
{0x30,0x00,0x20,0x00,0x27,0xC0,0x38,0x00,0x20,0x00,0x00,0x00},/*"7",23*/
{0x1B,0x80,0x24,0x40,0x24,0x40,0x24,0x40,0x1B,0x80,0x00,0x00},/*"8",24*/
{0x1C,0x00,0x22,0xC0,0x22,0x40,0x22,0x40,0x1F,0x80,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x08,0x40,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x04,0x60,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/
{0x00,0x00,0x04,0x00,0x0A,0x00,0x11,0x00,0x20,0x80,0x40,0x40},/*"<",28*/
{0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x00,0x00},/*"=",29*/
{0x00,0x00,0x40,0x40,0x20,0x80,0x11,0x00,0x0A,0x00,0x04,0x00},/*">",30*/
{0x18,0x00,0x20,0x00,0x23,0x40,0x24,0x00,0x18,0x00,0x00,0x00},/*"?",31*/
{0x1F,0x80,0x20,0x40,0x27,0x40,0x29,0x40,0x1F,0x40,0x00,0x00},/*"@",32*/
{0x00,0x40,0x07,0xC0,0x39,0x00,0x0F,0x00,0x01,0xC0,0x00,0x40},/*"A",33*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x24,0x40,0x1B,0x80,0x00,0x00},/*"B",34*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x30,0x80,0x00,0x00},/*"C",35*/
{0x20,0x40,0x3F,0xC0,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"D",36*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x2E,0x40,0x30,0xC0,0x00,0x00},/*"E",37*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x2E,0x00,0x30,0x00,0x00,0x00},/*"F",38*/
{0x0F,0x00,0x10,0x80,0x20,0x40,0x22,0x40,0x33,0x80,0x02,0x00},/*"G",39*/
{0x20,0x40,0x3F,0xC0,0x04,0x00,0x04,0x00,0x3F,0xC0,0x20,0x40},/*"H",40*/
{0x20,0x40,0x20,0x40,0x3F,0xC0,0x20,0x40,0x20,0x40,0x00,0x00},/*"I",41*/
{0x00,0x60,0x20,0x20,0x20,0x20,0x3F,0xC0,0x20,0x00,0x20,0x00},/*"J",42*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x0B,0x00,0x30,0xC0,0x20,0x40},/*"K",43*/
{0x20,0x40,0x3F,0xC0,0x20,0x40,0x00,0x40,0x00,0x40,0x00,0xC0},/*"L",44*/
{0x3F,0xC0,0x3C,0x00,0x03,0xC0,0x3C,0x00,0x3F,0xC0,0x00,0x00},/*"M",45*/
{0x20,0x40,0x3F,0xC0,0x0C,0x40,0x23,0x00,0x3F,0xC0,0x20,0x00},/*"N",46*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"O",47*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x24,0x00,0x18,0x00,0x00,0x00},/*"P",48*/
{0x1F,0x80,0x21,0x40,0x21,0x40,0x20,0xE0,0x1F,0xA0,0x00,0x00},/*"Q",49*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x26,0x00,0x19,0xC0,0x00,0x40},/*"R",50*/
{0x18,0xC0,0x24,0x40,0x24,0x40,0x22,0x40,0x31,0x80,0x00,0x00},/*"S",51*/
{0x30,0x00,0x20,0x40,0x3F,0xC0,0x20,0x40,0x30,0x00,0x00,0x00},/*"T",52*/
{0x20,0x00,0x3F,0x80,0x00,0x40,0x00,0x40,0x3F,0x80,0x20,0x00},/*"U",53*/
{0x20,0x00,0x3E,0x00,0x01,0xC0,0x07,0x00,0x38,0x00,0x20,0x00},/*"V",54*/
{0x38,0x00,0x07,0xC0,0x3C,0x00,0x07,0xC0,0x38,0x00,0x00,0x00},/*"W",55*/
{0x20,0x40,0x39,0xC0,0x06,0x00,0x39,0xC0,0x20,0x40,0x00,0x00},/*"X",56*/
{0x20,0x00,0x38,0x40,0x07,0xC0,0x38,0x40,0x20,0x00,0x00,0x00},/*"Y",57*/
{0x30,0x40,0x21,0xC0,0x26,0x40,0x38,0x40,0x20,0xC0,0x00,0x00},/*"Z",58*/
{0x00,0x00,0x00,0x00,0x7F,0xE0,0x40,0x20,0x40,0x20,0x00,0x00},/*"[",59*/
{0x00,0x00,0x70,0x00,0x0C,0x00,0x03,0x80,0x00,0x40,0x00,0x00},/*"\",60*/
{0x00,0x00,0x40,0x20,0x40,0x20,0x7F,0xE0,0x00,0x00,0x00,0x00},/*"]",61*/
{0x00,0x00,0x20,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10},/*"_",63*/
{0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x02,0x80,0x05,0x40,0x05,0x40,0x03,0xC0,0x00,0x40},/*"a",65*/
{0x20,0x00,0x3F,0xC0,0x04,0x40,0x04,0x40,0x03,0x80,0x00,0x00},/*"b",66*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x40,0x06,0x40,0x00,0x00},/*"c",67*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x24,0x40,0x3F,0xC0,0x00,0x40},/*"d",68*/
{0x00,0x00,0x03,0x80,0x05,0x40,0x05,0x40,0x03,0x40,0x00,0x00},/*"e",69*/
{0x00,0x00,0x04,0x40,0x1F,0xC0,0x24,0x40,0x24,0x40,0x20,0x00},/*"f",70*/
{0x00,0x00,0x02,0xE0,0x05,0x50,0x05,0x50,0x06,0x50,0x04,0x20},/*"g",71*/
{0x20,0x40,0x3F,0xC0,0x04,0x40,0x04,0x00,0x03,0xC0,0x00,0x40},/*"h",72*/
{0x00,0x00,0x04,0x40,0x27,0xC0,0x00,0x40,0x00,0x00,0x00,0x00},/*"i",73*/
{0x00,0x10,0x00,0x10,0x04,0x10,0x27,0xE0,0x00,0x00,0x00,0x00},/*"j",74*/
{0x20,0x40,0x3F,0xC0,0x01,0x40,0x07,0x00,0x04,0xC0,0x04,0x40},/*"k",75*/
{0x20,0x40,0x20,0x40,0x3F,0xC0,0x00,0x40,0x00,0x40,0x00,0x00},/*"l",76*/
{0x07,0xC0,0x04,0x00,0x07,0xC0,0x04,0x00,0x03,0xC0,0x00,0x00},/*"m",77*/
{0x04,0x40,0x07,0xC0,0x04,0x40,0x04,0x00,0x03,0xC0,0x00,0x40},/*"n",78*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x40,0x03,0x80,0x00,0x00},/*"o",79*/
{0x04,0x10,0x07,0xF0,0x04,0x50,0x04,0x40,0x03,0x80,0x00,0x00},/*"p",80*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x50,0x07,0xF0,0x00,0x10},/*"q",81*/
{0x04,0x40,0x07,0xC0,0x02,0x40,0x04,0x00,0x04,0x00,0x00,0x00},/*"r",82*/
{0x00,0x00,0x06,0x40,0x05,0x40,0x05,0x40,0x04,0xC0,0x00,0x00},/*"s",83*/
{0x00,0x00,0x04,0x00,0x1F,0x80,0x04,0x40,0x00,0x40,0x00,0x00},/*"t",84*/
{0x04,0x00,0x07,0x80,0x00,0x40,0x04,0x40,0x07,0xC0,0x00,0x40},/*"u",85*/
{0x04,0x00,0x07,0x00,0x04,0xC0,0x01,0x80,0x06,0x00,0x04,0x00},/*"v",86*/
{0x06,0x00,0x01,0xC0,0x07,0x00,0x01,0xC0,0x06,0x00,0x00,0x00},/*"w",87*/
{0x04,0x40,0x06,0xC0,0x01,0x00,0x06,0xC0,0x04,0x40,0x00,0x00},/*"x",88*/
{0x04,0x10,0x07,0x10,0x04,0xE0,0x01,0x80,0x06,0x00,0x04,0x00},/*"y",89*/
{0x00,0x00,0x04,0x40,0x05,0xC0,0x06,0x40,0x04,0x40,0x00,0x00},/*"z",90*/
{0x00,0x00,0x00,0x00,0x04,0x00,0x7B,0xE0,0x40,0x20,0x00,0x00},/*"{",91*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,0x00,0x00,0x00,0x00},/*"|",92*/
{0x00,0x00,0x40,0x20,0x7B,0xE0,0x04,0x00,0x00,0x00,0x00,0x00},/*"}",93*/
{0x40,0x00,0x80,0x00,0x40,0x00,0x20,0x00,0x20,0x00,0x40,0x00},/*"~",94*/
}; 
const unsigned char asc2_1608[95][16]={	  
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xCC,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
{0x00,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x00,0x00},/*""",2*/
{0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x00,0x00},/*"#",3*/
{0x00,0x00,0x0E,0x18,0x11,0x04,0x3F,0xFF,0x10,0x84,0x0C,0x78,0x00,0x00,0x00,0x00},/*"$",4*/
{0x0F,0x00,0x10,0x84,0x0F,0x38,0x00,0xC0,0x07,0x78,0x18,0x84,0x00,0x78,0x00,0x00},/*"%",5*/
{0x00,0x78,0x0F,0x84,0x10,0xC4,0x11,0x24,0x0E,0x98,0x00,0xE4,0x00,0x84,0x00,0x08},/*"&",6*/
{0x08,0x00,0x68,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x18,0x18,0x20,0x04,0x40,0x02,0x00,0x00},/*"(",8*/
{0x00,0x00,0x40,0x02,0x20,0x04,0x18,0x18,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*")",9*/
{0x02,0x40,0x02,0x40,0x01,0x80,0x0F,0xF0,0x01,0x80,0x02,0x40,0x02,0x40,0x00,0x00},/*"*",10*/
{0x00,0x80,0x00,0x80,0x00,0x80,0x0F,0xF8,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00},/*"+",11*/
{0x00,0x01,0x00,0x0D,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*",",12*/
{0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80},/*"-",13*/
{0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*".",14*/
{0x00,0x00,0x00,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x20,0x00},/*"/",15*/
{0x00,0x00,0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"0",16*/
{0x00,0x00,0x08,0x04,0x08,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"1",17*/
{0x00,0x00,0x0E,0x0C,0x10,0x14,0x10,0x24,0x10,0x44,0x11,0x84,0x0E,0x0C,0x00,0x00},/*"2",18*/
{0x00,0x00,0x0C,0x18,0x10,0x04,0x11,0x04,0x11,0x04,0x12,0x88,0x0C,0x70,0x00,0x00},/*"3",19*/
{0x00,0x00,0x00,0xE0,0x03,0x20,0x04,0x24,0x08,0x24,0x1F,0xFC,0x00,0x24,0x00,0x00},/*"4",20*/
{0x00,0x00,0x1F,0x98,0x10,0x84,0x11,0x04,0x11,0x04,0x10,0x88,0x10,0x70,0x00,0x00},/*"5",21*/
{0x00,0x00,0x07,0xF0,0x08,0x88,0x11,0x04,0x11,0x04,0x18,0x88,0x00,0x70,0x00,0x00},/*"6",22*/
{0x00,0x00,0x1C,0x00,0x10,0x00,0x10,0xFC,0x13,0x00,0x1C,0x00,0x10,0x00,0x00,0x00},/*"7",23*/
{0x00,0x00,0x0E,0x38,0x11,0x44,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00},/*"8",24*/
{0x00,0x00,0x07,0x00,0x08,0x8C,0x10,0x44,0x10,0x44,0x08,0x88,0x07,0xF0,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x03,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/
{0x00,0x00,0x00,0x80,0x01,0x40,0x02,0x20,0x04,0x10,0x08,0x08,0x10,0x04,0x00,0x00},/*"<",28*/
{0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x00,0x00},/*"=",29*/
{0x00,0x00,0x10,0x04,0x08,0x08,0x04,0x10,0x02,0x20,0x01,0x40,0x00,0x80,0x00,0x00},/*">",30*/
{0x00,0x00,0x0E,0x00,0x12,0x00,0x10,0x0C,0x10,0x6C,0x10,0x80,0x0F,0x00,0x00,0x00},/*"?",31*/
{0x03,0xE0,0x0C,0x18,0x13,0xE4,0x14,0x24,0x17,0xC4,0x08,0x28,0x07,0xD0,0x00,0x00},/*"@",32*/
{0x00,0x04,0x00,0x3C,0x03,0xC4,0x1C,0x40,0x07,0x40,0x00,0xE4,0x00,0x1C,0x00,0x04},/*"A",33*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x11,0x04,0x0E,0x88,0x00,0x70,0x00,0x00},/*"B",34*/
{0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x08,0x1C,0x10,0x00,0x00},/*"C",35*/
{0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"D",36*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x17,0xC4,0x10,0x04,0x08,0x18,0x00,0x00},/*"E",37*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x17,0xC0,0x10,0x00,0x08,0x00,0x00,0x00},/*"F",38*/
{0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x44,0x1C,0x78,0x00,0x40,0x00,0x00},/*"G",39*/
{0x10,0x04,0x1F,0xFC,0x10,0x84,0x00,0x80,0x00,0x80,0x10,0x84,0x1F,0xFC,0x10,0x04},/*"H",40*/
{0x00,0x00,0x10,0x04,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x00,0x00,0x00,0x00},/*"I",41*/
{0x00,0x03,0x00,0x01,0x10,0x01,0x10,0x01,0x1F,0xFE,0x10,0x00,0x10,0x00,0x00,0x00},/*"J",42*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x03,0x80,0x14,0x64,0x18,0x1C,0x10,0x04,0x00,0x00},/*"K",43*/
{0x10,0x04,0x1F,0xFC,0x10,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x0C,0x00,0x00},/*"L",44*/
{0x10,0x04,0x1F,0xFC,0x1F,0x00,0x00,0xFC,0x1F,0x00,0x1F,0xFC,0x10,0x04,0x00,0x00},/*"M",45*/
{0x10,0x04,0x1F,0xFC,0x0C,0x04,0x03,0x00,0x00,0xE0,0x10,0x18,0x1F,0xFC,0x10,0x00},/*"N",46*/
{0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"O",47*/
{0x10,0x04,0x1F,0xFC,0x10,0x84,0x10,0x80,0x10,0x80,0x10,0x80,0x0F,0x00,0x00,0x00},/*"P",48*/
{0x07,0xF0,0x08,0x18,0x10,0x24,0x10,0x24,0x10,0x1C,0x08,0x0A,0x07,0xF2,0x00,0x00},/*"Q",49*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x11,0xC0,0x11,0x30,0x0E,0x0C,0x00,0x04},/*"R",50*/
{0x00,0x00,0x0E,0x1C,0x11,0x04,0x10,0x84,0x10,0x84,0x10,0x44,0x1C,0x38,0x00,0x00},/*"S",51*/
{0x18,0x00,0x10,0x00,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x00,0x18,0x00,0x00,0x00},/*"T",52*/
{0x10,0x00,0x1F,0xF8,0x10,0x04,0x00,0x04,0x00,0x04,0x10,0x04,0x1F,0xF8,0x10,0x00},/*"U",53*/
{0x10,0x00,0x1E,0x00,0x11,0xE0,0x00,0x1C,0x00,0x70,0x13,0x80,0x1C,0x00,0x10,0x00},/*"V",54*/
{0x1F,0xC0,0x10,0x3C,0x00,0xE0,0x1F,0x00,0x00,0xE0,0x10,0x3C,0x1F,0xC0,0x00,0x00},/*"W",55*/
{0x10,0x04,0x18,0x0C,0x16,0x34,0x01,0xC0,0x01,0xC0,0x16,0x34,0x18,0x0C,0x10,0x04},/*"X",56*/
{0x10,0x00,0x1C,0x00,0x13,0x04,0x00,0xFC,0x13,0x04,0x1C,0x00,0x10,0x00,0x00,0x00},/*"Y",57*/
{0x08,0x04,0x10,0x1C,0x10,0x64,0x10,0x84,0x13,0x04,0x1C,0x04,0x10,0x18,0x00,0x00},/*"Z",58*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x40,0x02,0x40,0x02,0x40,0x02,0x00,0x00},/*"[",59*/
{0x00,0x00,0x30,0x00,0x0C,0x00,0x03,0x80,0x00,0x60,0x00,0x1C,0x00,0x03,0x00,0x00},/*"\",60*/
{0x00,0x00,0x40,0x02,0x40,0x02,0x40,0x02,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"]",61*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00},/*"^",62*/
{0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01},/*"_",63*/
{0x00,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x00,0x98,0x01,0x24,0x01,0x44,0x01,0x44,0x01,0x44,0x00,0xFC,0x00,0x04},/*"a",65*/
{0x10,0x00,0x1F,0xFC,0x00,0x88,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00},/*"b",66*/
{0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x00},/*"c",67*/
{0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x11,0x08,0x1F,0xFC,0x00,0x04},/*"d",68*/
{0x00,0x00,0x00,0xF8,0x01,0x44,0x01,0x44,0x01,0x44,0x01,0x44,0x00,0xC8,0x00,0x00},/*"e",69*/
{0x00,0x00,0x01,0x04,0x01,0x04,0x0F,0xFC,0x11,0x04,0x11,0x04,0x11,0x00,0x18,0x00},/*"f",70*/
{0x00,0x00,0x00,0xD6,0x01,0x29,0x01,0x29,0x01,0x29,0x01,0xC9,0x01,0x06,0x00,0x00},/*"g",71*/
{0x10,0x04,0x1F,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04},/*"h",72*/
{0x00,0x00,0x01,0x04,0x19,0x04,0x19,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"i",73*/
{0x00,0x00,0x00,0x03,0x00,0x01,0x01,0x01,0x19,0x01,0x19,0xFE,0x00,0x00,0x00,0x00},/*"j",74*/
{0x10,0x04,0x1F,0xFC,0x00,0x24,0x00,0x40,0x01,0xB4,0x01,0x0C,0x01,0x04,0x00,0x00},/*"k",75*/
{0x00,0x00,0x10,0x04,0x10,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"l",76*/
{0x01,0x04,0x01,0xFC,0x01,0x04,0x01,0x00,0x01,0xFC,0x01,0x04,0x01,0x00,0x00,0xFC},/*"m",77*/
{0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04},/*"n",78*/
{0x00,0x00,0x00,0xF8,0x01,0x04,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0xF8,0x00,0x00},/*"o",79*/
{0x01,0x01,0x01,0xFF,0x00,0x85,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00},/*"p",80*/
{0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x01,0x05,0x01,0xFF,0x00,0x01},/*"q",81*/
{0x01,0x04,0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x04,0x01,0x00,0x01,0x80,0x00,0x00},/*"r",82*/
{0x00,0x00,0x00,0xCC,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x98,0x00,0x00},/*"s",83*/
{0x00,0x00,0x01,0x00,0x01,0x00,0x07,0xF8,0x01,0x04,0x01,0x04,0x00,0x00,0x00,0x00},/*"t",84*/
{0x01,0x00,0x01,0xF8,0x00,0x04,0x00,0x04,0x00,0x04,0x01,0x08,0x01,0xFC,0x00,0x04},/*"u",85*/
{0x01,0x00,0x01,0x80,0x01,0x70,0x00,0x0C,0x00,0x10,0x01,0x60,0x01,0x80,0x01,0x00},/*"v",86*/
{0x01,0xF0,0x01,0x0C,0x00,0x30,0x01,0xC0,0x00,0x30,0x01,0x0C,0x01,0xF0,0x01,0x00},/*"w",87*/
{0x00,0x00,0x01,0x04,0x01,0x8C,0x00,0x74,0x01,0x70,0x01,0x8C,0x01,0x04,0x00,0x00},/*"x",88*/
{0x01,0x01,0x01,0x81,0x01,0x71,0x00,0x0E,0x00,0x18,0x01,0x60,0x01,0x80,0x01,0x00},/*"y",89*/
{0x00,0x00,0x01,0x84,0x01,0x0C,0x01,0x34,0x01,0x44,0x01,0x84,0x01,0x0C,0x00,0x00},/*"z",90*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x3E,0xFC,0x40,0x02,0x40,0x02},/*"{",91*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00},/*"|",92*/
{0x00,0x00,0x40,0x02,0x40,0x02,0x3E,0xFC,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"}",93*/
{0x00,0x00,0x60,0x00,0x80,0x00,0x80,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x20,0x00},/*"~",94*/
};      
#endif
