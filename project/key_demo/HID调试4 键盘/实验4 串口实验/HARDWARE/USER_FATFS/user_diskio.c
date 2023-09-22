

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
// �ļ���ȡ����
FIL file;		
// �������
FRESULT f_res;
// ��ȡ�ֽ�����ָ��
UINT bw;

// ��������
static __IO BYTE ReadBuffer[500];    
// ��ʱ�洢����
uint8_t temp[500];
//extern void pic_data_copy(uint8_t key);
//extern void KEY_data_copy(uint8_t key);

// ���ı��ļ������������
//extern volatile uint8_t Menu_level;
  uint8_t Menu_level;
//extern volatile uint8_t key_set[30][201];
volatile uint8_t key_buff[7000];
volatile uint8_t key_line;
volatile uint8_t key_set_value;
volatile uint32_t file_size;
// ��¼·��
char USER_Path[4];

void mount_disk(void)
{
	/*
		fat�ļ�ϵͳ������һ���ṹ��,��Ҫ�û����з���,Ȼ��ᱻ��¼��ȫ�ֵ�FATFS[]���������
		USER_Path -> �������
		0 -> ��ʾ�����أ�1 -> ��ʾ�������
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

// ��ȡ�ļ�
void read_file(void)
{
	uint16_t i,k;
 
	//��bin�ļ����ȡͼƬ
//	f_res = f_open(&file, "0:/menu_1/lock.bin", FA_READ);
//	f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw);
	
//	for(k=0; k<360; k++)	
//	{
//		//printf("%c",ReadBuffer[k]);
//		work[k] = ReadBuffer[k];	//��ͼƬ����
//	}	
//	for(k=0; k<360; k++)	
//	{
//		printf("%c",work[k]);
//	}	
	
	// 20���������ζ�ȡ
	for(i=0; i<20; i++)
	{
		switch(i)
		{
			// ��һ���㼶����
			case 0:
					//f_res = f_mount(&fs, USER_Path, 0);
					// ͨ���˵���ȡ�� ��Ӧ�Ĳ˵�ͼƬ�ļ�
					switch(Menu_level)
					{
						case 0:
								// ���ļ����ɹ����ȡ
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
					// ��һ���˵���ȡ�ɹ��� ��ȡ�����ļ�
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
					// �ļ���״̬
					if(f_res == RES_OK)
					{
						/*
							�ļ�ָ��
							�ַ�����ָ��
							���������С
							��ȡ�ֽ�����ָ��
						*/
						f_res = f_read(&file, ReadBuffer, sizeof ReadBuffer, &bw); 
						
						for(k=0; k<360; k++)	
						{
							// ���뻺�����������
							temp[k] = ReadBuffer[k];		
						}	
						// ��ȡ��һ��Ҫ��ʾ��ͼƬ
					//	pic_data_copy(1);
					}
					// �ر��ļ�
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
	
	//���ı��ļ����ȡ��������ֵ
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
	//f_res = f_mount(NULL, USER_Path, 0);	//ȡ������ 1227-
	
	for(k=0, key_line=0, key_set_value=1; key_line<20; k++,key_set_value++)
	{
		// �ж��Ƿ�Ϊ�س�
		if(key_buff[k] != 13)	
		{
			// ��Ϊ�س���ʱ�����δ�������
			temp[key_set_value] = key_buff[k];
		}
		else	
		{	
			// ���ֽڱ��水���Ķ��峤��
			temp[0] = key_set_value - 1;
			//KEY_data_copy(key_line);
			// ����������
			key_line++;
			// ���еĳ�������
			key_set_value = 0;
		}
	}
	
	//���ÿ������ֵ
//	for(key_line=0, key_set_value=0; key_line<20; key_line++, key_set_value = 0)
//	{
//		while(key_set_value < (key_set[key_line][0]+1))
//		{
//			printf("%d ",key_set[key_line][key_set_value]);	
//			key_set_value++;
//		}		
//	}
	
	//�������� 
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
	
	f_res = f_mount(NULL, USER_Path, 0);	//ȡ������
}

void File_read(void)
{	
	// ��ȡ�û��趨�ļ��˵�
	//Menu_level = FLASH_EEPROM_Read();
	// Ӳ�����̹���
	mount_disk();
	//format_disk();
	//create_file();
	// ��ȡ�ļ��� ִ�к���
	read_file();
}

