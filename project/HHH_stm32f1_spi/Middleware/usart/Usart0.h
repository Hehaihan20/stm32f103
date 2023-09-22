#ifndef __USART0_H__
#define __USART0_H__

#include "stm32f10x.h"

#include <stdio.h>

#define USART0_RX_ENABLE	1

//1. 初始化
void Usart0_init();

//2. 发送
void Usart0_send_byte(uint8_t data);
void Usart0_send_string(char* data);


#if USART0_RX_ENABLE
//3. 接收
extern void Usart0_recv(uint8_t* data, uint32_t len);
#endif


#endif