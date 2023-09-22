#include "oled.h"

u8 OLED_GRAM[144][4];
uint32_t stat =0xfffff;
#define buff_size 256
unsigned char sendbuff[buff_size];
void OLED_Spi_init(void) {
    SPI_InitTypeDef SPI_InitStructure;   
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//����״̬
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//�ڶ������ز���
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_I2S_DMACmd(SPI1 , SPI_I2S_DMAReq_Tx,ENABLE);
    SPI_Cmd(SPI1, ENABLE);
}
void DMA_OLED_Init(void){
  // �жϽṹ��
  DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ�� DMA ʱ��
	DMA_DeInit(DMA1_Channel3);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI1->DR)); //SPI���ݼĴ�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&OLED_GRAM; //���ý��ջ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //�Ӵ�������ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = 1024; //DMA ͨ���� DMA ����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //8 λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8 λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA ͨ�� x ӵ�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; ////DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel3, &DMA_InitStructure); //����ָ���Ĳ�����ʼ��
  //DMA_Cmd(DMA1_Channel3, DISABLE); //��ʹ��DMA1 CH3��ָʾ��ͨ��
  DMA_Cmd(DMA1_Channel3, ENABLE); //ʹ��DMA1 CH3��ָʾ��ͨ��
}


////���Ժ���
//void OLED_ColorTurn(u8 i)
//{
//    if(i==0)
//    {
//        OLED_WR_CMD(0xA6);//������ʾ
//    }
//    if(i==1)
//    {
//        OLED_WR_CMD(0xA7);//��ɫ��ʾ
//    }
//}

void OLED_WR_CMD(u8 dat) {  
  // ȷ��SPI�������
	  OLED_DC_Clr(); // OLED CS low for cmd
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ǵüӡ��������ߡ�{}��	
    SPI_I2S_SendData(SPI1, dat);	
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET){}//�ǵüӡ�����	���ߡ�{}��	
		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);	
    OLED_DC_Clr(); // OLED CS high for data
}
void OLED_WR_DATA(u8 dat) { 
// ȷ��SPI�������
	  OLED_DC_Set(); // OLED DC high for data
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ǵüӡ��������ߡ�{}��	
    SPI_I2S_SendData(SPI1, dat);	
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET){}//�ǵüӡ�����	���ߡ�{}��	
		SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);	
	  OLED_DC_Clr(); // refresh
}
void OLED_WR_Multi_Bytes(uint8_t *data, uint16_t size) {
    // ����DMA����
    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA1_Channel3->CNDTR = size; // ���ô������ݵ�����
    DMA1_Channel3->CMAR = (uint32_t)data; // ��������Դ��ַ
    DMA1_Channel3->CPAR = (uint32_t)(&(SPI1->DR)); // ����SPI���ݼĴ�����ַ
    DMA_Cmd(DMA1_Channel3, ENABLE);
    // �ȴ�DMA�������
    while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);
    // ���DMA������ɱ�־
    DMA_ClearFlag(DMA1_FLAG_TC3);
    // �ȴ�SPI�������
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

//�����Դ浽OLED
void OLED_Refresh(void)
{
    u8 i,n;
	  u8 data_to_send[128 * 4]; // 128���� * 4��
    for(i=0; i<4; i++)
    {
       OLED_WR_CMD(0xb0+i); //��������ʼ��ַ
       OLED_WR_CMD(0x00);   //���õ�����ʼ��ַ
       OLED_WR_CMD(0x10);   //���ø�����ʼ��ַ
        for(n=0; n<128; n++){
				         data_to_send[n] = OLED_GRAM[n][i];			
				}				
        // ʹ�õ��κ������÷�������
        // ���� OLED_WR_Multi_Bytes ��һ�����ڷ��Ͷ���ֽڵĺ���
           OLED_WR_Multi_Bytes(data_to_send, 128);
           OLED_WR_DATA(OLED_GRAM[n][i]);
    }
}


//��������
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<4; i++)
    {
        for(n=0; n<128; n++)
        {
            OLED_GRAM[n][i]=0;//�����������
        }
    }
    OLED_Refresh();//������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
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
		  GPIO_TypeDef*  port = oled_cs_pins[i].port; // ��ȡ�˿���Ϣ
			uint16_t pin = oled_cs_pins[i].pin; // ��ȡ������Ϣ
			GPIO_WriteBit(port, pin, Bit_SET);	
		}
}
//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode,u8 index)
{ 
	  GPIO_TypeDef*  port = oled_cs_pins[index].port; // ��ȡ�˿���Ϣ
    uint16_t pin = oled_cs_pins[index].pin; // ��ȡ������Ϣ
    GPIO_WriteBit(port, pin, Bit_RESET);
	
		u16 j=0;
    u8 i,n,temp,m;
    u8 x0=x,y0=y;
    //sizey=sizey/8+((sizey%8)?1:0);
	  sizey = (sizey + 7) / 8; // �Ż���ʹ��λ�������������ȡģ
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





//OLED�ĳ�ʼ��
void OLED_Init(void)
{
    RCC_APB2PeriphClockCmd(OLED_SPI_RCC|RCC_APB2Periph_AFIO|RCC_APB2Periph_SPI1, ENABLE);	 //ʹ��A�˿�ʱ��


	  GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_SCK_PIN | OLED_SPI_MOSI_PIN; // SPI SCK and MOSI
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OLED_SPI_DC_PIN|OLED_SPI_RES_PIN|OLED_SPI_CS1_PIN|OLED_SW_PIN; // OLED CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	  GPIO_SetBits(OLED_SPI_GPIO,OLED_SW_PIN);
    OLED_Spi_init();
    DMA_OLED_Init();
    OLED_RES_Clr();
    delay_1ms(200);
    OLED_RES_Set();

    OLED_WR_CMD(0xAE); /*display off*/
    OLED_WR_CMD(0x00); /*set lower column address*/
    OLED_WR_CMD(0x10); /*set higher column address*/
    OLED_WR_CMD(0x00); /*set display start line*/
    OLED_WR_CMD(0xB0); /*set page address*/
    OLED_WR_CMD(0x81); /*contract control*/
    OLED_WR_CMD(0xff); /*128*/
    OLED_WR_CMD(0xA1); /*set segment remap*/
    OLED_WR_CMD(0xA6); /*normal / reverse*/
    OLED_WR_CMD(0xA8); /*multiplex ratio*/
    OLED_WR_CMD(0x1F); /*duty = 1/32*/
    OLED_WR_CMD(0xC8); /*Com scan direction*/
    OLED_WR_CMD(0xD3); /*set display offset*/
    OLED_WR_CMD(0x00);
    OLED_WR_CMD(0xD5); /*set osc division*/
    OLED_WR_CMD(0x80);
    OLED_WR_CMD(0xD9); /*set pre-charge period*/
    OLED_WR_CMD(0x1f);
    OLED_WR_CMD(0xDA); /*set COM pins*/
    OLED_WR_CMD(0x00);
    OLED_WR_CMD(0xdb); /*set vcomh*/
    OLED_WR_CMD(0x40);
    OLED_WR_CMD(0x8d); /*set charge pump enable*/
    OLED_WR_CMD(0x14);
	//	OLED_WR_CMD(0xA7);//��ɫ��ʾ
    OLED_Clear();
    OLED_WR_CMD(0xAF); /*display ON*/
    CS_ALL_OFF();
}
