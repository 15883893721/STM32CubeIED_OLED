
#include "OLED.h"
#include "codetab.h"
#include "main.h"
//#include "stm32l1xx_hal_i2c.h"
#include "stm32l1xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;


extern I2C_HandleTypeDef hi2c1;

#if IIC_SPI_TYPE
void OLED_WrCmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1,&cmd,sizeof(cmd),100);
	//HAL_SPI_Transmit_DMA(&hspi1, &cmd, sizeof(cmd));

}
void OLED_WrDat(uint8_t dat)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi1,&dat,sizeof(dat),100);
	//HAL_SPI_Transmit_DMA(&hspi1, &dat, sizeof(dat));
}

#else
void OLED_WrCmd(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, 1, &cmd, 1, 100);
}

void OLED_WrDat(uint8_t dat)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, 1, &dat, 1, 100);
}

#endif
void OLED_SetPos(unsigned char x, unsigned char y)
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01); 
}


void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}


void OLED_CLS(void)
{
	OLED_Fill(0x00);
}


void OLED_ON(void)
{
	OLED_WrCmd(0X8D);
	OLED_WrCmd(0X14);
	OLED_WrCmd(0XAF);
}


void OLED_Init(void)
{
  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(100);
	
#if CHIP_IS_SSD1306
	
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	
#else //1106
	
	OLED_WrCmd(0xAE);    /*display off*/
	OLED_WrCmd(0x02);    /*set lower column address*/
	OLED_WrCmd(0x10);    /*set higher column address*/
	OLED_WrCmd(0x40);    /*set display start line*/
	OLED_WrCmd(0xB0);    /*set page address*/
	OLED_WrCmd(0x81);    /*contract control*/
	OLED_WrCmd(Brightness);    /*128*/
	OLED_WrCmd(0xA1);    /*set segment remap*/
	OLED_WrCmd(0xA6);    /*normal / reverse*/
	OLED_WrCmd(0xA8);    /*multiplex ratio*/
	OLED_WrCmd(0x3F);    /*duty = 1/32*/
	OLED_WrCmd(0xad);    /*set charge pump enable*/
	OLED_WrCmd(0x8b);    /*    0x8a    ??VCC   */
	OLED_WrCmd(0x30);    /*0X30---0X33  set VPP   9V liangdu!!!!*/
	OLED_WrCmd(0xC8);    /*Com scan direction*/
	OLED_WrCmd(0xD3);    /*set display offset*/
	OLED_WrCmd(0x00);    /*   0x20  */
	OLED_WrCmd(0xD5);    /*set osc division*/
	OLED_WrCmd(0x80);    
	OLED_WrCmd(0xD9);    /*set pre-charge period*/
	OLED_WrCmd(0x1f);    /*0x22*/
	OLED_WrCmd(0xDA);    /*set COM pins*/
	OLED_WrCmd(0x12);		 //0x02 -- duanhang xianshi,0x12 -- lianxuhang xianshi!!!!!!!!!
	OLED_WrCmd(0xdb);    /*set vcomh*/
	OLED_WrCmd(0x40);     
	OLED_WrCmd(0xAF);    /*display ON*/
	
#endif
	
	OLED_Fill(0x00);
	OLED_SetPos(0,0); 	
} 


void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[10], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_WrDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_WrDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_WrDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}


void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
}


void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_WrDat(BMP[j++]);
		}
	}
}
