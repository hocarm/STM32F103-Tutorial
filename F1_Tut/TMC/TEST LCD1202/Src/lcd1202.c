#define LCD1202_ON                  (0x0F)                // Display on
#define LCD1202_OFF                 (0x0E)                // Display off
#define LCD1202_ALL                 (0x05)                // All points ON
#define LCD1202_NORMAL              (0x04)                // Normal display
#define LCD1202_NON_REVERSE         (0x06)                // Non-reverse display
#define LCD1202_REVERSE             (0x07)                // Reverse display
#define LCD1202_MODE                (0xA0)                // Display mode command identifier
#define LCD1202_NOP                 (0xE3)
#define LCD1202_CHARGE_PUMP_ON      (0x2F)
#define LCD1202_RAM_ADDR_VER_MODE   (0xAB)
#define LCD1202_RAM_ADDR_HOR_MODE   (0xAA)
#define LCD1202_CHANGE_COL_LSB      (0x00)
#define LCD1202_CHANGE_COL_MSB      (0x10)
#define LCD1202_CHANGE_ROW          (0xB0)
#define LCD1202_START_LINE          (0x40)     
#define LCD1202_MIRROR_Y            (0xC8)
#define LCD1202_MIRROR_X            (0xA1)
#define LCD1202_EXT_OSC             (0x3A)
#define LCD1202_SOFT_RESET          (0xE2)
#define LCD1202_DRIVER_READ         (0xDB)
   

#define LCD1202_FLAG_CMD            (0x00)          //Du lieu ghi vao la command
#define LCD1202_FLAG_DATA           (0x01)          //Du lieu ghi vao la data
#define LCD1202_CONTRAST            (0x82)         // Value range should be 0x80 -> 0x9F
#define LCD1202_HEIGHT                68
#define LCD1202_WIDTH                 96



#define GPIO_PORT_LCD  GPIOC
#define output_high(LCD_1202_SDA)              HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_SDA_Pin,1)
#define output_low(LCD_1202_SDA)               HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_SDA_Pin,0)
#define output_high(LCD_1202_CLK)              HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_CLK_Pin,1)
#define output_low(LCD_1202_CLK)               HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_CLK_Pin,0)
#define output_high(LCD_1202_CS)               HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_CS_Pin,1)
#define output_low(LCD_1202_CS)                HAL_GPIO_WritePin(GPIO_PORT_LCD,LCD1202_CS_Pin,0)


/******************************************************************************
   *ASCII table
******************************************************************************/

