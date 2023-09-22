#ifndef EC35_H

#define EC35_H
#include "stm32f10x.h"
#include "systick.h"
#include "usart.h"
#include "string.h"
#define  once_angel         18//1个定位点转的度数
#define  point              20//一圈有20个定位点
#define  real_point	      5  //实际转几个定位点产生事件 
#define EC35_GPIO_RCC 		RCC_APB2Periph_GPIOC
#define EC35_GPIO  				GPIOC
#define EC35_A_PIN  			GPIO_Pin_12
#define EC35_B_PIN  			GPIO_Pin_13
					
#define EC35_EXTI_A_RCC     GPIO_PortSourceGPIOC
#define EC35_EXTI_A_PIN     GPIO_PinSource12
					
#define EC35_EXTI_B__RCC     GPIO_PortSourceGPIOC
#define EC35_EXTI_B_PIN      GPIO_PinSource13

#define EC35_A_EXTI_Line    EXTI_Line12        //中断线选择
#define EC35_B_EXTI_Line    EXTI_Line13        //中断线选择
#define EXTI_A_EXTI_Mode    EXTI_Trigger_Falling //下降沿触发      
#define EXTI_B_EXTI_Mode    EXTI_Trigger_Falling//下降沿触发 

#define HIGH              1
#define LOW               0

#define CW                1//顺时针
#define CWW               0//逆时针


#define EC35_A_STATE      GPIO_ReadInputDataBit(EC35_GPIO,EC35_A_PIN)
#define EC35_B_STATE      GPIO_ReadInputDataBit(EC35_GPIO,EC35_B_PIN)
void EXTIX_Init(void);
uint16_t get_angel(void);
uint8_t get_refreshScreen(void); // 是否需要刷新屏幕

void flag_to_false(void);//把刷新标志位置为0

#endif