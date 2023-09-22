
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"
#include "EC35.h"
void EC2_CW_ACTIVE(){

printf("EC2_CW_ACTIVE--\r\n");
}
void EC2_CWW_ACTIVE(){
printf("EC2_CWW_ACTIVE--\r\n");

}
void EC3_CW_ACTIVE(){

printf("EC3_CW_ACTIVE--\r\n");
}
void EC3_CWW_ACTIVE(){
printf("EC3_CWW_ACTIVE--\r\n");

}

void EC4_CW_ACTIVE(){

printf("EC4_CW_ACTIVE--\r\n");
}
void EC4_CWW_ACTIVE(){
printf("EC4_CWW_ACTIVE--\r\n");

}
void EC1_CW_ACTIVE(){

printf("EC1_CW_ACTIVE--\r\n");
}
void EC1_CWW_ACTIVE(){
printf("EC1_CWW_ACTIVE--\r\n");

}
int main(void)
{
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	printf("sda");
	EXTIX_Init();
  while(1)
		{
  }
}


	