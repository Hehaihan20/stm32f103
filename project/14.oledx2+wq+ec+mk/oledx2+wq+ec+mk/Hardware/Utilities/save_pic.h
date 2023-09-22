#ifndef __SAVE_PIC_H
#define __SAVE_PIC_H


#include "bmp.h"
#include "w25qxx.h"
void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize);
void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData,uint16_t photoSize);
void pic_default_init();
#endif