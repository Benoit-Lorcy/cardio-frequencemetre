/* INCLUDE ************************************************/
#include "iostm8s105.h"
#include "fonc_delay.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser fonctions de temporisation
#include "max7219.h" 		// demasquer et ajouter max7219.c dans le projet pour utiliser afficheurs 7 segments
// #include "fonc_tft.h" 	// demasquer et ajouter fonc_tft.c dans le projet pour utiliser ecran TFT
// #include "fonc_I2C.h" 	// demasquer et ajouter fonc_delay.c dans le projet pour utiliser liaison I2C


/* DEFINE *************************************************/
#define NOTES_PER_MS 526
#define TAB_LENGTH 34

/* VARIABLE ***********************************************/
/* Gamme de la bémol mineur */
uint16_t freq_note[7] = {
	415, /* Ab */
	466, /* Bb */
	523, /* C */
	554, /* Db */
	622, /* Eb */
	698, /* F */
	740, /* Gb */
};

int8_t music_notes[TAB_LENGTH] = {
	0, 1, 3, 1, 5, -1, 5, 4, -1,
	0, 1, 3, 1, 4, -1, 4, 3, 2, 1,
	0, 1, 3, 1, 3, 4, 2, 3, 0,
	-1, 0, 4, 3, -1,
};

float music_time_intervals[TAB_LENGTH] = {
	0.25, 0.25, 0.25, 0.25, 0.65, 0,1, 0.75, 1.0, 0.5,
	0.25, 0.25, 0.25, 0.25, 0.65, 0.1, 0.75, 0.5, 0.25, 0.75,
	0.25, 0.25, 0.25, 0.25, 0.75, 0.75, 0.25, 0.75, 0.5,
	0.5, 0.5, 1, 1, 1,
};

/* FUNCTION ***********************************************/
void init_timer2_PWM(void) {
	CLK_PCKENR1 |= 1 << 5;

	TIM2_PSCR = 0;
	
	TIM2_ARRH = 1;
	TIM2_ARRL = 1;
	
	TIM2_CCR1H = 1;
	TIM2_CCR1L = 1;

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
 	uint8_t i = 0;
	uint16_t wait = 0;
	init_ports_SPI();
	init_timer2_PWM();
	
	MAX7219_Init();

	for (;;) {
		for (i = 0; i < TAB_LENGTH; i++) {
			if (music_notes[i] < 0) {
				stop_PWM();
			} else {
				start_freq_PWM(freq_note[music_notes[i]], 0.5);
			}

			MAX7219_Clear();
			MAX7219_DisplayChar(4, music_notes[i]);
	
			wait = NOTES_PER_MS * music_time_intervals[i];
			attend_ms(wait);
		}
	}
}
