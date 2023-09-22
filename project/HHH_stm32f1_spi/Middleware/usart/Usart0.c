#include "Usart0.h"

#if USART0_RX_ENABLE
#define USART_RECEIVE_LENGTH  1024
//串口接收缓冲区大小
uint8_t g_recv_buff[USART_RECEIVE_LENGTH];   // 接收缓冲区
//接收到字符存放的位置
uint32_t g_recv_length = 0;
#endif

//1. 初始化
void Usart0_init() {
		uint32_t usartx_tx_rcu = RCC_APB2Periph_GPIOA;
    GPIO_TypeDef *usartx_tx_port = GPIOA;
    uint32_t usartx_tx_pin = GPIO_Pin_9;

    uint32_t usartx_rx_rcu = RCC_APB2Periph_GPIOA;
    GPIO_TypeDef *usartx_rx_port = GPIOA;
    uint32_t usartx_rx_pin = GPIO_Pin_10;

    uint32_t usartx_rcu = RCC_APB2Periph_USART1;
    USART_TypeDef* usartx = USART1;

    /***************** GPIO *********************/
    GPIO_InitTypeDef  GPIO_InitStructure;
    // TX
    RCC_APB2PeriphClockCmd(usartx_tx_rcu, ENABLE);
		GPIO_InitStructure.GPIO_Pin = usartx_tx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(usartx_tx_port, &GPIO_InitStructure);

    // RX
    RCC_APB2PeriphClockCmd(usartx_rx_rcu, ENABLE);
		GPIO_InitStructure.GPIO_Pin = usartx_rx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(usartx_rx_port, &GPIO_InitStructure);

    /***************** USART ********************/
    // 串口时钟
    RCC_APB2PeriphClockCmd(usartx_rcu, ENABLE);
    // 复位
    USART_DeInit(usartx);

    USART_InitTypeDef param;
    USART_StructInit(&param);
    param.USART_BaudRate = 115200;
    USART_Init(usartx, &param);

#if USART0_RX_ENABLE
    NVIC_InitTypeDef irq;
    irq.NVIC_IRQChannel = USART1_IRQn;
    irq.NVIC_IRQChannelPreemptionPriority = 2;
    irq.NVIC_IRQChannelSubPriority = 2;
    irq.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&irq);
    // 中断接收
    USART_ITConfig(usartx, USART_IT_RXNE, ENABLE);
    USART_ITConfig(usartx, USART_IT_IDLE, ENABLE);
#endif

    USART_Cmd(usartx, ENABLE);
}

//2. 发送
void Usart0_send_byte(uint8_t data) {
    //通过USART发送
    USART_SendData(USART1, data);
    //判断缓冲区是否已经空了
    //FlagStatus state = usart_flag_get(USART_NUM,USART_FLAG_TBE);
    while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}
void Usart0_send_string(char* data) {

    while(data && *data) {
        Usart0_send_byte((uint8_t)(*data));
        data++;
    }
}

// printf打印功能
int fputc(int ch, FILE *f){
	Usart0_send_byte((uint8_t)ch);
	return ch;
}


#if USART0_RX_ENABLE
// 名称不能随意改，串口0的中断，就是这个名字

void USART1_IRQHandler() {

    if ((USART_GetITStatus(USART1, USART_IT_RXNE)) == SET) {
        uint16_t value = USART_ReceiveData(USART1);
        g_recv_buff[g_recv_length] = value;
        g_recv_length++;
    }
    if (USART_GetITStatus(USART1, USART_IT_IDLE) == SET) {
        //读取缓冲区,清空缓冲区
        USART_ReceiveData(USART1);
        g_recv_buff[g_recv_length] = '\0';

        // TODO: g_recv_buff为接收的数据，g_recv_length为接收的长度
       // printf("recv: %s", g_recv_buff);
				Usart0_recv(g_recv_buff, g_recv_length);

        g_recv_length = 0;
    }

}
#endif