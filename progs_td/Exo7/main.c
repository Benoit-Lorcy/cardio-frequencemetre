/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "iostm8s105.h"
#include "max7219.h"
#include "fonc_delay.h"
 
void init_ports_SPI(void) {
		CLK_PCKENR1 |= 1 << 1;
		
		PC_DDR |= 1 << 7;
		PC_CR1 |= 1 << 7;
		PC_CR2 &= ~(1 << 7);
		
		SPI_CR1 = 0x2f;
		SPI_CR2 = 0x03;
		
		SPI_CR1 |= 1 << 6;
}

void main(void) {
		uint8_t compteur = 0;
		
		init_ports_SPI();
		MAX7219_Init();
				
		for (;;) {
				MAX7219_Clear();
				MAX7219_DisplayChar(4, compteur % 10);
				MAX7219_DisplayChar(3, compteur / 10);
				
				compteur = compteur == 99 ? 0 : compteur + 1;
				
				attend_500ms();
		}
}