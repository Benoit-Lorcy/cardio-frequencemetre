   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2551                     ; 7 void init_SPI(void){
2553                     	switch	.text
2554  0000               _init_SPI:
2558                     ; 9 }
2561  0000 81            	ret
2596                     ; 11 void affiche_mot(uint8_t * mot, uint8_t col, uint8_t ligne){
2597                     	switch	.text
2598  0001               _affiche_mot:
2602                     ; 13 }
2605  0001 81            	ret
2639                     ; 15 void affiche_nombre(uint16_t nombre, uint8_t col, uint8_t ligne){
2640                     	switch	.text
2641  0002               _affiche_nombre:
2645                     ; 17 }
2648  0002 81            	ret
2671                     ; 19 uint8_t init_ADC(void) {
2672                     	switch	.text
2673  0003               _init_ADC:
2677                     ; 21 }
2680  0003 81            	ret
2703                     ; 23 uint8_t read_ADC_8b(void) {
2704                     	switch	.text
2705  0004               _read_ADC_8b:
2709                     ; 25 }
2712  0004 81            	ret
2735                     ; 27 void init_Poussoirs(void){
2736                     	switch	.text
2737  0005               _init_Poussoirs:
2741                     ; 29 }
2744  0005 81            	ret
2757                     	xdef	_init_Poussoirs
2758                     	xdef	_read_ADC_8b
2759                     	xdef	_init_ADC
2760                     	xdef	_affiche_nombre
2761                     	xdef	_affiche_mot
2762                     	xdef	_init_SPI
2781                     	end
