#include "oled.h"

u8 OLED_GRAM[88][5];
uint32_t stat =0xfffff;
#define buff_size 256
unsigned char sendbuff[buff_size];
void OLED_Spi_init(void) {
    SPI_InitTypeDef SPI_InitStructure;   
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//空闲状态
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//第二个边沿采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(OLED_042_SPI, &SPI_InitStructure);
  //  SPI_I2S_DMACmd(OLED_042_SPI , SPI_I2S_DMAReq_Tx,ENABLE);
    SPI_Cmd(OLED_042_SPI, ENABLE);
}



////反显函数
//void OLED_ColorTurn(u8 i)
//{
//    if(i==0)
//    {
//        OLED_WR_CMD(0xA6);//正常显示
//    }
//    if(i==1)
//    {
//        OLED_WR_CMD(0xA7);//反色显示
//    }
//}

void OLED_WR_CMD(u8 dat) {  
  // 确保SPI传输空闲
	  OLED_DC_Clr(); // OLED CS low for cmd
	  while (SPI_I2S_GetFlagStatus(OLED_042_SPI, SPI_I2S_FLAG_TXE) == RESET){}//记得加‘；’或者’{}‘	
    SPI_I2S_SendData(OLED_042_SPI, dat);	
    while (SPI_I2S_GetFlagStatus(OLED_042_SPI, SPI_I2S_FLAG_BSY) == SET){}//记得加‘；’	或者‘{}’	
	
    OLED_DC_Set(); // OLED CS high for data
}
void OLED_WR_DATA(u8 dat) { 
// 确保SPI传输空闲
	  OLED_DC_Set(); // OLED DC high for data 
	  while (SPI_I2S_GetFlagStatus(OLED_042_SPI, SPI_I2S_FLAG_TXE) == RESET){}//记得加‘；’或者’{}‘	
    SPI_I2S_SendData(OLED_042_SPI, dat);	
    while (SPI_I2S_GetFlagStatus(OLED_042_SPI, SPI_I2S_FLAG_BSY) == SET){}//记得加‘；’	或者‘{}’	
	  OLED_DC_Set(); // refresh
}





//更新显存到OLED
void OLED_Refresh(void)
{
    u8 i,n;
	  u8 data_to_send[88 * 5]; // 128像素 * 4列
    for(i=0; i<5; i++)
    {
       OLED_WR_CMD(0xb0+i); //设置行起始地址
       OLED_WR_CMD(0x0b);   //设置低列起始地址
       OLED_WR_CMD(0x11);   //设置高列起始地址
        for(n=0; n<88; n++){
				       //  data_to_send[n] = OLED_GRAM[n][i];	
								OLED_WR_DATA(OLED_GRAM[n][i]);					
				}				
        // 使用单次函数调用发送数据
        // 假设 OLED_WR_Multi_Bytes 是一个用于发送多个字节的函数
          // OLED_WR_Multi_Bytes(data_to_send, 88);
        

    }
}


//清屏函数
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<5; i++)
    {
        for(n=0; n<72; n++)
        {
            OLED_GRAM[n][i]=0;//清除所有数据
        }
    }
    OLED_Refresh();//更新显示
}

//画点
//x:0~127
//y:0~63
//t:1 填充 0,清空
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 i,m,n;
    i=y/8;
    m=y%8;
    n=1<<m;
    if(t) {
        OLED_GRAM[x][i]|=n;
    }
    else
    {
        OLED_GRAM[x][i]=~OLED_GRAM[x][i];
        OLED_GRAM[x][i]|=n;
        OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    }
}


