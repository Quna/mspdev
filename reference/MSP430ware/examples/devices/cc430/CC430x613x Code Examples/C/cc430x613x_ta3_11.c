//******************************************************************************
//  CC430F613x Demo - Timer_A3, Toggle P2.1/TA1.0, Up Mode, 32kHz ACLK
//
//  Description: Toggle P2.0 using hardware TA1.0 output. Timer1_A is configured
//  for up mode with CCR0 defining period. 
//  Thus the output frequency on P2.0 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P2.0 output frequency = 32768/20 = 1.6384kHz.
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                CC430F6137
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.0/TA1.0|--> ACLK/20
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_TA1CCR0A;                     // Map TA1CCR0 output to P2.0 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2DIR |= BIT0;                            // P2.0 output
  P2SEL |= BIT0;                            // P2.0 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 10-1;
  TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
