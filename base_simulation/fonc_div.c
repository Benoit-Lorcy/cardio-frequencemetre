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
	PD_DDR |= 0b10000001;
	PD_CR1 |= 0b10000001;
	PD_CR2 &= 0b01111110;
	PC_ODR |= 1 << 7;
	PD_ODR &= 0b01111110;
	SPI_CR1 = 0x14;
	SPI_CR2 = 0x03;
	SPI_CR1 |= 1 << 6;
	
	init_TFT();
}

void affiche_mot(uint8_t* mot, uint8_t col, uint8_t ligne) {
	while(*mot) {
		displayChar_TFT(col, ligne, *mot, ST7735_RED,ST7735_BLACK, 2);
		col = col + 11;
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

uint8_t read_ADC_8b(void) {
	uint8_t temps;
	ADC_CR1 |= 1;
	
	while((ADC_CSR & (1<<7)) == 0);
	temps = ADC_DRH;
	ADC_CSR &= ~(1<<7);
		
	return temps;
}

void init_Poussoirs(void){
	PE_DDR &= ~(1 << 5);
	PE_CR1 &= ~(1 << 5);
	PE_CR2 |= (1 << 5);
	
		
	PC_DDR &= ~(1 << 4);
	PC_CR1 &= ~(1 << 4);
	PC_CR2 |= (1 << 4);
	
	EXTI_CR1 |= (1<<5);
	EXTI_CR1 &=~ (1 << 4);
	
	//EXTI_CR2 &= ~1;
	//EXTI_CR2 |= 2;
	EXTI_CR2 |= 1<<1;
	EXTI_CR2 &= ~(1<<0);
}

void init_PD4(void){
	PD_DDR &= ~(1 << 4);
	PD_CR1 &= ~(1 << 4);
	PD_CR2 |= (1 << 4);
	
	EXTI_CR1 |= (1<<7);
	EXTI_CR1 |= (1<<6);
}

void init_timer3(void){
	uint16_t arr = 1600;
	CLK_PCKENR1 |= 1 << 6;
	
	TIM3_PSCR = 0;
	TIM3_ARRH = arr / 256;
	TIM3_ARRL = arr % 256;
	
	//TIM3_CCMR1 = 0x68;
	//TIM3_CCER1 &= ~(11);
	//TIM3_CCER1 |= 1;
	TIM3_CR1 = 0x81;
	TIM3_SR1 &= ~1;
}

void init_I2C_Slave(void) {
	I2C_FREQR = (I2C_FREQR & 0b11000000)| 0b00010000; 
	
		I2C_ITR &= ~1;
    I2C_ITR |= 6;

    I2C_CR1 &= 192;
    I2C_CR1 |= 1;

    I2C_CR2 &= 128;
    I2C_CR2 |= 4;

    I2C_OARH = 0b01000000 | (I2C_OARH & 0b00111001);
    I2C_OARL = 0b01010000 | (I2C_OARL & 1);

    CLK_PCKENR1 |= 1;

}

void init_timer1_2ms(void){
		CLK_PCKENR1 |= 1 << 7;
		
		TIM1_PSCRH = 999 / 256;
		TIM1_PSCRL = 999 % 256;
		TIM1_ARRH = 31 / 256;
		TIM1_ARRL = 31 % 256;
		TIM1_CR1 = 0;
		TIM1_IER |= 1;
		TIM1_SR1 = 0;
		TIM1_CR1 |= 1;
}
