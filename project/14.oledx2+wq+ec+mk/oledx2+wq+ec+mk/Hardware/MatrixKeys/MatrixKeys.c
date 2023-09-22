#include "MatrixKeys.h"


// 定义状态记录,记录所有的
static u32 key_state = 0xfffff;
/*************第一行*************/
//第一行第一列（0，0），1向右移动0（0*5+0）
//第一行第二列（0，1），1向右移动1位（0*5+1）
//第一行第三列（0，2），1向右移动1位（0*5+2）
//第一行第四列（0，3），1向右移动1位（0*5+3）
//第一行第五列(0,4),1向右移动1位    （0*5+4）
//第二行第一列(1,0),1向右移动1位    （1*5+0）
//此处注意,如果我*的是小的行数(4),第一行第五列和地二行第一列都会是右移四位
//第一行第五列(0,4),1向右移动1位（0*4+4）=4
//第二行第一列(1,0),1向右移动1位（1*4+0）=4

/*.......*/
/*************第N行*************/
//第一行第一列（N-1，0），1向右移动0（N-1*5+0）
//第一行第二列（N-1，1），1向右移动1位（N-1*5+1）
//第一行第三列（N-1，2），1向右移动1位（N-1*5+2）
//第一行第四列（N-1，3），1向右移动1位（N-1*5+3）
#define IS_KEY_UP(row, col) 	((key_state >> (row * COL_NUM + col)) & 0x01) == KEY_UP
#define IS_KEY_DOWN(row, col) ((key_state >> (row * COL_NUM + col)) & 0x01) == KEY_DOWN
//高电平按下
//#define SET_KEY_UP(row, col)		key_state &= ~(1 << (row * ROW_NUM + col))
//#define SET_KEY_DOWN(row, col)	key_state |= (1 << (row * ROW_NUM + col))


////低电平按下
#define SET_KEY_UP(row, col)		key_state |= (1 << (row * COL_NUM + col))
#define SET_KEY_DOWN(row, col)	key_state &= ~(1 << (row * COL_NUM + col))

void KEY_INIT(){
    GPIO_InitTypeDef GPIO_InitStructure;
    //ROW 行设置推挽输出,默认设置
  	RCC_APB2PeriphClockCmd(ROW_GPIO_RCC, ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin = ROW1_PIN|ROW2_PIN|ROW3_PIN|ROW4_PIN;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	  GPIO_Init(ROW_GPIO,&GPIO_InitStructure);
	
	  //COL 列设置输入
  	RCC_APB2PeriphClockCmd(COL_GPIO_RCC, ENABLE);
	  GPIO_InitStructure.GPIO_Pin = COL1_PIN|COL2_PIN|COL3_PIN|COL4_PIN|COL5_PIN;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
    GPIO_Init(COL_GPIO,&GPIO_InitStructure);
	
		GPIO_WriteBit(COL_GPIO,COL1_PIN|COL2_PIN|COL3_PIN|COL4_PIN|COL5_PIN,Bit_SET);
}



static u8 COL_STATE(u8 col) {
    if(col == 0) return COL1;
    if(col == 1) return COL2;
    if(col == 2) return COL3;
    if(col == 3) return COL4;
   	if(col == 4) return COL5;
}



static void ROW_OUT(u8 row) {
    if(row == 0) {SET_ROW1_LOW; SET_ROW2_HIGH; SET_ROW3_HIGH; SET_ROW4_HIGH;}
    if(row == 1) {SET_ROW1_HIGH; SET_ROW2_LOW; SET_ROW3_HIGH; SET_ROW4_HIGH;}
    if(row == 2) {SET_ROW1_HIGH; SET_ROW2_HIGH; SET_ROW3_LOW; SET_ROW4_HIGH;}
    if(row == 3) {SET_ROW1_HIGH; SET_ROW2_HIGH; SET_ROW3_HIGH; SET_ROW4_LOW;}
}

void MK_init() {
    KEY_INIT();
}
void MK_scan(u32 *state) {
    u8 i, j;
    for(j = 0; j < ROW_NUM; j++) {
        // j: row
        // i: col
        // 只让row1工作
        ROW_OUT(j);
        for(i = 0; i < COL_NUM; i++) {
            // 列
            // 判断某个列是否抬起或者按下
            // i就是某个列
            // row, col
            if(COL_STATE(i) == KEY_DOWN && IS_KEY_UP(j, i)) {
                // 按键如果是按下， 并且上一次是高电平，电平应该是低
                // 记录状态
					
                SET_KEY_DOWN(j, i);							
								MK_on_keydown(j, i);
            } else if(COL_STATE(i) == KEY_UP && IS_KEY_DOWN(j, i)) {
                // 按键如果是抬起，并且上一次是低电平, 电平应该是高
                // 记录状态
                SET_KEY_UP(j, i);							
								MK_on_keyup(j, i);
            }
        }
    }
		*state = key_state;
}