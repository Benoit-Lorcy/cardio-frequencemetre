/*******************************************************************************
* Noms binome  :                                                                                         
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/

#include "fonc_div.h"

void init_spi_port_display(void) {
	CLK_PCKENR1 |= 1 << 1;
	PC_DDR |= 1 << 7;
	PC_CR1 |= 1 << 7;
	PC_CR2 &= ~(1 << 7);
	PD_DDR |= 0b10000001;
	PD_CR1 |= 0b10000001;
	PD_CR2 &= 0b01111110;
	PC_ODR |= 1 << 7;
	PD_ODR &= 0b01111110;
	
	SPI_CR1 = 0x14;
	SPI_CR2 = 0x03;
	SPI_CR1 |= 1 << 6;
	
	init_TFT();
}

void affice_mot(uint8_t* mot, uint8_t col, uint8_t ligne) {
	while(*mot) {
		displayChar_TFT(col+5, ligne, *mot, ST7735_RED,ST7735_BLACK, 1);
		mot++;
	}
}

void affiche_nombre(uint16_t nombre, uint8_t col, uint_t ligne) {
	if(nombre < 1000) {
		displayChar_TFT(col, ligne, '0'+(nombre/100), ST7735_YELLOW, ST7735_BLACK, 1);
		displayChar_TFT(col+5, ligne, '0'+((nombre%100)/10), ST7735_YELLOW, ST7735_BLACK, 1);
		displayChar_TFT(col+5*2, ligne, '0'+(nombre%10), ST7735_YELLOW, ST7735_BLACK, 1);
	}
}

void init_ADC(void) {
	
}

void init_Poussoirs() {
	
}

void init_LED(void) {
	
}