unsigned char FONT_5X7[95][5] = { 0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
                                  0x00, 0x00, 0x5F, 0x00, 0x00, // !
                                  0x00, 0x03, 0x00, 0x03, 0x00, // "
                                  0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                                  0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                                  0x43, 0x33, 0x08, 0x66, 0x61, // %
                                  0x36, 0x49, 0x55, 0x22, 0x50, // &
                                  0x00, 0x05, 0x03, 0x00, 0x00, // '
                                  0x00, 0x1C, 0x22, 0x41, 0x00, // (
                                  0x00, 0x41, 0x22, 0x1C, 0x00, // )
                                  0x14, 0x08, 0x3E, 0x08, 0x14, // *
                                  0x08, 0x08, 0x3E, 0x08, 0x08, // +
                                  0x00, 0x50, 0x30, 0x00, 0x00, // ,
                                  0x08, 0x08, 0x08, 0x08, 0x08, // -
                                  0x00, 0x60, 0x60, 0x00, 0x00, // .
                                  0x20, 0x10, 0x08, 0x04, 0x02, // /
                                  0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                                  0x00, 0x04, 0x02, 0x7F, 0x00, // 1
                                  0x42, 0x61, 0x51, 0x49, 0x46, // 2
                                  0x22, 0x41, 0x49, 0x49, 0x36, // 3
                                  0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                                  0x27, 0x45, 0x45, 0x45, 0x39, // 5
                                  0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                                  0x01, 0x01, 0x71, 0x09, 0x07, // 7
                                  0x36, 0x49, 0x49, 0x49, 0x36, // 8
                                  0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                                  0x00, 0x36, 0x36, 0x00, 0x00, // :
                                  0x00, 0x56, 0x36, 0x00, 0x00, // ;
                                  0x08, 0x14, 0x22, 0x41, 0x00, // <
                                  0x14, 0x14, 0x14, 0x14, 0x14, // =
                                  0x00, 0x41, 0x22, 0x14, 0x08, // >
                                  0x02, 0x01, 0x51, 0x09, 0x06, // ?
                                  0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                                  0x7E, 0x09, 0x09, 0x09, 0x7E, // A
                                  0x7F, 0x49, 0x49, 0x49, 0x36, // B
                                  0x3E, 0x41, 0x41, 0x41, 0x22, // C
                                  0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                                  0x7F, 0x49, 0x49, 0x49, 0x41, // E
                                  0x7F, 0x09, 0x09, 0x09, 0x01, // F
                                  0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                                  0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                                  0x00, 0x41, 0x7F, 0x41, 0x00, // I
                                  0x30, 0x40, 0x40, 0x40, 0x3F, // J
                                  0x7F, 0x08, 0x14, 0x22, 0x41, // K
                                  0x7F, 0x40, 0x40, 0x40, 0x40, // L
                                  0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                                  0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                                  0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                                  0x7F, 0x09, 0x09, 0x09, 0x06, // P
                                  0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                                  0x7F, 0x09, 0x09, 0x09, 0x76, // R
                                  0x26, 0x49, 0x49, 0x49, 0x32, // S
                                  0x01, 0x01, 0x7F, 0x01, 0x01, // T
                                  0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                                  0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                                  0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                                  0x41, 0x22, 0x1C, 0x22, 0x41, // X
                                  0x07, 0x08, 0x70, 0x08, 0x07, // Y
                                  0x61, 0x51, 0x49, 0x45, 0x43, // Z
                                  0x00, 0x7F, 0x41, 0x00, 0x00, // [
                                  0x02, 0x04, 0x08, 0x10, 0x20, // \
                                  0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                                  0x04, 0x02, 0x01, 0x02, 0x04, // ^
                                  0x40, 0x40, 0x40, 0x40, 0x40, // _
                                  0x00, 0x01, 0x02, 0x04, 0x00, // `
                                  0x20, 0x54, 0x54, 0x54, 0x78, // a
                                  0x7F, 0x44, 0x44, 0x44, 0x38, // b
                                  0x38, 0x44, 0x44, 0x44, 0x44, // c
                                  0x38, 0x44, 0x44, 0x44, 0x7F, // d
                                  0x38, 0x54, 0x54, 0x54, 0x18, // e
                                  0x04, 0x04, 0x7E, 0x05, 0x05, // f
                                  0x08, 0x54, 0x54, 0x54, 0x3C, // g
                                  0x7F, 0x08, 0x04, 0x04, 0x78, // h
                                  0x00, 0x44, 0x7D, 0x40, 0x00, // i
                                  0x20, 0x40, 0x44, 0x3D, 0x00, // j
                                  0x7F, 0x10, 0x28, 0x44, 0x00, // k
                                  0x00, 0x41, 0x7F, 0x40, 0x00, // l
                                  0x7C, 0x04, 0x78, 0x04, 0x78, // m
                                  0x7C, 0x08, 0x04, 0x04, 0x78, // n
                                  0x38, 0x44, 0x44, 0x44, 0x38, // o
                                  0x7C, 0x14, 0x14, 0x14, 0x08, // p
                                  0x08, 0x14, 0x14, 0x14, 0x7C, // q
                                  0x00, 0x7C, 0x08, 0x04, 0x04, // r
                                  0x48, 0x54, 0x54, 0x54, 0x20, // s
                                  0x04, 0x04, 0x3F, 0x44, 0x44, // t
                                  0x3C, 0x40, 0x40, 0x20, 0x7C, // u
                                  0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                                  0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                                  0x44, 0x28, 0x10, 0x28, 0x44, // x
                                  0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                                  0x44, 0x64, 0x54, 0x4C, 0x44, // z
                                  0x00, 0x08, 0x36, 0x41, 0x41, // {
                                  0x00, 0x00, 0x7F, 0x00, 0x00, // |
                                  0x41, 0x41, 0x36, 0x08, 0x00, // }
                                  0x02, 0x01, 0x02, 0x04, 0x02};// ~ 


