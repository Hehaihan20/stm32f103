#ifndef FILE_CONTROL_H
#define FILE_CONTROL_H

#include "stm32f10x.h"
#include "w25qxx.h"
#include "usart.h"
#define NUM_FOLDERS 10
#define NUM_PHOTOS_PER_FOLDER 26
#define SECTOR_SIZE   4096
void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize);
void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData);


#endif