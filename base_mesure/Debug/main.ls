   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2551                     ; 11 void init_PWM(void) {
2553                     	switch	.text
2554  0000               _init_PWM:
2558                     ; 13 }
2561  0000 81            	ret
2584                     ; 15 void init_I2C(void) {
2585                     	switch	.text
2586  0001               _init_I2C:
2590                     ; 17 }
2593  0001 81            	ret
2642                     ; 19 uint16_t read_AD7991(uint8_t octet_conf) {
2643                     	switch	.text
2644  0002               _read_AD7991:
2646  0002 88            	push	a
2647  0003 89            	pushw	x
2648       00000002      OFST:	set	2
2651                     ; 22 	Start_I2C();
2653  0004 cd0000        	call	_Start_I2C
2655                     ; 23 	Write_I2C(0b01010000);
2657  0007 a650          	ld	a,#80
2658  0009 cd0000        	call	_Write_I2C
2660                     ; 24 	Write_I2C(octet_conf);
2662  000c 7b03          	ld	a,(OFST+1,sp)
2663  000e cd0000        	call	_Write_I2C
2665                     ; 25 	Stop_I2C();
2667  0011 cd0000        	call	_Stop_I2C
2669                     ; 27 	Start_I2C();
2671  0014 cd0000        	call	_Start_I2C
2673                     ; 28 	Write_I2C(0b01010001);
2675  0017 a651          	ld	a,#81
2676  0019 cd0000        	call	_Write_I2C
2678                     ; 30 	data = Read_I2C() << 8;
2680  001c cd0000        	call	_Read_I2C
2682  001f 5f            	clrw	x
2683  0020 97            	ld	xl,a
2684  0021 4f            	clr	a
2685  0022 02            	rlwa	x,a
2686  0023 1f01          	ldw	(OFST-1,sp),x
2687                     ; 31 	Ack_I2C();
2689  0025 cd0000        	call	_Ack_I2C
2691                     ; 32 	data |= Read_I2C();
2693  0028 cd0000        	call	_Read_I2C
2695  002b 5f            	clrw	x
2696  002c 97            	ld	xl,a
2697  002d 01            	rrwa	x,a
2698  002e 1a02          	or	a,(OFST+0,sp)
2699  0030 01            	rrwa	x,a
2700  0031 1a01          	or	a,(OFST-1,sp)
2701  0033 01            	rrwa	x,a
2702  0034 1f01          	ldw	(OFST-1,sp),x
2703                     ; 33 	NoAck_I2C();
2705  0036 cd0000        	call	_NoAck_I2C
2707                     ; 34 	Stop_I2C();
2709  0039 cd0000        	call	_Stop_I2C
2711                     ; 35 }
2714  003c 5b03          	addw	sp,#3
2715  003e 81            	ret
2752                     ; 37 void init_UART2(void) {
2753                     	switch	.text
2754  003f               _init_UART2:
2756  003f 89            	pushw	x
2757       00000002      OFST:	set	2
2760                     ; 38 	uint16_t uart = 277;
2762                     ; 39 	UART2_BRR1 = 0xF & (uart >> 4);
2764  0040 35015242      	mov	_UART2_BRR1,#1
2765                     ; 40 	UART2_BRR2 = 0xF0 & (uart >> 4) + 0xF & uart;
2767  0044 725f5243      	clr	_UART2_BRR2
2768                     ; 42 	UART2_CR1 = 0b00000000;
2770  0048 725f5244      	clr	_UART2_CR1
2771                     ; 43 }
2774  004c 85            	popw	x
2775  004d 81            	ret
2811                     ; 45 void write_byte_UART2(uint8_t data) {
2812                     	switch	.text
2813  004e               _write_byte_UART2:
2817                     ; 46 	UART2_DR = data;
2819  004e c75241        	ld	_UART2_DR,a
2821  0051               L3371:
2822                     ; 47 	while( !(UART2_SR & (1<<5)) );
2824  0051 c65240        	ld	a,_UART2_SR
2825  0054 a520          	bcp	a,#32
2826  0056 27f9          	jreq	L3371
2827                     ; 48 }
2830  0058 81            	ret
2865                     ; 50 void send_ac_cap_UART(uint16_t cap) {
2866                     	switch	.text
2867  0059               _send_ac_cap_UART:
2869  0059 89            	pushw	x
2870       00000000      OFST:	set	0
2873                     ; 51 	write_byte_UART2((cap >> 8) & 0x0F);
2875  005a 9e            	ld	a,xh
2876  005b a40f          	and	a,#15
2877  005d adef          	call	_write_byte_UART2
2879                     ; 52 	write_byte_UART2(((cap >> 4) & 0x0F) | 0x10);
2881  005f 1e01          	ldw	x,(OFST+1,sp)
2882  0061 54            	srlw	x
2883  0062 54            	srlw	x
2884  0063 54            	srlw	x
2885  0064 54            	srlw	x
2886  0065 9f            	ld	a,xl
2887  0066 a40f          	and	a,#15
2888  0068 aa10          	or	a,#16
2889  006a ade2          	call	_write_byte_UART2
2891                     ; 53 	write_byte_UART2(((cap >> 0) & 0x0F) | 0x20);
2893  006c 7b02          	ld	a,(OFST+2,sp)
2894  006e a40f          	and	a,#15
2895  0070 aa20          	or	a,#32
2896  0072 adda          	call	_write_byte_UART2
2898                     ; 54 }
2901  0074 85            	popw	x
2902  0075 81            	ret
2937                     ; 56 void send_dc_cap_UART(uint16_t cap) {
2938                     	switch	.text
2939  0076               _send_dc_cap_UART:
2941  0076 89            	pushw	x
2942       00000000      OFST:	set	0
2945                     ; 57 	write_byte_UART2(((cap >> 8) & 0x0F) | 0x80);
2947  0077 9e            	ld	a,xh
2948  0078 a40f          	and	a,#15
2949  007a aa80          	or	a,#128
2950  007c add0          	call	_write_byte_UART2
2952                     ; 58 	write_byte_UART2(((cap >> 4) & 0x0F) | 0x90);
2954  007e 1e01          	ldw	x,(OFST+1,sp)
2955  0080 54            	srlw	x
2956  0081 54            	srlw	x
2957  0082 54            	srlw	x
2958  0083 54            	srlw	x
2959  0084 9f            	ld	a,xl
2960  0085 a40f          	and	a,#15
2961  0087 aa90          	or	a,#144
2962  0089 adc3          	call	_write_byte_UART2
2964                     ; 59 	write_byte_UART2(((cap >> 0) & 0x0F) | 0xA0);
2966  008b 7b02          	ld	a,(OFST+2,sp)
2967  008d a40f          	and	a,#15
2968  008f aaa0          	or	a,#160
2969  0091 adbb          	call	_write_byte_UART2
2971                     ; 60 }
2974  0093 85            	popw	x
2975  0094 81            	ret
3001                     ; 62 main()
3001                     ; 63 {
3002                     	switch	.text
3003  0095               _main:
3007                     ; 64 	init_PWM();
3009  0095 cd0000        	call	_init_PWM
3011                     ; 65 	init_I2C();
3013  0098 cd0001        	call	_init_I2C
3015                     ; 66 	init_UART2();
3017  009b ada2          	call	_init_UART2
3019  009d               L3002:
3020                     ; 70 	while (1);
3022  009d 20fe          	jra	L3002
3035                     	xdef	_main
3036                     	xdef	_send_dc_cap_UART
3037                     	xdef	_send_ac_cap_UART
3038                     	xdef	_write_byte_UART2
3039                     	xdef	_init_UART2
3040                     	xdef	_read_AD7991
3041                     	xdef	_init_I2C
3042                     	xdef	_init_PWM
3043                     	xref	_Stop_I2C
3044                     	xref	_NoAck_I2C
3045                     	xref	_Ack_I2C
3046                     	xref	_Read_I2C
3047                     	xref	_Write_I2C
3048                     	xref	_Start_I2C
3067                     	end
