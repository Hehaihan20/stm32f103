
#include "file_control.h"


// ���豣����Ƭ��С������
uint16_t photoSizes[NUM_FOLDERS][NUM_PHOTOS_PER_FOLDER];
void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndexInFolder);
	  W25QXX_Write_Enable(); // ����Flash	
    W25QXX_Write(photoData, sector * SECTOR_SIZE, photoSize);
		W25QXX_Write_Disable();
	// ����Ƭ��С���浽������
    photoSizes[folderIndex][photoIndexInFolder] = photoSize;

}
void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData) {
    uint32_t sector = (folderIndex * NUM_PHOTOS_PER_FOLDER + photoIndex);

    // �������л�ȡ��Ƭ��С��Ϣ
    uint16_t photoSize = photoSizes[folderIndex][photoIndex];

    // ��ȡ��Ƭ����
    W25QXX_Read(photoData, sector * SECTOR_SIZE, photoSize);
}