
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "w25qxx.h"
#include "spi1_dma.h"

 
const u8 TEXT_Buffer[]={"abcdefg1234567!"};
//const u8 TEXT_Buffer[4096];
#define SIZE sizeof(TEXT_Buffer)
int main(void)
{
	
	u8 datatemp[SIZE];
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	W25QXX_Config();
	   printf("\r\nID:%x\r\n",W25QXX_ReadID());	
	
	printf("SR1:%x\r\n",W25QXX_ReadSR());
	
	printf("SR2:%x\r\n",W25QXX_ReadSR_2());
	
	printf("SR3:%x\r\n",W25QXX_ReadSR_3());

    W25QXX_Write((u8*)TEXT_Buffer,0,SIZE);
    delay_1ms(200);
		W25QXX_Read(datatemp,0,SIZE);
    printf("fe:%s",datatemp);

  while(1)
		{
	   	
  }
}


	