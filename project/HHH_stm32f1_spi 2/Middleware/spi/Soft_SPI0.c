#include "Soft_SPI0.h"


void SoftSPI0_init() {	
		/******************* GPIO **********************/
		GPIO_InitTypeDef  GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(OLED_42_SPI_SCK_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = OLED_42_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(OLED_42_SPI_SCK_GPIO, &GPIO_InitStructure);

		RCC_APB2PeriphClockCmd(OLED_42_SPI_MOSI_RCC,ENABLE);
		GPIO_InitStructure.GPIO_Pin = OLED_42_SPI_MOSI_PIN;
		GPIO_Init(OLED_42_SPI_MOSI_GPIO, &GPIO_InitStructure);
	
	
		/******************* io state ****************/
#if SPI0_CPOL
		CLK(1);
#else
		CLK(0);
#endif
}

static void CLK_START() {
#if SPI0_CPOL 
		CLK(1); 
#else 
		CLK(0);
#endif
}

static void CLK_END() {
#if SPI0_CPOL 
		CLK(0); 
#else 
		CLK(1);
#endif
}


void SoftSPI0_write_byte(uint8_t data) {
		
		uint8_t i;
		for(i = 0; i < 8; i++)
    {
        CLK_START();
        if(data&0x80)
            MOSI(1);
        else
            MOSI(0);
        CLK_END();
        data <<= 1;
    }
		CLK_START();
}

//uint8_t SoftSPI0_read_byte() {
//		uint8_t i,read=0;
//    for(i = 0; i < 8; i++)
//    {
//        CLK_START();
//        read<<=1;
//        if(MISO_STATE())
//        {
//            read++;
//        }
//        CLK_END();
//    }
//    CLK_START();
//    return read;
//}