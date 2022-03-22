   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2557                     ; 7 void init_SPI(void){
2559                     	switch	.text
2560  0000               _init_SPI:
2564                     ; 8 			CLK_PCKENR1 |= 1 << 1;
2566  0000 721250c7      	bset	_CLK_PCKENR1,#1
2567                     ; 9 		PC_DDR |= 1 << 7;
2569  0004 721e500c      	bset	_PC_DDR,#7
2570                     ; 10 		PC_CR1 |= 1 << 7;
2572  0008 721e500d      	bset	_PC_CR1,#7
2573                     ; 11 		PC_CR2 &= ~(1 << 7);
2575  000c 721f500e      	bres	_PC_CR2,#7
2576                     ; 12 		SPI_CR1 = 0x2f;
2578  0010 352f5200      	mov	_SPI_CR1,#47
2579                     ; 13 		SPI_CR2 = 0x03;
2581  0014 35035201      	mov	_SPI_CR2,#3
2582                     ; 15 		SPI_CR1 |= 1 << 6;
2584  0018 721c5200      	bset	_SPI_CR1,#6
2585                     ; 16 }
2588  001c 81            	ret
2642                     ; 18 void affiche_mot(uint8_t* mot, uint8_t col, uint8_t ligne) {
2643                     	switch	.text
2644  001d               _affiche_mot:
2646  001d 89            	pushw	x
2647       00000000      OFST:	set	0
2650  001e 202a          	jra	L1761
2651  0020               L7661:
2652                     ; 20 		displayChar_TFT(col+5, ligne, *mot, ST7735_RED,ST7735_BLACK, 1);
2654  0020 4b01          	push	#1
2655  0022 5f            	clrw	x
2656  0023 89            	pushw	x
2657  0024 aef800        	ldw	x,#63488
2658  0027 89            	pushw	x
2659  0028 1e06          	ldw	x,(OFST+6,sp)
2660  002a f6            	ld	a,(x)
2661  002b 88            	push	a
2662  002c 7b0c          	ld	a,(OFST+12,sp)
2663  002e 5f            	clrw	x
2664  002f 97            	ld	xl,a
2665  0030 89            	pushw	x
2666  0031 7b0d          	ld	a,(OFST+13,sp)
2667  0033 5f            	clrw	x
2668  0034 97            	ld	xl,a
2669  0035 1c0005        	addw	x,#5
2670  0038 cd0000        	call	_displayChar_TFT
2672  003b 5b08          	addw	sp,#8
2673                     ; 21 		col = col + 11;
2675  003d 7b05          	ld	a,(OFST+5,sp)
2676  003f ab0b          	add	a,#11
2677  0041 6b05          	ld	(OFST+5,sp),a
2678                     ; 22 		mot++;
2680  0043 1e01          	ldw	x,(OFST+1,sp)
2681  0045 1c0001        	addw	x,#1
2682  0048 1f01          	ldw	(OFST+1,sp),x
2683  004a               L1761:
2684                     ; 19 	while(*mot) {
2686  004a 1e01          	ldw	x,(OFST+1,sp)
2687  004c 7d            	tnz	(x)
2688  004d 26d1          	jrne	L7661
2689                     ; 24 }
2692  004f 85            	popw	x
2693  0050 81            	ret
2716                     ; 34 void init_ADC(void) {
2717                     	switch	.text
2718  0051               _init_ADC:
2722                     ; 36 }
2725  0051 81            	ret
2748                     ; 38 uint8_t read_ADC_8b(void) {
2749                     	switch	.text
2750  0052               _read_ADC_8b:
2754                     ; 40 }
2757  0052 81            	ret
2780                     ; 42 void init_Poussoirs(void){
2781                     	switch	.text
2782  0053               _init_Poussoirs:
2786                     ; 44 }
2789  0053 81            	ret
2802                     	xdef	_init_Poussoirs
2803                     	xdef	_read_ADC_8b
2804                     	xdef	_init_ADC
2805                     	xdef	_affiche_mot
2806                     	xdef	_init_SPI
2807                     	xref	_displayChar_TFT
2826                     	end
