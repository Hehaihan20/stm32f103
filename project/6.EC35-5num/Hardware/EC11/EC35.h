#ifndef EC35_H

#define EC35_H
#include "stm32f10x.h"
#include "systick.h"
#include "usart.h"
#include "string.h"
#define  once_angel         18//1个定位点转的度数
#define  point              20//一圈有20个定位点
#define  real_point	      	5//实际转几个定位点产生事件 


#define EC35_GPIO_RCC 		   RCC_APB2Periph_GPIOC
#define EC35_GPIO  				   GPIOC
#define EC35_EXTI_RCC        GPIO_PortSourceGPIOC
#define EXTI_A_EXTI_Mode    EXTI_Trigger_Falling //下降沿触发      
#define EXTI_B_EXTI_Mode    EXTI_Trigger_Falling//下降沿触发 


#define EC35_12_EXTI_IRQn		 EXTI9_5_IRQn
#define EC35_34_EXTI_IRQn		 EXTI15_10_IRQn

/*****GROUP-0****/
#define EC35_A0_PIN  			   GPIO_Pin_0
#define EC35_B0_PIN  			   GPIO_Pin_1
#define EC35_EXTI_A0_PIN     GPIO_PinSource0
#define EC35_EXTI_B0_PIN     GPIO_PinSource1
#define EC35_A0_EXTI_Line    EXTI_Line0         //中断线选择
#define EC35_B0_EXTI_Line    EXTI_Line1         //中断线选择
#define EC35_A0_STATE     	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_A0_PIN)
#define EC35_B0_STATE      	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_B0_PIN)
#define EC35_A0_EXTI_IRQn		 EXTI0_IRQn
#define EC35_B0_EXTI_IRQn    EXTI1_IRQn



/*****GROUP-1****/

#define EC35_A1_PIN  			   GPIO_Pin_5
#define EC35_B1_PIN  			   GPIO_Pin_6
#define EC35_EXTI_A1_PIN     GPIO_PinSource5
#define EC35_EXTI_B1_PIN     GPIO_PinSource6
#define EC35_A1_EXTI_Line    EXTI_Line5         //中断线选择
#define EC35_B1_EXTI_Line    EXTI_Line6         //中断线选择
#define EC35_A1_STATE     	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_A1_PIN)
#define EC35_B1_STATE      	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_B1_PIN)

/*****GROUP-2****/
#define EC35_A2_PIN  			   GPIO_Pin_7
#define EC35_B2_PIN  			   GPIO_Pin_8
#define EC35_EXTI_A2_PIN     GPIO_PinSource7
#define EC35_EXTI_B2_PIN     GPIO_PinSource8
#define EC35_A2_EXTI_Line    EXTI_Line7         //中断线选择
#define EC35_B2_EXTI_Line    EXTI_Line8         //中断线选择
#define EC35_A2_STATE     	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_A2_PIN)
#define EC35_B2_STATE      	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_B2_PIN)

/*****GROUP-3****/
#define EC35_A3_PIN  			   GPIO_Pin_10
#define EC35_B3_PIN  			   GPIO_Pin_11
#define EC35_EXTI_A3_PIN     GPIO_PinSource10
#define EC35_EXTI_B3_PIN     GPIO_PinSource11
#define EC35_A3_EXTI_Line    EXTI_Line10         //中断线选择
#define EC35_B3_EXTI_Line    EXTI_Line11         //中断线选择
#define EC35_A3_STATE     	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_A3_PIN)
#define EC35_B3_STATE      	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_B3_PIN)



/*****GROUP-4****/
#define EC35_A4_PIN  			   GPIO_Pin_12
#define EC35_B4_PIN  			   GPIO_Pin_13
#define EC35_EXTI_A4_PIN     GPIO_PinSource12
#define EC35_EXTI_B4_PIN     GPIO_PinSource13
#define EC35_A4_EXTI_Line    EXTI_Line12         //中断线选择
#define EC35_B4_EXTI_Line    EXTI_Line13         //中断线选择
#define EC35_A4_STATE     	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_A4_PIN)
#define EC35_B4_STATE      	 GPIO_ReadInputDataBit(EC35_GPIO,EC35_B4_PIN)




extern void EC1_CW_ACTIVE();
extern void EC1_CWW_ACTIVE();
extern void EC2_CW_ACTIVE();
extern void EC2_CWW_ACTIVE();
extern void EC3_CW_ACTIVE();
extern void EC3_CWW_ACTIVE();
extern void EC4_CW_ACTIVE();
extern void EC4_CWW_ACTIVE();


#define HIGH                1
#define LOW                 0

#define CW                  1//顺时针
#define CWW                 0//逆时针



void EXTIX_Init(void);
uint16_t get_angel(void);
uint8_t get_refreshScreen(void); // 是否需要刷新屏幕
void flag_to_false(void);//把刷新标志位置为0




#endif