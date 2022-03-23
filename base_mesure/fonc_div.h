
#include "iostm8s105.h"
#include "fonc_tft.h"
//prototype fonctions 
//control_1

void init_SPI(void);
void affiche_mot(uint8_t* mot, uint8_t col, uint8_t ligne);
void affiche_nombre(uint16_t nombre, uint8_t col, uint8_t ligne);
void init_ADC(void);
void init_Poussoirs(void);
void init_LED(void);


//control_2

void init_timer1_2ms(void);
void init_UART2(uint16_t UART_BAUDRATE);
void write_byte_UART2(uint8_t data);
void init_timer2_pwm(void);

//control_3


void machine_etat(void);

//control_f


