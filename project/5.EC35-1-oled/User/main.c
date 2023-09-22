
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "EC35.h"
#include "oled.h"

#include "bmp.h"
int main(void)
{
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	printf("sda");
	EXTIX_Init();
	
	
	  OLED_Init();	
		OLED_Clear();
		//OLED_ShowPicture(1,1,128,32,BMP1,1,0);
		OLED_ShowPicture(10,1,29,32,BMP2,1,0);
  while(1)
		{
	   if(get_refreshScreen()) {
            OLED_Clear();
            if(get_angel()==0)
            {
                OLED_ShowPicture(0,0,128,32,BMP1,1,0);

            }
            else if(get_angel()==18)
            {
                OLED_ShowPicture(10,1,29,32,BMP2,1,0);
            }
            else if(get_angel()==36)
            {
                OLED_ShowPicture(0,0,128,32,BMP1,1,0);
            }
            else if(get_angel()==54)
            {
                OLED_ShowPicture(22,1,29,32,BMP2,1,0);
            }


            flag_to_false();//���λ��д������ʱ��û����Ϊ0�����ַ����жϣ��ͻ�clear��
            //������һ�����ݻ�û���ü����£��������ݾͻ���,�Ӷ��������󡣡�������Ų��룬����Ҫ�õ��Թ��߷���һ�¡�
            delay_1ms(600);
        }
  }
}


	