#ifndef __SPI0_H__
#define __SPI0_H__

#include "stm32f10x.h"
#include "systick.h"


/*************** pin config *****************/
#define OLED_42_SPI_CLK_RCC			RCC_APB2Periph_GPIOB
#define OLED_42_SPI_CLK_GPIO		GPIOB
#define OLED_42_SPI_CLK_PIN			GPIO_Pin_13
#define OLED_42_SPI_CLK_AF			GPIO_AF_SPI2
//#define OLED_42_SPI_CLK_AF_SRC	GPIO_PinSource3

#define OLED_42_SPI_MOSI_RCC		RCC_APB2Periph_GPIOB
#define OLED_42_SPI_MOSI_GPIO		GPIOB
#define OLED_42_SPI_MOSI_PIN		GPIO_Pin_15
#define OLED_42_SPI_MOSI_AF			GPIO_AF_SPI2
//#define OLED_42_SPI_MOSI_AF_SRC	GPIO_PinSource5

//#define MISO_RCU	RCU_GPIOB
//#define MISO_PORT	GPIOB
//#define MISO_PIN	GPIO_PIN_4
//#define MISO_AF		GPIO_AF_5

#define OLED_42_SPI_RCC		RCC_APB1Periph_SPI2
#define OLED_42_SPI				SPI2


void SPI0_init();
void SPI0_write_byte(uint8_t data);
//uint8_t SPI0_read_byte();



#endif