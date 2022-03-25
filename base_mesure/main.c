/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
// MESURE
 
#include "fonc_div.h"
#include "defs.h"
#include "fonc_delay.h"

void send_ac_cap_UART(uint16_t cap) {
	write_byte_UART2((cap >> 8) & 0x0F);
	write_byte_UART2(((cap >> 4) & 0x0F) | 0x10);
	write_byte_UART2(((cap >> 0) & 0x0F) | 0x20);
}

void send_dc_cap_UART(uint16_t cap) {
	write_byte_UART2(((cap >> 8) & 0x0F) | 0x80);
	write_byte_UART2(((cap >> 4) & 0x0F) | 0x90);
	write_byte_UART2(((cap >> 0) & 0x0F) | 0xA0);
}

void init_ecran_defaut(void) {
	MODE = 0;
	
	fillScreen_TFT(ST7735_BLACK);
	
	affiche_mot(Mesure, 28, 5);
	affiche_mot(Bpm, 1, 40);
	affiche_mot(Seuil_bas, 1, 70);
	affiche_mot(Seuil_haut, 1, 100);
	affiche_mot(Puis, 1, 130);
	
	affiche_nombre(sal_bas, 90, 70);
	affiche_nombre(sal_haut, 90, 100);
	affiche_nombre(BPM, 90, 40);
}

void init_ecran_couleurs(void) {
	MODE = 1;
	
	fillScreen_TFT(ST7735_BLACK);

	affiche_mot(Fond, 1, 10);
	affiche_mot(Texte, 1, 40);
	affiche_mot(Valeurs, 1, 70);
}

main()
{
	uint8_t old_adc_drh = 0;
	uint16_t calc_ccr = 0;
	
	CLK_CKDIVR &= 0b11100000;
	
	init_SPI();
	init_TFT();
	init_Poussoirs();
	init_LED();
	init_ADC();
	
	init_timer1_2ms();
	init_timer2_pwm();
	init_UART2(57600);
	
	init_I2C();
	
	couleur_fond = ST7735_BLACK;
	couleur_texte = ST7735_RED;
	couleur_valeurs = ST7735_YELLOW;
	
	init_ecran_defaut();
	
	ADC_CR1 |= 1;
	EnableGeneralInterrupt();
	
	while (1) {
		if (BPM <= sal_bas || BPM >= sal_haut) {
			PB_ODR |= 2;
		} else {
			PB_ODR &= ~2;
		}
		
		if(ADC_CSR & (1<<7)) {
			if(old_adc_drh != ADC_DRH) {
				PUIS = (ADC_DRH * 100) / 255;
				affiche_nombre(PUIS, 90, 130);
				old_adc_drh = ADC_DRH;
				
				TIM2_CCR1H = PUIS / 256;
				TIM2_CCR1L = PUIS % 256;
			}
			ADC_CSR &= ~(1<<7);
			ADC_CR1 |= 1;
		}
		
		if(int_2ms_ok == 1) {
			int_2ms_ok = 0;
			cpt_ech++;
			
			ac_cap = read_AD7991(0b00011000);
			dc_cap = read_AD7991(0b00101000);
			
			if(cpt_ech == 0 > 1500) { // 20bpm cutoff
				cpt_ech = 0;
				affiche_nombre(888, 90, 40);

			} else {
				machine_etat();
			}
			send_ac_cap_UART(2000);
			send_dc_cap_UART(1000);
		}
	}
}