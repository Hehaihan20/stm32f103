#include "Utikites.h"

void Utikites_Init() {

    MK_init();
    EXTIX_Init();

}


void MK_on_keydown(u8 row, u8 col) {
    printf("第%d行第%d列 DOWN\r\n", (int)row, (int)col);
	  Menu2();

}
void MK_on_keyup(u8 row, u8 col) {
    printf("第%d行第%d列 UP\r\n", (int)row, (int)col);
	   Menu1();
}

void EC2_CW_ACTIVE() {

    printf("EC2_CW_ACTIVE--\r\n");
}
void EC2_CWW_ACTIVE() {
    printf("EC2_CWW_ACTIVE--\r\n");

}
void EC3_CW_ACTIVE() {

    printf("EC3_CW_ACTIVE--\r\n");
}
void EC3_CWW_ACTIVE() {
    printf("EC3_CWW_ACTIVE--\r\n");

}

void EC4_CW_ACTIVE() {
 Menu2();
    printf("EC4_CW_ACTIVE--\r\n");
}
void EC4_CWW_ACTIVE() {
    printf("EC4_CWW_ACTIVE--\r\n");
	 Menu1();

}
void EC1_CW_ACTIVE() {
   
    printf("EC1_CW_ACTIVE--\r\n");
}
void EC1_CWW_ACTIVE() {
    printf("EC1_CWW_ACTIVE--\r\n");
}