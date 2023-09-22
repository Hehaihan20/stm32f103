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


#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

void usart_init(u32 bound);



char* get_data(void);
#endif 