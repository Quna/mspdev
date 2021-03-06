;******************************************************************************
;   MSP430xG46x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
;   breakpoints are set in slave RX ISR, master must stopped also to avoid
;   overrunning slave RXBUF.
;
;                MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 |   32kHz xtal
;          | |             XOUT|-
; Master---+-|RST              |
;            |             P7.1|<- Data In (UCA0SIMO)
;            |                 |
;            |             P7.2|-> Data Out (UCA0SOMI)
;            |                 |
;            |             P7.3|<- Serial Clock In (UCA0CLK)
;
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"

MST_Data	.equ   R6
SLV_Data   	.equ   R7

;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

            mov.w   #2100,R15               ; Now with stable ACLK, wait for
DCO_delay   dec.w   R15                     ; DCO to stabilize
            jnz     DCO_delay

waitForMstr bit.b   #08h,&P7IN             ; If clock sig from mstr stays low,
            jz      waitForMstr             ; it is not yet in SPI mode

            bis.b   #00Eh,&P7SEL            ; P7.3,2,1 option select
SetupSPI    mov.b   #UCSWRST,&UCA0CTL1      ; **Put state machine in reset**
            bis.b   #UCSYNC+UCCKPL+UCMSB,&UCA0CTL0;3-pin, 8-bit SPI master
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt

Mainloop    bis.b   #LPM4+GIE,SR            ; Enter LPM4, enable interrupts
            nop                             ; Required for debugger only
                                            ;
;------------------------------------------------------------------------------
USCIA0RX_ISR;       Test for valid RX and TX character
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG1,&IFG2
            jz      TX1
            mov.b   &UCA0RXBUF,&UCA0TXBUF
            reti
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int25"        ; USCI_A0 Rx Vector
            .short   USCIA0RX_ISR             ;
            .sect    ".reset"            ; RESET Vector
            .short   RESET                   ;
            .end
