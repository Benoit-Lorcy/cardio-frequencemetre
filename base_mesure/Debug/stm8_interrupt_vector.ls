   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
2553                     ; 13 @far @interrupt void NonHandledInterrupt (void)
2553                     ; 14 {
2554                     	switch	.text
2555  0000               f_NonHandledInterrupt:
2559                     ; 18 	return;
2562  0000 80            	iret
2564                     .const:	section	.text
2565  0000               __vectab:
2566  0000 82            	dc.b	130
2568  0001 00            	dc.b	page(__stext)
2569  0002 0000          	dc.w	__stext
2570  0004 82            	dc.b	130
2572  0005 00            	dc.b	page(f_NonHandledInterrupt)
2573  0006 0000          	dc.w	f_NonHandledInterrupt
2574  0008 82            	dc.b	130
2576  0009 00            	dc.b	page(f_NonHandledInterrupt)
2577  000a 0000          	dc.w	f_NonHandledInterrupt
2578  000c 82            	dc.b	130
2580  000d 00            	dc.b	page(f_NonHandledInterrupt)
2581  000e 0000          	dc.w	f_NonHandledInterrupt
2582  0010 82            	dc.b	130
2584  0011 00            	dc.b	page(f_NonHandledInterrupt)
2585  0012 0000          	dc.w	f_NonHandledInterrupt
2586  0014 82            	dc.b	130
2588  0015 00            	dc.b	page(f_NonHandledInterrupt)
2589  0016 0000          	dc.w	f_NonHandledInterrupt
2590  0018 82            	dc.b	130
2592  0019 00            	dc.b	page(f_NonHandledInterrupt)
2593  001a 0000          	dc.w	f_NonHandledInterrupt
2594  001c 82            	dc.b	130
2596  001d 00            	dc.b	page(f_NonHandledInterrupt)
2597  001e 0000          	dc.w	f_NonHandledInterrupt
2598  0020 82            	dc.b	130
2600  0021 00            	dc.b	page(f_NonHandledInterrupt)
2601  0022 0000          	dc.w	f_NonHandledInterrupt
2602  0024 82            	dc.b	130
2604  0025 00            	dc.b	page(f_NonHandledInterrupt)
2605  0026 0000          	dc.w	f_NonHandledInterrupt
2606  0028 82            	dc.b	130
2608  0029 00            	dc.b	page(f_NonHandledInterrupt)
2609  002a 0000          	dc.w	f_NonHandledInterrupt
2610  002c 82            	dc.b	130
2612  002d 00            	dc.b	page(f_NonHandledInterrupt)
2613  002e 0000          	dc.w	f_NonHandledInterrupt
2614  0030 82            	dc.b	130
2616  0031 00            	dc.b	page(f_NonHandledInterrupt)
2617  0032 0000          	dc.w	f_NonHandledInterrupt
2618  0034 82            	dc.b	130
2620  0035 00            	dc.b	page(f_NonHandledInterrupt)
2621  0036 0000          	dc.w	f_NonHandledInterrupt
2622  0038 82            	dc.b	130
2624  0039 00            	dc.b	page(f_NonHandledInterrupt)
2625  003a 0000          	dc.w	f_NonHandledInterrupt
2626  003c 82            	dc.b	130
2628  003d 00            	dc.b	page(f_NonHandledInterrupt)
2629  003e 0000          	dc.w	f_NonHandledInterrupt
2630  0040 82            	dc.b	130
2632  0041 00            	dc.b	page(f_NonHandledInterrupt)
2633  0042 0000          	dc.w	f_NonHandledInterrupt
2634  0044 82            	dc.b	130
2636  0045 00            	dc.b	page(f_NonHandledInterrupt)
2637  0046 0000          	dc.w	f_NonHandledInterrupt
2638  0048 82            	dc.b	130
2640  0049 00            	dc.b	page(f_NonHandledInterrupt)
2641  004a 0000          	dc.w	f_NonHandledInterrupt
2642  004c 82            	dc.b	130
2644  004d 00            	dc.b	page(f_NonHandledInterrupt)
2645  004e 0000          	dc.w	f_NonHandledInterrupt
2646  0050 82            	dc.b	130
2648  0051 00            	dc.b	page(f_NonHandledInterrupt)
2649  0052 0000          	dc.w	f_NonHandledInterrupt
2650  0054 82            	dc.b	130
2652  0055 00            	dc.b	page(f_NonHandledInterrupt)
2653  0056 0000          	dc.w	f_NonHandledInterrupt
2654  0058 82            	dc.b	130
2656  0059 00            	dc.b	page(f_NonHandledInterrupt)
2657  005a 0000          	dc.w	f_NonHandledInterrupt
2658  005c 82            	dc.b	130
2660  005d 00            	dc.b	page(f_NonHandledInterrupt)
2661  005e 0000          	dc.w	f_NonHandledInterrupt
2662  0060 82            	dc.b	130
2664  0061 00            	dc.b	page(f_NonHandledInterrupt)
2665  0062 0000          	dc.w	f_NonHandledInterrupt
2666  0064 82            	dc.b	130
2668  0065 00            	dc.b	page(f_NonHandledInterrupt)
2669  0066 0000          	dc.w	f_NonHandledInterrupt
2670  0068 82            	dc.b	130
2672  0069 00            	dc.b	page(f_NonHandledInterrupt)
2673  006a 0000          	dc.w	f_NonHandledInterrupt
2674  006c 82            	dc.b	130
2676  006d 00            	dc.b	page(f_NonHandledInterrupt)
2677  006e 0000          	dc.w	f_NonHandledInterrupt
2678  0070 82            	dc.b	130
2680  0071 00            	dc.b	page(f_NonHandledInterrupt)
2681  0072 0000          	dc.w	f_NonHandledInterrupt
2682  0074 82            	dc.b	130
2684  0075 00            	dc.b	page(f_NonHandledInterrupt)
2685  0076 0000          	dc.w	f_NonHandledInterrupt
2686  0078 82            	dc.b	130
2688  0079 00            	dc.b	page(f_NonHandledInterrupt)
2689  007a 0000          	dc.w	f_NonHandledInterrupt
2690  007c 82            	dc.b	130
2692  007d 00            	dc.b	page(f_NonHandledInterrupt)
2693  007e 0000          	dc.w	f_NonHandledInterrupt
2744                     	xdef	__vectab
2745                     	xref	__stext
2746                     	xdef	f_NonHandledInterrupt
2765                     	end
