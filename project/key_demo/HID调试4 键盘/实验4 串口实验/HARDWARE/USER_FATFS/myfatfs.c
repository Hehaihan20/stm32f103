

#include "usart.h"
#include "myfatfs.h"
#include "delay.h"
FATFS fsObject;//每个设备挂在都需要一个


FIL *file;
FRESULT res;
UINT br, bw;
FILINFO fileinfo;
DIR dir;
UINT	bW,bR;
uint8_t Buffs[4096]= {0};
void fatfs_init(){
      res = f_mount(&fsObject, "0:", 1);
			printf("f_mount=%d \r\n",res);
    if (res == FR_NO_FILESYSTEM)
    {
         
         res = f_mkfs("1:", NULL, NULL, FF_MAX_SS);			
			   res = f_mount(NULL,"0:",1);
           /* 重新挂载 */
         res = f_mount(&fsObject,"0:",1);	 			
			 printf("Flash Disk Formatting...%d \r\n",res);
        if (res == FR_OK)
        {
            f_setlabel((const TCHAR *)"0:DAPTKEY");
          	printf("Flash Disk Formatting...%d \r\n",res);
        }
        else
        {
					 	printf("Flash Disk Format Error ...%d \r\n",res);
        
    
        }
        delay_ms(1000);
    }
		

}
void fatfs_write(const TCHAR* path,const uint8_t WrtieBuffs[]){
	  f_open(file,path,FA_READ|FA_CREATE_ALWAYS|FA_WRITE);
	  printf("f_open=%d\n",res);
	  res=f_write (file,WrtieBuffs,sizeof(file),&bW);			
	  printf("f_write=%d bW=%d\n",res,bW);
	  f_close(file);	
}
void fatfs_read(const TCHAR* path){
	  f_open(file,path,FA_READ);
	  res=f_read (file,Buffs,f_size(file),&bR);			
	  f_lseek(file,0);		
	  printf("\n内容：%s",Buffs);	
	  f_close(file);	
}