static unsigned char    LCD1202_RAM[9][96];


/*******************************************************************************
    *Ten ham   : void LCD1202_Write(uchar_t Select_Data,uchar_t Data)
    *Noi dung  : Ghi lenh hoac du lieu vao LCD
    *Tham bien : Select_Data : Lua chon du lieu ghi vao la Data hay Command
                               Select_Data = LCD1202_FLAG_CMD  : Du lieu la Command
                               Select_Data = LCD1202_FLAG_DATA : Du lieu la Data
                 Data        : Du lieu ghi vao
    *Tra ve    : Khong
																	
																	
//                                PB0 CS
																	PB1 SDA
																	PB2 CLK
																	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,1) output_high(LCD_1202_SDA)
																	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,1) output_low(LCD_1202_SDA)
																	
********************************************************************************/                                                
void LCD1202_Write(unsigned char Select_Data, unsigned char Data)
{
   unsigned int i;
   
   if (Select_Data) 
      output_high(LCD_1202_SDA);
   else 
      output_low(LCD_1202_SDA);
   output_low(LCD_1202_CS);
   output_high(LCD_1202_CLK);
   output_low(LCD_1202_CLK);
   
   for(i = 0; i < 8; i++)
   {
      if((Data<<i) & 0x80) 
         output_high(LCD_1202_SDA);
      else 
         output_low(LCD_1202_SDA);
      output_high(LCD_1202_CLK);
      output_low(LCD_1202_CLK);
   }
   output_high(LCD_1202_CS);
}

/********************************************************************************
    *Ten ham   : void LCD1202_Gotoxy(uchar_t Col,uchar_t Row)
    *Noi dung  : Ham di chuyen con tro den vi tri (Col,Row)
    *Tham bien : Col : Cot
                 Row : Hang
    *Tra ve    : Khong
*********************************************************************************/           
void LCD1202_Gotoxy(unsigned char Col, unsigned char Row)
{
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_COL_LSB | ( Col & 0x0F));
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_COL_MSB | ((Col >> 4) & 0x07 ));
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_ROW | (Row & 0x0F));
}

/********************************************************************************
    *Ten ham   : void LCD1202_Clear(void)
    *Noi dung  : Ham xoa man hinh LCD1202
    *Tham bien : Khong
    *Tra ve    : Khong
*********************************************************************************/
void LCD1202_Clear()
{
   for(char i=0;i<9;i++)
   {
       for(char j=0;j<96;j++)
       {
           LCD1202_RAM[i][j] = 0x00;
       }
   }  
   LCD1202_Gotoxy(0,0);
}

/*******************************************************************************
    *Ten ham   : void LCD1202_Init(void)
    *Noi dung  : Ham khoi tao cho LCD1202
    *Tham bien : Khong
    *Tra ve    : Khong
********************************************************************************/    
void LCD1202_Init()
{
   output_high(LCD_1202_CS);
   output_low(LCD_1202_CLK);

   LCD1202_Write(LCD1202_FLAG_CMD, 0x20);                                      // Set voltage range
   LCD1202_Write(LCD1202_FLAG_CMD, LCD1202_CONTRAST);
   LCD1202_Write(LCD1202_FLAG_CMD, LCD1202_MODE | LCD1202_NORMAL);
   LCD1202_Write(LCD1202_FLAG_CMD, LCD1202_CHARGE_PUMP_ON);                    // Enable charge pump
   LCD1202_Write(LCD1202_FLAG_CMD, LCD1202_MODE | LCD1202_ON);                 // Display on
   LCD1202_Clear(); 
}

