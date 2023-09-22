#ifndef _SOFT_SPI_H
#define _SOFT_SPI_H


#include "stm32f10x.h"
#include "systick.h" 			  	    													  

/**
filename: soft_spi.

**/



//�����ʾ����IO�ڵ���Դ��
#define SPI_PORT GPIOA
#define SPI_MOSI GPIO_Pin_7
#define SPI_MISO GPIO_Pin_6
#define SPI_SCK  GPIO_Pin_5
#define SPI_CS   GPIO_Pin_4

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

void soft_spi_init(void);    // spiͨ��׼������ʼ��
void soft_spi_init_io(void); // ��ʼ��spiͨ���õ���io��
void soft_spi_init_mode(uint8_t spi_mode); // ��ʼ��spiͨ��ģʽ��ʱ����λ��ʱ�Ӽ���

void soft_spi_begin(void);               // ��ʼspiͨ��
void soft_spi_w_cs(uint8_t bit_value);// дƬѡcs��

uint8_t soft_spi_swap(uint8_t byte_to_send);
void soft_spi_w_sck(uint8_t bit_value);  // дʱ�ӿ�
void soft_spi_w_mosi(uint8_t bit_value);  // дMOSI��
uint8_t soft_spi_r_miso(void);    // ��MISO��

void soft_spi_end(void);

#endif