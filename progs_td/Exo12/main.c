/* INCLUDE ************************************************/
#include "iostm8s105.h"
#include "fonc_delay.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser fonctions de temporisation
// #include "max7219.h" 		// demasquer et ajouter max7219.c dans le projet pour utiliser afficheurs 7 segments
#include "fonc_tft.h" 	// demasquer et ajouter fonc_tft.c dans le projet pour utiliser ecran TFT
// #include "fonc_I2C.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser liaison I2C


/* DEFINE *************************************************/




/* VARIABLE ***********************************************/




/* FUNCTION ***********************************************/
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
}

void affiche(uint16_t nombre) {
	uint8_t compte_mil = (nombre / 1000) % 10;
	uint8_t compte_cen = (nombre / 100) % 10;
	uint8_t compte_diz = (nombre / 10) % 10;
	uint8_t compte_uni = nombre % 10;

	displayChar_TFT(40, 80, compte_mil + 0x30, ST7735_YELLOW, ST7735_BLACK, 2);
	displayChar_TFT(52, 80, compte_cen + 0x30, ST7735_YELLOW, ST7735_BLACK, 2);
	displayChar_TFT(64, 80, compte_diz + 0x30, ST7735_YELLOW, ST7735_BLACK, 2);
	displayChar_TFT(76, 80, compte_uni + 0x30, ST7735_YELLOW, ST7735_BLACK, 2);
}

/* MAIN ***************************************************/
void main(void) {
	uint16_t valeur_affiche = 2389;
	
	init_spi_port_display();
	init_TFT();

	affiche(3920);

	for (;;) {
		affiche(valeur_affiche++);
		attend_ms(50);
	}
}
