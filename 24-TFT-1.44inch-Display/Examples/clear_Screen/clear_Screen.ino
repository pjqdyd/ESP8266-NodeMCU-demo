#include <SPI.h>

#define X_MAX_PIXEL 128
#define Y_MAX_PIXEL 128

#define LCD_CS  D1
#define LCD_RST D2
#define LCD_RS  D3

#define LCD_CS_SET (digitalWrite(LCD_CS,HIGH))
#define LCD_RST_SET (digitalWrite(LCD_RST,HIGH))
#define LCD_RS_SET (digitalWrite(LCD_RS,HIGH))

#define LCD_CS_CLR (digitalWrite(LCD_CS,LOW))
#define LCD_RST_CLR (digitalWrite(LCD_RST,LOW))
#define LCD_RS_CLR (digitalWrite(LCD_RS,LOW))

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE  0x001F

void spi_init(void)
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4); // 4 MHz (half speed)
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); 
}

void spi_write(unsigned char data)
{
  SPI.transfer(data);
}

void Lcd_WriteIndex(unsigned char index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   spi_write(index);
   LCD_CS_SET;
}

void Lcd_WriteData(unsigned char data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   spi_write(data);
   LCD_CS_SET; 
}

void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{    
  Lcd_WriteIndex(0x2a);
  Lcd_WriteData(0x00);
  Lcd_WriteData(x_start+2);
  Lcd_WriteData(0x00);
  Lcd_WriteData(x_end+2);

  Lcd_WriteIndex(0x2b);
  Lcd_WriteData(0x00);
  Lcd_WriteData(y_start+3);
  Lcd_WriteData(0x00);
  Lcd_WriteData(y_end+3);  
  Lcd_WriteIndex(0x2c);
}

void Lcd_Reset(void)
{
  LCD_RST_CLR;
  delay(100);
  LCD_RST_SET;
  delay(50);
}

void Lcd_WriteReg(unsigned char index,unsigned char data)
{
  Lcd_WriteIndex(index);
  Lcd_WriteData(data);
}

void LCD_WriteData_16Bit(unsigned int data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   spi_write(data>>8); 
   spi_write(data);    
   LCD_CS_SET; 
}

void Lcd_Clear(unsigned int color)               
{  
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    { 
      LCD_WriteData_16Bit(color);
    }   
}

void Lcd_Init(void)
{  
  Lcd_Reset(); //Reset before LCD Init.
  //LCD Init For 1.44Inch LCD Panel with ST7735R.
  Lcd_WriteIndex(0x11);//Sleep exit 
  delay(120);
    
  //ST7735R Frame Rate
  Lcd_WriteIndex(0xB1); 
  Lcd_WriteData(0x01); 
  Lcd_WriteData(0x2C); 
  Lcd_WriteData(0x2D); 

  Lcd_WriteIndex(0xB2); 
  Lcd_WriteData(0x01); 
  Lcd_WriteData(0x2C); 
  Lcd_WriteData(0x2D); 

  Lcd_WriteIndex(0xB3); 
  Lcd_WriteData(0x01); 
  Lcd_WriteData(0x2C); 
  Lcd_WriteData(0x2D); 
  Lcd_WriteData(0x01); 
  Lcd_WriteData(0x2C); 
  Lcd_WriteData(0x2D); 
  
  Lcd_WriteIndex(0xB4); //Column inversion 
  Lcd_WriteData(0x07); 
  
  //ST7735R Power Sequence
  Lcd_WriteIndex(0xC0); 
  Lcd_WriteData(0xA2); 
  Lcd_WriteData(0x02); 
  Lcd_WriteData(0x84); 
  Lcd_WriteIndex(0xC1); 
  Lcd_WriteData(0xC5); 

  Lcd_WriteIndex(0xC2); 
  Lcd_WriteData(0x0A); 
  Lcd_WriteData(0x00); 

  Lcd_WriteIndex(0xC3); 
  Lcd_WriteData(0x8A); 
  Lcd_WriteData(0x2A); 
  Lcd_WriteIndex(0xC4); 
  Lcd_WriteData(0x8A); 
  Lcd_WriteData(0xEE); 
  
  Lcd_WriteIndex(0xC5); //VCOM 
  Lcd_WriteData(0x0E); 
  
  Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
  Lcd_WriteData(0xC8); 
  
  //ST7735R Gamma Sequence
  Lcd_WriteIndex(0xe0); 
  Lcd_WriteData(0x0f); 
  Lcd_WriteData(0x1a); 
  Lcd_WriteData(0x0f); 
  Lcd_WriteData(0x18); 
  Lcd_WriteData(0x2f); 
  Lcd_WriteData(0x28); 
  Lcd_WriteData(0x20); 
  Lcd_WriteData(0x22); 
  Lcd_WriteData(0x1f); 
  Lcd_WriteData(0x1b); 
  Lcd_WriteData(0x23); 
  Lcd_WriteData(0x37); 
  Lcd_WriteData(0x00);  
  Lcd_WriteData(0x07); 
  Lcd_WriteData(0x02); 
  Lcd_WriteData(0x10); 

  Lcd_WriteIndex(0xe1); 
  Lcd_WriteData(0x0f); 
  Lcd_WriteData(0x1b); 
  Lcd_WriteData(0x0f); 
  Lcd_WriteData(0x17); 
  Lcd_WriteData(0x33); 
  Lcd_WriteData(0x2c); 
  Lcd_WriteData(0x29); 
  Lcd_WriteData(0x2e); 
  Lcd_WriteData(0x30); 
  Lcd_WriteData(0x30); 
  Lcd_WriteData(0x39); 
  Lcd_WriteData(0x3f); 
  Lcd_WriteData(0x00); 
  Lcd_WriteData(0x07); 
  Lcd_WriteData(0x03); 
  Lcd_WriteData(0x10);  
  
  Lcd_WriteIndex(0x2a);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x7f);

  Lcd_WriteIndex(0x2b);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x9f);
  
  Lcd_WriteIndex(0xF0); //Enable test command  
  Lcd_WriteData(0x01); 
  Lcd_WriteIndex(0xF6); //Disable ram power save mode 
  Lcd_WriteData(0x00); 
  
  Lcd_WriteIndex(0x3A); //65k mode 
  Lcd_WriteData(0x05); 
  
  Lcd_WriteIndex(0x29);//Display on  
}

void pin_init(void)
{
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_RST, OUTPUT);
    pinMode(LCD_RS, OUTPUT); 
    LCD_CS_SET;
    LCD_RST_SET;
    LCD_RS_SET;
}

void setup() 
{
    Serial.begin(9600);
    spi_init();
    pin_init();
    Lcd_Init();
    Lcd_Clear(BLACK); 
}

void loop() 
{    
   Lcd_Clear(WHITE);
   delay(1000); 
   Lcd_Clear(BLACK);
    delay(1000); 
   Lcd_Clear(RED); 
   delay(1000); 
   Lcd_Clear(GREEN);
   delay(1000);  
   Lcd_Clear(BLUE); 
  delay(1000); 
}
