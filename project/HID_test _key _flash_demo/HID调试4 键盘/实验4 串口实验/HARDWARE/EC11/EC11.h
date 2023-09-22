#ifndef EC11_H

#define EC11_H
#include "stm32f10x.h"
#include "sys.h"
#include "oled.h"

#define  once_angel         18//1个定位点转的度数
#define  point              20//一圈有20个定位点
#define  real_point	      5  //实际转几个定位点产生事件 
#define EC11_GPIO_RCC 		RCC_APB2Periph_GPIOC
#define EC11_GPIO  				GPIOC
#define EC11_A_PIN  			GPIO_Pin_6
#define EC11_B_PIN  			GPIO_Pin_1

#define EC11_EXTI_A_RCC     GPIO_PortSourceGPIOC
#define EC11_EXTI_A_PIN     GPIO_PinSource6

#define EC11_EXTI_B__RCC     GPIO_PortSourceGPIOC
#define EC11_EXTI_B_PIN      GPIO_PinSource1

#define EC11_A_EXTI_Line    EXTI_Line6         //中断线选择
#define EC11_B_EXTI_Line    EXTI_Line1         //中断线选择
#define EXTI_A_EXTI_Mode    EXTI_Trigger_Falling //下降沿触发      
#define EXTI_B_EXTI_Mode    EXTI_Trigger_Falling//下降沿触发

#define HIGH              1
#define LOW               0

#define CW                1//顺时针
#define CWW               0//逆时针


#define EC11_A_STATE      GPIO_ReadInputDataBit(EC11_GPIO,EC11_A_PIN)
#define EC11_B_STATE      GPIO_ReadInputDataBit(EC11_GPIO,EC11_B_PIN)
void EXTIX_Init(void);
uint16_t get_angel(void);
uint8_t get_refreshScreen(void); // 是否需要刷新屏幕

void flag_to_false(void);//把刷新标志位置为0

#endif