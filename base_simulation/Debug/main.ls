   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2552                     ; 23 main()
2552                     ; 24 {
2554                     	switch	.text
2555  0000               _main:
2559                     ; 25 	init_ADC();
2561  0000 cd0000        	call	_init_ADC
2563  0003               L1461:
2564                     ; 28 	while (1);
2566  0003 20fe          	jra	L1461
2579                     	xdef	_main
2580                     	xref	_init_ADC
2599                     	end
