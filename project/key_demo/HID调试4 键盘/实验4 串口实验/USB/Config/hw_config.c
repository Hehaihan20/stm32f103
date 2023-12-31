/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"


///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
//ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

///* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
	// GPIO_InitTypeDef  GPIO_InitStructure;  // omit
  
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32xxx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32xxx.c file
     */
	
	/* Enable the PWR clock */
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);  // omit
	
	/* Set all the GPIOs to AIN */
	// GPIO_AINConfig();  // omit
	
  /* Configure the EXTI line 18 connected internally to the USB IP ************/  //开启usb唤醒事件
  EXTI_ClearITPendingBit(EXTI_Line18);
  EXTI_InitStructure.EXTI_Line = EXTI_Line18;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //设置输入电路为上升沿请求中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
	/* Select USBCLK source */
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
	/* Enable the USB clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

///*******************************************************************************
//* Function Name  : GPIO_AINConfig
//* Description    : Configures all IOs as AIN to reduce the power consumption.
//* Input          : None.
//* Output         : None.
//* Return         : None.
//*******************************************************************************/
//#ifndef STM32F37X 
//void GPIO_AINConfig(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)|| defined(STM32F30X)
//  /* Enable all GPIOs Clock*/
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, ENABLE);  
//#else 
//  /* Enable all GPIOs Clock*/
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, ENABLE);
//#endif /* STM32L1XX_XD */

//  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
//#if defined(STM32F30X)
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//#else
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//#endif
//  //GPIO_Init(GPIOA, &GPIO_InitStructure); // Some GPIOA pins are used for JTAG and USB
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
//  GPIO_Init(GPIOE, &GPIO_InitStructure);

//#if defined (USE_STM32L152_EVAL)
//  GPIO_Init(GPIOH, &GPIO_InitStructure);
//#endif /* USE_STM32L152_EVAL */  

//#if defined (USE_STM32L152D_EVAL)
//  GPIO_Init(GPIOF, &GPIO_InitStructure);
//  GPIO_Init(GPIOG, &GPIO_InitStructure);
//  GPIO_Init(GPIOH, &GPIO_InitStructure);
//#endif /* USE_STM32L152D_EVAL */ 
//  
//#if defined (USE_STM3210E_EVAL)
//  GPIO_Init(GPIOF, &GPIO_InitStructure);
//  GPIO_Init(GPIOG, &GPIO_InitStructure);
//#endif /* USE_STM3210E_EVAL */

//}
//#endif /*STM32F37X*/
///*******************************************************************************
//* Function Name  : Enter_LowPowerMode.
//* Description    : Power-off system clocks and power while entering suspend mode.
//* Input          : None.
//* Output         : None.
//* Return         : None.
//*******************************************************************************/
//void Enter_LowPowerMode(void)
//{
//  /* Set the device state to suspend */
//  bDeviceState = SUSPENDED;

//  /* Clear EXTI Line18 pending bit */
//  EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE);

//  /* Request to enter STOP mode with regulator in low power mode */
//  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
//}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;
  
  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
  
  /*Enable SystemCoreClock*/
  SystemInit();
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : Configures the USB interrupts.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USB interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; //USB低优先级或者CAN接收0中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn; //USB通过外部中断线唤醒中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config(FunctionalState NewState)
{
	//if (NewState != DISABLE) {
	//	GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	//}
	//else {
	//	GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	//}
}


/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
	uint32_t Device_Serial0, Device_Serial1, Device_Serial2;
	
	Device_Serial0 = *(uint32_t*)ID1;
	Device_Serial1 = *(uint32_t*)ID2;
	Device_Serial2 = *(uint32_t*)ID3;
	
	Device_Serial0 += Device_Serial2;
	
	if (Device_Serial0 != 0) {
		IntToUnicode (Device_Serial0, &Joystick_StringSerial[2] , 8);
		IntToUnicode (Device_Serial1, &Joystick_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
	uint8_t idx = 0;
	
	for( idx = 0 ; idx < len ; idx ++) {
		if( ((value >> 28)) < 0xA ) {
			pbuf[ 2* idx] = (value >> 28) + '0';
		}
		else {
			pbuf[2* idx] = (value >> 28) + 'A' - 10;
		}
		
		value = value << 4;
		
		pbuf[ 2* idx + 1] = 0;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
