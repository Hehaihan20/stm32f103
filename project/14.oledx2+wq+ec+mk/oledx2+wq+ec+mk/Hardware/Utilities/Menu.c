#include "Menu.h"
#include "save_pic.h"
//void StorePhoto(uint8_t folderIndex, uint8_t photoIndexInFolder, uint8_t *photoData, uint16_t photoSize)
//void ReadPhoto(uint8_t folderIndex, uint8_t photoIndex, uint8_t *photoData);
#define SIZE1 sizeof(BMP1)
#define SIZE2 sizeof(BMP2)
#define SIZE3 sizeof(BMP2)	
#define oled_42_size_x 72
#define oled_42_size_y 40 
u8 buffer1[SIZE1];
u8 buffer2[SIZE2];
void Menu_init(void){
	  W25QXX_Init();
	  //W25QXX_Write(BMP1,0, sizeof(BMP1));
	//W25QXX_Read(buffer, 0,sizeof(BMP1));
  // StorePhoto(0,1,BMP2,SIZE2);
   ReadPhoto(0,0,buffer1,SIZE1);
	 ReadPhoto(0,1,buffer2,SIZE2);
}

void Menu1(void) {
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,0);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,1);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,2);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,3);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,4);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,5);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,6);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,7);
    OLED_42_ShowPicture(0,0,70,22,BMP3,1,8);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP4,1,9);

    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,10);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,11);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,12);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,13);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,14);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,15);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,16);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,17);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer1,1,18);
    OLED_42_ShowPicture(2,3,29,27,buffer2,1,19);
	 	OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,buffer1,1,3);
		OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,buffer2,1,4);
		OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,buffer2,1,0);
		OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,buffer2,1,1);
		OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,buffer1,1,2);
	
}
void Menu2(void) {
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP9,1,0);
    OLED_42_ShowPicture(0,0,72,40,BMP1,1,1);
    OLED_42_ShowPicture(20,1,29,32,buffer2,1,2);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP4,1,3);
    OLED_42_ShowPicture(20,1,29,32,buffer2,1,4);
    OLED_42_ShowPicture(0,0,72,40,BMP1,1,5);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,6);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,buffer2,1,7);
    OLED_42_ShowPicture(0,0,72,40,BMP1,1,8);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP5,1,9);

    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP6,1,10);
    OLED_42_ShowPicture(0,0,70,22,BMP3,1,11);
    OLED_42_ShowPicture(0,0,72,40,BMP7,1,12);
    OLED_42_ShowPicture(20,1,29,32,buffer2,1,13);
    OLED_42_ShowPicture(0,0,70,22,BMP3,1,14);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP5,1,15);
    OLED_42_ShowPicture(0,0,72,40,BMP8,1,16);
    OLED_42_ShowPicture(0,0,oled_42_size_x,oled_42_size_y,BMP4,1,17);
    OLED_42_ShowPicture(0,1,oled_42_size_x,oled_42_size_y,buffer2,1,18);
    OLED_42_ShowPicture(0,1,oled_42_size_x,oled_42_size_y,buffer2,1,19);
	  
		OLED_92_ShowPicture(20,1,70,22,BMP1,1,0);
		OLED_92_ShowPicture(20,1,29,32,BMP3,1,1);
		OLED_92_ShowPicture(0,1,oled_42_size_x,oled_42_size_y,buffer2,1,2);
		OLED_92_ShowPicture(20,1,70,22,BMP4,1,3);
		OLED_92_ShowPicture(20,1,oled_42_size_x,oled_42_size_y,BMP5,1,4);
	
}