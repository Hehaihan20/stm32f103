#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	
#include "stm32f10x.h"
//-----------------OLED端口定义---------------- 

#define OLED_SPI_RCC				RCC_APB2Periph_GPIOB
#define OLED_SPI_GPIO				GPIOB
#define OLED_SPI_SCK_PIN    GPIO_Pin_3//SCL
#define OLED_SPI_DC_PIN		  GPIO_Pin_11//DC
#define OLED_SPI_MOSI_PIN		GPIO_Pin_5//SDA
#define OLED_SPI_RES_PIN    GPIO_Pin_10//RES
#define OLED_SPI_CS1_PIN     GPIO_Pin_9//CS
#define OLED_SW_PIN       GPIO_Pin_0//CS
//SCL
#define OLED_SCL_Clr() GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
#define OLED_SCL_Set() GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
//SDA
#define OLED_SDA_Clr() GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)//MOSI主设备输出
#define OLED_SDA_Set() GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)
//RES
#define OLED_RES_Clr() GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_RES_PIN)//接低电平复位
#define OLED_RES_Set() GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_RES_PIN)
//DC
#define OLED_DC_Clr()  GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_DC_PIN)//命令 拉低
#define OLED_DC_Set()  GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_DC_PIN)//数据
//CS
#define OLED_CS_Clr()  GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_CS1_PIN)//
#define OLED_CS_Set()  GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_CS1_PIN)//



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

