   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2551                     ; 8 void init_pwm(void) {
2553                     	switch	.text
2554  0000               _init_pwm:
2558                     ; 10 }
2561  0000 81            	ret
2584                     ; 13 void init_I2C(void) {
2585                     	switch	.text
2586  0001               _init_I2C:
2590                     ; 15 }
2593  0001 81            	ret
2618                     ; 17 main()
2618                     ; 18 {
2619                     	switch	.text
2620  0002               _main:
2624                     ; 19 	init_pwm();
2626  0002 adfc          	call	_init_pwm
2628                     ; 20 	init_I2C();
2630  0004 adfb          	call	_init_I2C
2632  0006               L1661:
2633                     ; 24 	while (1);
2635  0006 20fe          	jra	L1661
2648                     	xdef	_main
2649                     	xdef	_init_I2C
2650                     	xdef	_init_pwm
2669                     	end
