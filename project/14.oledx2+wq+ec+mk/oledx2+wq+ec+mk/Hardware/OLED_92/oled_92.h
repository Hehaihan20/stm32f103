#ifndef __OLED_92_H
#define __OLED_92_H

#include "stdlib.h"
#include "stm32f10x.h"
#include "systick.h"
//-----------------OLED端口定义----------------
#define OLED_92_NUM 						5
#define OLED_92_SPI_RCC					RCC_APB2Periph_GPIOB
#define OLED_92_SPI_GPIO				GPIOB
#define OLED_92_SPI_SCK_PIN    	GPIO_Pin_3//SCL

#define OLED_92_SPI_MOSI_PIN		GPIO_Pin_5//SDA
#define OLED_92_SPI_DC_PIN		  GPIO_Pin_11//DC
#define OLED_92_SPI_RES_PIN    	GPIO_Pin_10//RES
/**********CS******/
//GROUP_1

#define OLED_92_SPI_CS_GROUP_1_RCC				RCC_APB2Periph_GPIOA
#define OLED_92_SPI_CS_GROUP_1_GPIO				GPIOA
#define OLED_92_SPI_CS0_PIN    						GPIO_Pin_1//CS
#define OLED_92_SPI_CS1_PIN    						GPIO_Pin_2//CS
#define OLED_92_SPI_CS2_PIN     					GPIO_Pin_3//CS
//GROUP_2
#define OLED_92_SPI_CS_GROUP_2_RCC				RCC_APB2Periph_GPIOB
#define OLED_92_SPI_CS_GROUP_2_GPIO				GPIOB

#define OLED_92_SPI_CS3_PIN     GPIO_Pin_8//CS
#define OLED_92_SPI_CS4_PIN     GPIO_Pin_9//CS


#define OLED_92_SW_PIN       		GPIO_Pin_0//SW
//SCL
#define OLED_92_SCL_Clr() GPIO_ResetBits(OLED_92_SPI_GPIO,OLED_92_SPI_SCK_PIN)
#define OLED_92_SCL_Set() GPIO_SetBits(OLED_92_SPI_GPIO,OLED_92_SPI_SCK_PIN)
//SDA
#define OLED_92_SDA_Clr() GPIO_ResetBits(OLED_92_SPI_GPIO,OLED_92_SPI_MOSI_PIN)//MOSI主设备输出
#define OLED_92_SDA_Set() GPIO_SetBits(OLED_92_SPI_GPIO,OLED_92_SPI_MOSI_PIN)
//RES
#define OLED_92_RES_Clr() GPIO_ResetBits(OLED_92_SPI_GPIO,OLED_92_SPI_RES_PIN)//接低电平复位
#define OLED_92_RES_Set() GPIO_SetBits(OLED_92_SPI_GPIO,OLED_92_SPI_RES_PIN)
//DC
#define OLED_92_DC_Clr()  GPIO_ResetBits(OLED_92_SPI_GPIO,OLED_92_SPI_DC_PIN)//命令 拉低
#define OLED_92_DC_Set()  GPIO_SetBits(OLED_92_SPI_GPIO,OLED_92_SPI_DC_PIN)//数据
////CS
//#define OLED_92_CS_Clr()  GPIO_ResetBits(OLED_92_SPI_GPIO,OLED_92_SPI_CS1_PIN)//
//#define OLED_92_CS_Set()  GPIO_SetBits(OLED_92_SPI_GPIO,OLED_92_SPI_CS1_PIN)//


#define OLED_92_CS_0 							OLED_92_SPI_CS_GROUP_1_GPIO,OLED_92_SPI_CS0_PIN
#define OLED_92_CS_1 							OLED_92_SPI_CS_GROUP_1_GPIO,OLED_92_SPI_CS1_PIN
#define OLED_92_CS_2 							OLED_92_SPI_CS_GROUP_1_GPIO,OLED_92_SPI_CS2_PIN
#define OLED_92_CS_3 							OLED_92_SPI_CS_GROUP_2_GPIO,OLED_92_SPI_CS3_PIN
#define OLED_92_CS_4 							OLED_92_SPI_CS_GROUP_2_GPIO,OLED_92_SPI_CS4_PIN
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} CS_92_PinInfo;


static CS_92_PinInfo oled_92_cs_pins [OLED_92_NUM]=
{
    {OLED_92_CS_0}, //OLED_CS0
    {OLED_92_CS_1}, //OLED_CS1
    {OLED_92_CS_2}, //OLED_CS2
    {OLED_92_CS_3}, //OLED_CS3
    {OLED_92_CS_4}, //OLED_CS4
};


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);

void OLED_WR_Byte(u8 dat,u8 mode);

void OLED_92_Refresh(void);
void OLED_92_Clear(void);

void OLED_92_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode,u8 index);
void OLED_92_Init(void);

#endif

