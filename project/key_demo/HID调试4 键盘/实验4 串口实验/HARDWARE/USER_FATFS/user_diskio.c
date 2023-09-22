

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0

#endif
#include <string.h>
#include "ff.h"
#include "stm32f10x.h"
#include "diskio.h"
#include "user_diskio.h"
static volatile DSTATUS Stat = STA_NOINIT;

#define PAGE_SIZE       4096	//256
#define SECTOR_SIZE     4096
#define SECTOR_COUNT		256	//200
#define BLOCK_SIZE			65536
#define FLASH_PAGES_PER_SECTOR	SECTOR_SIZE/PAGE_SIZE

FATFS fs;
// 文件读取变量
FIL file;		
// 结果变量
FRESULT f_res;
// 读取字节数的指针
UINT bw;

// 缓冲数组
static __IO BYTE ReadBuffer[500];    
// 临时存储数组
uint8_t temp[500];
//extern void pic_data_copy(uint8_t key);
//extern void KEY_data_copy(uint8_t key);

// 从文本文件里读按键定义
//extern volatile uint8_t Menu_level;
  uint8_t Menu_level;
//extern volatile uint8_t key_set[30][201];
volatile uint8_t key_buff[7000];
volatile uint8_t key_line;
volatile uint8_t key_set_value;
volatile uint32_t file_size;
// 记录路径
char USER_Path[4];

void mount_disk(void)
{
	/*
		fat文件系统描述的一个结构体,需要用户进行分配,然后会被记录在全局的FATFS[]这个数组中
		USER_Path -> 物理磁盘
		0 -> 表示不挂载，1 -> 表示立马挂载
	*/
   f_res = f_mount(&fs, USER_Path, 0);
   printf("f_mount = %d\n",f_res);
}
u8 TEXT_Buffer[4096];
void format_disk(void)
{
 
	 f_res=f_mkfs(USER_Path,0,TEXT_Buffer,4096);
  //printf("f_mkfs = %d\n",f_res);
}

void create_file(void)
{
  uint8_t res;
  f_res = f_open(&file, "0:/test.txt", FA_OPEN_ALWAYS | FA_WRITE);
	//printf("f_open = %d\n",f_res);	
  //f_res = f_write(&file, WriteBuffer, sizeof(WriteBuffer), &bw);
	//printf("f_write = %d\n",f_res);	
  f_res = f_close(&file);
}

