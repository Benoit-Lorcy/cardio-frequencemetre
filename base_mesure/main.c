/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
// MESURE
 
#include "fonc_div.h"
#include "defs.h"
#include "fonc_I2C.h"
#include "fonc_delay.h"


void init_PWM(void) {
	
}

void init_I2C(void) {
	//Init_I2C();
}

uint16_t read_AD7991(uint8_t octet_conf) {
	uint16_t data;
	
	Start_I2C();
	Write_I2C(0b01010000);
	Write_I2C(octet_conf);
	Stop_I2C();
	
	Start_I2C();
	Write_I2C(0b01010001);
	
	Ack_I2C();
	data = Read_I2C() << 8;
	
	NoAck_I2C();
	data |= Read_I2C();
	
	Stop_I2C();
	
	return data;
}

void init_UART2(void) {
	uint16_t uart = 277;
	
	UART2_BRR2 = 0xF0 & (uart >> 4) + 0xF & uart; // BRR2 first
	UART2_BRR1 = 0xF & (uart >> 4);
	
	UART2_CR2 = 0x08; // TEN bit(3) to allow transmitting
	
	UART2_CR1 = 0b00000000; // M bit 0 for 8 bit word length
	UART2_CR3 = 0b00000000; // STOP bit 00 (4,5) for 1 stop bit
	
	//page 329 instruction
}

void write_byte_UART2(uint8_t data) {
	UART2_DR = data;
	while( !(UART2_SR & (1<<7)) );
}

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

main()
{
	uint8_t old_adc_drh = 0;
	
	CLK_CKDIVR = 0;
	BPM = 50;
	
	init_SPI();
	init_TFT();
	init_Poussoirs();
	init_LED();
	init_ADC();
	
	fillScreen_TFT(ST7735_BLACK);
	
	affiche_mot(Mesure, 28, 5);
	affiche_mot(Bpm, 1, 40);
	affiche_mot(Seuil_bas, 1, 70);
	affiche_mot(Seuil_haut, 1, 100);
	affiche_mot(Puis, 1, 130);
	
	affiche_nombre(sal_bas, 90, 70);
	affiche_nombre(sal_haut, 90, 100);
	affiche_nombre(BPM, 90, 40);
	
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
			}
			ADC_CSR &= ~(1<<7);
			ADC_CR1 |= 1;
		}
	}
}