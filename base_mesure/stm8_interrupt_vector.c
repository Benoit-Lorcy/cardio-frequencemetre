/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */
#include "fonc_div.h"

extern volatile uint8_t sal_bas;
extern volatile uint8_t sal_haut;
extern volatile uint16_t int_2ms_ok;

extern volatile uint8_t led_poul_counter;
extern volatile uint16_t cpt_ech;

extern volatile uint8_t MODE;
extern volatile uint8_t Selection_couleur; // 0 = Fond, 1 = Text, 2 = Valeurs

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

@far @interrupt void int_PE5(void)
{
	if(MODE == 0) {
		sal_bas += 2;
		if(sal_bas > 60) {
			sal_bas = 40;
		}
		
		affiche_nombre(sal_bas, 90, 70);
	} else {
		
	}
	return;
}

extern void init_ecran_defaut(void);
extern void init_ecran_couleurs(void);

@far @interrupt void int_PC4 (void) {
	if(MODE == 0) {
		init_ecran_couleurs();
	} else {
		init_ecran_defaut();
	}
	return;
}

@far @interrupt void int_PD3 (void)
{
	if(MODE == 0) {
		sal_haut -= 10;
		if(sal_haut < 100) {
			sal_haut = 240;
		}
		
		affiche_nombre(sal_haut, 90, 100);
	} else {
		
	}
	return;
}

@far @interrupt void int_timer1_2ms (void)
{
	if(int_2ms_ok == 1) {
			TIM1_SR1 &= ~1;
		return;
	}
	int_2ms_ok = 1;
	
	if(led_poul_counter > 0) {
		led_poul_counter--;
	} else {
		PB_ODR &= ~1;
	}
	
	TIM1_SR1 &= ~1;
	return;
}

extern void _stext();     /* startup routine */

struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, /* reset */
	{0x82, NonHandledInterrupt}, /* trap  */
	{0x82, NonHandledInterrupt}, /* irq0  */
	{0x82, NonHandledInterrupt}, /* irq1  */
	{0x82, NonHandledInterrupt}, /* irq2  */
	{0x82, NonHandledInterrupt}, /* irq3  */
	{0x82, NonHandledInterrupt}, /* irq4  */
	{0x82, int_PC4}, /* irq5  */
	{0x82, int_PD3}, /* irq6  */
	{0x82, int_PE5}, /* irq7  */
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, int_timer1_2ms}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */
	{0x82, NonHandledInterrupt}, /* irq14 */
	{0x82, NonHandledInterrupt}, /* irq15 */
	{0x82, NonHandledInterrupt}, /* irq16 */
	{0x82, NonHandledInterrupt}, /* irq17 */
	{0x82, NonHandledInterrupt}, /* irq18 */
	{0x82, NonHandledInterrupt}, /* irq19 */
	{0x82, NonHandledInterrupt}, /* irq20 */
	{0x82, NonHandledInterrupt}, /* irq21 */
	{0x82, NonHandledInterrupt}, /* irq22 */
	{0x82, NonHandledInterrupt}, /* irq23 */
	{0x82, NonHandledInterrupt}, /* irq24 */
	{0x82, NonHandledInterrupt}, /* irq25 */
	{0x82, NonHandledInterrupt}, /* irq26 */
	{0x82, NonHandledInterrupt}, /* irq27 */
	{0x82, NonHandledInterrupt}, /* irq28 */
	{0x82, NonHandledInterrupt}, /* irq29 */
};