// 读取文件
void read_file(void)
{
	uint16_t i,k;
 
	//从bin文件里读取图片
//	f_res = f_open(&file, "0:/menu_1/lock.bin", FA_READ);
//	f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
	
//	for(k=0; k<360; k++)	
//	{
//		//printf("%c",ReadBuffer[k]);
//		work[k] = ReadBuffer[k];	//锁图片测试
//	}	
//	for(k=0; k<360; k++)	
//	{
//		printf("%c",work[k]);
//	}	
	
	// 20个按键依次读取
	for(i=0; i<20; i++)
	{
		switch(i)
		{
			// 第一个层级按键
			case 0:
					//f_res = f_mount(&fs, USER_Path, 0);
					// 通过菜单读取， 对应的菜单图片文件
					switch(Menu_level)
					{
						case 0:
								// 打开文件，成功后读取
								f_res = f_open(&file, "0:/menu_1/pic_1.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_1.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_1.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_1.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_1.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_1.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_1.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_1.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_1.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_1.bin", FA_READ);							
								break;						
					}	
					// 上一布菜单读取成功后， 读取配置文件
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{										
							temp[k] = ReadBuffer[k];		
							//printf("%c",temp[k]);													
						}	

						//pic_data_copy(0);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 1:			
					//f_res = f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_2.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_2.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_2.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_2.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_2.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_2.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_2.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_2.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_2.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_2.bin", FA_READ);							
								break;						
					}	
					// 文件打开状态
					if(f_res == RES_OK)
					{
						/*
							文件指针
							字符缓冲指针
							缓冲数组大小
							读取字节数的指针
						*/
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw); 
						
						for(k=0; k<360; k++)	
						{
							// 存入缓冲数组的数据
							temp[k] = ReadBuffer[k];		
						}	
						// 读取第一层要显示的图片
					//	pic_data_copy(1);
					}
					// 关闭文件
					f_res = f_close(&file);
					
					break;
					
			case 2:
					//f_res = f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_3.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_3.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_3.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_3.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_3.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_3.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_3.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_3.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_3.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_3.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}	
						
					//	pic_data_copy(2);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 3:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_4.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_4.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_4.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_4.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_4.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_4.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_4.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_4.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_4.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_4.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];		
						}	
						
					//	pic_data_copy(3);
					}
					
					f_res = f_close(&file);
					
					break;
			
			case 4:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_5.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_5.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_5.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_5.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_5.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_5.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_5.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_5.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_5.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_5.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];
						}		
						
					//	pic_data_copy(4);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 5:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_6.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_6.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_6.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_6.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_6.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_6.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_6.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_6.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_6.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_6.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];
						}	

						//pic_data_copy(5);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 6:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_7.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_7.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_7.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_7.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_7.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_7.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_7.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_7.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_7.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_7.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		
						
						//pic_data_copy(6);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 7:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_8.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_8.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_8.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_8.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_8.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_8.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_8.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_8.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_8.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_8.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		
						
					//	pic_data_copy(7);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 8:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_9.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_9.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_9.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_9.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_9.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_9.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_9.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_9.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_9.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_9.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		

						//pic_data_copy(8);						
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 9:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_10.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_10.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_10.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_10.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_10.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_10.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_10.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_10.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_10.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_10.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		

						//pic_data_copy(9);
					}
					
					f_res = f_close(&file);
					
					break;
			
			case 10:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_11.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_11.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_11.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_11.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_11.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_11.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_11.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_11.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_11.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_11.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		
						
					//	pic_data_copy(10);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 11:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_12.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_12.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_12.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_12.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_12.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_12.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_12.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_12.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_12.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_12.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];		
						}

						//pic_data_copy(11);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 12:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_13.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_13.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_13.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_13.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_13.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_13.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_13.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_13.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_13.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_13.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];
						}	
						
						//pic_data_copy(12);						
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 13:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_14.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_14.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_14.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_14.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_14.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_14.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_14.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_14.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_14.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_14.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}		
						
					//	pic_data_copy(13);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 14:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_15.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_15.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_15.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_15.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_15.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_15.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_15.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_15.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_15.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_15.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}	

					//	pic_data_copy(14);
					}
					
					f_res = f_close(&file);
					char aa[12] = "234";
					strncat(aa,"1231", 3);
					
					break;
					
			case 15:
					//f_mount(&fs, USER_Path, 0);
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_16.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_16.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_16.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_16.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_16.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_16.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_16.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_16.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_16.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_16.bin", FA_READ);							
								break;						
					}
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];
						}	

					//	pic_data_copy(15);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 16:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_17.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_17.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_17.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_17.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_17.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_17.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_17.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_17.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_17.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_17.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}	

						//pic_data_copy(16);							
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 17:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_18.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_18.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_18.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_18.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_18.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_18.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_18.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_18.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_18.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_18.bin", FA_READ);							
								break;						
					}	
					
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];		
						}

						//pic_data_copy(17);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 18:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_19.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_19.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_19.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_19.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_19.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_19.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_19.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_19.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_19.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_19.bin", FA_READ);							
								break;
					}
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)
						{
							temp[k] = ReadBuffer[k];	
						}	

					//	pic_data_copy(18);
					}
					
					f_res = f_close(&file);
					
					break;
					
			case 19:
					//f_mount(&fs, USER_Path, 0);
			
					switch(Menu_level)
					{
						case 0:
								f_res = f_open(&file, "0:/menu_1/pic_20.bin", FA_READ);											
								break;
						case 1:
								f_res = f_open(&file, "0:/menu_2/pic_20.bin", FA_READ);	
								break;
						case 2:
								f_res = f_open(&file, "0:/menu_3/pic_20.bin", FA_READ);					
								break;
						case 3:
								f_res = f_open(&file, "0:/menu_4/pic_20.bin", FA_READ);
								break;
						case 4:
								f_res = f_open(&file, "0:/menu_5/pic_20.bin", FA_READ);
								break;
						case 5:
								f_res = f_open(&file, "0:/menu_6/pic_20.bin", FA_READ);
								break;
						case 6:
								f_res = f_open(&file, "0:/menu_7/pic_20.bin", FA_READ);		
								break;
						case 7:
								f_res = f_open(&file, "0:/menu_8/pic_20.bin", FA_READ);
								break;
						case 8:
								f_res = f_open(&file, "0:/menu_9/pic_20.bin", FA_READ);
								break;
						case 9:
								f_res = f_open(&file, "0:/menu_10/pic_20.bin", FA_READ);							
								break;
					}
					if(f_res == RES_OK)
					{
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
						
						for(k=0; k<360; k++)	
						{
							temp[k] = ReadBuffer[k];	
						}
						
					//	pic_data_copy(19); 
					}
					
					f_res = f_close(&file);
					
					break;
		}
		
		//f_res = f_close(&file);
	}
	
	//从文本文件里读取按键定义值
	switch(Menu_level)
	{
		case 0:
			f_res = f_open(&file, "0:/menu_1/key_1.txt", FA_READ);
			break;
		case 1:
			f_res = f_open(&file, "0:/menu_2/key_2.txt", FA_READ);
			break;
		case 2:
			f_res = f_open(&file, "0:/menu_3/key_3.txt", FA_READ);
			break;
		case 3:
			f_res = f_open(&file, "0:/menu_4/key_4.txt", FA_READ);
			break;
		case 4:
			f_res = f_open(&file, "0:/menu_5/key_5.txt", FA_READ);
			break;
		case 5:
			f_res = f_open(&file, "0:/menu_6/key_6.txt", FA_READ);
			break;
		case 6:
			f_res = f_open(&file, "0:/menu_7/key_7.txt", FA_READ);
			break;
		case 7:
			f_res = f_open(&file, "0:/menu_8/key_8.txt", FA_READ);
			break;
		case 8:
			f_res = f_open(&file, "0:/menu_9/key_9.txt", FA_READ);
			break;
		case 9:
			f_res = f_open(&file, "0:/menu_10/key_10.txt", FA_READ);
			break;
	}	
	
	//f_res = f_open(&file, "0:/key.txt", FA_READ);
	f_res = f_read(&file, key_buff, sizeof ReadBuffer, &bw);
	//file_size = f_size(&file);	printf("%d ",file_size);
	f_res = f_close(&file);
	//f_res = f_mount(NULL, USER_Path, 0);	//取消挂载 1227-
	
	for(k=0, key_line=0, key_set_value=1; key_line<20; k++,key_set_value++)
	{
		// 判断是否为回车
		if(key_buff[k] != 13)	
		{
			// 不为回车的时候，依次存入数据
			temp[key_set_value] = key_buff[k];
		}
		else	
		{	
			// 首字节保存按键的定义长度
			temp[0] = key_set_value - 1;
			//KEY_data_copy(key_line);
			// 按键的行数
			key_line++;
			// 下行的长度置零
			key_set_value = 0;
		}
	}
	
	//输出每个按键值
//	for(key_line=0, key_set_value=0; key_line<20; key_line++, key_set_value = 0)
//	{
//		while(key_set_value < (key_set[key_line][0]+1))
//		{
//			printf("%d ",key_set[key_line][key_set_value]);	
//			key_set_value++;
//		}		
//	}
	
	//进程配置 
	f_res = f_open(&file, "0:/XC.txt", FA_READ);	
	f_res = f_read(&file, key_buff, sizeof ReadBuffer, &bw);
	f_res = f_close(&file);
	
	for(k=0, key_line=20, key_set_value=1; key_line<26; k++,key_set_value++)
	{		
		if(key_buff[k] != 13)	
		{
			temp[key_set_value] = key_buff[k];
		}
		else	
		{
			temp[0] = key_set_value - 1;
		//	KEY_data_copy(key_line);
			
			key_line++;
			key_set_value = 0;
		}
	}
	
	f_res = f_mount(NULL, USER_Path, 0);	//取消挂载
}

void File_read(void)
{	
	// 读取用户设定的级菜单
	//Menu_level = FLASH_EEPROM_Read();
	// 硬件磁盘挂载
	mount_disk();
	//format_disk();
	//create_file();
	// 读取文件， 执行函数
	read_file();
}

