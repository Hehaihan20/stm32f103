#include "spi1_dma.h"
#include "stdio.h"

#define Rx_BFSize  (u8)20
#define Tx_BFSize  (u8)20
#define SPI1_DR_Addr ( (u32)0x4001300C )
u8 Rx_Addr[Rx_BFSize];
u8 Tx_Addr[Tx_BFSize];

/*长度一定要>=数据接收发送大小*/
u8 SPI_RX_BUFFER[4096];	
u8 SPI_TX_BUFFER[4096];

void SPI1_Config(void)
{	 
	u8 count=0;
	SPI_InitTypeDef		SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 , ENABLE);
	

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式				//NSS由	软件控制
	
	SPI_Init(SPI1, &SPI_InitStructure);					//初始化SPI1
#ifdef	SPI1_DMA
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);	//使能DMA Tx通道
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);	//使能DMA Rx通道
#endif
	SPI_Cmd(SPI1, ENABLE);							//使能SPI
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);	
	
}   

//SPI1速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI1->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); //使能SPI1
} 
#ifdef SPI1_DMA
void SPI1_DMA_Config(void)
{	
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	/*********************  DMA_Rx  *********************/
	DMA_DeInit(DMA1_Channel2);	//DMA1 通道2 SPI1_RX 
	
	DMA_InitStructure.DMA_BufferSize=Rx_BFSize; //传输数据量的大小
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC; 	//DMA传输方向，SRC 外设为数据源
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;			//非存储器到存储器传输模式
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)Rx_Addr;	//数据缓冲区地址
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //内存数据宽度 数据宽度 8位
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;  		//传输数据时候内存地址递增
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal; 		//内存不循环采集数据
	DMA_InitStructure.DMA_PeripheralBaseAddr=SPI1_DR_Addr;	//SPI1 外设基地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //外设数据宽度 数据宽度 8位
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; 	//传输地址固定不变  ENABLE时下次发送数据地址递增+1
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;		//通道优先级
	
	DMA_Init(DMA1_Channel2,&DMA_InitStructure);		//DMA1 通道2 SPI1_RX 
	
	/*********************  DMA_Tx  *********************/
	DMA_DeInit(DMA1_Channel3);	//DMA1 通道3 SPI1_TX 
	
	DMA_InitStructure.DMA_BufferSize=Tx_BFSize; //传输数据量的大小
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralDST; 	//DMA传输方向，DST 内存作为数据源
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;			//非存储器到存储器传输模式
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)Tx_Addr;	//数据缓冲区地址
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //内存数据宽度 数据宽度 8位
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;  		//传输数据时候内存地址递增
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal; 		//内存不循环采集数据
	DMA_InitStructure.DMA_PeripheralBaseAddr=SPI1_DR_Addr;	//SPI1 外设基地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //外设数据宽度 数据宽度 8位
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable; 	//传输地址固定不变  ENABLE时下次发送数据地址递增+1
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;		//通道优先级
	
	DMA_Init(DMA1_Channel3,&DMA_InitStructure);		//DMA1 通道2 SPI1_RX 
}

void SPI_transmission(u8 *rx_buf,u8 *tx_buf,u16 NumByte)
{
//	DMA_Cmd(DMA1_Channel2,DISABLE);		//关闭DMA
//	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_SetCurrDataCounter(DMA1_Channel2,NumByte);		//设定通道内存宽度
	DMA_SetCurrDataCounter(DMA1_Channel3,NumByte);
	
	DMA1_Channel2->CCR |= (1<<7);			//打开地址自增
	DMA1_Channel3->CCR |= (1<<7);
	
	DMA1_Channel2->CMAR =(u32)rx_buf;
	DMA1_Channel3->CMAR =(u32)tx_buf;
	
	SPI1->DR;		//清空SPI DR寄存器
	
	while((SPI1->SR&1<<1)==0);	//等待清除
	
	DMA_Cmd(DMA1_Channel2,ENABLE);	//开启DMA
	DMA_Cmd(DMA1_Channel3,ENABLE);
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);	//等待传输完成
	while( DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);
	
	DMA_Cmd(DMA1_Channel2,DISABLE);		//关闭DMA
	DMA_Cmd(DMA1_Channel3,DISABLE);
	
	DMA_ClearFlag(DMA1_FLAG_TC3);		//清空传输完成flag
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


