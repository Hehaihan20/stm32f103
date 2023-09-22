#include "usart.h"

#include <stdio.h>

#include <string.h>

void _sys_exit(int x) 
{ 
	x = x; 
}
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
#endif

void usart_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART1_GPIO_RCC|USART1_RCC, ENABLE);	//ʹ��USART1��GPIOAʱ��
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin=USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO,&GPIO_InitStructure);
	
	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin=UASRT1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);//��ʼ��GPIOA.10 
	
	//param
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����RXNE��־λ��NVIC�����

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	
	NVIC_Init(&NVIC_InitStructure);

  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    
	USART1->DR = (u8) ch;      
	return ch;
}

void USART1_IRQHandler(void){
	static uint8_t RxState = 0;//״̬����S�����գ�
	//�����̬����������ȫ�ֱ��������������ֻ���ʼ��һ��0�������˳���������Ȼ��Ч
	//��ȫ�ֱ�����ͬ���ǣ���̬����ֻ���ڱ�����ʹ��
	static uint8_t pRxPacket = 0;//ָʾ���յ���һ���ֽڣ��غ����ݣ�
	if (USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET){
		uint8_t RxData = USART_ReceiveData(USART1);//ȡ�����յ����ֽڣ�һ��һ����
		if (RxState == 0){
			if (RxData == 0xFF){//��⵽��ͷ
				RxState = 1;//������һ��״̬
				pRxPacket = 0;//�ڽ���S=1ǰ����ǰ��0
			}
		}
		else if (RxState == 1){
		//	Serial_RxPacket[pRxPacket] = RxData;//������������
			pRxPacket++;
			if (pRxPacket >=4){//���չ�4���ֽڵ��غ�����
				RxState = 2;//������һ��״̬
			}
		}
		else if (RxState == 2){
			if (RxData == 0xFE){//��⵽��β
				RxState = 0;//S��0��ʼ��һ�ֻ�
			//	Serial_RxFlag = 1;//һ�����ݰ�������ϣ���һ����־λ
			}
		}
		//����3��if����ֹ��һ��ifִ��һ��ʱ���ֶ��֦ͬʱ������ִ�й��ϡ�����if(RxState=0)ִ�е���SΪ1ʱ...
		//��else if�ɱ�֤ÿ�ν���ֻ��ѡ��һ����ִ֧�У�Ҳ����switchʵ��
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}





