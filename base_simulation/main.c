/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
 // SIMULATION
 
//#include <iostm8s105.h>
#include "fonc_div.h"
#include "defs.h"
/*
// Init PWM connection for PUIS
void init_pwm(void) {
	
}

// Init I2C Slave connection with interruptions
void init_I2C(void) {
	
}
*/
#define PUIS=40
#define BPM=30
#define MODE=0
#define CLK_CKDIVR=

main()
{
	EnableGeneralInterrupt();
	init_SPI();
	init_TFT();
	init_Poussoirs();
	affiche_mot("TEST", 0, 0);
	affiche_mot("TETS", 0, 20);
	
	affiche_nombre(999, 0 ,40);
	
	while (1);
}