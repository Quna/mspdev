//******************************************************************************
//  MSP-FET430P140 Demo - USART0, Ultra-Low Pwr UART 2400 Echo ISR, 32kHz ACLK
//
//  Description: Echo a received character, RX ISR used. In the Mainloop UART0
//  is made ready to receive one character with interrupt active. The Mainloop
//  waits in LPM3. The UART0 ISR forces the Mainloop to exit LPM3 after
//  receiving one character which echo's back the received character.
//  ACLK = UCLK0 = LFXT1 = 32768, MCLK = SMCLK = DCO~ 800k
//  Baud rate divider with 32768hz XTAL @2400 = 32768Hz/2400 = 13.65 (000Dh)
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//                MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P3.4|----------->
//           |                 | 2400 - 8N1
//           |             P3.5|<-----------
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
  ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
  UCTL0 |= CHAR;                            // 8-bit character
  UTCTL0 |= SSEL0;                          // UCLK = ACLK
  UBR00 = 0x0D;                             // 32k/2400 - 13.65
  UBR10 = 0x00;                             //
  UMCTL0 = 0x6B;                            // Modulation
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
  IE1 |= URXIE0;                            // Enable USART0 RX interrupt

// Mainloop
  for (;;)
  {
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
  while (!(IFG1 & UTXIFG0));                // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
  }
}

// UART0 RX ISR will for exit from LPM3 in Mainloop
#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  _BIC_SR_IRQ(LPM3_bits);                   // Clear LPM3 bits from 0(SR)
}
