#ifndef __OLED_H
#define __OLED_H

#include "systick.h"

#include "stm32f10x.h"
//-----------------OLED端口定义----------------
//硬件spi 3
#define OLED_96_SPI_GPIO_RCC				RCC_APB2Periph_GPIOB
#define OLED_96_CS_RCC			    		RCC_APB2Periph_GPIOA
#define OLED_96_SPI_RCC					   	RCC_APB1Periph_SPI3
#define OLED_96_DAM_RCC							RCC_AHBPeriph_DMA2
#define OLED_96_SPI  			  				SPI3

#define OLED_96_DMA 						    DMA2_Channel2
#define OLED_96_CS_GPIO							GPIOA
#define OLED_SPI_GPIO								GPIOB
#define OLED_SPI_SCK_PIN   			 		GPIO_Pin_5//SCL
#define OLED_SPI_MOSI_PIN						GPIO_Pin_3//SDA

#define OLED_SPI_RES_PIN   					GPIO_Pin_10//RES
#define OLED_SPI_DC_PIN		  				GPIO_Pin_11//DC
#define OLED_96_CS1_PIN     				GPIO_Pin_1//CS

#define OLED_SW_PIN        				 	GPIO_Pin_0//CS
//SCL
#define OLED_SCL_Clr() 							GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
#define OLED_SCL_Set()							GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
//SDA							
#define OLED_SDA_Clr()							GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)//MOSI主设备输出
#define OLED_SDA_Set()							GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)
//RES							
#define OLED_RES_Clr()							GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_RES_PIN)//接低电平复位
#define OLED_RES_Set()							GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_RES_PIN)
//DC							
#define OLED_DC_Clr() 							GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_DC_PIN)//命令 拉低
#define OLED_DC_Set() 							GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_DC_PIN)//数据
//CS							
#define OLED_CS_Clr() 							GPIO_ResetBits(OLED_96_CS_GPIO,OLED_96_CS1_PIN)//
#define OLED_CS_Set() 							GPIO_SetBits(OLED_96_CS_GPIO,OLED_96_CS1_PIN)//
#define OLED_SW_OPEN  							GPIO_SetBits(OLED_SPI_GPIO,OLED_SW_PIN)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//cs逻辑

#define OLED_NUM 1
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} CS_PinInfo;
#define OLED_CS1	OLED_SPI_GPIO,OLED_96_CS1_PIN
// 定义片选引脚信息数组
static CS_PinInfo oled_cs_pins[OLED_NUM] = {
    {OLED_CS1}, // OLED_CS1

};

void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_CMD(u8 dat);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);

void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode,u8 index);
void OLED_Init(void);

#endif

