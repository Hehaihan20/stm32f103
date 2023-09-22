#ifndef W25QXX_H
#define W25QXX_H
#include "spi1_dma.h"
#include "stm32f10x.h"
/*�������W25Q256����������define*/		
//#define W25Q256
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define W25QXX_CS PAout(4)

#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 
#define W25X_Entry4ByteMode 	0xB7
#define W25X_Exit4ByteMode 		0xE9
#define W25X_ReadStatusReg_2	0x35 
#define W25X_WriteStatusReg_2	0x31 
#define W25X_ReadStatusReg_3	0x15 
#define W25X_WriteStatusReg_3	0x11



void W25QXX_Config(void);
u16  W25QXX_ReadID(void);  	    		//��ȡFLASH ID
u8	 W25QXX_ReadSR(void);        		//��ȡ״̬�Ĵ��� 
void W25QXX_Write_SR(u8 sr);  			//д״̬�Ĵ���
void W25QXX_Write_Enable(void);  		//дʹ�� 
void W25QXX_Write_Disable(void);		//д����
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
void W25QXX_Erase_Sector(u32 Dst_Addr);	//��������
void W25QXX_Wait_Busy(void);           	//�ȴ�����
void W25QXX_PowerDown(void);        	//�������ģʽ
void W25QXX_WAKEUP(void);				//����
u8 W25QXX_ReadSR_2(void);
void W25QXX_Write_SR_2(u8 sr);
u8 W25QXX_ReadSR_3(void);

#endif