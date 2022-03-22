   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2553                     ; 23 main()
2553                     ; 24 {
2555                     	switch	.text
2556  0000               _main:
2560                     ; 25 	init_SPI();
2562  0000 cd0000        	call	_init_SPI
2564                     ; 26 	affiche_mot("despacito", 0, 0);
2566  0003 4b00          	push	#0
2567  0005 4b00          	push	#0
2568  0007 ae0000        	ldw	x,#L1461
2569  000a cd0000        	call	_affiche_mot
2571  000d 85            	popw	x
2572  000e               L3461:
2573                     ; 29 	while (1);
2575  000e 20fe          	jra	L3461
2588                     	xdef	_main
2589                     	xref	_affiche_mot
2590                     	xref	_init_SPI
2591                     .const:	section	.text
2592  0000               L1461:
2593  0000 646573706163  	dc.b	"despacito",0
2613                     	end
