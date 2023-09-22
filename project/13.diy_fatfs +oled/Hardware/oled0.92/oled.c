#include "oled.h"

u8 OLED_GRAM[144][8];
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
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(OLED_96_SPI, &SPI_InitStructure);
    //SPI_I2S_DMACmd(OLED_96_SPI, SPI_I2S_DMAReq_Tx,ENABLE);
    SPI_Cmd(OLED_96_SPI, ENABLE);
}
//void DMA_OLED_Init(void) {
//    // �жϽṹ��
//    DMA_InitTypeDef DMA_InitStructure;
//    RCC_AHBPeriphClockCmd(OLED_96_DAM_RCC, ENABLE); //ʹ�� DMA ʱ��
//    DMA_DeInit(OLED_96_DMA);

//    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(OLED_96_SPI->DR)); //SPI���ݼĴ�����ַ
//    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&OLED_GRAM; //���ý��ջ������׵�ַ
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //�Ӵ�������ȡ���͵�����
//    DMA_InitStructure.DMA_BufferSize = 1024; //DMA ͨ���� DMA ����Ĵ�С
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //8 λ
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8 λ
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //������ѭ������ģʽ
//    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA ͨ�� x ӵ�������ȼ�
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; ////DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
//    DMA_Init(OLED_96_DMA, &DMA_InitStructure); //����ָ���Ĳ�����ʼ��
//    //DMA_Cmd(DMA1_Channel3, DISABLE); //��ʹ��DMA1 CH3��ָʾ��ͨ��
//    DMA_Cmd(OLED_96_DMA, ENABLE); //ʹ��DMA1 CH3��ָʾ��ͨ��
//}


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
    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_TXE) == RESET) {}
    SPI_I2S_SendData(OLED_96_SPI, dat);
    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_BSY) == SET) {}
    while ((OLED_96_SPI->SR & SPI_SR_TXE) == RESET) {} // �ȴ��������
    OLED_DC_Set(); // OLED CS high for data
}

//void OLED_WR_DATA(u8 dat) {
//    // ȷ��SPI�������
//    OLED_DC_Set(); // OLED DC high for data
//    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_TXE) == RESET) {}
//    SPI_I2S_SendData(OLED_96_SPI, dat);
//    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_BSY) == SET) {}
//    while ((OLED_96_SPI->SR & SPI_SR_TXE) == RESET) {} // �ȴ��������
//    OLED_DC_Clr(); // refresh
//}

////void OLED_WR_CMD(u8 dat) {
////    // ȷ��SPI�������
////    OLED_DC_Clr(); // OLED CS low for cmd
////    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_TXE) == RESET) {} //�ǵüӡ��������ߡ�{}��
////    SPI_I2S_SendData(OLED_96_SPI, dat);
////    SPI_I2S_DMACmd(OLED_96_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
////    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_BSY) == SET) {} //�ǵüӡ�����	���ߡ�{}��
////    SPI_I2S_DMACmd(OLED_96_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
////    OLED_DC_Clr(); // OLED CS high for data
////}
void OLED_WR_DATA(u8 dat) {
// ȷ��SPI�������
    OLED_DC_Set(); // OLED DC high for data
    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_TXE) == RESET) {} //�ǵüӡ��������ߡ�{}��
    SPI_I2S_SendData(OLED_96_SPI, dat);
    SPI_I2S_DMACmd(OLED_96_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
    while (SPI_I2S_GetFlagStatus(OLED_96_SPI, SPI_I2S_FLAG_BSY) == SET) {} //�ǵüӡ�����	���ߡ�{}��
    SPI_I2S_DMACmd(OLED_96_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
    OLED_DC_Clr(); // refresh
}
void OLED_WR_Multi_Bytes(uint8_t *data, uint16_t size) {
    // ����DMA����
    DMA_Cmd(OLED_96_DMA, DISABLE);
    OLED_96_DMA->CNDTR = size; // ���ô������ݵ�����
    OLED_96_DMA->CMAR = (uint32_t)data; // ��������Դ��ַ
    OLED_96_DMA->CPAR = (uint32_t)(&(OLED_96_SPI->DR)); // ����SPI���ݼĴ�����ַ
    DMA_Cmd(OLED_96_DMA, ENABLE);
    // �ȴ�DMA�������
    while (DMA_GetFlagStatus(DMA2_FLAG_TC3) == RESET);
    // ���DMA������ɱ�־
    DMA_ClearFlag(DMA2_FLAG_TC3);
    // �ȴ�SPI�������
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET);
}

