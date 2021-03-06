;*******************************************************************************
;   MSP430F21x2 Demo - ADC10, DTC Sample A0 64x, AVcc, HF XTAL
;
;   Description: For non-low power applications HF XTAL can source ACLK and be
;   used also for CPU MCLK, as in this example. DTC always uses MCLK for data
;   transfer. Though not required, ADC10 can also clock from HF XTAL as in this
;   example using ACLK.
;   MCLK = ACLK = ADC10CLK = HF XTAL in this example.
;   DTC Used to sample A0 64 times with reference to AVcc. Software writes to
;   ADC10SC to trigger sample burst. In Mainloop MSP430 waits in LPM0 to save
;   power until ADC10 conversion burst complete, ADC10_ISR(DTC) will force
;   exit from LPM0 in Mainloop on reti. In this example ACLK times sample
;   period (16x) and conversion (13x). DTC transfers conversion code to RAM
;   200h - 280h. P1.0 set at start of conversion burst, reset on completion.
;   //* HF XTAL NOT INSTALLED ON FET *//
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (3  16MHz crystal or resonator)
;          --|RST          XOUT|-
;            |                 |
;        >---|P2.0/A0      P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP        		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            bis.b   #LFXT1S1,&BCSCTL3       ; 3  16MHz crystal or resonator
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupADC10  mov.w   #ADC10SSEL_1+CONSEQ_2,&ADC10CTL1 ;
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #01h,&ADC10AE0          ; P2.0 ADC option select
            mov.b   #040h,&ADC10DTC1        ; 64 conversions
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bis.b   #001h,&P1OUT            ; P1.0 = 1
            bic.w   #ENC,&ADC10CTL0         ;
busy_test   bit.w   #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC12 ISR will force exit
            bic.b   #001h,&P1OUT            ; P1.0 = 0
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int05"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect	".reset"	            ; POR, ext. Reset
            .short      RESET
           	.end
