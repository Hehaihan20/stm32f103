
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "w25qxx.h"
#include "spi_soft.h"

int main(void)
{
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	w25qxx_init();
	uint8_t read_buffer[12];
	uint8_t write_buffer[] = "W25Q64_TEST";
	//w25qxx_write_enable();
  w25qxx_write(write_buffer, 0x100000,12);
	//w25qxx_erase_chip();
	w25qxx_read(read_buffer, 0x100000 ,12);
	printf("read_buffer=%s\r\n",read_buffer);
 
	  printf("W25QXX_ReadID=%d\r\n",W25QXX_ReadID());
	while(1)
		{
	
  }
}


	