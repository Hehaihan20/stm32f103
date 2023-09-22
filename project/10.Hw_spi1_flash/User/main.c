
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "w25qxx.h"

 uint8_t read_data[128];
 uint8_t write_data[] = "Hello, W25QXX!";
int main(void)
{
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	W25QXX_Init();
	W25QXX_Write_Enable();
	W25QXX_Write(write_data, 0x100000,3);
	W25QXX_Read(read_data, 0x100000,3);

	  printf("W25QXX_ReadID=%d\r\n",W25QXX_ReadID());
  while(1)
		{
	   	
  }
}


	