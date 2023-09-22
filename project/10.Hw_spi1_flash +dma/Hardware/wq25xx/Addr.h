
#define FILE_NUME
#define DIR_NUME
#define DIR

#define SINGLE_SECTOR_SIZE 							4096
#define SINLE_BLOCK_SECTOR_NUME 		 		16
#define SINGLE_BLOCK_SIZE								SINGLE_SECTOR_SIZE*SINLE_BLOCK_SECTOR_NUME

#define TOTLE_BLOCK_NUM									64
#define TOTLE_DIRK_SIZE 								TOTLE_BLOCK_NUM*SINGLE_BLOCK_SIZE

#define BASE_ADDR                       0X000000

#define REAL_BLOCK_NUM									20
/*
16M�ֽڣ�128Mbit���ռ䷶Χ0x000000-0xFFFFFF��
��Ϊ256����
ÿ��16��������256*16��������
ÿ������16ҳ ��2561616ҳ��
ÿ��Ĵ�С 16384KB/256 =64KB
ÿ�������Ĵ�С 64KB/16 = 4KB
ÿ��ҳ�Ĵ�С 4KB/16 = 256B
ÿ����ĵ�ַ��
��0��ַ��0x000000-0x00FFFF
��1��ַ��0x010000-0x01FFFF
��
��0��ַ��0xFF0000-0xFFFFFF
ÿ�������ĵ�ַ��
0��0������0x000000-0x000FFF
0��1������0x001000-0x001FFF
��
0��16������0x00F000-0x00FFFF
��ַ��8λ��23-16����ʾ���λ�ã��ڣ�15-12����ʾ������λ�á�


*/
/*

BIT7  6   5   4   3   2   1   0
SPR   RV  TB BP2 BP1 BP0 WEL BUSY
BUSYλָʾ��ǰ��״̬��0��ʾ���У�1��ʾæµ
WEL:дʹ��������Ϊ1ʱ�����Բ���ҳ/����/�顣Ϊ0ʱ��д��ֹ��
SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
TB,BP2,BP1,BP0:FLASH����д��������


*/














//����
typedef struct Link {
    char data;
    struct Link* next;
} link;

//USER
#define MENU_NUM                  REAL_BLOCK_NUM/2
#define MENU_0_ADDR								BASE_ADDR+(0*SINGLE_BLOCK_SIZE)
#define MENU_1_ADDR  							BASE_ADDR+(2*SINGLE_BLOCK_SIZE)
#define MENU_2_ADDR		            BASE_ADDR+(4*SINGLE_BLOCK_SIZE)
#define MENU_3_ADDR	              BASE_ADDR+(6*SINGLE_BLOCK_SIZE)
#define MENU_4_ADDR	 						  BASE_ADDR+(8*SINGLE_BLOCK_SIZE)
#define MENU_5_ADDR								BASE_ADDR+(10*SINGLE_BLOCK_SIZE)
#define MENU_6_ADDR								BASE_ADDR+(12*SINGLE_BLOCK_SIZE)
#define MENU_7_ADDR								BASE_ADDR+(14*SINGLE_BLOCK_SIZE)
#define MENU_8_ADDR		         		BASE_ADDR+(16*SINGLE_BLOCK_SIZE)
#define MENU_9_ADDR								BASE_ADDR+(18*SINGLE_BLOCK_SIZE)
/*MENU0*/
#define MENU_0_PIC0_ADDR					MENU_0_ADDR+(0*SINGLE_SECTOR_SIZE)
#define MENU_0_PIC1_ADDR					MENU_0_ADDR+(1*SINGLE_SECTOR_SIZE)
#define MENU_0_PIC2_ADDR					MENU_0_ADDR+(2*SINGLE_SECTOR_SIZE)
#define MENU_0_PIC3_ADDR					MENU_0_ADDR+(3*SINGLE_SECTOR_SIZE)
#define MENU_0_PIC4_ADDR					MENU_0_ADDR+(4*SINGLE_SECTOR_SIZE)
#define MENU_0_PIC5_ADDR
#define MENU_0_PIC6_ADDR
#define MENU_0_PIC7_ADDR
#define MENU_0_PIC8_ADDR
#define MENU_0_PIC9_ADDR
#define MENU_0_PIC10_ADDR
#define MENU_0_PIC11_ADDR
#define MENU_0_PIC12_ADDR
#define MENU_0_PIC13_ADDR
#define MENU_0_PIC14_ADDR
#define MENU_0_PIC15_ADDR
#define MENU_0_PIC16_ADDR
#define MENU_0_PIC17_ADDR
#define MENU_0_PIC18_ADDR
#define MENU_0_PIC19_ADDR
#define MENU_0_PIC20_ADDR
#define MENU_0_PIC25_ADDR


/*MENU1*/
#define MENU_1_PIC0_ADDR
#define MENU_1_PIC1_ADDR
#define MENU_1_PIC2_ADDR
#define MENU_1_PIC3_ADDR
#define MENU_1_PIC4_ADDR
#define MENU_1_PIC5_ADDR
#define MENU_1_PIC6_ADDR
#define MENU_1_PIC7_ADDR
#define MENU_1_PIC8_ADDR
#define MENU_1_PIC9_ADDR
#define MENU_1_PIC10_ADDR
#define MENU_1_PIC11_ADDR
#define MENU_1_PIC12_ADDR
#define MENU_1_PIC13_ADDR
#define MENU_1_PIC14_ADDR
#define MENU_1_PIC15_ADDR
#define MENU_1_PIC16_ADDR
#define MENU_1_PIC17_ADDR
#define MENU_1_PIC18_ADDR
#define MENU_1_PIC19_ADDR
#define MENU_1_PIC20_ADDR
#define MENU_1_PIC25_ADDR








/*MENU2*/
#define MENU_2_PIC0_ADDR
#define MENU_2_PIC1_ADDR
#define MENU_2_PIC2_ADDR
#define MENU_2_PIC3_ADDR
#define MENU_2_PIC4_ADDR
#define MENU_2_PIC5_ADDR
#define MENU_2_PIC6_ADDR
#define MENU_2_PIC7_ADDR
#define MENU_2_PIC8_ADDR
#define MENU_2_PIC9_ADDR
#define MENU_2_PIC10_ADDR
#define MENU_2_PIC11_ADDR
#define MENU_2_PIC12_ADDR
#define MENU_2_PIC13_ADDR
#define MENU_2_PIC14_ADDR
#define MENU_2_PIC15_ADDR
#define MENU_2_PIC16_ADDR
#define MENU_2_PIC17_ADDR
#define MENU_2_PIC18_ADDR
#define MENU_2_PIC19_ADDR
#define MENU_2_PIC20_ADDR
#define MENU_2_PIC25_ADDR

/*MENU3*/
#define MENU_3_PIC0_ADDR
#define MENU_3_PIC3_ADDR
/*MENU4*/

#define MENU_4_PIC0_ADDR
#define MENU_4_PIC4_ADDR
/*MENU5*/
#define MENU_5_PIC0_ADDR
#define MENU_5_PIC5_ADDR
/*MENU6*/

#define MENU_6_PIC0_ADDR



#define MENU_6_PIC6_ADDR
/*MENU7*/
#define MENU_7_PIC0_ADDR
#define MENU_7_PIC7_ADDR
/*MENU8*/
#define MENU_8_PIC0_ADDR
#define MENU_8_PIC8_ADDR


/*MENU9*/


#define MENU_9_PIC0_ADDR
#define MENU_9_PIC9_ADDR


