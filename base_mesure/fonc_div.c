/*******************************************************************************
* Noms binome  :                                                                                         
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/

#include "fonc_div.h"

extern volatile uint16_t cpt_ech;
extern volatile uint16_t tab_cpt[8];

extern volatile uint16_t ac_cap;
extern volatile uint16_t dc_cap;
extern volatile uint8_t etat;
extern volatile uint8_t led_poul_counter;
extern volatile uint8_t BPM;

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

void affiche_nombre(uint16_t nombre, uint8_t col, uint8_t ligne) {
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

void init_Poussoirs(void) {
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

void init_timer1_2ms(void) {
		CLK_PCKENR1 |= 1 << 7;
		TIM1_PSCRH = 1 / 256;
		TIM1_PSCRL = 1 % 256;
		TIM1_ARRH = 15999 / 256;
		TIM1_ARRL = 15999 % 256;
		TIM1_CR1 = 0;
		TIM1_IER |= 1;
		TIM1_SR1 = 0;
		TIM1_CR1 |= 1;
}

void init_UART2(uint16_t UART_BAUDRATE) {
	
	uint16_t uart = 16000000/UART_BAUDRATE;
	
	CLK_PCKENR1 |= 1 << 3;
	
	UART2_BRR2 = (0xF0 & (uart >> 8)) | (0x0F & uart); // BRR2 first
	UART2_BRR1 = 0xFF & (uart >> 4);
	
	UART2_CR1 = 0b00000000; // M bit 0 for 8 bit word length
	UART2_CR2 = 0b00001100; // TEN bit(3) to allow transmitting
	UART2_CR3 &= 0b10000000; // STOP bit 00 (4,5) for 1 stop bit
	
	//page 329 instruction
}

void write_byte_UART2(uint8_t data) {
	UART2_DR = data;
	while( !(UART2_SR & (1<<7)) );
}

void init_timer2_pwm(void) {
	CLK_PCKENR1 |= 1 << 5;
	
	TIM2_PSCR = 4;
	TIM2_ARRH = 0;
	TIM2_ARRL = 99;
	TIM2_CCR1H = 0;
	TIM2_CCR1L = 50;
	
	TIM2_CCMR1 = 0x68;
	TIM2_CCER1 &= ~(1<<1);
	TIM2_CCER1 |= 1 << 0;
	TIM2_CR1 = 0x81;
	
	PD_DDR |= 1 << 4;
	PD_CR1 |= 1 << 4;
	PD_CR2 &= ~(1 << 4);
}

void machine_etat(void) {
	uint16_t cmpt_moyenne = 0;
	switch(etat) {
		case 1:
			if(ac_cap > 2148) {
				etat = 2;
			}
			break;
		case 2:
			if(ac_cap < 1948) {
				etat = 3;
				cpt_ech = 0;
			}
			break;
		case 3:
			if(ac_cap > 2148) {
				etat = 4;
				PB_ODR |= 1;
				led_poul_counter = 49;
			}
			break;
		case 4:
			if(ac_cap < 1948) {
				etat=3;
				cmpt_moyenne = (cpt_ech + tab_cpt[0] + tab_cpt[1] + tab_cpt[2] + tab_cpt[3] + tab_cpt[4] + tab_cpt[5] + tab_cpt[6] + tab_cpt[7]) / 9;
				tab_cpt[7] = tab_cpt[6];
				tab_cpt[6] = tab_cpt[5];
				tab_cpt[5] = tab_cpt[4];
				tab_cpt[4] = tab_cpt[3];
				tab_cpt[3] = tab_cpt[2];
				tab_cpt[2] = tab_cpt[1];
				tab_cpt[1] = tab_cpt[0];
				
				tab_cpt[0] = cpt_ech;
				cpt_ech = 0;
				BPM = (60 * 1000) / (cmpt_moyenne * 2);
			}
			break;
		default: etat = 1;
	}
}