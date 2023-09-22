#ifndef __SOFT_SPI0_H__
#define __SOFT_SPI0_H__

#include "stm32f10x.h"
#include "systick.h"


/*************** pin config *****************/
//SCK
#define OLED_42_SPI_SCK_RCC		RCC_APB2Periph_GPIOB
#define OLED_42_SPI_SCK_GPIO	GPIOB
#define OLED_42_SPI_SCK_PIN		GPIO_Pin_13

//MOSI
#define OLED_42_SPI_MOSI_RCC	RCC_APB2Periph_GPIOB
#define OLED_42_SPI_MOSI_GPIO	GPIOB
#define OLED_42_SPI_MOSI_PIN	GPIO_Pin_15


//#define MISO_RCU	RCU_GPIOB
//#define MISO_PORT	GPIOB
//#define MISO_PIN	GPIO_PIN_4

/************** spi config *******************/
// clock polarity: hight(0) or low(1)
#define SPI0_CPOL		0
// clock phase: leading(0) or trailing(1)
#define SPIO_CPHA		0


/*************** gpio opt ********************/
#define CLK(bit)		GPIO_WriteBit(OLED_42_SPI_SCK_GPIO, OLED_42_SPI_SCK_PIN, bit ? Bit_SET : Bit_RESET)
#define MOSI(bit)		GPIO_WriteBit(OLED_42_SPI_MOSI_GPIO, OLED_42_SPI_MOSI_PIN, bit ? Bit_SET : Bit_RESET)

//#define MISO_STATE() GPIO_ReadInputDataBit(MISO_PORT, MISO_PIN)

void SoftSPI0_init();
void SoftSPI0_write_byte(uint8_t data);
//uint8_t SoftSPI0_read_byte();

#endif