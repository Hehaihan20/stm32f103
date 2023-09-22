#ifndef USART_H
#define USART_H
#include "stm32f10x.h"
#include "systick.h"
#include "stdio.h"	
#include "w25qxx.h"
#define USART1_GPIO			GPIOA
#define USART1_GPIO_RCC RCC_APB2Periph_GPIOA
#define USART1_RCC			RCC_APB2Periph_USART1
#define USART1_TX_PIN  	GPIO_Pin_9
#define UASRT1_RX_PIN		GPIO_Pin_10


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

void usart_init(u32 bound);



char* get_data(void);
#endif 