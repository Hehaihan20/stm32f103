
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "w25qxx.h"
#include <stdio.h>
#include <string.h>
uint8_t RxData;
 uint8_t read_data[128];
 uint8_t write_data[] = "Hello, W25QXX!";
int main(void)
{
  systick_config();
	usart_init(115200);

	W25QXX_Init();
	
   W25QXX_Read(read_data,0,3);
	
	 //FILE* pf= fopen("test.txt", "w+");	
	printf("W25QXX_ReadID= %d\r\n",W25QXX_ReadID());
	  	printf("read_data= %s\r\n",read_data);
  while(1)
		{
	   
	  
		}
  }



	