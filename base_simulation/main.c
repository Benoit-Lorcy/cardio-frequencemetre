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
main()
{
	//definition des variables
	uint8_t i = 0;
	uint16_t temp_PUIS = PUIS;
	
	//redefiniton des variables globales
	PUIS=40;
	BPM=30;
	MODE=1;
	CLK_CKDIVR&=0b11100000;
	
	//initialisation des foncitons
	init_I2C_Slave();
	init_SPI();
	init_TFT();
	init_ADC();
	init_PD4();
	init_timer3();
	init_Poussoirs();
	
	// initialisation de l'affichage
	affiche_mot(Simu, 45, 5);
	affiche_mot(Bpm, 1, 25);
	affiche_mot(Puis, 1, 45);
	affiche_mot(Ops, 10, 65);
	
	affiche_nombre(BPM, 90, 25);
	affiche_nombre(PUIS, 90, 45);
	EnableGeneralInterrupt();
	
	//boucle principale
	for(;;){
		//interruption li�e au BPM
		if(mod_BPM){
			mod_BPM=0;
			BPM=30*k;
			affiche_nombre(BPM, 90, 25);
		}
		
		//interruption li� au MODE
		if(mod_MODE){
			mod_MODE = 0; 
			MODE = MODE ^ 1;
			init_I2C_Slave();
			if(!MODE){
				affiche_mot(Demo,10,65);
			}
			else
			{
				affiche_mot(Ops,10,65);
				fillRect_TFT(0, 80, 128, 80, ST7735_BLACK);
			}
		}
		
		//permet de mettre a jour l'afficheage
		if(temp_PUIS != PUIS){
			affiche_nombre(PUIS, 90, 45);
			temp_PUIS = PUIS;
		}
		
		//permet de mettre les valeur si le signal est constant
		if(TIM3_SR1 & (1<<0)){
			PUIS = PD_IDR & (1<<4) ? 100 : 0;
			TIM3_SR1 &= ~(1<<0);
		}
		

		
		//si mode DEMO => on affiche la courbe
		if(!MODE){
			ac_cap = (tab_ech[(k*i*4)%1000]<<(PUIS>>4)>>3)/32;
			drawVLine_TFT(i, 120-40, 80, ST7735_BLACK);
			drawVLine_TFT(i, 120 - ac_cap, 5, ST7735_YELLOW);
			i = (i+1)%128;
			
			PUIS = (read_ADC_8b()*100)/255;
			affiche_nombre(PUIS,90,45);
		}
		affiche_nombre(dc_cap,10,45);
		affiche_nombre(ac_cap,10,65);
	}
}