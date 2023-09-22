#include "save_pic.h"
#define NUM_FOLDERS 10
#define NUM_PHOTOS_PER_FOLDER 26
#define SECTOR_SIZE 4096


// 假设保存照片大小的数组
uint16_t photoSizes[NUM_FOLDERS][NUM_PHOTOS_PER_FOLDER];
void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndexInFolder);
	  W25QXX_Write_Enable(); // 解锁Flash	
    W25QXX_Write(photoData, sector * SECTOR_SIZE, photoSize);
		W25QXX_Write_Disable();


}
void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData,uint16_t photoSize) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndex);
    // 读取照片数据
	   W25QXX_Read(photoData, sector * SECTOR_SIZE, photoSize);
}

 void pic_default_init(){
 
 
 
 }