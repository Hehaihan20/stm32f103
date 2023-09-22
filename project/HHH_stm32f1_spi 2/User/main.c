
#include "stm32f10x.h"
#include <stdio.h>
#include "systick.h"
#include "Usart0.h"


#include "oled.h"
#include "bmp.h"

#include "SPI0.h"


void Usart0_recv(uint8_t* data, uint32_t len) {
	printf("recv: %s\r\n", data);
}

int main(void)
{
    systick_config();
		Usart0_init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响
    SPI0_init();

    OLED_42_Init();
    //OLED_42_Refresh_ALL();
//    printf("123");
    while(1)
    {  
        int i=0;
//        for(int i=0; i<80; i+=10) {
//            OLED_42_Clear();

            OLED_42_ShowPicture(0,0,72,40,BMP1,1,0);
			      OLED_42_ShowPicture(0,0,29,27,BMP2,1,1);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,2);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,3);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,4);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,5);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,6);
						OLED_42_ShowPicture(0,0,29,27,BMP2,1,7);
						OLED_42_ShowPicture(0,0,70,22,BMP3,1,8);
			      OLED_42_ShowPicture(0,0,70,27,BMP4,1,9);
						OLED_42_ShowPicture(0,0,70,22,BMP3,1,10);
			      OLED_42_ShowPicture(2,3,70,22,BMP5,1,11);
					//OLED_42_Refresh_ALL();
           // OLED_42_Refresh_Single(0);
//            delay_1ms(200);
//        }
    }
}

