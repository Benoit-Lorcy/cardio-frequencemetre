/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "iostm8s105.h"

void init_timer2_pwm(uint16_t freq, float rap) {
		uint16_t ccr;
		
		CLK_PCKENR1 |= 1 << 5;
		
		TIM2_PSCR = 0;
		
		TIM2_ARRH = (2000000 / freq - 1) / 256;
		TIM2_ARRL = (2000000 / freq - 1) % 256;
		
		ccr = rap * (TIM2_ARRH * 256 + TIM2_ARRL + 1);
		TIM2_CCR1H = ccr / 256;
		TIM2_CCR1L = ccr % 256;
		
		TIM2_CCMR1 = 0x68;
		TIM2_CCER1 &= ~(1 << 1);
		TIM2_CCER1 |= 1 << 0;
		TIM2_CR1 = 0x81;
		
		PD_DDR |= 1 << 4;
		PD_CR1 |= 1 << 4;
		PD_CR2 &= ~(1 << 4);
}

void main(void) {
		init_timer2_pwm(250, 0.5);
	
		for (;;);
}