
#include "ff.h"			/* Obtains integer types */
#include "diskio.h"
#include "w25qxx.h"
#include "malloc.h"

/* Definitions of physical drive number for each drive */
#define DEV_FLASH		0	/* Example: Map Ramdisk to physical drive 0 */
u16 FLASH_SECTOR_COUNT=2048*12;//ǰ12M�ֽڸ�FATFSռ��
#define FLASH_SECTOR_SIZE 512
#define FLASH_BOLCK_SIZE 8

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;
    if(W25QXX_ReadID()==0xef17) {
        stat=0;
    }
    else	stat= STA_NOINIT;

    return stat;
}

//}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;
    W25QXX_WAKEUP();
    W25QXX_Init();

    // DSTATUS stat;
    stat= disk_status(DEV_FLASH);
    return	stat ;
}
/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,		/* Physical drive nmuber to identify the drive */
    BYTE *buff,		/* Data buffer to store read data */
    LBA_t sector,	/* Start sector in LBA */
    UINT count		/* Number of sectors to read */
)
{
    DRESULT res;
    // W25QXX_Read(buff, sector * 4096, count * 4096);
    for(; count>0; count--)
    {
        W25QXX_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
        sector++;
        buff+=FLASH_SECTOR_SIZE;
    }
    res=RES_OK;
    return res;
}
/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,			/* Physical drive nmuber to identify the drive */
    const BYTE *buff,	/* Data to be written */
    LBA_t sector,		/* Start sector in LBA */
    UINT count			/* Number of sectors to write */
)
{
    DRESULT res;
    //W25QXX_Write((u8 *)buff, sector * 4096, count * 4096);
    for(; count>0; count--)
    {
        W25QXX_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
        sector++;
        buff+=FLASH_SECTOR_SIZE;
    }
    res=RES_OK;
    return res;
}
#endif
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (//������ǰ�Ǹ�ʽ��
    BYTE pdrv,		/* Physical drive nmuber (0..) */
    BYTE cmd,		/* Control code */
    void *buff		/* Buffer to send/receive control data */
)
{
    DRESULT res =RES_OK;
    // Process of the command for the RAM drive
    switch(cmd) {
    //������������
    case CTRL_SYNC:
        res = RES_OK;
        break;
    case GET_SECTOR_COUNT:
        *(DWORD*)buff=FLASH_SECTOR_COUNT;
        //����ÿ��������С
        break;
    case GET_SECTOR_SIZE:
        *(WORD*)buff=FLASH_SECTOR_SIZE;
        break;
    //���ز�����������С����(��λΪ����)
    case GET_BLOCK_SIZE:
        *(WORD*)buff=FLASH_BOLCK_SIZE;
        break;
    default:
        res = RES_PARERR;
    }
    return res;
}


DWORD get_fattime() {

    return 0;
}

//��̬�����ڴ�
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}

//�ͷ��ڴ�
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}




