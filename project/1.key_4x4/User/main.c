
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "MatrixKeys.h"
void MK_on_keydown(u8 row, u8 col) {
      printf("��%d�е�%d�� DOWN\r\n", (int)row, (int)col);
   
}
void MK_on_keyup(u8 row, u8 col) {
     printf("��%d�е�%d�� UP\r\n", (int)row, (int)col);
}
int main(void)
{
  systick_config();
	 u32 state=0x1ffff;
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	printf("sda2");
	MK_init();
  while(1)
		{MK_scan(&state);
			delay_1ms(1000);
  }
}


	