//******************************************************************************
//  MSP430F20xx Demo - USICNT Used as a One-Shot Timer Function, DCO SMCLK
//
//  Description: USI conunter is used as a one-shot timer. The USI
//  conunter ISR toggles P1.0 using software. As coded ACLK is pre-divided by
//  128 and the USICNT loaded with 32, for a total divided of 4096 or
//  12-bits. USICNT must be reloaded after each interrupt which also clears
//  interrupt flag.
//  ACLK = VLO, MCLK = SMCLK = default DCO
//
//		  MSP430F20xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M. Buccini / L. Westlund
//  Texas Instruments Inc.
//  September 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************

#include <msp430x20x3.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  USICTL0 |= USIMST;                        // Master mode
  USICTL1 |= USIIE;                         // Counter interrupt, flag remains set
  USICKCTL = USIDIV_7 + USISSEL_1;          // /128 ACLK
  USICTL0 &= ~USISWRST;                     // USI released for operation
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
  USICNT = 0x1F;                            // re-load counter
}

