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
extern volatile uint8_t int_2ms_ok;
volatile uint8_t bit_to_transmit = 0;
volatile uint8_t demande = 0;

extern volatile uint8_t cmpt_ech;
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
    uint8_t sr3;
    uint8_t dr;

    if(I2C_SR2 & 0x04) { // No Ack
        I2C_SR2 &= ~0x04;    
    }

    if(I2C_SR2 & 7) { // Check line disconnected/errors, disable I2C
        I2C_CR1 &= ~1;
        return;
    }

    sr1 = I2C_SR1;
    sr3 = I2C_SR3;

    if( sr1 & (1 << 4) ) { // Stop detection, STOPF bit
        // Il faut ecrire dans CR2 pour gerer STOPF
        I2C_CR2 |= (1 << 7); // Bit SWRST: Software Reset
    }

    // Bit start + bonne addresse
    if( (sr1 & 0x2) && (sr3 & 0x2) ) {
        // Simplement lire sr1 et sr3 est suffisant pour valide cette etape
        return;
    }

    // Recoit-on de l'information (bit RxNE)
    if( sr1 & (1 << 6) ) {
        dr = I2C_DR;

        if(dr == 0b00011000) {
            demande = 0; // VIN0
        } else if(dr == 0b00101000) {
            demande = 1; // VIN1
        }
        return;
    }
		
		

    // Doit-on fournir de l'information (bit TxE)
    if ( (sr1 & (1 << 7)) ) {
			if (demande == 0) {
            if(bit_to_transmit == 0) {
                I2C_DR = (ac_cap >> 8) & 0xFF;
                bit_to_transmit = 1;
            } else if(bit_to_transmit == 1){
                I2C_DR = ac_cap & 0xFF;
                bit_to_transmit = 2;
            } else {
							I2C_DR = 0;
							bit_to_transmit = 0;
						}
        } else {
            if(bit_to_transmit == 0) {
                I2C_DR = (dc_cap >> 8) & 0xFF;
                bit_to_transmit = 1;
            } else if(bit_to_transmit == 1){
                I2C_DR = dc_cap & 0xFF;
                bit_to_transmit = 2;
            } else {
							I2C_DR = 0;
							bit_to_transmit = 0;
						}
        }
    }
}


@far @interrupt void int_timer1_2ms(void) {
	int_2ms_ok = 1;
	TIM1_SR1 &= ~1;
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
	{0x82, int_timer1_2ms}, /* irq11 */
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