/********************************************************************************
    *Ten ham   : void LCD1202_DisplayAll(void)
    *Noi dung  : Ham hien thi toan bo pixel tren man hinh LCD1202
    *Tham bien : Khong
    *Tra ve    : Khong
*********************************************************************************/
void LCD1202_DisplayAll()
{
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_ON);
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_NON_REVERSE);
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_ALL);
}

/********************************************************************************
    *Ten ham   : void LCD1202_Normal(void)
    *Noi dung  : Ham cai dat trang thai Normal
    *Tham bien : Khong
    *Tra ve    : Khong
*********************************************************************************/
void LCD1202_NormalMode() 
{
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_ON);
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_NON_REVERSE);
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_MODE|LCD1202_NORMAL);
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_RAM_ADDR_VER_MODE);
}

/*******************************************************
Ten Ham  : void LCD1202_StartPage(uchar_t Page)
Noi Dung : Ham Chon Page Ghi Du Lieu 
Tham So  : Page : Page Duoc Chon 
Tra Ve   : Khong
********************************************************/
void LCD1202_StartPage(unsigned char Page)
{
    LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_ROW | (Page & 0x0F));
}

/*******************************************************
Ten Ham  : void LCD1202_StartColumn(uchar_t Column)
Noi Dung : Ham Chon Colum Dau Tien Ghi Du Lieu
Tham So  : Column : Colum Duoc Chon 
Tra Ve   : Khong
********************************************************/
void LCD1202_StartColumn(unsigned char Column)
{
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_COL_LSB | ( Column & 0x0F));
   LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_CHANGE_COL_MSB | ((Column >> 4) & 0x07 ));
}

/*******************************************************
Ten Ham  : LCD1202_StartLine(uchar_t Line)
Noi Dung : Ham Chon Line Dau Tien Ghi Du Lieu
Tham So  : Line : Line Duoc Chon 
Tra Ve   : Khong
********************************************************/
void LCD1202_StartLine(unsigned char Line)
{
    LCD1202_Write(LCD1202_FLAG_CMD,LCD1202_START_LINE | (Line & 0x3F));
}

/*******************************************************
Ten Ham  : LCD1202_RefreshRam()
Noi Dung : Thiet lap lai toan bo man hinh
Tham So  : Khong
Tra Ve   : Khong
********************************************************/
void LCD1202_RefreshRam()
{
    unsigned char i,j;
    for(i=0;i<9;i++)
    {
       LCD1202_StartPage(i);
       LCD1202_StartColumn(0x00); 
       for(j=0;j<96;j++)
       {
           LCD1202_Write(LCD1202_FLAG_DATA,LCD1202_RAM[i][j]);
       }
    }      
}

/*******************************************************
Ten Ham  : LCD1202_DrawPixel(uchar_t x ,uchar_t y ,uchar_t Color)
Noi Dung : Hien Thi 1 diem tren man hinh
Tham So  : x : Toa do hang
           y : Toa do cot
           Status : Bat /Tat 
Tra Ve   : Khong
********************************************************/
void LCD1202_DrawPixel(unsigned char x ,unsigned char y, unsigned char Status)
{
    if((x>LCD1202_HEIGHT)||(y>LCD1202_WIDTH))return;
    else
    { 
        if(Status==1)
        {
            LCD1202_RAM[x/8][y] |= (0x01 << (x%8));
        }
        else
        {
            LCD1202_RAM[x/8][y] &= ~(0x01 << (x%8));
        } 
    } 
}

