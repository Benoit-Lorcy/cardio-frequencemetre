/************************************************************************
* TITLE: fonc_delay.c               
* AUTHOR:               
* DESCRIPTION: fonctions de temporisation calibrees pour frequence Fcpu = 2 MHz        
* VERSION : 1.0
*           2.0 adapatation carte STM8
*	    2.1 ajout temporisation 10us, 100us
*           2.2 attend_100us correction commentaire
*           2.3 utilisation uint16_t et uint8_t
*           2.4 attend_10us correction commentaire 
*************************************************************************/

/* INCLUDE *************************************************************/
#include "iostm8s105.h"

	
/* DEFINE **************************************************************/


/* FUNCTION ************************************************************/

/*******************************************************************************
* Function Name  : attend_10us
* Description    : temporisation de 10us
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
 1 cycle = 1/ Fcpu avec FoscRC HSI interne = 16 MHz et Fcpu = FoscRC HSI / 8 par defaut 
 20 cycles avec CALL (appel) et RET (retour) si Fcpu = 2 MHz)
*/
void attend_10us( void) // CALL = 4 cycles
{
#asm
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
	NOP				; 1 cycle
#endasm						
}	// RET = 4 cycles


/*******************************************************************************
* Function Name  : attend_100us
* Description    : temporisation de 100us
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
 1 cycle = 1/ Fcpu avec FoscRC HSI interne = 16 MHz et Fcpu = FoscRC HSI / 8 par defaut 
 200 cycles avec CALL et RET si Fcpu = 2 MHz
 Nboucle_100us	EQU	37		; (200-15)/5 
*/
void attend_100us( void) // CALL = 4 cycles
{
#asm

	PUSHW	X		; 2 cycles

	LDW		X,#37	; 2 cycles 
	
temp5cyc:
; boucle 5 cycles
	NOP				; 1 cycle
	NOP				; 1 cycle
	
	DECW 	X		; 1 cycles X = X-1
	JRNE	temp5cyc		; 2 cycles si X <> 0 alors continue tempo (1 cycle si X=0)
	
	POPW		X		; 2 cycles
#endasm						
}	// RET = 4 cycles


/*******************************************************************************
* Function Name  : attend_1ms
* Description    : temporisation de 1ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
 1 cycle = 1/ Fcpu avec FoscRC HSI interne = 16 MHz et Fcpu = FoscRC HSI / 8 par defaut (reglage 1 a 8)
 2000 cycles avec CALL et RET si Fcpu = 2 MHz
 Nboucle_1ms	EQU	397		; (2000-15)/5 
*/
void attend_1ms( void) // CALL = 4 cycles
{
#asm

	PUSHW	X		; 2 cycles

	LDW		X,#397    ; 2 cycles 
	
tempo5cyc:
; boucle 5 cycles
	NOP				; 1 cycle
	NOP				; 1 cycle
	
	DECW 	X		; 1 cycles X = X-1
	JRNE	tempo5cyc	     ; 2 cycles si X <> 0 alors continue tempo (1 cycle si X=0)
	
	POPW		X		; 2 cycles
#endasm						
}	// RET = 4 cycles


/*******************************************************************************
* Function Name  : attend_500ms
* Description    : temporisation de 500ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_500ms( void)
{
	uint16_t n;


	for ( n = 0; n < 500; n++)
		attend_1ms(); // duree  cycles par boucle 
}

/*******************************************************************************
* Function Name  : attend_ms
* Description    : temporisation reglable de 0 a 255ms
* Input          : nombre ms 0 a 255
* Output         : None
* Return         : None
*******************************************************************************/
void attend_ms( uint16_t nb_ms)
{
	uint16_t n;


	for ( n = 0; n < nb_ms; n++)
		attend_1ms();  
}