//�����Դ浽OLED
void OLED_Refresh(void)
{
    u8 i,n;
    u8 data_to_send[128 * 8]; // 128���� * 8��
    for(i=0; i<8; i++)
    {
        OLED_WR_CMD(0xb0+i); //��������ʼ��ַ
        OLED_WR_CMD(0x00);   //���õ�����ʼ��ַ
        OLED_WR_CMD(0x10);   //���ø�����ʼ��ַ
        for(n=0; n<128; n++) {
            OLED_WR_DATA(OLED_GRAM[n][i]);
            data_to_send[n] = OLED_GRAM[n][i];
        }
        // ʹ�õ��κ������÷�������
        // ���� OLED_WR_Multi_Bytes ��һ�����ڷ��Ͷ���ֽڵĺ���
        // OLED_WR_Multi_Bytes(data_to_send, 128);
        //OLED_WR_DATA(OLED_GRAM[n][i]);
    }
}


//��������
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
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


void CS_ALL_OFF() {
    for (int i=0; i<OLED_NUM; i++) {
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
    RCC_APB2PeriphClockCmd(OLED_96_SPI_GPIO_RCC|RCC_APB2Periph_AFIO|OLED_96_CS_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��
    RCC_APB2PeriphClockCmd(OLED_96_SPI_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��
	 
	
	
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_SCK_PIN | OLED_SPI_MOSI_PIN; // SPI SCK and MOSI
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(OLED_SPI_GPIO, &GPIO_InitStructure);

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG����(PB3/4)��ֻʹ��SWD(PA13/14)����
   	GPIO_PinRemapConfig(GPIO_Remap_SPI1 , ENABLE);//�ͷ�GPIO_Remap_SPI1 ����
	
    GPIO_InitStructure.GPIO_Pin = OLED_SPI_DC_PIN|OLED_SPI_RES_PIN|OLED_SW_PIN; // OLED CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OLED_SPI_GPIO, &GPIO_InitStructure);
    GPIO_SetBits(OLED_SPI_GPIO,OLED_SW_PIN);


    GPIO_InitStructure.GPIO_Pin = OLED_96_CS1_PIN; // OLED CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OLED_96_CS_GPIO, &GPIO_InitStructure);

      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG����(PB3/4)��ֻʹ��SWD(PA13/14)����


    OLED_Spi_init();
   // DMA_OLED_Init();
    OLED_RES_Clr();
    delay_1ms(200);
    OLED_RES_Set();

    OLED_WR_CMD(0xAE);//--turn off oled panel
    OLED_WR_CMD(0x00);//---set low column address
    OLED_WR_CMD(0x10);//---set high column address
    OLED_WR_CMD(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_CMD(0x81);//--set contrast control register
    OLED_WR_CMD(0xCF);// Set SEG Output Current Brightness
    OLED_WR_CMD(0xA1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_CMD(0xC8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_CMD(0xA6);//--set normal display
    OLED_WR_CMD(0xA8);//--set multiplex ratio(1 to 64)
    OLED_WR_CMD(0x3f);//--1/64 duty
    OLED_WR_CMD(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_CMD(0x00);//-not offset
    OLED_WR_CMD(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WR_CMD(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_CMD(0xD9);//--set pre-charge period
    OLED_WR_CMD(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_CMD(0xDA);//--set com pins hardware configuration
    OLED_WR_CMD(0x12);
    OLED_WR_CMD(0xDB);//--set vcomh
    OLED_WR_CMD(0x40);//Set VCOM Deselect Level
    OLED_WR_CMD(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_CMD(0x02);//
    OLED_WR_CMD(0x8D);//--set Charge Pump enable/disable
    OLED_WR_CMD(0x14);//--set(0x10) disable
    OLED_WR_CMD(0xA4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_CMD(0xA6);// Disable Inverse Display On (0xa6/a7)
    OLED_Clear();
    OLED_WR_CMD(0xAF);
    CS_ALL_OFF();
}

