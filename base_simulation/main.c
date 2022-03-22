/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
 // SIMULATION
 
//#include <iostm8s105.h>
#include "fonc_div.h"
#include "defs.h"

uint8_t PUIS = 40;
uint8_t BPM = 30;
uint8_t MODE = 0;

volatile uint8_t k = 1;
volatile uint8_t mod_BPM = 0;
volatile uint8_t mod_MODE = 0;

/*
// Init PWM connection for PUIS
void init_pwm(void) {
	
}

// Init I2C Slave connection with interruptions
void init_I2C(void) {
	
}
*/
main()
{
	PUIS=40;
	BPM=30;
	MODE=0;
	CLK_CKDIVR=0;
	
	
	init_SPI();
	init_TFT();
	init_ADC();
	init_Poussoirs();
	
	affiche_mot(Simu, 45, 5);
	affiche_mot(Bpm, 1, 25);
	affiche_mot(Puis, 1, 45);
	affiche_mot(Demo, 10, 65);
	
	affiche_nombre(BPM, 90, 25);
	affiche_nombre(PUIS, 90, 45);
	EnableGeneralInterrupt();
	
	for(;;){
		if(mod_BPM){
			mod_BPM=0;
			BPM=30*k;
			affiche_nombre(BPM, 90, 25);
		}
		if(mod_MODE){
			mod_MODE = 0;
			MODE = MODE ^ 1;
			if(!MODE){
				affiche_mot(Demo,10,65);
			}
			else
			{
				affiche_mot(Ops,10,65);
			}
		}
		PUIS = (read_ADC_8b()*100)/255;
		affiche_nombre(PUIS,90,45);
		
	}
}