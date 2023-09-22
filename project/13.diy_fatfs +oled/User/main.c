
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "w25qxx.h"
#include <stdio.h>
#include <string.h>
#include "bmp.h"
#include "oled.h"

 uint8_t read_data[128];
 uint8_t write_data[] = "Hello, W25QXX!";
int main(void)
{
  systick_config();
	usart_init(115200);

	W25QXX_Init();
	OLED_Init();
  W25QXX_Read(read_data,0,3);
	OLED_Clear();
	printf("W25QXX_ReadID= %d\r\n",W25QXX_ReadID());
	printf("read_data= %s\r\n",read_data);
	
  while(1)
		{
	   for(int i=0;i<120;i+=10){
				OLED_Clear();
			  OLED_ShowPicture(i,1,29,32,BMP2,1,0);
				//OLED_Refresh();
				delay_1ms(200);
			}
	  
		}
  }



	