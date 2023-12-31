//#include "hw_config.h"
//#include "usb_lib.h"
//#include "usb_pwr.h"
//#include "delay.h"
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include  "usart.h"
#include "MatrixKeys.h"
#include "EC11.h"
#include "oled.h"
#include "bmp.h"
#include "w25qxx.h"
#include "Addr.h"
__IO uint8_t PrevXferComplete = 1;
__IO uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
void MK_on_keyup(u8 row, u8 col) {

    buffer[0] = 0x00;
    buffer[2] = 0x00;
    USB_SIL_Write(ENDP1,buffer,sizeof(buffer));
    SetEPTxValid(ENDP1);
    // printf("第%d行第%d列 UP\r\n", (int)row, (int)col);
}

void MK_on_keydown(u8 row, u8 col) {
    //  printf("第%d行第%d列 DOWN\r\n", (int)row, (int)col);
    if(col==0) {
        if(get_angel()==0) {
            if(row==0) {
                buffer[0] = 0x00; //0
                buffer[2] = 0x04; //a
                USB_SIL_Write(ENDP1,buffer,sizeof(buffer));
                SetEPTxValid(ENDP1);
            }
            if(row==1) {
                buffer[0] = 0x00; //0
                buffer[2] = 0x08; //b
                USB_SIL_Write(ENDP1,buffer,sizeof(buffer));
                SetEPTxValid(ENDP1);
            }
         
            }

   if(get_angel()==18) {
                if(row==0) {
                    buffer[0] = 0x00; //0
                    buffer[2] = 0x10; //a
                    USB_SIL_Write(ENDP1,buffer,sizeof(buffer));
                    SetEPTxValid(ENDP1);
                }
                if(row==1) {
                    buffer[0] = 0x00; //0
                    buffer[2] = 0x08; //b
                    USB_SIL_Write(ENDP1,buffer,sizeof(buffer));
                    SetEPTxValid(ENDP1);
                }


        }
}
}
 uint8_t read_data[sizeof(BMP1)];
 uint8_t write_data[] = "Hello, W25QXX!";
 uint8_t write2_data[] = "skjdhasjkdhsajk!";
        int main(void)
        {
					FILE *fopen(const char *pathname, const char *mode);
            u16 state=0xffff;

            NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
            uart_init(115200);
            delay_init();
            OLED_Init();
            Set_System();
            USB_Interrupts_Config();

            Set_USBClock();

            USB_Init();
            MK_init();
						W25QXX_Init();
            EXTIX_Init();
            OLED_Clear();
						W25QXX_Write_Enable();
						printf("start---- \r\n");
						W25QXX_Write(write_data, MENU_0_PIC0_ADDR	,sizeof(write_data));
						W25QXX_Write(write2_data, MENU_0_PIC1_ADDR	,sizeof(write2_data));
					
						W25QXX_Read(read_data,MENU_0_PIC0_ADDR,sizeof(write_data));
					  printf("read_data= %s\r\n",read_data);
						W25QXX_Read(read_data,MENU_0_PIC1_ADDR,sizeof(write2_data));
					  printf("read_data= %s\r\n",read_data);				







					//	printf("W25QXX_ReadID= %d\r\n",W25QXX_ReadID());
					
            while(1)
            {

                MK_scan(&state);
                if(get_refreshScreen()) {
                    OLED_Clear();
                    if(get_angel()==0)
                    {
                        OLED_ShowPicture(0,0,128,32,read_data,1,0);

                    }
                    else if(get_angel()==18)
                    {
                        OLED_ShowPicture(10,1,29,32,BMP2,1,0);
                    }
                    else if(get_angel()==36)
                    {
                        OLED_ShowPicture(0,0,128,32,BMP1,1,0);
                    }
                    else if(get_angel()==54)
                    {
                        OLED_ShowPicture(22,1,29,32,BMP2,1,0);
                    }


                    flag_to_false();//如果位置写反，此时还没有置为0，而又发生中断，就会clear。
                    //但是上一次数据还没来得及更新，所以数据就会脏,从而发生错误。《——大概猜想，具体要用调试工具分析一下。
                    delay_ms(600);
                }

            }
        }


