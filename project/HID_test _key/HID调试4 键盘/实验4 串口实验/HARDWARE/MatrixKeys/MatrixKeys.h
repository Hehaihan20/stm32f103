#ifndef __MATRIX_KEYS__
#define __MATRIX_KEYS__

#include "stm32f10x.h"

//����������
#define	ROW_NUM	4
#define	COL_NUM	4
//GPIO��Ҫ�Ĳ���
#define ROW_GPIO_RCC RCC_APB2Periph_GPIOE
#define COL_GPIO_RCC RCC_APB2Periph_GPIOB
#define ROW_GPIO	 	 GPIOE
#define COL_GPIO	   GPIOB

#define ROW1_PIN		GPIO_Pin_0
#define ROW2_PIN		GPIO_Pin_1
#define ROW3_PIN		GPIO_Pin_2
#define ROW4_PIN		GPIO_Pin_4


#define COL1_PIN  	GPIO_Pin_9
#define COL2_PIN 	 	GPIO_Pin_8
#define COL3_PIN 	 	GPIO_Pin_7
#define COL4_PIN  	GPIO_Pin_4

//�����ò�ͬ�а��µ������Ȼ��ɨ���е���Ϊ1������¾Ͱ��¡�
//��ȡCOL������ƽ
#define COL1        GPIO_ReadInputDataBit(COL_GPIO,COL1_PIN)
#define COL2        GPIO_ReadInputDataBit(COL_GPIO,COL2_PIN)
#define COL3        GPIO_ReadInputDataBit(COL_GPIO,COL3_PIN)
#define COL4        GPIO_ReadInputDataBit(COL_GPIO,COL4_PIN)

//����ROWΪ�ߵ�ƽ
#define SET_ROW1_HIGH        GPIO_WriteBit(ROW_GPIO,ROW1_PIN,Bit_SET)
#define SET_ROW2_HIGH        GPIO_WriteBit(ROW_GPIO,ROW2_PIN,Bit_SET)
#define SET_ROW3_HIGH        GPIO_WriteBit(ROW_GPIO,ROW3_PIN,Bit_SET)
#define SET_ROW4_HIGH        GPIO_WriteBit(ROW_GPIO,ROW4_PIN,Bit_SET)

//����ROWΪ�͵�ƽ
#define SET_ROW1_LOW        GPIO_WriteBit(ROW_GPIO,ROW1_PIN,Bit_RESET)
#define SET_ROW2_LOW        GPIO_WriteBit(ROW_GPIO,ROW2_PIN,Bit_RESET)
#define SET_ROW3_LOW        GPIO_WriteBit(ROW_GPIO,ROW3_PIN,Bit_RESET)
#define SET_ROW4_LOW        GPIO_WriteBit(ROW_GPIO,ROW4_PIN,Bit_RESET)

// �ߵ�ƽ
#define KEY_DOWN	0
// �͵�ƽ
#define KEY_UP		1


//// �ߵ�ƽ
//#define KEY_DOWN	1
//// �͵�ƽ
//#define KEY_UP		0

void MK_init();
void MK_scan(u16 *state);
	
extern void MK_on_keyup(u8 row, u8 col);
extern void MK_on_keydown(u8 row, u8 col);

#endif