
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include "usart.h"


int main(void)
{
  systick_config();
	usart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	printf("sda");
  while(1)
		{
  }
}


	