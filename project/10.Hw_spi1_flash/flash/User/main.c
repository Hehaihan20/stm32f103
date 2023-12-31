
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	W25QXX_Init();
	W25QXX_Write_Enable();
	W25QXX_Write(write_data,0,3);
	W25QXX_Read(write_data,0,3);
	    
  while(1)
		{
			printf("W25QXX_ReadID= %d\r\n",W25QXX_ReadID());
  }
}


	