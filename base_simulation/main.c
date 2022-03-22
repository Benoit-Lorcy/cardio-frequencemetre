/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
 // SIMULATION
 
#include <iostm8s105.h>

// Init PWM connection for PUIS
void init_pwm(void) {
	
}

// Init I2C Slave connection with interruptions
void init_I2C(void) {
	
}

main()
{
	init_pwm();
	init_I2C();
	
	// enableInterrupts
	
	while (1);
}