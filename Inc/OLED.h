#ifndef __OLED_H__
#define __OLED_H__
#include "stdint.h"

#define	Brightness	0xCF
#define X_WIDTH 		   128//0.96(SSD1306) is 128 ，1.30（SH1106） is 132
#define Y_WIDTH 		64

#define IIC_SPI_TYPE 		0    //1 is the spi,0 is the i2c

#define CHIP_IS_SSD1306     1   //1 - SSD1306; 0 -- SH1106

#define INCH				0  // 0 is 0.96 inch & 0.91 inch ,1 is 0.49 inch  (This Macro definition is for IIC with SSD1306)

void OLED_WrDat(uint8_t dat);
void OLED_WrCmd(uint8_t cmd);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char bmp_dat);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_Init(void);
//void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
//void OLED_Char(unsigned char x, unsigned char y, unsigned char ch);
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif
