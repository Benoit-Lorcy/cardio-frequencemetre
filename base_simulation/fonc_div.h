#include <iostm8s105.h>
#include "fonc_tft.h"
#include "fonc_delay.h"

//prototype fonctions 
//simu_1
void init_SPI(void);
void affiche_mot(uint8_t * mot, uint8_t col, uint8_t ligne);
void affiche_nombre(uint16_t nombre, uint8_t col, uint8_t ligne);
void init_ADC(void);

//simu_2

uint8_t read_ADC_8b(void);
void init_Poussoirs(void);
void init_PD4(void);
void init_timer3(void);

//simu_f

void init_I2C_Slave(void);
void init_timer1_2ms(void);