void CS_ALL_OFF(){
 for (int i=0;i<OLED_NUM;i++){
		  GPIO_TypeDef*  port = oled_cs_pins[i].port; // 获取端口信息
			uint16_t pin = oled_cs_pins[i].pin; // 获取引脚信息
			GPIO_WriteBit(port, pin, Bit_SET);	
		}
}
//x,y：起点坐标
//sizex,sizey,图片长宽
//BMP[]：要写入的图片数组
//mode:0,反色显示;1,正常显示
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode,u8 index)
{ 
	  GPIO_TypeDef*  port = oled_cs_pins[index].port; // 获取端口信息
    uint16_t pin = oled_cs_pins[index].pin; // 获取引脚信息
    GPIO_WriteBit(port, pin, Bit_RESET);
	
		u16 j=0;
    u8 i,n,temp,m;
    u8 x0=x,y0=y;
    //sizey=sizey/8+((sizey%8)?1:0);
	  sizey = (sizey + 7) / 8; // 优化：使用位操作替代除法和取模
    for(n=0; n<sizey; n++)
    {
        for(i=0; i<sizex; i++)
        {
            temp=BMP[j];
            j++;
            for(m=0; m<8; m++)
            {
                if(temp&0x01)OLED_DrawPoint(x,y,mode);
                else OLED_DrawPoint(x,y,!mode);
                temp>>=1;
                y++;
            }
            x++;
            if((x-x0)==sizex)
            {
                x=x0;
                y0=y0+8;
            }
            y=y0;
        }
    }
		
	  OLED_Refresh();
		GPIO_WriteBit(port, pin, Bit_SET);
}





//OLED的初始化
void OLED_Init(void)
{   
	 
    RCC_APB2PeriphClockCmd(OLED_42_RCC|RCC_APB2Periph_AFIO, ENABLE);	 //使能端口时钟
		RCC_APB1PeriphClockCmd(OLED_42_SPI_RCC, ENABLE);
	  GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_SCK_PIN | OLED_SPI_MOSI_PIN; // SPI SCK and MOSI
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(OLED_SPI_GPIO, &GPIO_InitStructure);

	
	
	  RCC_APB2PeriphClockCmd(OLED_42_CS_RCC, ENABLE);	 //使能D端口时钟
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_CS1_PIN; // SPI SCK and MOSI
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(OLED_CS_GPIO, &GPIO_InitStructure);
		GPIO_ResetBits(OLED_CS_GPIO,OLED_SPI_CS1_PIN);
   
	  RCC_APB2PeriphClockCmd(OLED_42_RES_RCC, ENABLE);	 //使能D端口时钟
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_DC_PIN|OLED_SPI_RES_PIN; // OLED CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(OLED_42_RES_GPIO, &GPIO_InitStructure);
  	GPIO_SetBits(OLED_42_RES_GPIO,OLED_SPI_DC_PIN|OLED_SPI_RES_PIN);
   

		OLED_Spi_init();
    OLED_RES_Clr();
    delay_1ms(200);
    OLED_RES_Set();

	
	OLED_WR_CMD(0xAE); /*display off*/
	OLED_WR_CMD(0xD5); /*set osc division*/
	OLED_WR_CMD(0xF0);
	OLED_WR_CMD(0xA8); /*multiplex ratio*/
	OLED_WR_CMD(0x27); /*duty = 1/40*/
	OLED_WR_CMD(0xD3); /*set display offset*/
	OLED_WR_CMD(0x00);
	OLED_WR_CMD(0x40); /*Set Display Start Line */
	OLED_WR_CMD(0x8d); /*set charge pump enable*/
	OLED_WR_CMD(0x14);
	OLED_WR_CMD(0x20); /*Set page address mode*/
	OLED_WR_CMD(0x02);
	OLED_WR_CMD(0xA1); /*set segment remap*/
	OLED_WR_CMD(0xC8); /*Com scan direction*/
	OLED_WR_CMD(0xDA); /*set COM pins*/
	OLED_WR_CMD(0x12);
	OLED_WR_CMD(0xAD); /*Internal IREF Setting*/
	OLED_WR_CMD(0x30);
	OLED_WR_CMD(0x81); /*contract control*/
	OLED_WR_CMD(0xfF); /*128*/
	OLED_WR_CMD(0xD9); /*set pre-charge period*/
	OLED_WR_CMD(0x22);
	OLED_WR_CMD(0xdb); /*set vcomh*/
	OLED_WR_CMD(0x20);
	OLED_WR_CMD(0xA4); /*Set Entire Display On/Off*/
	OLED_WR_CMD(0xA6); /*normal / reverse*/
	OLED_WR_CMD(0x0C); /*set lower column address*/
	OLED_WR_CMD(0x11); /*set higher column address*/	
	
		

	
	//	OLED_WR_CMD(0xA7);//反色显示
	
	
	
	
	
	
    OLED_Clear();
    OLED_WR_CMD(0xAF); /*display ON*/
   // CS_ALL_OFF();
}

