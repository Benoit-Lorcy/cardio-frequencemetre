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
	while( !(UART2_SR & (1<<6)) );
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
	CLK_CKDIVR = 0;
	BPM = 50;
	
	init_SPI();
	init_TFT();
	init_Poussoirs();
	
	init_PWM();
	init_I2C();
	init_UART2();
	
	init_spi_port_display();
	
	affiche_mot("Mon beau mot", 4, 4);
	affiche_nombre(345, 12, 12);
	
	// enableInterrupts
	
	while (1);
}