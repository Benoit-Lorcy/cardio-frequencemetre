/*******************************************************************************
* Noms binome  :                                                                                         
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/
#include "fonc_div.h"

void init_SPI(void){
			CLK_PCKENR1 |= 1 << 1;
		PC_DDR |= 1 << 7;
		PC_CR1 |= 1 << 7;
		PC_CR2 &= ~(1 << 7);
		SPI_CR1 = 0x2f;
		SPI_CR2 = 0x03;
		
		SPI_CR1 |= 1 << 6;
}

void affiche_mot(uint8_t * mot, uint8_t col, uint8_t ligne){
	
}

void affiche_nombre(uint16_t nombre, uint8_t col, uint8_t ligne){
	
}

uint8_t init_ADC(void) {
	
}

uint8_t read_ADC_8b(void) {
	
}

void init_Poussoirs(void){
	
}