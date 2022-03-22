   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2564                     ; 10 void init_spi_port_display(void) {
2566                     	switch	.text
2567  0000               _init_spi_port_display:
2571                     ; 11 	CLK_PCKENR1 |= 1 << 1;
2573  0000 721250c7      	bset	_CLK_PCKENR1,#1
2574                     ; 13 	PC_DDR |= 1 << 7;
2576  0004 721e500c      	bset	_PC_DDR,#7
2577                     ; 14 	PC_CR1 |= 1 << 7;
2579  0008 721e500d      	bset	_PC_CR1,#7
2580                     ; 15 	PC_CR2 &= ~(1 << 7);
2582  000c 721f500e      	bres	_PC_CR2,#7
2583                     ; 16 	PD_DDR |= 0b10000001;
2585  0010 c65011        	ld	a,_PD_DDR
2586  0013 aa81          	or	a,#129
2587  0015 c75011        	ld	_PD_DDR,a
2588                     ; 17 	PD_CR1 |= 0b10000001;
2590  0018 c65012        	ld	a,_PD_CR1
2591  001b aa81          	or	a,#129
2592  001d c75012        	ld	_PD_CR1,a
2593                     ; 18 	PD_CR2 &= 0b01111110;
2595  0020 c65013        	ld	a,_PD_CR2
2596  0023 a47e          	and	a,#126
2597  0025 c75013        	ld	_PD_CR2,a
2598                     ; 19 	PC_ODR |= 1 << 7;
2600  0028 721e500a      	bset	_PC_ODR,#7
2601                     ; 20 	PD_ODR &= 0b01111110;
2603  002c c6500f        	ld	a,_PD_ODR
2604  002f a47e          	and	a,#126
2605  0031 c7500f        	ld	_PD_ODR,a
2606                     ; 21 	SPI_CR1 = 0x14;
2608  0034 35145200      	mov	_SPI_CR1,#20
2609                     ; 22 	SPI_CR2 = 0x03;
2611  0038 35035201      	mov	_SPI_CR2,#3
2612                     ; 23 	SPI_CR1 |= 1 << 6;
2614  003c 721c5200      	bset	_SPI_CR1,#6
2615                     ; 25 	init_TFT();
2617  0040 cd0000        	call	_init_TFT
2619                     ; 26 }
2622  0043 81            	ret
2676                     ; 29 void affiche_mot(uint8_t* mot, uint8_t col, uint8_t ligne) {
2677                     	switch	.text
2678  0044               _affiche_mot:
2680  0044 89            	pushw	x
2681       00000000      OFST:	set	0
2684  0045 2027          	jra	L1761
2685  0047               L7661:
2686                     ; 31 		displayChar_TFT(col, ligne, *mot, ST7735_RED,ST7735_BLACK, 2);
2688  0047 4b02          	push	#2
2689  0049 5f            	clrw	x
2690  004a 89            	pushw	x
2691  004b aef800        	ldw	x,#63488
2692  004e 89            	pushw	x
2693  004f 1e06          	ldw	x,(OFST+6,sp)
2694  0051 f6            	ld	a,(x)
2695  0052 88            	push	a
2696  0053 7b0c          	ld	a,(OFST+12,sp)
2697  0055 5f            	clrw	x
2698  0056 97            	ld	xl,a
2699  0057 89            	pushw	x
2700  0058 7b0d          	ld	a,(OFST+13,sp)
2701  005a 5f            	clrw	x
2702  005b 97            	ld	xl,a
2703  005c cd0000        	call	_displayChar_TFT
2705  005f 5b08          	addw	sp,#8
2706                     ; 32 		col += 11;
2708  0061 7b05          	ld	a,(OFST+5,sp)
2709  0063 ab0b          	add	a,#11
2710  0065 6b05          	ld	(OFST+5,sp),a
2711                     ; 33 		mot++;
2713  0067 1e01          	ldw	x,(OFST+1,sp)
2714  0069 1c0001        	addw	x,#1
2715  006c 1f01          	ldw	(OFST+1,sp),x
2716  006e               L1761:
2717                     ; 30 	while(*mot) {
2719  006e 1e01          	ldw	x,(OFST+1,sp)
2720  0070 7d            	tnz	(x)
2721  0071 26d4          	jrne	L7661
2722                     ; 35 }
2725  0073 85            	popw	x
2726  0074 81            	ret
2779                     ; 37 void affiche_nombre(unsigned short nombre, uint8_t col, uint8_t ligne) {
2780                     	switch	.text
2781  0075               _affiche_nombre:
2783  0075 89            	pushw	x
2784       00000000      OFST:	set	0
2787                     ; 38 	if(nombre < 1000) {
2789  0076 a303e8        	cpw	x,#1000
2790  0079 2473          	jruge	L3271
2791                     ; 39 		displayChar_TFT(col, ligne, '0'+(nombre/100), ST7735_YELLOW, ST7735_BLACK, 2);
2793  007b 4b02          	push	#2
2794  007d 5f            	clrw	x
2795  007e 89            	pushw	x
2796  007f aeffe0        	ldw	x,#65504
2797  0082 89            	pushw	x
2798  0083 1e06          	ldw	x,(OFST+6,sp)
2799  0085 90ae0064      	ldw	y,#100
2800  0089 65            	divw	x,y
2801  008a 1c0030        	addw	x,#48
2802  008d 9f            	ld	a,xl
2803  008e 88            	push	a
2804  008f 7b0c          	ld	a,(OFST+12,sp)
2805  0091 5f            	clrw	x
2806  0092 97            	ld	xl,a
2807  0093 89            	pushw	x
2808  0094 7b0d          	ld	a,(OFST+13,sp)
2809  0096 5f            	clrw	x
2810  0097 97            	ld	xl,a
2811  0098 cd0000        	call	_displayChar_TFT
2813  009b 5b08          	addw	sp,#8
2814                     ; 40 		displayChar_TFT(col+11, ligne, '0'+((nombre%100)/10), ST7735_YELLOW, ST7735_BLACK, 2);
2816  009d 4b02          	push	#2
2817  009f 5f            	clrw	x
2818  00a0 89            	pushw	x
2819  00a1 aeffe0        	ldw	x,#65504
2820  00a4 89            	pushw	x
2821  00a5 1e06          	ldw	x,(OFST+6,sp)
2822  00a7 90ae0064      	ldw	y,#100
2823  00ab 65            	divw	x,y
2824  00ac 51            	exgw	x,y
2825  00ad 90ae000a      	ldw	y,#10
2826  00b1 65            	divw	x,y
2827  00b2 1c0030        	addw	x,#48
2828  00b5 9f            	ld	a,xl
2829  00b6 88            	push	a
2830  00b7 7b0c          	ld	a,(OFST+12,sp)
2831  00b9 5f            	clrw	x
2832  00ba 97            	ld	xl,a
2833  00bb 89            	pushw	x
2834  00bc 7b0d          	ld	a,(OFST+13,sp)
2835  00be 5f            	clrw	x
2836  00bf 97            	ld	xl,a
2837  00c0 1c000b        	addw	x,#11
2838  00c3 cd0000        	call	_displayChar_TFT
2840  00c6 5b08          	addw	sp,#8
2841                     ; 41 		displayChar_TFT(col+11*2, ligne, '0'+(nombre%10), ST7735_YELLOW, ST7735_BLACK, 2);
2843  00c8 4b02          	push	#2
2844  00ca 5f            	clrw	x
2845  00cb 89            	pushw	x
2846  00cc aeffe0        	ldw	x,#65504
2847  00cf 89            	pushw	x
2848  00d0 1e06          	ldw	x,(OFST+6,sp)
2849  00d2 90ae000a      	ldw	y,#10
2850  00d6 65            	divw	x,y
2851  00d7 51            	exgw	x,y
2852  00d8 1c0030        	addw	x,#48
2853  00db 9f            	ld	a,xl
2854  00dc 88            	push	a
2855  00dd 7b0c          	ld	a,(OFST+12,sp)
2856  00df 5f            	clrw	x
2857  00e0 97            	ld	xl,a
2858  00e1 89            	pushw	x
2859  00e2 7b0d          	ld	a,(OFST+13,sp)
2860  00e4 5f            	clrw	x
2861  00e5 97            	ld	xl,a
2862  00e6 1c0016        	addw	x,#22
2863  00e9 cd0000        	call	_displayChar_TFT
2865  00ec 5b08          	addw	sp,#8
2866  00ee               L3271:
2867                     ; 43 }
2870  00ee 85            	popw	x
2871  00ef 81            	ret
2901                     ; 45 void init_ADC(void) {
2902                     	switch	.text
2903  00f0               _init_ADC:
2907                     ; 46 	CLK_PCKENR2 |= (1<<3);
2909  00f0 721650ca      	bset	_CLK_PCKENR2,#3
2910                     ; 48 	PF_DDR &= ~(1 << 4);
2912  00f4 7219501b      	bres	_PF_DDR,#4
2913                     ; 49 	PF_CR1 &= ~(1 << 4);
2915  00f8 7219501c      	bres	_PF_CR1,#4
2916                     ; 50 	PF_CR2 &= ~(1 << 4);
2918  00fc 7219501d      	bres	_PF_CR2,#4
2919                     ; 52 	ADC_CSR = 0x0C;
2921  0100 350c5400      	mov	_ADC_CSR,#12
2922                     ; 53 	ADC_CR1 = 0x01;
2924  0104 35015401      	mov	_ADC_CR1,#1
2925                     ; 54 	ADC_CR2 = 0x00;
2927  0108 725f5402      	clr	_ADC_CR2
2928                     ; 55 }
2931  010c 81            	ret
2965                     ; 57 void init_Poussoirs() {
2966                     	switch	.text
2967  010d               _init_Poussoirs:
2971                     ; 58 	PE_DDR &= ~(1 << 5);
2973  010d 721b5016      	bres	_PE_DDR,#5
2974                     ; 59 	PE_CR1 &= ~(1 << 5);
2976  0111 721b5017      	bres	_PE_CR1,#5
2977                     ; 60 	PE_CR2 |= (1 << 5);
2979  0115 721a5018      	bset	_PE_CR2,#5
2980                     ; 62 	PD_DDR &= ~(1 << 3);
2982  0119 72175011      	bres	_PD_DDR,#3
2983                     ; 63 	PD_CR1 &= ~(1 << 3);
2985  011d 72175012      	bres	_PD_CR1,#3
2986                     ; 64 	PD_CR2 |= (1 << 3);
2988  0121 72165013      	bset	_PD_CR2,#3
2989                     ; 66 	PC_DDR &= ~(1 << 4);
2991  0125 7219500c      	bres	_PC_DDR,#4
2992                     ; 67 	PC_CR1 &= ~(1 << 4);
2994  0129 7219500d      	bres	_PC_CR1,#4
2995                     ; 68 	PC_CR2 |= (1 << 4);
2997  012d 7218500e      	bset	_PC_CR2,#4
2998                     ; 70 	EXTI_CR1 |= (1<<6)|(1<<4);
3000  0131 c650a0        	ld	a,_EXTI_CR1
3001  0134 aa50          	or	a,#80
3002  0136 c750a0        	ld	_EXTI_CR1,a
3003                     ; 71 	EXTI_CR1 &= 0b01011111;
3005  0139 c650a0        	ld	a,_EXTI_CR1
3006  013c a45f          	and	a,#95
3007  013e c750a0        	ld	_EXTI_CR1,a
3008                     ; 73 	EXTI_CR2 |= 1;
3010  0141 721050a1      	bset	_EXTI_CR2,#0
3011                     ; 74 	EXTI_CR2 &= ~2;
3013  0145 721350a1      	bres	_EXTI_CR2,#1
3014                     ; 75 }
3017  0149 81            	ret
3043                     ; 77 void init_LED(void) {
3044                     	switch	.text
3045  014a               _init_LED:
3049                     ; 78 	PB_DDR|=7; //bit 0 à 1 pour le push pull en sortie
3051  014a c65007        	ld	a,_PB_DDR
3052  014d aa07          	or	a,#7
3053  014f c75007        	ld	_PB_DDR,a
3054                     ; 79   PB_CR1|=7;
3056  0152 c65008        	ld	a,_PB_CR1
3057  0155 aa07          	or	a,#7
3058  0157 c75008        	ld	_PB_CR1,a
3059                     ; 80 	PB_CR2|=7;
3061  015a c65009        	ld	a,_PB_CR2
3062  015d aa07          	or	a,#7
3063  015f c75009        	ld	_PB_CR2,a
3064                     ; 81 }
3067  0162 81            	ret
3080                     	xref	_displayChar_TFT
3081                     	xref	_init_TFT
3082                     	xdef	_init_LED
3083                     	xdef	_init_Poussoirs
3084                     	xdef	_init_ADC
3085                     	xdef	_affiche_nombre
3086                     	xdef	_affiche_mot
3087                     	xdef	_init_spi_port_display
3106                     	end
