
#include "Usart0.h"
#include "oled.h"
#include "oled_92.h"
#include "Menu.h"
#include "Utikites.h"
#include "save_pic.h"
#include "EC35.h"
void Usart0_recv(uint8_t* data, uint32_t len) {
	printf("recv: %s\r\n", data);
	printf("W25QXX_ReadID=%d\r\n",W25QXX_ReadID());
	
}

int main(void)
{ 
	  u32 state=0xfffff;
    systick_config();
		Usart0_init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��
    
	  Utikites_Init();
    OLED_42_Init();
    OLED_92_Init();
    //OLED_42_Refresh_ALL();
     //printf("123");

		Menu_init();
	EXTIX_Init();
        Menu1();
    while(1)
    {  
     MK_scan(&state);
    }
}

