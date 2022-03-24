/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */
#include <iostm8s105.h>

extern volatile uint8_t k;
extern volatile uint8_t mod_BPM;
extern volatile uint8_t mod_MODE;
extern volatile uint16_t PUIS;
extern volatile uint16_t ac_cap;
extern volatile uint16_t dc_cap;
volatile uint8_t etat = 0;
volatile uint8_t demande = 0;


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

@far @interrupt void int_PE5(void){
	mod_BPM=1;
	k=(k&7)+1;
	return;
}

@far @interrupt void int_PC4(void){
	mod_MODE=1;
	return;
}

@far @interrupt void int_PD4(void){
	if(!(PD_IDR & (1<<4))) PUIS	= ((TIM3_CNTRH << 8) + TIM3_CNTRL + 8)/16;
	TIM3_CNTRH = 0;
	TIM3_CNTRL = 0;
}

@far @interrupt void Int_I2C(void) {
    uint8_t sr1;
    uint8_t sr3 = I2C_SR2;
		
	if(I2C_SR2 & 7) {
		I2C_CR1 &= ~1;
		return;
	}
    switch(etat) // Premiere connexion, demande de lecture de ViN0/Vin1
    {
    case 0: // Nouvelle connexion
        sr1 = I2C_SR1;
        sr3 = I2C_SR3;
        // ADDR mit a 0 automatiquement
        if((sr1 & 0x2) && (sr3 & 0x2)) { // Toujours vraie
            if(sr3 & 0x4) {
                etat = 3; // Ecriture
            } else {
                etat = 1; // Lecture instruction
            }
        }
        break;
    case 1:
        sr1 = I2C_DR; // RxNE mit a 0 automatiquement

        if(sr1 == 0b00011000) {
            demande = 0; // VIN0
        } else if(sr1 == 0b00101000) {
            demande = 1; // VIN1
        }
        etat = 0; // STOP
        break;
    case 2:
        sr1 = I2C_SR1;

        if(sr1 & 0x10) {
            etat = 0;
        }
        break;
    case 3:
        sr1 = I2C_SR1;

        if(sr1 & 0x80) {
            if(demande == 0) {
                I2C_DR = ac_cap & 0xFF;
            } else if(demande == 1) {
                I2C_DR = dc_cap & 0xFF;
            }
            etat = 4;
        }
        break;
    case 4:
					sr1 = I2C_SR1;
        if(sr1 & 0x80) {
            if(demande == 0) {
                I2C_DR = (ac_cap >> 8) & 0xFF;
            } else if(demande == 1) {
                I2C_DR = (dc_cap >> 8)& 0xFF;
            }
            etat = 5; // No Ack
        }
        break;
    case 5:
        etat = 0;
        I2C_SR2 &= ~4;
    default:
			break;
		}
		
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
	{0x82, int_PD4}, /* irq6  */
	{0x82, int_PE5}, /* irq7  */
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, NonHandledInterrupt}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */
	{0x82, NonHandledInterrupt}, /* irq14 */
	{0x82, NonHandledInterrupt}, /* irq15 */
	{0x82, NonHandledInterrupt}, /* irq16 */
	{0x82, NonHandledInterrupt}, /* irq17 */
	{0x82, NonHandledInterrupt}, /* irq18 */
	{0x82, Int_I2C}, /* irq19 */
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
