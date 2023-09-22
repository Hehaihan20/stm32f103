#include "usart.h"

#include <stdio.h>

#include <string.h>

void _sys_exit(int x) 
{ 
	x = x; 
}
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
#endif

void usart_init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART1_GPIO_RCC|USART1_RCC, ENABLE);	//使能USART1，GPIOA时钟
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin=USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO,&GPIO_InitStructure);
	
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin=UASRT1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);//初始化GPIOA.10 
	
	//param
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启RXNE标志位到NVIC的输出

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC分组
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	
	NVIC_Init(&NVIC_InitStructure);

  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    
	USART1->DR = (u8) ch;      
	return ch;
}

void USART1_IRQHandler(void){
	static uint8_t RxState = 0;//状态变量S（接收）
	//这个静态变量类似于全局变量，函数进入后只会初始化一次0，函数退出后数据仍然有效
	//与全局变量不同的是，静态变量只能在本函数使用
	static uint8_t pRxPacket = 0;//指示接收到哪一个字节（载荷数据）
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET){
		uint8_t RxData = USART_ReceiveData(USART1);//取出接收到的字节（一次一个）
		if (RxState == 0){
			if (RxData == 0xFF){//检测到包头
				RxState = 1;//进入下一个状态
				pRxPacket = 0;//在进入S=1前，提前清0
			}
		}
		else if (RxState == 1){
		//	Serial_RxPacket[pRxPacket] = RxData;//传给接收数组
			pRxPacket++;
			if (pRxPacket >=4){//接收够4个字节的载荷数据
				RxState = 2;//进入下一个状态
			}
		}
		else if (RxState == 2){
			if (RxData == 0xFE){//检测到包尾
				RxState = 0;//S清0开始下一轮回
			//	Serial_RxFlag = 1;//一个数据包接收完毕，置一个标志位
			}
		}
		//别用3个if，防止上一个if执行一半时出现多分枝同时成立，执行故障。比如if(RxState=0)执行到置S为1时...
		//用else if可保证每次进来只能选择一个分支执行，也可用switch实现
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}





