#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "systick.h"
#include	"sys.h"

/*�����ʹ��SPI_DMA����������define*/
#define	SPI1_DMA

#ifdef	SPI1_DMA
extern u8 SPI_RX_BUFFER[4096];
extern u8 SPI_TX_BUFFER[4096];
#endif

void SPI1_Config(void);			 //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
	
void SPI1_DMA_Config(void);
void SPI_transmission(u8 *rx_buf,u8 *tx_buf,u16 NumByte);
void SPI_DMA_Read(u8 *rx_buf,u8 *tx_data,u16 NumByte);
void SPI_DMA_Write(u8 *rx_data,u8 *tx_buf,u16 NumByte);
#endif


