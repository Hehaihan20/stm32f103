#include "SPI0.h"
#include <stdio.h>


void SPI0_init() {

    /************************** GPIO **********************/
		GPIO_InitTypeDef  GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // sclk	
		RCC_APB2PeriphClockCmd(OLED_42_SPI_CLK_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = OLED_42_SPI_CLK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(OLED_42_SPI_CLK_GPIO, &GPIO_InitStructure);

    // mosi
    RCC_APB2PeriphClockCmd(OLED_42_SPI_MOSI_RCC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = OLED_42_SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(OLED_42_SPI_MOSI_GPIO, &GPIO_InitStructure);

    // miso
//    rcu_periph_clock_enable(MISO_RCU);
//    gpio_mode_set(MISO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, MISO_PIN);
//    gpio_output_options_set(MISO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, MISO_PIN);
//    gpio_af_set(MISO_PORT, MISO_AF, MISO_PIN);
//    gpio_bit_set(MISO_PORT, MISO_PIN);  

    /************************** SPI **********************/
		RCC_APB1PeriphClockCmd(OLED_42_SPI_RCC, ENABLE);
		SPI_I2S_DeInit(OLED_42_SPI);
		
		SPI_InitTypeDef param;
		SPI_StructInit(&param);
		param.SPI_Mode = SPI_Mode_Master;
		param.SPI_DataSize = SPI_DataSize_8b;
		param.SPI_CPOL = SPI_CPOL_Low;
		param.SPI_CPHA = SPI_CPHA_1Edge;
		param.SPI_NSS = SPI_NSS_Soft;
		param.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		param.SPI_FirstBit = SPI_FirstBit_MSB;

    SPI_Init(OLED_42_SPI, &param);
    SPI_Cmd(OLED_42_SPI, ENABLE);
}

void SPI0_write_byte(uint8_t data) {
    while(RESET == SPI_I2S_GetFlagStatus(OLED_42_SPI, SPI_I2S_FLAG_TXE)) {};
    SPI_I2S_SendData(OLED_42_SPI, data);
    while(RESET == SPI_I2S_GetFlagStatus(OLED_42_SPI, SPI_I2S_FLAG_RXNE)) {};
    SPI_I2S_ReceiveData(OLED_42_SPI);
}

//uint8_t SPI0_read_byte() {
//    while(RESET == SPI_I2S_GetFlagStatus(OLED_42_SPI, SPI_I2S_FLAG_TXE)) {};
//    SPI_I2S_SendData(OLED_42_SPI, 0x00);
//    while(RESET == SPI_I2S_GetFlagStatus(OLED_42_SPI, SPI_I2S_FLAG_RXNE)) {};
//    return SPI_I2S_ReceiveData(OLED_42_SPI);
//}

