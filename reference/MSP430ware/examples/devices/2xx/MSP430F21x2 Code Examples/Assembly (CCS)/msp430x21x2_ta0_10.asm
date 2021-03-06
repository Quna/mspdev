;******************************************************************************
;  MSP430F21x2 Demo - Timer0_A3, Toggle P1.1/TA0_0, Up Mode, DCO SMCLK
;
;  Description: Toggle P1.1 using hardware TA0_0 output. Timer0_A3 is configured
;  for up mode with TA0CCR0 defining period, TA1_0 also output on P1.1. In this
;  example, TA0CCR0 is loaded with 500-1 and TA0_0 will toggle P1.1 at TA0CLK/500.
;  Thus the output frequency on P1.1 will be TACLK/1000. No CPU or software
;  resources required.
;  As coded with TA0CLK = SMCLK, P1.1 output frequency is ~1200000/1000.
;  SMCLK = MCLK = TA0CLK = default DCO ~1.2MHz
;
;            MSP430F21x2
;         -----------------
;     /|\|              XIN|-
;      | |                 |
;      --|RST          XOUT|-
;        |                 |
;        |       P1.1/TA0_0|--> SMCLK/1000
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output
            bis.b   #002h,&P1SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&TA0CCTL0     ; TACCR0 toggle, upmode
            mov.w   #500-1,&TA0CCR0         ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TA0CTL  ; SMCLK, clear TAR
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .end
