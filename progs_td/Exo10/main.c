/* INCLUDE ************************************************/
#include "iostm8s105.h"
#include "fonc_delay.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser fonctions de temporisation
#include "max7219.h" 		// demasquer et ajouter max7219.c dans le projet pour utiliser afficheurs 7 segments
// #include "fonc_tft.h" 	// demasquer et ajouter fonc_tft.c dans le projet pour utiliser ecran TFT
// #include "fonc_I2C.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser liaison I2C


/* DEFINE *************************************************/




/* VARIABLE ***********************************************/
uint16_t tab_freq_note[7] = {
	524,
	587,
	662,
	701,
	787,
	878,
	1004
};

/* FUNCTION ***********************************************/
void init_timer2_PWM(void) {
	CLK_PCKENR1 |= 1 << 5;

	TIM2_PSCR = 0;

	TIM2_CCMR1 = 0x68;
	TIM2_CCER1 &= ~(0b11);
	TIM2_CR1 = 0x81;

	PD_DDR |= 1 << 4;
	PD_CR1 |= 1 << 4;
	PD_CR2 &= ~(1 << 4);
}

void init_ports_SPI(void) {
	CLK_PCKENR1 |= 1 << 1;

	PC_DDR |= 1 << 7;
	PC_CR1 |= 1 << 7;
	PC_CR2 &= ~(1 << 7);

	SPI_CR1 = 0x2f;
	SPI_CR2 = 0x03;

	SPI_CR1 |= 1 << 6;
}

void start_freq_PWM(uint16_t freq, float rap) {
	uint16_t ccr;
	
	TIM2_ARRH = (2000000 / freq - 1) / 256;
	TIM2_ARRL = (2000000 / freq - 1) % 256;

	ccr = rap * (TIM2_ARRH * 256 + TIM2_ARRL + 1);
	TIM2_CCR1H = ccr / 256;
	TIM2_CCR1L = ccr % 256;

	TIM2_CCER1 |= 1;
}

void stop_PWM(void) {
	TIM2_CCER1 &= ~1;
}

/* MAIN ***************************************************/
void main(void) {
 	uint8_t note = 0;
	init_ports_SPI();
	init_timer2_PWM();
	
	MAX7219_Init();

	for (;;) {
		for (note = 0; note < 7; note++) {
			start_freq_PWM(tab_freq_note[note], 0.5);
			
			MAX7219_Clear();
			MAX7219_DisplayChar(4, note);
	
			attend_500ms();
		}
	}
}
