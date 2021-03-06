//******************************************************************************
//   MSP430F543xA Demo - Write a byte to Port 1
//
//   Description: Writes a byte(0xFF) to Port 1 and stays in LPM4 mode
//   ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |             P1.x|-->HI
//            |                 |
//            |                 |
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x0FF;                            // Set P1.x to output direction
  P1OUT = 0x0FF;                            // Set all P1 pins HI

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
  __no_operation();                         // For debugger
}

