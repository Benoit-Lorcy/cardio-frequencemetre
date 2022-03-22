   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2524                     .const:	section	.text
2525  0000               L3261_Mesure:
2526  0000 4d4553555245  	dc.b	"MESURE",0
2527  0007               L5261_Simu:
2528  0007 53494d5500    	dc.b	"SIMU",0
2529  000c               L7261_Bpm:
2530  000c 42504d3a00    	dc.b	"BPM:",0
2531  0011               L1361_Seuil_bas:
2532  0011 416c5f626173  	dc.b	"Al_bas:",0
2533  0019               L3361_Seuil_haut:
2534  0019 416c5f686175  	dc.b	"Al_haut:",0
2535  0022               L5361_Puis:
2536  0022 505549533a00  	dc.b	"PUIS:",0
2537  0028               L7361_Demo:
2538  0028 4d4f44452044  	dc.b	"MODE DEMO",0
2539  0032               L1461_Ops:
2540  0032 4d4f4445204f  	dc.b	"MODE OPS ",0
2541  003c               L3461_Texte:
2542  003c 54657874653a  	dc.b	"Texte:",0
2543  0043               L5461_Fond:
2544  0043 466f6e643a00  	dc.b	"Fond:",0
2545  0049               L7461_Valeurs:
2546  0049 56616c657572  	dc.b	"Valeurs:",0
2547                     	bsct
2548  0000               _sal_bas:
2549  0000 00            	dc.b	0
2550  0001               _sal_haut:
2551  0001 00            	dc.b	0
2727                     ; 14 void init_PWM(void) {
2729                     	switch	.text
2730  0000               _init_PWM:
2734                     ; 16 }
2737  0000 81            	ret
2760                     ; 18 void init_I2C(void) {
2761                     	switch	.text
2762  0001               _init_I2C:
2766                     ; 20 }
2769  0001 81            	ret
2818                     ; 22 uint16_t read_AD7991(uint8_t octet_conf) {
2819                     	switch	.text
2820  0002               _read_AD7991:
2822  0002 88            	push	a
2823  0003 89            	pushw	x
2824       00000002      OFST:	set	2
2827                     ; 25 	Start_I2C();
2829  0004 cd0000        	call	_Start_I2C
2831                     ; 26 	Write_I2C(0b01010000);
2833  0007 a650          	ld	a,#80
2834  0009 cd0000        	call	_Write_I2C
2836                     ; 27 	Write_I2C(octet_conf);
2838  000c 7b03          	ld	a,(OFST+1,sp)
2839  000e cd0000        	call	_Write_I2C
2841                     ; 28 	Stop_I2C();
2843  0011 cd0000        	call	_Stop_I2C
2845                     ; 30 	Start_I2C();
2847  0014 cd0000        	call	_Start_I2C
2849                     ; 31 	Write_I2C(0b01010001);
2851  0017 a651          	ld	a,#81
2852  0019 cd0000        	call	_Write_I2C
2854                     ; 33 	Ack_I2C();
2856  001c cd0000        	call	_Ack_I2C
2858                     ; 34 	data = Read_I2C() << 8;
2860  001f cd0000        	call	_Read_I2C
2862  0022 5f            	clrw	x
2863  0023 97            	ld	xl,a
2864  0024 4f            	clr	a
2865  0025 02            	rlwa	x,a
2866  0026 1f01          	ldw	(OFST-1,sp),x
2867                     ; 36 	NoAck_I2C();
2869  0028 cd0000        	call	_NoAck_I2C
2871                     ; 37 	data |= Read_I2C();
2873  002b cd0000        	call	_Read_I2C
2875  002e 5f            	clrw	x
2876  002f 97            	ld	xl,a
2877  0030 01            	rrwa	x,a
2878  0031 1a02          	or	a,(OFST+0,sp)
2879  0033 01            	rrwa	x,a
2880  0034 1a01          	or	a,(OFST-1,sp)
2881  0036 01            	rrwa	x,a
2882  0037 1f01          	ldw	(OFST-1,sp),x
2883                     ; 39 	Stop_I2C();
2885  0039 cd0000        	call	_Stop_I2C
2887                     ; 41 	return data;
2889  003c 1e01          	ldw	x,(OFST-1,sp)
2892  003e 5b03          	addw	sp,#3
2893  0040 81            	ret
2932                     ; 44 void init_UART2(void) {
2933                     	switch	.text
2934  0041               _init_UART2:
2936  0041 89            	pushw	x
2937       00000002      OFST:	set	2
2940                     ; 45 	uint16_t uart = 277;
2942                     ; 47 	UART2_BRR2 = 0xF0 & (uart >> 4) + 0xF & uart; // BRR2 first
2944  0042 725f5243      	clr	_UART2_BRR2
2945                     ; 48 	UART2_BRR1 = 0xF & (uart >> 4);
2947  0046 35015242      	mov	_UART2_BRR1,#1
2948                     ; 50 	UART2_CR2 = 0x08; // TEN bit(3) to allow transmitting
2950  004a 35085245      	mov	_UART2_CR2,#8
2951                     ; 52 	UART2_CR1 = 0b00000000; // M bit 0 for 8 bit word length
2953  004e 725f5244      	clr	_UART2_CR1
2954                     ; 53 	UART2_CR3 = 0b00000000; // STOP bit 00 (4,5) for 1 stop bit
2956  0052 725f5246      	clr	_UART2_CR3
2957                     ; 56 }
2960  0056 85            	popw	x
2961  0057 81            	ret
2997                     ; 58 void write_byte_UART2(uint8_t data) {
2998                     	switch	.text
2999  0058               _write_byte_UART2:
3003                     ; 59 	UART2_DR = data;
3005  0058 c75241        	ld	_UART2_DR,a
3007  005b               L5502:
3008                     ; 60 	while( !(UART2_SR & (1<<6)) );
3010  005b c65240        	ld	a,_UART2_SR
3011  005e a540          	bcp	a,#64
3012  0060 27f9          	jreq	L5502
3013                     ; 61 }
3016  0062 81            	ret
3051                     ; 63 void send_ac_cap_UART(uint16_t cap) {
3052                     	switch	.text
3053  0063               _send_ac_cap_UART:
3055  0063 89            	pushw	x
3056       00000000      OFST:	set	0
3059                     ; 64 	write_byte_UART2((cap >> 8) & 0x0F);
3061  0064 9e            	ld	a,xh
3062  0065 a40f          	and	a,#15
3063  0067 adef          	call	_write_byte_UART2
3065                     ; 65 	write_byte_UART2(((cap >> 4) & 0x0F) | 0x10);
3067  0069 1e01          	ldw	x,(OFST+1,sp)
3068  006b 54            	srlw	x
3069  006c 54            	srlw	x
3070  006d 54            	srlw	x
3071  006e 54            	srlw	x
3072  006f 9f            	ld	a,xl
3073  0070 a40f          	and	a,#15
3074  0072 aa10          	or	a,#16
3075  0074 ade2          	call	_write_byte_UART2
3077                     ; 66 	write_byte_UART2(((cap >> 0) & 0x0F) | 0x20);
3079  0076 7b02          	ld	a,(OFST+2,sp)
3080  0078 a40f          	and	a,#15
3081  007a aa20          	or	a,#32
3082  007c adda          	call	_write_byte_UART2
3084                     ; 67 }
3087  007e 85            	popw	x
3088  007f 81            	ret
3123                     ; 69 void send_dc_cap_UART(uint16_t cap) {
3124                     	switch	.text
3125  0080               _send_dc_cap_UART:
3127  0080 89            	pushw	x
3128       00000000      OFST:	set	0
3131                     ; 70 	write_byte_UART2(((cap >> 8) & 0x0F) | 0x80);
3133  0081 9e            	ld	a,xh
3134  0082 a40f          	and	a,#15
3135  0084 aa80          	or	a,#128
3136  0086 add0          	call	_write_byte_UART2
3138                     ; 71 	write_byte_UART2(((cap >> 4) & 0x0F) | 0x90);
3140  0088 1e01          	ldw	x,(OFST+1,sp)
3141  008a 54            	srlw	x
3142  008b 54            	srlw	x
3143  008c 54            	srlw	x
3144  008d 54            	srlw	x
3145  008e 9f            	ld	a,xl
3146  008f a40f          	and	a,#15
3147  0091 aa90          	or	a,#144
3148  0093 adc3          	call	_write_byte_UART2
3150                     ; 72 	write_byte_UART2(((cap >> 0) & 0x0F) | 0xA0);
3152  0095 7b02          	ld	a,(OFST+2,sp)
3153  0097 a40f          	and	a,#15
3154  0099 aaa0          	or	a,#160
3155  009b adbb          	call	_write_byte_UART2
3157                     ; 73 }
3160  009d 85            	popw	x
3161  009e 81            	ret
3191                     ; 75 main()
3191                     ; 76 {
3192                     	switch	.text
3193  009f               _main:
3197                     ; 77 	CLK_CKDIVR = 0;
3199  009f 725f50c6      	clr	_CLK_CKDIVR
3200                     ; 78 	init_PWM();
3202  00a3 cd0000        	call	_init_PWM
3204                     ; 79 	init_I2C();
3206  00a6 cd0001        	call	_init_I2C
3208                     ; 80 	init_UART2();
3210  00a9 ad96          	call	_init_UART2
3212                     ; 82 	init_spi_port_display();
3214  00ab cd0000        	call	_init_spi_port_display
3216                     ; 84 	affiche_mot("Mon beau mot", 4, 4);
3218  00ae 4b04          	push	#4
3219  00b0 4b04          	push	#4
3220  00b2 ae0052        	ldw	x,#L5212
3221  00b5 cd0000        	call	_affiche_mot
3223  00b8 85            	popw	x
3224                     ; 85 	affiche_nombre(345, 12, 12);
3226  00b9 4b0c          	push	#12
3227  00bb 4b0c          	push	#12
3228  00bd ae0159        	ldw	x,#345
3229  00c0 cd0000        	call	_affiche_nombre
3231  00c3 85            	popw	x
3232  00c4               L7212:
3233                     ; 89 	while (1);
3235  00c4 20fe          	jra	L7212
3248                     	xdef	_main
3249                     	xdef	_send_dc_cap_UART
3250                     	xdef	_send_ac_cap_UART
3251                     	xdef	_write_byte_UART2
3252                     	xdef	_init_UART2
3253                     	xdef	_read_AD7991
3254                     	xdef	_init_I2C
3255                     	xdef	_init_PWM
3256                     	xref	_Stop_I2C
3257                     	xref	_NoAck_I2C
3258                     	xref	_Ack_I2C
3259                     	xref	_Read_I2C
3260                     	xref	_Write_I2C
3261                     	xref	_Start_I2C
3262                     	xdef	_sal_haut
3263                     	xdef	_sal_bas
3264                     	xref	_affiche_nombre
3265                     	xref	_affiche_mot
3266                     	xref	_init_spi_port_display
3267                     	switch	.const
3268  0052               L5212:
3269  0052 4d6f6e206265  	dc.b	"Mon beau mot",0
3289                     	end
