/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "iostm8s105.h"
#include "max7219.h"

volatile uint8_t tempo_500ms_ok = 0;
volatile uint8_t marche = 1;

void init_ports_SPI(void) {
		CLK_PCKENR1 |= 1 << 1;
		
		PC_DDR |= 1 << 7;
		PC_CR1 |= 1 << 7;
		PC_CR2 &= ~(1 << 7);
		
		SPI_CR1 = 0x2f;
		SPI_CR2 = 0x03;
		
		SPI_CR1 |= 1 << 6;
}

void init_interrupt_ext(void) {
		PE_DDR &= ~(1 << 5);
		PE_CR1 &= ~(1 << 5);
		PE_CR2 |= 1 << 5;
		
		PD_DDR &= ~(1 << 3);
		PD_CR1 &= ~(1 << 3);
		PD_CR2 |= 1 << 3;
		
		EXTI_CR1 |= 1 << 7;
		EXTI_CR1 &= ~(1 << 6);

		EXTI_CR2 |= 1 << 1;
		EXTI_CR2 &= ~(1 << 0);
}

void init_timer1(void) {
		CLK_PCKENR1 |= 1 << 7;
		
		TIM1_PSCRH = 24999 / 256;
		TIM1_PSCRL = 24999 % 256;
		
		TIM1_ARRH = 39 / 256;
		TIM1_ARRL = 39 % 256;
		
		TIM1_CR1 = 0;
		
		TIM1_IER |= 1;
		TIM1_SR1 = 0;
		
		TIM1_CR1 |= 1;
}

void affiche_compteur(uint8_t n) {
		MAX7219_Clear();
		MAX7219_DisplayChar(4, n % 10);
		MAX7219_DisplayChar(3, n / 10);
}

void main(void) {
		uint8_t compteur = 0;
		
		init_ports_SPI();
		init_timer1();
		init_interrupt_ext();
		MAX7219_Init();
		
		EnableGeneralInterrupt();
		
		for (;;) {
				if (tempo_500ms_ok) {
						tempo_500ms_ok = 0;
						
						if (marche) {
								affiche_compteur(compteur);
								compteur = (compteur + 1) % 100;
						}
				}
		}
}