#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "systick.h"
#include	"sys.h"

/*如果不使用SPI_DMA，屏蔽下面define*/
#define	SPI1_DMA

#ifdef	SPI1_DMA
extern u8 SPI_RX_BUFFER[4096];
extern u8 SPI_TX_BUFFER[4096];
#endif

void SPI1_Config(void);			 //初始化SPI1口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI1速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1总线读写一个字节
	
void SPI1_DMA_Config(void);
void SPI_transmission(u8 *rx_buf,u8 *tx_buf,u16 NumByte);
void SPI_DMA_Read(u8 *rx_buf,u8 *tx_data,u16 NumByte);
void SPI_DMA_Write(u8 *rx_data,u8 *tx_buf,u16 NumByte);
#endif


