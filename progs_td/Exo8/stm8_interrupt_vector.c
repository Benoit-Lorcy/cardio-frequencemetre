/***********************************************************
* TITLE: stm8_interrupt_vector.c               
* AUTHOR:               
* DESCRIPTION: table vecteur d'interruption
* VERSION : 1.1
***********************************************************/
#include "iostm8s105.h"

/* EXTERNAL INTERRUPT FUNCTION ****************************/
extern void _stext();     /* startup routine */


/* DEFINITION TYPE ****************************************/

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};


/* INTERRUPT FUNCTION *************************************/

@far @interrupt void NonHandledInterrupt (void) {
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

extern uint8_t tempo_500ms_ok;
extern uint8_t marche;

@far @interrupt void int_timer_500ms(void) {
		tempo_500ms_ok = 1;
		TIM1_SR1 &= ~1;
}

@far @interrupt void int_PE5(void) {
		marche = 1;
}

@far @interrupt void int_PD3(void) {
		marche = 0;
}

/* INTERRUPT VECTOR TABLE *********************************/
struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, // RESET	
	{0x82, NonHandledInterrupt}, // TRAP : software interrupt 
	{0x82, NonHandledInterrupt}, // irq0 : TLI external Top Level Interrupt
	{0x82, NonHandledInterrupt}, // irq1 : AWU Autoo Wake Upu from Halt
	{0x82, NonHandledInterrupt}, // irq2 : CLK clock controller
	{0x82, NonHandledInterrupt}, // irq3 : EXTI0 PORT A external interrupt
	{0x82, NonHandledInterrupt}, // irq4 : EXTI1 PORT B external interrupt
	{0x82, NonHandledInterrupt}, // irq5 : EXTI2 PORT C external interrupt
	{0x82, int_PD3}, // irq6 : EXTI3 PORT D external interrupt
	{0x82, int_PE5}, // irq7 : EXTI4 PORT E external interrupt
	{0x82, NonHandledInterrupt}, // irq8
	{0x82, NonHandledInterrupt}, // irq9
	{0x82, NonHandledInterrupt}, // irq10 : SPI end of transfert
	{0x82, int_timer_500ms}, // irq11 : TIM1 update/overflow/underflow/trigger/break
	{0x82, NonHandledInterrupt}, // irq12 : TIM1 capture/compare
	{0x82, NonHandledInterrupt}, // irq13 : TIM2 update/overflow 
	{0x82, NonHandledInterrupt}, // irq14 : TIM2 capture/compare 
	{0x82, NonHandledInterrupt}, // irq15 : TIM3 update/overflow 
	{0x82, NonHandledInterrupt}, // irq16 : TIM3 capture/compare 
	{0x82, NonHandledInterrupt}, // irq17
	{0x82, NonHandledInterrupt}, // irq18
	{0x82, NonHandledInterrupt}, // irq19 : I2C
	{0x82, NonHandledInterrupt}, // irq20 : UART TX complete
	{0x82, NonHandledInterrupt}, // irq21 : UART Receive register DATA full
	{0x82, NonHandledInterrupt}, // irq22 : ADC end of conversion/ analog watchdof interrupt
	{0x82, NonHandledInterrupt}, // irq23 : TIM4 update/overflow
	{0x82, NonHandledInterrupt}, // irq24 : FLASH EOP/WR_PG_DIS
	{0x82, NonHandledInterrupt}, // irq25
	{0x82, NonHandledInterrupt}, // irq26
	{0x82, NonHandledInterrupt}, // irq27
	{0x82, NonHandledInterrupt}, // irq28
	{0x82, NonHandledInterrupt}, // irq29
};
