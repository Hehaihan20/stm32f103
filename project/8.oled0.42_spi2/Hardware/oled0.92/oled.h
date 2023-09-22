#ifndef __OLED_H
#define __OLED_H

#include "systick.h"

#include "stm32f10x.h"
//-----------------OLED�˿ڶ���----------------
//Ӳ��spi 1
#define OLED_42_RCC				      RCC_APB2Periph_GPIOB
#define OLED_42_RES_RCC			    RCC_APB2Periph_GPIOD

#define OLED_42_CS_RCC					 RCC_APB2Periph_GPIOE	 //ʹ��D�˿�ʱ��
#define OLED_42_SPI_RCC         RCC_APB1Periph_SPI2

#define OLED_SPI_GPIO				    GPIOB
#define OLED_CS_GPIO				    GPIOE
#define OLED_42_RES_GPIO				GPIOD
#define OLED_042_SPI 						SPI2
#define OLED_042_DMA_FLAG 		  DMA2_FLAG_TC2
#define OLED_042_DMA						DMA2_Channel2
#define OLED_SPI_SCK_PIN        GPIO_Pin_13//SCL

#define OLED_SPI_MOSI_PIN			  GPIO_Pin_15//SDA
#define OLED_SPI_RES_PIN   		  GPIO_Pin_11//RES
#define OLED_SPI_DC_PIN		  	  GPIO_Pin_10//DC
#define OLED_SPI_CS1_PIN   		  GPIO_Pin_15//CS

//SCL
#define OLED_SCL_Clr() GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
#define OLED_SCL_Set() GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_SCK_PIN)
//SDA
#define OLED_SDA_Clr() GPIO_ResetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)//MOSI���豸���
#define OLED_SDA_Set() GPIO_SetBits(OLED_SPI_GPIO,OLED_SPI_MOSI_PIN)

//CS
#define OLED_CS_Clr()  GPIO_ResetBits(OLED_CS_GPIO,OLED_SPI_CS1_PIN)//
#define OLED_CS_Set()  GPIO_SetBits(OLED_CS_GPIO,OLED_SPI_CS1_PIN)//
//RES
#define OLED_RES_Clr() GPIO_ResetBits(OLED_42_RES_GPIO,OLED_SPI_RES_PIN)//�ӵ͵�ƽ��λ
#define OLED_RES_Set() GPIO_SetBits(OLED_42_RES_GPIO,OLED_SPI_RES_PIN)
//DC
#define OLED_DC_Clr()  GPIO_ResetBits(OLED_42_RES_GPIO,OLED_SPI_DC_PIN)//���� ����
#define OLED_DC_Set()  GPIO_SetBits(OLED_42_RES_GPIO,OLED_SPI_DC_PIN)//����

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//cs�߼�

#define OLED_NUM 1
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} CS_PinInfo;
#define OLED_CS1	OLED_SPI_GPIO,OLED_SPI_CS1_PIN
// ����Ƭѡ������Ϣ����
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

