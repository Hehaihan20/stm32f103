
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "MatrixKeys.h"
void MK_on_keydown(u8 row, u8 col) {
      printf("第%d行第%d列 DOWN\r\n", (int)row, (int)col);
   
}
void MK_on_keyup(u8 row, u8 col) {
     printf("第%d行第%d列 UP\r\n", (int)row, (int)col);
}
int main(void)
{
  systick_config();
	 u32 state=0x1ffff;
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	printf("sda2");
	MK_init();
  while(1)
		{MK_scan(&state);
			delay_1ms(1000);
  }
}


	