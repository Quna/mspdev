//******************************************************************************
//  MSP430F(G)47x Demo - Basic Timer, Toggle P4.6 Inside ISR, 32kHz ACLK
//
//  Description: Toggles P4.6 by xor'ing P4.6 inside of a basic timer ISR.
//  ACLK provides the basic timer clock source. LED toggles every 125ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load cap for 32k xtal
  P4DIR |= 0x40;                            // Set P4.6 as output
  BTCTL = BTDIV + BT_fCLK2_DIV16;           // ACLK/(256*16)
  IE2 |= BTIE;                              // Enable BT interrupt

  __bis_SR_register(LPM3_bits + GIE);                 // Enter LPM3, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6
}

