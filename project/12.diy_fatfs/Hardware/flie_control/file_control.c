
#include "file_control.h"


// 假设保存照片大小的数组
uint16_t photoSizes[NUM_FOLDERS][NUM_PHOTOS_PER_FOLDER];
void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndexInFolder);
	  W25QXX_Write_Enable(); // 解锁Flash	
    W25QXX_Write(photoData, sector * SECTOR_SIZE, photoSize);
		W25QXX_Write_Disable();
	// 将照片大小保存到数组中
    photoSizes[folderIndex][photoIndexInFolder] = photoSize;

}
void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndex);

    // 从数组中获取照片大小信息
    uint16_t photoSize = photoSizes[folderIndex][photoIndex];

    // 读取照片数据
    W25QXX_Read(photoData, sector * SECTOR_SIZE, photoSize);
}