/******************************************************************************
Ten Ham     :   LCD1202_DrawLine(uchar_t x1, uchar_t y1, uchar_t x2, uchar_t y2, uchar_t Color);
Noi Dung    :   Ve 1 duong thang tren LCD128X64.  
Tham Bien   :   (x1,y1) : Toa do diem dau cua duong thang.
                (x2,y2) : Toa do diem cuoi cua duong thang.
                Color=1 : Bat duong thang.
                Color=0 : Tat duong thang. 
Tra Ve      :   Khong.
*******************************************************************************/
void LCD1202_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char Color)
{
    char dy,dx;
    char Addx = 1 ,Addy = 1;
    unsigned char i=0;
    char P,Diff;
    if(x1 > x2)
    {
        dx = x1 - x2 ;
        Addx = -1;
    }
    else dx = x2 - x1; 
    if(y1 > y2)
    {
        dy = y1 - y2;
        Addy = -1;
    }
    else dy = y2 - y1; 
    if(dx >= dy)
    {
        dy*=2;
        P = dy - dx ;
        Diff = P - dx;
        for(;i<=dx;++i)
        {
            LCD1202_DrawPixel(x1,y1,Color);
            if(P<0)
            {
                P = P + dy;
                x1 = x1 + Addx;
            }
            else
            {
                P  = P + Diff; 
                x1 = x1 + Addx ;
                y1 = y1 + Addy ;
            }
        }
    } 
    else
    {
        dx*=2;
        P = dx - dy ;
        Diff = P - dy;
        for(;i<=dy;++i)
        {
            LCD1202_DrawPixel(x1,y1,Color);
            if(P<0)
            {
                P = P + dx;
                y1 = y1 + Addy;
            }
            else
            {
                P  = P + Diff; 
                x1 = x1 + Addx ;
                y1 = y1 + Addy ;
            }
        }
    }   
}

/******************************************************************************
Ten Ham     :   void LCD1202_DrawRect(uchar_t x1, uchar_t y1, uchar_t x2, uchar_t y2,uchar_t Fill, uchar_t Color);
Noi Dung    :   Ve 1 hinh chu nhat  
Tham Bien   :   (x1,y1) : Toa do dinh dau tien cua hinh chu nhat.
                (x2,y2) : Toa do dinh doi dien cua hinh chu nhat. 
                Fill=1  : To mau hinh chu nhat.
                    =0  : Khong to mau hinh chu nhat.
                Color=1 : Bat hinh chu nhat.
                     =0 : Tat hinh chu nhat.
Tra Ve      :   Khong.
*******************************************************************************/
void LCD1202_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char Fill, unsigned char Color)
{
    if(Fill==1)
    {       
        unsigned char  i,xmin,xmax,ymin,ymax;
        if(x1 < x2)                            
        {
            xmin = x1;
            xmax = x2;
        }
        else
        {
            xmin = x2;
            xmax = x1;
        }
        if(y1 < y2)                           
        {
            ymin = y1;
            ymax = y2;
        }
        else
        {
            ymin = y2;
            ymax = y1;
        }
        for(;xmin<=xmax;++xmin)
        {
            for(i=ymin;i<=ymax;++i)
            {
                LCD1202_DrawPixel(xmin,i,Color);
            }
        }
    }
    else
    {
        LCD1202_DrawLine(x1,y1,x2,y1,Color);      
        LCD1202_DrawLine(x1,y2,x2,y2,Color);
        LCD1202_DrawLine(x1,y1,x1,y2,Color);
        LCD1202_DrawLine(x2,y1,x2,y2,Color);
    }
}

