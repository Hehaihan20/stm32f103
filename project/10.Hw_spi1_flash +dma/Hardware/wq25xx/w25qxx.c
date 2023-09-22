#include "W25QXX.h"

void W25QXX_Config(void)
{ 	
	W25QXX_CS=1;			//SPI FLASH��ѡ��
	SPI1_DMA_Config();
	SPI1_Config();		   			//��ʼ��SPI
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);		//����Ϊ42Mʱ��,����ģʽ 
#ifdef W25Q256	
	u8 count=0;
	
	W25QXX_CS=0; 
	SPI_TX_BUFFER[count++]=W25X_Entry4ByteMode;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);
    W25QXX_CS=1;
#endif
}  
	
u8 W25QXX_ReadSR(void)   
{  
	u8 byte=0;  
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_ReadStatusReg;
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_DMA_Write(&byte,SPI_TX_BUFFER,count);	
	W25QXX_CS=1;	//ȡ��Ƭѡ  
	return byte;   
} 

u8 W25QXX_ReadSR_2(void)   
{  
	u8 byte=0;  
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_ReadStatusReg_2;
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_DMA_Write(&byte,SPI_TX_BUFFER,count);	
	W25QXX_CS=1;	//ȡ��Ƭѡ  
	return byte;   
} 

u8 W25QXX_ReadSR_3(void)   
{  
	u8 byte=0;  
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_ReadStatusReg_3;
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_DMA_Write(&byte,SPI_TX_BUFFER,count);	
	W25QXX_CS=1;	//ȡ��Ƭѡ  
	return byte;   
} 

//дW25QXX״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25QXX_Write_SR(u8 sr)   
{   
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������   
	SPI_TX_BUFFER[count++]=W25X_WriteStatusReg;
	SPI_TX_BUFFER[count++]=sr;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count); 
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
}   

//W25QXXдʹ��	
//��WEL��λ   
void W25QXX_Write_Enable(void)   
{
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_WriteEnable;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 
//W25QXXд��ֹ	
//��WEL����  
void W25QXX_Write_Disable(void)   
{  
	u8 count=0;
	
	W25QXX_CS=0;                            //ʹ������   
	SPI_TX_BUFFER[count++]=W25X_WriteDisable;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);   
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 		
//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
u16 W25QXX_ReadID(void)
{
	u8 count = 0;
	u16 Temp = 0;
	
	W25QXX_CS=0;				    
	SPI_TX_BUFFER[count++]=W25X_ManufactDeviceID;
	SPI_TX_BUFFER[count++]=0x00;
	SPI_TX_BUFFER[count++]=0x00;
	SPI_TX_BUFFER[count++]=0x00;
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_TX_BUFFER[count++]=0xFF;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);
	Temp = SPI_RX_BUFFER[4]<<8 | SPI_RX_BUFFER[5];  	 
	W25QXX_CS=1;				    
	return Temp;
} 

//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
	u8 count=0;
	u8 temp=0xFF; 
	
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_ReadData;
#ifdef W25Q256
	SPI_TX_BUFFER[count++]=(u8)((ReadAddr)>>24);
#endif
	SPI_TX_BUFFER[count++]=(u8)((ReadAddr)>>16);
	SPI_TX_BUFFER[count++]=(u8)((ReadAddr)>>8);
	SPI_TX_BUFFER[count++]=(u8)ReadAddr;	  
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);
	SPI_DMA_Read(pBuffer,&temp,NumByteToRead);
	W25QXX_CS=1;  				    	      
} 

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u8 count=0;
	u8 temp=0; 
	
    W25QXX_Write_Enable();                  //SET WEL 
	W25QXX_CS=0;                            //ʹ������ 
	SPI_TX_BUFFER[count++]=W25X_PageProgram;
#ifdef W25Q256
	SPI_TX_BUFFER[count++]=(u8)((WriteAddr)>>24);
#endif
	SPI_TX_BUFFER[count++]=(u8)((WriteAddr)>>16);
	SPI_TX_BUFFER[count++]=(u8)((WriteAddr)>>8);
	SPI_TX_BUFFER[count++]=(u8)WriteAddr;
	SPI_transmission(SPI_RX_BUFFER, SPI_TX_BUFFER, count);
	SPI_DMA_Write(&temp,pBuffer,NumByteToWrite);	
	W25QXX_CS=1;                            //ȡ��Ƭѡ 
	W25QXX_Wait_Busy();					   //�ȴ�д�����
} 

//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;
	
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 

//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * W25QXX_BUF;	
	
   	W25QXX_BUF=W25QXX_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;	//������ʣ��ռ�
	while(1) 
	{	
		W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			W25QXX_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
			W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д����������  

		}else W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	 
}

//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{          
	u8 count=0;
	u8 temp=0; 
	
    W25QXX_Write_Enable();                  //SET WEL 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;	//ʹ������   
	SPI_TX_BUFFER[count++]=W25X_ChipErase;
	SPI_DMA_Write(&temp,SPI_TX_BUFFER,count);
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
	W25QXX_Wait_Busy();   				   //�ȴ�оƬ��������
}  

//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ��ɽ��������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
	u8 count=0;
	u8 temp=0;
 	
 	Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0; 	//ʹ������  	
	SPI_TX_BUFFER[count++]=W25X_SectorErase;
#ifdef W25Q256
	SPI_TX_BUFFER[count++]=(u8)((Dst_Addr)>>24);
#endif
	SPI_TX_BUFFER[count++]=(u8)((Dst_Addr)>>16);
	SPI_TX_BUFFER[count++]=(u8)((Dst_Addr)>>8);
	SPI_TX_BUFFER[count++]=(u8)Dst_Addr;
	SPI_DMA_Write(&temp,SPI_TX_BUFFER,count);
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   				   //�ȴ��������
} 

//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);	// �ȴ�BUSYλ���
}

//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
	u8 count=0;
	u8 temp=0;
	
  	W25QXX_CS=0;                            //ʹ������
	SPI_TX_BUFFER[count++]=W25X_PowerDown;
	SPI_DMA_Write(&temp,SPI_TX_BUFFER,count);  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
    delay_1us(3);                               //�ȴ�TPD  
} 


void W25QXX_WAKEUP(void)   
{  
	u8 count=0;
	u8 temp=0;
	
  	W25QXX_CS=0;                            //ʹ������  
	SPI_TX_BUFFER[count++]=W25X_ReleasePowerDown;
	SPI_DMA_Write(&temp,SPI_TX_BUFFER,count); 
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
    delay_1us(3);                               //�ȴ�TRES1
}   

