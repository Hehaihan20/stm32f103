
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "oled.h"

#include "bmp.h"
int main(void)
{
    systick_config();
	  usart_init(115200);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  printf("sda");
	  OLED_Init();	
		OLED_Clear();
		//OLED_ShowPicture(1,1,128,32,BMP1,1,0);
		OLED_ShowPicture(10,1,29,32,BMP2,1,0);
		
  while(1)
		{
//			for(int i=0;i<80;i+=10){
//				OLED_Clear();
//			  OLED_ShowPicture(i,1,29,32,BMP2,1,0);
//				delay_1ms(200);
//			}
  }
}


	