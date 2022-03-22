/*******************************************************************************
* Noms binome  :                                                                                         
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/

#include "fonc_div.h"

#include "fonc_tft.h"

void init_SPI(void) {
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
}


void affiche_mot(uint8_t* mot, uint8_t col, uint8_t ligne) {
	while(*mot) {
		displayChar_TFT(col, ligne, *mot, ST7735_RED,ST7735_BLACK, 2);
		col += 11;
		mot++;
	}
}

void affiche_nombre(unsigned short nombre, uint8_t col, uint8_t ligne) {
	if(nombre < 1000) {
		displayChar_TFT(col, ligne, '0'+(nombre/100), ST7735_YELLOW, ST7735_BLACK, 2);
		displayChar_TFT(col+11, ligne, '0'+((nombre%100)/10), ST7735_YELLOW, ST7735_BLACK, 2);
		displayChar_TFT(col+11*2, ligne, '0'+(nombre%10), ST7735_YELLOW, ST7735_BLACK, 2);
	}
}

void init_ADC(void) {
	CLK_PCKENR2 |= (1<<3);
	
	PF_DDR &= ~(1 << 4);
	PF_CR1 &= ~(1 << 4);
	PF_CR2 &= ~(1 << 4);
	
	ADC_CSR = 0x0C;
	ADC_CR1 = 0x01;
	ADC_CR2 = 0x00;
}

void init_Poussoirs() {
	PE_DDR &= ~(1 << 5);
	PE_CR1 &= ~(1 << 5);
	PE_CR2 |= (1 << 5);
	
	PD_DDR &= ~(1 << 3);
	PD_CR1 &= ~(1 << 3);
	PD_CR2 |= (1 << 3);
	
	PC_DDR &= ~(1 << 4);
	PC_CR1 &= ~(1 << 4);
	PC_CR2 |= (1 << 4);
	
	EXTI_CR1 |= (1<<6)|(1<<4);
	EXTI_CR1 &= 0b01011111;
	
	EXTI_CR2 |= 1;
	EXTI_CR2 &= ~2;
}

void init_LED(void) {
	PB_DDR|=7; //bit 0 � 1 pour le push pull en sortie
  PB_CR1|=7;
	PB_CR2|=7;
}