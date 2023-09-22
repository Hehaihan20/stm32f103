
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
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


            flag_to_false();//如果位置写反，此时还没有置为0，而又发生中断，就会clear。
            //但是上一次数据还没来得及更新，所以数据就会脏,从而发生错误。《——大概猜想，具体要用调试工具分析一下。
            delay_1ms(600);
        }
  }
}


	