#ifndef __MATRIX_KEYS__
#define __MATRIX_KEYS__

#include "stm32f10x.h"

//设置行列数
#define	ROW_NUM	4
#define	COL_NUM	5
//GPIO需要的参数
#define ROW_GPIO_RCC RCC_APB2Periph_GPIOD
#define COL_GPIO_RCC RCC_APB2Periph_GPIOD
#define ROW_GPIO	 	 GPIOD
#define COL_GPIO	   GPIOD

#define ROW1_PIN		GPIO_Pin_3
#define ROW2_PIN		GPIO_Pin_2
#define ROW3_PIN		GPIO_Pin_1
#define ROW4_PIN		GPIO_Pin_0


#define COL1_PIN  	GPIO_Pin_5
#define COL2_PIN 	 	GPIO_Pin_6
#define COL3_PIN 	 	GPIO_Pin_7
#define COL4_PIN  	GPIO_Pin_8
#define COL5_PIN  	GPIO_Pin_9




//先设置不同行按下的情况，然后扫描列的列为1的情况下就按下。
//读取COL按键电平
#define COL1        GPIO_ReadInputDataBit(COL_GPIO,COL1_PIN)
#define COL2        GPIO_ReadInputDataBit(COL_GPIO,COL2_PIN)
#define COL3        GPIO_ReadInputDataBit(COL_GPIO,COL3_PIN)
#define COL4        GPIO_ReadInputDataBit(COL_GPIO,COL4_PIN)
#define COL5        GPIO_ReadInputDataBit(COL_GPIO,COL5_PIN)
//设置ROW为高电平
#define SET_ROW1_HIGH        GPIO_WriteBit(ROW_GPIO,ROW1_PIN,Bit_SET)
#define SET_ROW2_HIGH        GPIO_WriteBit(ROW_GPIO,ROW2_PIN,Bit_SET)
#define SET_ROW3_HIGH        GPIO_WriteBit(ROW_GPIO,ROW3_PIN,Bit_SET)
#define SET_ROW4_HIGH        GPIO_WriteBit(ROW_GPIO,ROW4_PIN,Bit_SET)

//设置ROW为低电平
#define SET_ROW1_LOW        GPIO_WriteBit(ROW_GPIO,ROW1_PIN,Bit_RESET)
#define SET_ROW2_LOW        GPIO_WriteBit(ROW_GPIO,ROW2_PIN,Bit_RESET)
#define SET_ROW3_LOW        GPIO_WriteBit(ROW_GPIO,ROW3_PIN,Bit_RESET)
#define SET_ROW4_LOW        GPIO_WriteBit(ROW_GPIO,ROW4_PIN,Bit_RESET)

// 高电平
#define KEY_DOWN	0
// 低电平
#define KEY_UP		1


//// 高电平
//#define KEY_DOWN	1
//// 低电平
//#define KEY_UP		0

void MK_init();
void MK_scan(u32 *state);
	
extern void MK_on_keyup(u8 row, u8 col);
extern void MK_on_keydown(u8 row, u8 col);

#endif