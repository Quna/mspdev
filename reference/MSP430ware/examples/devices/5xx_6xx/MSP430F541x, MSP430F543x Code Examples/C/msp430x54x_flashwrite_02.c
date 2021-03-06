//******************************************************************************
//  MSP430x54x Demo - Flash In-System Programming w/ Long-Word write at 0x1800
//
//  Description: This program first erases flash seg D, then it writes a 32-bit
//  value to memory location 0x1800 using long-word write mode. Long-word write
//  provides faster write than byte/word mode.
//  RESET the device to re-execute code. This is implemented to prevent
//  stressing of Flash unintentionally.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//                MSP430x54x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//
//  W. Goh
//  Texas Instruments Inc.
//  July 2011
//  Built with CCS v4.2.3.00004 and IAR Embedded Workbench v5.20.1
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  unsigned long * Flash_ptrD;               // Initialize Flash pointer Seg D
  unsigned long value;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  Flash_ptrD = (unsigned long *) 0x1800;    // Initialize Flash pointer
  value = 0x12345678;                       // Initialize Value
  __disable_interrupt();                    // 5xx Workaround: Disable global
                                            // interrupt while erasing. Re-Enable
                                            // GIE if needed
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *(unsigned int *)Flash_ptrD = 0;         // Dummy write to erase Flash seg
  FCTL1 = FWKEY+BLKWRT;                     // Enable long-word write
  *(unsigned long *)Flash_ptrD = value;     // Write to Flash
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  while(1);                                 // Loop forever, SET BREAKPOINT HERE
}
