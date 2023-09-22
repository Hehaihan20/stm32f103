#include "spi1_dma.h"
#include "stdio.h"

#define Rx_BFSize  (u8)20
#define Tx_BFSize  (u8)20
#define SPI1_DR_Addr ( (u32)0x4001300C )
u8 Rx_Addr[Rx_BFSize];
u8 Tx_Addr[Tx_BFSize];

/*����һ��Ҫ>=���ݽ��շ��ʹ�С*/
u8 SPI_RX_BUFFER[4096];	
u8 SPI_TX_BUFFER[4096];

void SPI1_Config(void)
{	 
	u8 count=0;
	SPI_InitTypeDef		SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 , ENABLE);
	

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ				//NSS��	�������
	
	SPI_Init(SPI1, &SPI_InitStructure);					//��ʼ��SPI1
#ifdef	SPI1_DMA
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);	//ʹ��DMA Txͨ��
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);	//ʹ��DMA Rxͨ��
#endif
	SPI_Cmd(SPI1, ENABLE);							//ʹ��SPI
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);	
	
}   

//SPI1�ٶ����ú���
//SPI�ٶ�=fAPB2/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI1->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI1,ENABLE); //ʹ��SPI1
} 
#ifdef SPI1_DMA
void SPI1_DMA_Config(void)
{	
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	/*********************  DMA_Rx  *********************/
	DMA_DeInit(DMA1_Channel2);	//DMA1 ͨ��2 SPI1_RX 
	
	DMA_InitStructure.DMA_BufferSize=Rx_BFSize; //�����������Ĵ�С
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC; 	//DMA���䷽��SRC ����Ϊ����Դ
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;			//�Ǵ洢�����洢������ģʽ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)Rx_Addr;	//���ݻ�������ַ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //�ڴ����ݿ�� ���ݿ�� 8λ
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;  		//��������ʱ���ڴ��ַ����
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal; 		//�ڴ治ѭ���ɼ�����
	DMA_InitStructure.DMA_PeripheralBaseAddr=SPI1_DR_Addr;	//SPI1 �������ַ
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //�������ݿ�� ���ݿ�� 8λ
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; 	//�����ַ�̶�����  ENABLEʱ�´η������ݵ�ַ����+1
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;		//ͨ�����ȼ�
	
	DMA_Init(DMA1_Channel2,&DMA_InitStructure);		//DMA1 ͨ��2 SPI1_RX 
	
	/*********************  DMA_Tx  *********************/
	DMA_DeInit(DMA1_Channel3);	//DMA1 ͨ��3 SPI1_TX 
	
	DMA_InitStructure.DMA_BufferSize=Tx_BFSize; //�����������Ĵ�С
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; 	//DMA���䷽��DST �ڴ���Ϊ����Դ
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;			//�Ǵ洢�����洢������ģʽ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)Tx_Addr;	//���ݻ�������ַ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //�ڴ����ݿ�� ���ݿ�� 8λ
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;  		//��������ʱ���ڴ��ַ����
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal; 		//�ڴ治ѭ���ɼ�����
	DMA_InitStructure.DMA_PeripheralBaseAddr=SPI1_DR_Addr;	//SPI1 �������ַ
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //�������ݿ�� ���ݿ�� 8λ
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; 	//�����ַ�̶�����  ENABLEʱ�´η������ݵ�ַ����+1
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;		//ͨ�����ȼ�
	
	DMA_Init(DMA1_Channel3,&DMA_InitStructure);		//DMA1 ͨ��2 SPI1_RX 
}

void SPI_transmission(u8 *rx_buf,u8 *tx_buf,u16 NumByte)
{
//	DMA_Cmd(DMA1_Channel2,DISABLE);		//�ر�DMA
//	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_SetCurrDataCounter(DMA1_Channel2,NumByte);		//�趨ͨ���ڴ���
	DMA_SetCurrDataCounter(DMA1_Channel3,NumByte);
	
	DMA1_Channel2->CCR |= (1<<7);			//�򿪵�ַ����
	DMA1_Channel3->CCR |= (1<<7);
	
	DMA1_Channel2->CMAR =(u32)rx_buf;
	DMA1_Channel3->CMAR =(u32)tx_buf;
	
	SPI1->DR;		//���SPI DR�Ĵ���
	
	while((SPI1->SR&1<<1)==0);	//�ȴ����
	
	DMA_Cmd(DMA1_Channel2,ENABLE);	//����DMA
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);	//�ȴ��������
	while( DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);
	
	DMA_Cmd(DMA1_Channel2,DISABLE);		//�ر�DMA
	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC3);		//��մ������flag
	DMA_ClearFlag(DMA1_FLAG_TC2);
}
	
void SPI_DMA_Read(u8 *rx_buf,u8 *tx_data,u16 NumByte)
{
//	DMA_Cmd(DMA1_Channel2,DISABLE);
//	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_SetCurrDataCounter(DMA1_Channel2,NumByte);
	DMA_SetCurrDataCounter(DMA1_Channel3,NumByte);
		
	DMA1_Channel3->CCR &= ~(1<<7);
	
	DMA1_Channel2->CMAR =(u32)rx_buf;
	DMA1_Channel3->CMAR =(u32)tx_data;
	
	SPI1->DR;
	
	while((SPI1->SR&1<<1)==0);
	
	DMA_Cmd(DMA1_Channel2,ENABLE);
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);
	while( DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);
	
	DMA_Cmd(DMA1_Channel2,DISABLE);
	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC3);
	DMA_ClearFlag(DMA1_FLAG_TC2);
}

void SPI_DMA_Write(u8 *rx_data,u8 *tx_buf,u16 NumByte)
{
//	DMA_Cmd(DMA1_Channel2,DISABLE);
//	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_SetCurrDataCounter(DMA1_Channel2,NumByte);
	DMA_SetCurrDataCounter(DMA1_Channel3,NumByte);
	
	DMA1_Channel2->CCR &= ~(1<<7);	
	
	DMA1_Channel2->CMAR =(u32)rx_data;
	DMA1_Channel3->CMAR =(u32)tx_buf;
	
	SPI1->DR;
	
	while((SPI1->SR&1<<1)==0);
	
	DMA_Cmd(DMA1_Channel2,ENABLE);
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);
	while( DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);
	
	DMA_Cmd(DMA1_Channel2,DISABLE);
	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC3);
	DMA_ClearFlag(DMA1_FLAG_TC2);
}
#else
	u8 SPI1_ReadWriteByte(u8 TxData)
	{
		while((SPI1->SR&1<<1)==0);
		
		SPI1->DR=TxData;
		
		while((SPI1->SR&1<<0)==0);
		
		return SPI1->DR;
	}
#endif


