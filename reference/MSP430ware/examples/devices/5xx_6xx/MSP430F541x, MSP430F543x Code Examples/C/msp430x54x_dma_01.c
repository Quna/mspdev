//******************************************************************************
//  MSP430x54x Demo - DMA0, Repeated Block to-from RAM, Software Trigger
//
//  Description: A 16 word block from 1C00-1C1Fh is transfered to 1C20h-1C3fh
//  using DMA0 in a burst block using software DMAREQ trigger.
//  After each transfer, source, destination and DMA size are
//  reset to inital software setting because DMA transfer mode 5 is used.
//  P1.0 is toggled durring DMA transfer only for demonstration purposes.
//  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//                 MSP430x54x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  W. Goh
//  Texas Instruments Inc.
//  February 2009
//  Built with CCE v3.1 Build 3.2.3.6.4 & IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) 0x1C00);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) 0x1C20);
                                            // Destination single address
  DMA0SZ = 16;                              // Block size
  DMA0CTL = DMADT_5+DMASRCINCR_3+DMADSTINCR_3; // Rpt, inc
  DMA0CTL |= DMAEN;                         // Enable DMA0

  while(1)
  {
    P1OUT |= 0x01;                          // P1.0 = 1, LED on
    DMA0CTL |= DMAREQ;                      // Trigger block transfer
    P1OUT &= ~0x01;                         // P1.0 = 0, LED off
  }
}
