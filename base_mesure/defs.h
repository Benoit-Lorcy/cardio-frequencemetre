#ifndef DEFS_H
#define DEFS_H

// adresse I2C adc AD7991-0
#define adresse_esclave 0x50 

// ecran principal, carte controle, carte simulateur

static const uint8_t Mesure[]="MESURE";
static const uint8_t Simu[]="SIMU";
static const uint8_t Bpm[]="BPM:";
static const uint8_t Seuil_bas[]="Al_bas:"; 
static const uint8_t Seuil_haut[]="Al_haut:"; 
static const uint8_t Puis[]="PUIS:"; 
static const uint8_t Demo[]="MODE DEMO"; 
static const uint8_t Ops[]="MODE OPS "; 


// ecran choix couleur, carte controle
static const uint8_t Texte[]="Texte:";
static const uint8_t Fond[]="Fond:";
static const uint8_t Valeurs[]="Valeurs:";

//divers
volatile uint8_t sal_bas = 40;
volatile uint8_t sal_haut = 240;
volatile uint8_t BPM = 70;
volatile uint8_t PUIS = 30;
volatile uint16_t int_2ms_ok = 0;

#endif