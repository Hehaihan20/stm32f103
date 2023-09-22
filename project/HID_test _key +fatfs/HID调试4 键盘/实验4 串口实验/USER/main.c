//#include "hw_config.h"
//#include "usb_lib.h"
//#include "usb_pwr.h"
//#include "delay.h"
#include "ff.h"
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
#define SIZE sizeof(BMP1)
u8 TEXT_Buffer[4096];
const uint8_t WrtieBuffs[]= "FATFS_TEST";

uint8_t Buffs[4096]= {0};
FATFS fsObject;//每个设备挂在都需要一个
FIL Fil;
FRESULT res;
UINT	bW,bR;
FATFS **fs;
DWORD freeClusters;

int main(void)
{
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
 
    EXTIX_Init();
    OLED_Clear();
    W25QXX_Write_Enable();
    W25QXX_Write(BMP1,0,sizeof(BMP1));
    W25QXX_Read(read_data,0,sizeof(BMP1));

    printf("W25QXX_ReadID= %d\r\n",W25QXX_ReadID());
    printf("read_data= %s\r\n",read_data);

  res=f_mount(&fsObject,"0:",1);
    if(res!=0)
    {
        printf("f_mount=%d\n",res);
        res=f_mkfs("0:",0,TEXT_Buffer,4096);
        printf("f_mkfs=%d\n",res);//初始化以后要重新挂载
        f_mount(NULL,"0:",1);																		//取消挂载
        f_mount(&fsObject,"0:",1);
			 res=f_mount(&fsObject,"0:",1);
			 printf("f_mount=%d\n",res);
    }

    res=f_open(&Fil,"0:1.bin",FA_OPEN_ALWAYS | FA_WRITE | FA_READ);			//打开/创建文件
    printf("f_mkdir=%d\n",res);
    if(res==FR_OK)
    {
        res=f_write (&Fil,WrtieBuffs,sizeof(WrtieBuffs),&bW);				//写内容
        printf("f_write=%d bW=%d\n",res,bW);

        if(res==FR_OK)
        {
            f_lseek(&Fil,0);
            res=f_read (&Fil,Buffs,f_size(&Fil),&bR);											//读取文件内容
            printf("f_read=%d bW=%d\n",res,bR);
            if(res==FR_OK)
            {

                printf("\n内容：%s",Buffs);										//读取成功就打印
            }

        }
        f_close(&Fil);													//关闭文件
    }


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


