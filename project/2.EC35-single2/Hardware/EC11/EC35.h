#ifndef EC35_H

#define EC35_H
#include "stm32f10x.h"
#include "systick.h"
#include "usart.h"
#include "string.h"
#define  once_angel         18//1����λ��ת�Ķ���
#define  point              20//һȦ��20����λ��
#define  real_point	      5  //ʵ��ת������λ������¼� 
#define EC35_GPIO_RCC 		RCC_APB2Periph_GPIOC
#define EC35_GPIO  				GPIOC
#define EC35_A_PIN  			GPIO_Pin_12
#define EC35_B_PIN  			GPIO_Pin_13
					
#define EC35_EXTI_A_RCC     GPIO_PortSourceGPIOC
#define EC35_EXTI_A_PIN     GPIO_PinSource12
					
#define EC35_EXTI_B__RCC     GPIO_PortSourceGPIOC
#define EC35_EXTI_B_PIN      GPIO_PinSource13

#define EC35_A_EXTI_Line    EXTI_Line12        //�ж���ѡ��
#define EC35_B_EXTI_Line    EXTI_Line13        //�ж���ѡ��
#define EXTI_A_EXTI_Mode    EXTI_Trigger_Falling //�½��ش���      
#define EXTI_B_EXTI_Mode    EXTI_Trigger_Falling//�½��ش��� 

#define HIGH              1
#define LOW               0

#define CW                1//˳ʱ��
#define CWW               0//��ʱ��


#define EC35_A_STATE      GPIO_ReadInputDataBit(EC35_GPIO,EC35_A_PIN)
#define EC35_B_STATE      GPIO_ReadInputDataBit(EC35_GPIO,EC35_B_PIN)
void EXTIX_Init(void);
uint16_t get_angel(void);
uint8_t get_refreshScreen(void); // �Ƿ���Ҫˢ����Ļ

void flag_to_false(void);//��ˢ�±�־λ��Ϊ0

#endif