/******************************************************************************
Ten Ham     :   LCD1202_DrawCircle(uchar_t x, uchar_t y, uchar_t Radius, uchar_t Fill, uchar_t Color)
Noi Dung    :   Ve 1 hinh tron   
Tham Bien   :   (x,y)   : Toa do tam hinh tron.
                Radius  : Ban kinh hinh tron. 
                Fill=1  : To mau hinh tron.
                    =0  : Khong to mau hinh tron.
                Color=1 : Bat hinh tron.
                     =0 : Tat hinh tron. 
Tra Ve      :   Khong.
*******************************************************************************/
void LCD1202_DrawCircle(unsigned char x, unsigned char y, unsigned char Radius, unsigned char Fill, unsigned char Color)
{
    signed char  a, b, P;
    a = 0;
    b = Radius;
    P = 1 - Radius;
    do
    {
        if(Fill==1)
        {
            LCD1202_DrawLine(x-a,y+b,x+a,y+b,Color);
            LCD1202_DrawLine(x-a,y-b,x+a,y-b,Color);
            LCD1202_DrawLine(x-b,y+a,x+b,y+a,Color);
            LCD1202_DrawLine(x-b,y-a,x+b,y-a,Color);
        }
        else
        {
            LCD1202_DrawPixel(a+x,b+y,Color);
            LCD1202_DrawPixel(b+x,a+y,Color);
            LCD1202_DrawPixel(x-a,b+y,Color);
            LCD1202_DrawPixel(x-b,a+y,Color);
            LCD1202_DrawPixel(b+x,y-a,Color);
            LCD1202_DrawPixel(a+x,y-b,Color);
            LCD1202_DrawPixel(x-a,y-b,Color);
            LCD1202_DrawPixel(x-b,y-a,Color);
        }

        if(P < 0) P+=3+2*a++;
        else P+=5+2*(a++ - b--);
    } 
    while(a <= b);
}

/******************************************************************************
Ten Ham     :   void LCD1202_Image(flash uchar_t *str);
Noi Dung    :   Hien thi anh  
Tham Bien   :   *str  : Du lieu so cua hinh anh
Tra Ve      :   Khong.
*******************************************************************************/
void LCD1202_Image(unsigned char *str)
{
    unsigned short i;
    LCD1202_StartPage(0);
    LCD1202_StartColumn(0);
    for(i = 0; i < 768; i++)
    {
      LCD1202_Write(LCD1202_FLAG_DATA, str[i]);
   }
}

/******************************************************************************
Noi Dung    :   LCD1202_WriteText57(uchar_t x, uchar_t y,uchar_t *Textptr, uchar_t Size, uchar_t Color);
Noi Dung    :   Viet 1 chuoi ky tu len  
Tham Bien   :   (x,y)    : Toa do ghi chu cai dau tien.
                *Textptr : Chuoi ky tu can hien thi. 
                Size     : Font cua ki tu : 1 = 5x7, 2 = 10x14, ....
                Color=1  : Hien thi.
                     =0  : Khong. 
Tra Ve      :   Khong.
*******************************************************************************/
void LCD1202_WriteText57(unsigned char x, unsigned char y, unsigned char *Textptr, unsigned char Size, unsigned char Color)
{
   unsigned char j, k, l, m;             
   char PixelData[5];                    
   unsigned char i;

   for(; *Textptr != '\0'; ++Textptr, ++y)
   {
        if(*Textptr <= '~')
        {
            for(i=0;i<5;i++)
            PixelData[i] = FONT_5X7[(*Textptr - ' ')][i];
        }        
        else
        {
            for(i=0;i<5;i++)
            PixelData[i] = FONT_5X7[0][i];
        }
        switch(*Textptr)
        {
            case '\n':
                x += 7*Size + 1;
            continue;
            case '\r':
                y = 0;
            continue;
        }

        if(y+5*Size >= LCD1202_WIDTH)      
        {
            y = 0;                         
            x += 7*Size + 1;               
        }
        for(j=0; j<5; ++j, y+=Size)       
        {
            for(k=0; k < 7; ++k)            
            {
                if(PixelData[j]&(0x01<<k))                  
                {
                    for(l=0; l < Size; ++l)   
                    {                         
                        for(m=0; m < Size; ++m)
                        {
                            LCD1202_DrawPixel(x+k*Size+l, y+m, Color); 
                        }
                    }
                }
                else
                {
                    for(l=0; l < Size; ++l)    
                    {                         
                        for(m=0; m < Size; ++m)
                        {
                            LCD1202_DrawPixel(x+k*Size+l, y+m, !Color);
                        }
                    }   
                }
            }
        }
    }
}
/*********************************************************************************
                                    THE END
                          MinhHa R&D Team - GOOD LUCK
**********************************************************************************/
