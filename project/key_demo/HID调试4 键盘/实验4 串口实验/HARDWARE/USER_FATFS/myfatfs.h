
#ifndef __MY_FATFS_H
#define __MY_FATFS_H

#include "sys.h"
#include "ff.h"


void fatfs_init();

void fatfs_write(const TCHAR* path,const uint8_t WrtieBuffs[]);
void fatfs_read(const TCHAR* path);
#endif
























