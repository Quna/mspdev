/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* CC430F5147 devices.
*
* Texas Instruments, Version 1.7
*
* Rev. 1.0, First Release
* Rev. 1.1, added TLV definitions
* Rev. 1.2, added some more DMA Trigger definitions
* Rev. 1.3, fixed LCDMEM access
* Rev. 1.4, changed RTC_A_VECTOR to RTC_VECTOR
* Rev. 1.5, clean up of Flash section
* Rev. 1.6, Changed access type of DMAxSZ registers to word only
* Rev. 1.7  Changed access type of TimerA/B registers to word only
*
*
********************************************************************/

#ifndef __CC430F5147
#define __CC430F5147

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error cc430f5147.h file for use with ICC430/A430 only
#endif


#ifdef __IAR_SYSTEMS_ICC__
#include "in430.h"
#pragma language=extended

#define DEFC(name, address) __no_init volatile unsigned char name @ address;
#define DEFW(name, address) __no_init volatile unsigned short name @ address;

#define DEFCW(name, address) __no_init union \
{ \
  struct \
  { \
    volatile unsigned char  name##_L; \
    volatile unsigned char  name##_H; \
  }; \
  volatile unsigned short   name; \
} @ address;

#define READ_ONLY_DEFCW(name, address) __no_init union \
{ \
  struct \
  { \
    volatile READ_ONLY unsigned char  name##_L; \
    volatile READ_ONLY unsigned char  name##_H; \
  }; \
  volatile READ_ONLY unsigned short   name; \
} @ address;


#if __REGISTER_MODEL__ == __REGISTER_MODEL_REG20__
#define __ACCESS_20BIT_REG__  void __data20 * volatile
#else
#define __ACCESS_20BIT_REG__  volatile unsigned short  /* only short access from C is allowed in small memory model */
#endif

#define DEFA(name, address) __no_init union \
{ \
  struct \
  { \
    volatile unsigned char  name##_L; \
    volatile unsigned char  name##_H; \
  }; \
  struct \
  { \
    volatile unsigned short name##L; \
    volatile unsigned short name##H; \
  }; \
  __ACCESS_20BIT_REG__ name; \
} @ address;

#endif  /* __IAR_SYSTEMS_ICC__  */


#ifdef __IAR_SYSTEMS_ASM__
#define DEFC(name, address) sfrb name = address;
#define DEFW(name, address) sfrw name = address;

#define DEFCW(name, address) sfrbw name, name##_L, name##_H, address;
sfrbw macro name, name_L, name_H, address;
sfrb name_L = address;
sfrb name_H = address+1;
sfrw name   = address;
      endm

#define READ_ONLY_DEFCW(name, address) const_sfrbw name, name##_L, name##_H, address;
const_sfrbw macro name, name_L, name_H, address;
const sfrb name_L = address;
const sfrb name_H = address+1;
const sfrw name   = address;
      endm

#define DEFA(name, address) sfrba name, name##L, name##H, name##_L, name##_H, address;
sfrba macro name, nameL, nameH, name_L, name_H, address;
sfrb name_L = address;
sfrb name_H = address+1;
sfrw nameL  = address;
sfrw nameH  = address+2;
sfrl name   = address;
      endm

#endif /* __IAR_SYSTEMS_ASM__*/

#ifdef __cplusplus
#define READ_ONLY
#else
#define READ_ONLY const
#endif

/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x0001u)
#define BIT1                (0x0002u)
#define BIT2                (0x0004u)
#define BIT3                (0x0008u)
#define BIT4                (0x0010u)
#define BIT5                (0x0020u)
#define BIT6                (0x0040u)
#define BIT7                (0x0080u)
#define BIT8                (0x0100u)
#define BIT9                (0x0200u)
#define BITA                (0x0400u)
#define BITB                (0x0800u)
#define BITC                (0x1000u)
#define BITD                (0x2000u)
#define BITE                (0x4000u)
#define BITF                (0x8000u)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                   (0x0001u)
#define Z                   (0x0002u)
#define N                   (0x0004u)
#define V                   (0x0100u)
#define GIE                 (0x0008u)
#define CPUOFF              (0x0010u)
#define OSCOFF              (0x0020u)
#define SCG0                (0x0040u)
#define SCG1                (0x0080u)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifndef __IAR_SYSTEMS_ICC__ /* Begin #defines for assembler */
#define LPM0                (CPUOFF)
#define LPM1                (SCG0+CPUOFF)
#define LPM2                (SCG1+CPUOFF)
#define LPM3                (SCG1+SCG0+CPUOFF)
#define LPM4                (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"

#define LPM0      _BIS_SR(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT _BIC_SR_IRQ(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      _BIS_SR(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT _BIC_SR_IRQ(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      _BIS_SR(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT _BIC_SR_IRQ(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      _BIS_SR(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT _BIC_SR_IRQ(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      _BIS_SR(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT _BIC_SR_IRQ(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* CPU
************************************************************/
#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430XV2 CPU */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* ADC10_A
************************************************************/
#define __MSP430_HAS_ADC10_A__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC10_A__ 0x0740

#define ADC10CTL0_          (0x0740u)  /* ADC10 Control 0 */
DEFCW(  ADC10CTL0         , ADC10CTL0_)
#define ADC10CTL1_          (0x0742u)  /* ADC10 Control 1 */
DEFCW(  ADC10CTL1         , ADC10CTL1_)
#define ADC10CTL2_          (0x0744u)  /* ADC10 Control 2 */
DEFCW(  ADC10CTL2         , ADC10CTL2_)
#define ADC10LO_            (0x0746u)  /* ADC10 Window Comparator High Threshold */
DEFCW(  ADC10LO           , ADC10LO_)
#define ADC10HI_            (0x0748u)  /* ADC10 Window Comparator High Threshold */
DEFCW(  ADC10HI           , ADC10HI_)
#define ADC10MCTL0_         (0x074Au)  /* ADC10 Memory Control 0 */
DEFCW(  ADC10MCTL0        , ADC10MCTL0_)
#define ADC10MEM0_          (0x0752u)  /* ADC10 Conversion Memory 0 */
DEFCW(  ADC10MEM0         , ADC10MEM0_)
#define ADC10IE_            (0x075Au)  /* ADC10 Interrupt Enable */
DEFCW(  ADC10IE           , ADC10IE_)
#define ADC10IFG_           (0x075Cu)  /* ADC10 Interrupt Flag */
DEFCW(  ADC10IFG          , ADC10IFG_)
#define ADC10IV_            (0x075Eu)  /* ADC10 Interrupt Vector Word */
DEFCW(  ADC10IV           , ADC10IV_)

/* ADC10CTL0 Control Bits */
#define ADC10SC             (0x0001u)  /* ADC10 Start Conversion */
#define ADC10ENC            (0x0002u)  /* ADC10 Enable Conversion */
#define ADC10ON             (0x0010u)  /* ADC10 On/enable */
#define ADC10MSC            (0x0080u)  /* ADC10 Multiple SampleConversion */
#define ADC10SHT0           (0x0100u)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1           (0x0200u)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2           (0x0400u)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3           (0x0800u)  /* ADC10 Sample Hold Select Bit: 3 */

/* ADC10CTL0 Control Bits */
#define ADC10SC_L           (0x0001u)  /* ADC10 Start Conversion */
#define ADC10ENC_L          (0x0002u)  /* ADC10 Enable Conversion */
#define ADC10ON_L           (0x0010u)  /* ADC10 On/enable */
#define ADC10MSC_L          (0x0080u)  /* ADC10 Multiple SampleConversion */

/* ADC10CTL0 Control Bits */
#define ADC10SHT0_H         (0x0001u)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1_H         (0x0002u)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2_H         (0x0004u)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3_H         (0x0008u)  /* ADC10 Sample Hold Select Bit: 3 */

#define ADC10SHT_0          (0*0x100u) /* ADC10 Sample Hold Select 0 */
#define ADC10SHT_1          (1*0x100u) /* ADC10 Sample Hold Select 1 */
#define ADC10SHT_2          (2*0x100u) /* ADC10 Sample Hold Select 2 */
#define ADC10SHT_3          (3*0x100u) /* ADC10 Sample Hold Select 3 */
#define ADC10SHT_4          (4*0x100u) /* ADC10 Sample Hold Select 4 */
#define ADC10SHT_5          (5*0x100u) /* ADC10 Sample Hold Select 5 */
#define ADC10SHT_6          (6*0x100u) /* ADC10 Sample Hold Select 6 */
#define ADC10SHT_7          (7*0x100u) /* ADC10 Sample Hold Select 7 */
#define ADC10SHT_8          (8*0x100u) /* ADC10 Sample Hold Select 8 */
#define ADC10SHT_9          (9*0x100u) /* ADC10 Sample Hold Select 9 */
#define ADC10SHT_10         (10*0x100u) /* ADC10 Sample Hold Select 10 */
#define ADC10SHT_11         (11*0x100u) /* ADC10 Sample Hold Select 11 */
#define ADC10SHT_12         (12*0x100u) /* ADC10 Sample Hold Select 12 */
#define ADC10SHT_13         (13*0x100u) /* ADC10 Sample Hold Select 13 */
#define ADC10SHT_14         (14*0x100u) /* ADC10 Sample Hold Select 14 */
#define ADC10SHT_15         (15*0x100u) /* ADC10 Sample Hold Select 15 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY           (0x0001u)    /* ADC10 Busy */
#define ADC10CONSEQ0        (0x0002u)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1        (0x0004u)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0          (0x0008u)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1          (0x0010u)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0           (0x0020u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1           (0x0040u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2           (0x0080u)    /* ADC10 Clock Divider Select 2 */
#define ADC10ISSH           (0x0100u)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP            (0x0200u)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0           (0x0400u)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1           (0x0800u)    /* ADC10 Sample/Hold Source 1 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY_L         (0x0001u)    /* ADC10 Busy */
#define ADC10CONSEQ0_L      (0x0002u)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1_L      (0x0004u)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0_L        (0x0008u)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1_L        (0x0010u)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0_L         (0x0020u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1_L         (0x0040u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2_L         (0x0080u)    /* ADC10 Clock Divider Select 2 */

/* ADC10CTL1 Control Bits */
#define ADC10ISSH_H         (0x0001u)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP_H          (0x0002u)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0_H         (0x0004u)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1_H         (0x0008u)    /* ADC10 Sample/Hold Source 1 */

#define ADC10CONSEQ_0        (0*2u)      /* ADC10 Conversion Sequence Select: 0 */
#define ADC10CONSEQ_1        (1*2u)      /* ADC10 Conversion Sequence Select: 1 */
#define ADC10CONSEQ_2        (2*2u)      /* ADC10 Conversion Sequence Select: 2 */
#define ADC10CONSEQ_3        (3*2u)      /* ADC10 Conversion Sequence Select: 3 */

#define ADC10SSEL_0          (0*8u)      /* ADC10 Clock Source Select: 0 */
#define ADC10SSEL_1          (1*8u)      /* ADC10 Clock Source Select: 1 */
#define ADC10SSEL_2          (2*8u)      /* ADC10 Clock Source Select: 2 */
#define ADC10SSEL_3          (3*8u)      /* ADC10 Clock Source Select: 3 */

#define ADC10DIV_0           (0*0x20u)   /* ADC10 Clock Divider Select: 0 */
#define ADC10DIV_1           (1*0x20u)   /* ADC10 Clock Divider Select: 1 */
#define ADC10DIV_2           (2*0x20u)   /* ADC10 Clock Divider Select: 2 */
#define ADC10DIV_3           (3*0x20u)   /* ADC10 Clock Divider Select: 3 */
#define ADC10DIV_4           (4*0x20u)   /* ADC10 Clock Divider Select: 4 */
#define ADC10DIV_5           (5*0x20u)   /* ADC10 Clock Divider Select: 5 */
#define ADC10DIV_6           (6*0x20u)   /* ADC10 Clock Divider Select: 6 */
#define ADC10DIV_7           (7*0x20u)   /* ADC10 Clock Divider Select: 7 */

#define ADC10SHS_0           (0*0x400u)  /* ADC10 Sample/Hold Source: 0 */
#define ADC10SHS_1           (1*0x400u)  /* ADC10 Sample/Hold Source: 1 */
#define ADC10SHS_2           (2*0x400u)  /* ADC10 Sample/Hold Source: 2 */
#define ADC10SHS_3           (3*0x400u)  /* ADC10 Sample/Hold Source: 3 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST       (0x0001u)    /* ADC10 Reference Burst */
#define ADC10SR             (0x0004u)    /* ADC10 Sampling Rate */
#define ADC10DF             (0x0008u)    /* ADC10 Data Format */
#define ADC10RES            (0x0010u)    /* ADC10 Resolution Bit */
#define ADC10PDIV0          (0x0100u)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1          (0x0200u)    /* ADC10 predivider Bit: 1 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST_L     (0x0001u)    /* ADC10 Reference Burst */
#define ADC10SR_L           (0x0004u)    /* ADC10 Sampling Rate */
#define ADC10DF_L           (0x0008u)    /* ADC10 Data Format */
#define ADC10RES_L          (0x0010u)    /* ADC10 Resolution Bit */

/* ADC10CTL2 Control Bits */
#define ADC10PDIV0_H        (0x0001u)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1_H        (0x0002u)    /* ADC10 predivider Bit: 1 */

#define ADC10PDIV_0         (0x0000u)    /* ADC10 predivider /1 */
#define ADC10PDIV_1         (0x0100u)    /* ADC10 predivider /2 */
#define ADC10PDIV_2         (0x0200u)    /* ADC10 predivider /64 */
#define ADC10PDIV_3         (0x0300u)    /* ADC10 predivider reserved */

#define ADC10PDIV__1        (0x0000u)    /* ADC10 predivider /1 */
#define ADC10PDIV__4        (0x0100u)    /* ADC10 predivider /2 */
#define ADC10PDIV__64       (0x0200u)    /* ADC10 predivider /64 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0          (0x0001u)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1          (0x0002u)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2          (0x0004u)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3          (0x0008u)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0          (0x0010u)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1          (0x0020u)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2          (0x0040u)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0_L        (0x0001u)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1_L        (0x0002u)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2_L        (0x0004u)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3_L        (0x0008u)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0_L        (0x0010u)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1_L        (0x0020u)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2_L        (0x0040u)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */

#define ADC10INCH_0         (0)         /* ADC10 Input Channel 0 */
#define ADC10INCH_1         (1)         /* ADC10 Input Channel 1 */
#define ADC10INCH_2         (2)         /* ADC10 Input Channel 2 */
#define ADC10INCH_3         (3)         /* ADC10 Input Channel 3 */
#define ADC10INCH_4         (4)         /* ADC10 Input Channel 4 */
#define ADC10INCH_5         (5)         /* ADC10 Input Channel 5 */
#define ADC10INCH_6         (6)         /* ADC10 Input Channel 6 */
#define ADC10INCH_7         (7)         /* ADC10 Input Channel 7 */
#define ADC10INCH_8         (8)         /* ADC10 Input Channel 8 */
#define ADC10INCH_9         (9)         /* ADC10 Input Channel 9 */
#define ADC10INCH_10        (10)        /* ADC10 Input Channel 10 */
#define ADC10INCH_11        (11)        /* ADC10 Input Channel 11 */
#define ADC10INCH_12        (12)        /* ADC10 Input Channel 12 */
#define ADC10INCH_13        (13)        /* ADC10 Input Channel 13 */
#define ADC10INCH_14        (14)        /* ADC10 Input Channel 14 */
#define ADC10INCH_15        (15)        /* ADC10 Input Channel 15 */

#define ADC10SREF_0         (0*0x10u)    /* ADC10 Select Reference 0 */
#define ADC10SREF_1         (1*0x10u)    /* ADC10 Select Reference 1 */
#define ADC10SREF_2         (2*0x10u)    /* ADC10 Select Reference 2 */
#define ADC10SREF_3         (3*0x10u)    /* ADC10 Select Reference 3 */
#define ADC10SREF_4         (4*0x10u)    /* ADC10 Select Reference 4 */
#define ADC10SREF_5         (5*0x10u)    /* ADC10 Select Reference 5 */
#define ADC10SREF_6         (6*0x10u)    /* ADC10 Select Reference 6 */
#define ADC10SREF_7         (7*0x10u)    /* ADC10 Select Reference 7 */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0            (0x0001u)    /* ADC10_A Interrupt enable */
#define ADC10INIE           (0x0002u)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE           (0x0004u)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE           (0x0008u)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE           (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE          (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0_L          (0x0001u)    /* ADC10_A Interrupt enable */
#define ADC10INIE_L         (0x0002u)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE_L         (0x0004u)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE_L         (0x0008u)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE_L         (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE_L        (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0           (0x0001u)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG          (0x0002u)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG          (0x0004u)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG          (0x0008u)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG          (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG         (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0_L         (0x0001u)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG_L        (0x0002u)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG_L        (0x0004u)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG_L        (0x0008u)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG_L        (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG_L       (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */

/* ADC10IV Definitions */
#define ADC10IV_NONE        (0x0000u)    /* No Interrupt pending */
#define ADC10IV_ADC10OVIFG  (0x0002u)    /* ADC10OVIFG */
#define ADC10IV_ADC10TOVIFG (0x0004u)    /* ADC10TOVIFG */
#define ADC10IV_ADC10HIIFG  (0x0006u)    /* ADC10HIIFG */
#define ADC10IV_ADC10LOIFG  (0x0008u)    /* ADC10LOIFG */
#define ADC10IV_ADC10INIFG  (0x000Au)    /* ADC10INIFG */
#define ADC10IV_ADC10IFG    (0x000Cu)    /* ADC10IFG */

/************************************************************
* AES Accelerator
************************************************************/
#define __MSP430_HAS_AES__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_AES__ 0x09C0

#define  AESACTL0_           (0x09C0u)  /* AES accelerator control register 0 */
DEFCW(   AESACTL0          , AESACTL0_)
#define  AESASTAT_           (0x09C4u)  /* AES accelerator status register */
DEFCW(   AESASTAT          , AESASTAT_)
#define  AESAKEY_            (0x09C6u)  /* AES accelerator key register */
DEFCW(   AESAKEY           , AESAKEY_)
#define  AESADIN_            (0x09C8u)  /* AES accelerator data in register */
DEFCW(   AESADIN           , AESADIN_)
#define  AESADOUT_           (0x09CAu)  /* AES accelerator data out register  */
DEFCW(   AESADOUT          , AESADOUT_)

/* AESACTL0 Control Bits */
#define AESOP0              (0x0001u)  /* AES Operation Bit: 0 */
#define AESOP1              (0x0002u)  /* AES Operation Bit: 1 */
#define AESSWRST            (0x0080u)  /* AES Software Reset */
#define AESRDYIFG           (0x0100u)  /* AES ready interrupt flag */
#define AESERRFG            (0x0800u)  /* AES Error Flag */
#define AESRDYIE            (0x1000u)  /* AES ready interrupt enable*/

/* AESACTL0 Control Bits */
#define AESOP0_L            (0x0001u)  /* AES Operation Bit: 0 */
#define AESOP1_L            (0x0002u)  /* AES Operation Bit: 1 */
#define AESSWRST_L          (0x0080u)  /* AES Software Reset */

/* AESACTL0 Control Bits */
#define AESRDYIFG_H         (0x0001u)  /* AES ready interrupt flag */
#define AESERRFG_H          (0x0008u)  /* AES Error Flag */
#define AESRDYIE_H          (0x0010u)  /* AES ready interrupt enable*/

#define AESOP_0             (0x0000u)  /* AES Operation: Encrypt */
#define AESOP_1             (0x0001u)  /* AES Operation: Decrypt (same Key) */
#define AESOP_2             (0x0002u)  /* AES Operation: Decrypt (frist round Key) */
#define AESOP_3             (0x0003u)  /* AES Operation: Generate first round Key */

/* AESASTAT Control Bits */
#define AESBUSY             (0x0001u)  /* AES Busy */
#define AESKEYWR            (0x0002u)  /* AES All 16 bytes written to AESAKEY */
#define AESDINWR            (0x0004u)  /* AES All 16 bytes written to AESADIN */
#define AESDOUTRD           (0x0008u)  /* AES All 16 bytes read from AESADOUT */
#define AESKEYCNT0          (0x0010u)  /* AES Bytes written via AESAKEY Bit: 0 */
#define AESKEYCNT1          (0x0020u)  /* AES Bytes written via AESAKEY Bit: 1 */
#define AESKEYCNT2          (0x0040u)  /* AES Bytes written via AESAKEY Bit: 2 */
#define AESKEYCNT3          (0x0080u)  /* AES Bytes written via AESAKEY Bit: 3 */
#define AESDINCNT0          (0x0100u)  /* AES Bytes written via AESADIN Bit: 0 */
#define AESDINCNT1          (0x0200u)  /* AES Bytes written via AESADIN Bit: 1 */
#define AESDINCNT2          (0x0400u)  /* AES Bytes written via AESADIN Bit: 2 */
#define AESDINCNT3          (0x0800u)  /* AES Bytes written via AESADIN Bit: 3 */
#define AESDOUTCNT0         (0x1000u)  /* AES Bytes read via AESADOUT Bit: 0 */
#define AESDOUTCNT1         (0x2000u)  /* AES Bytes read via AESADOUT Bit: 1 */
#define AESDOUTCNT2         (0x4000u)  /* AES Bytes read via AESADOUT Bit: 2 */
#define AESDOUTCNT3         (0x8000u)  /* AES Bytes read via AESADOUT Bit: 3 */

/* AESASTAT Control Bits */
#define AESBUSY_L           (0x0001u)  /* AES Busy */
#define AESKEYWR_L          (0x0002u)  /* AES All 16 bytes written to AESAKEY */
#define AESDINWR_L          (0x0004u)  /* AES All 16 bytes written to AESADIN */
#define AESDOUTRD_L         (0x0008u)  /* AES All 16 bytes read from AESADOUT */
#define AESKEYCNT0_L        (0x0010u)  /* AES Bytes written via AESAKEY Bit: 0 */
#define AESKEYCNT1_L        (0x0020u)  /* AES Bytes written via AESAKEY Bit: 1 */
#define AESKEYCNT2_L        (0x0040u)  /* AES Bytes written via AESAKEY Bit: 2 */
#define AESKEYCNT3_L        (0x0080u)  /* AES Bytes written via AESAKEY Bit: 3 */

/* AESASTAT Control Bits */
#define AESDINCNT0_H        (0x0001u)  /* AES Bytes written via AESADIN Bit: 0 */
#define AESDINCNT1_H        (0x0002u)  /* AES Bytes written via AESADIN Bit: 1 */
#define AESDINCNT2_H        (0x0004u)  /* AES Bytes written via AESADIN Bit: 2 */
#define AESDINCNT3_H        (0x0008u)  /* AES Bytes written via AESADIN Bit: 3 */
#define AESDOUTCNT0_H       (0x0010u)  /* AES Bytes read via AESADOUT Bit: 0 */
#define AESDOUTCNT1_H       (0x0020u)  /* AES Bytes read via AESADOUT Bit: 1 */
#define AESDOUTCNT2_H       (0x0040u)  /* AES Bytes read via AESADOUT Bit: 2 */
#define AESDOUTCNT3_H       (0x0080u)  /* AES Bytes read via AESADOUT Bit: 3 */

/************************************************************
* Comparator B
************************************************************/
#define __MSP430_HAS_COMPB__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_COMPB__ 0x08C0

#define  CBCTL0_             (0x08C0u)  /* Comparator B Control Register 0 */
DEFCW(   CBCTL0            , CBCTL0_)
#define  CBCTL1_             (0x08C2u)  /* Comparator B Control Register 1 */
DEFCW(   CBCTL1            , CBCTL1_)
#define  CBCTL2_             (0x08C4u)  /* Comparator B Control Register 2 */
DEFCW(   CBCTL2            , CBCTL2_)
#define  CBCTL3_             (0x08C6u)  /* Comparator B Control Register 3 */
DEFCW(   CBCTL3            , CBCTL3_)
#define  CBINT_              (0x08CCu)  /* Comparator B Interrupt Register */
DEFCW(   CBINT             , CBINT_)
#define  CBIV_               (0x08CEu)  /* Comparator B Interrupt Vector Word */
DEFW(    CBIV              , CBIV_)

/* CBCTL0 Control Bits */
#define CBIPSEL0            (0x0001u)  /* Comp. B Pos. Channel Input Select 0 */
#define CBIPSEL1            (0x0002u)  /* Comp. B Pos. Channel Input Select 1 */
#define CBIPSEL2            (0x0004u)  /* Comp. B Pos. Channel Input Select 2 */
#define CBIPSEL3            (0x0008u)  /* Comp. B Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010u)  /* Comp. B */
//#define RESERVED            (0x0020u)  /* Comp. B */
//#define RESERVED            (0x0040u)  /* Comp. B */
#define CBIPEN              (0x0080u)  /* Comp. B Pos. Channel Input Enable */
#define CBIMSEL0            (0x0100u)  /* Comp. B Neg. Channel Input Select 0 */
#define CBIMSEL1            (0x0200u)  /* Comp. B Neg. Channel Input Select 1 */
#define CBIMSEL2            (0x0400u)  /* Comp. B Neg. Channel Input Select 2 */
#define CBIMSEL3            (0x0800u)  /* Comp. B Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000u)  /* Comp. B */
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */
#define CBIMEN              (0x8000u)  /* Comp. B Neg. Channel Input Enable */

/* CBCTL0 Control Bits */
#define CBIPSEL0_L          (0x0001u)  /* Comp. B Pos. Channel Input Select 0 */
#define CBIPSEL1_L          (0x0002u)  /* Comp. B Pos. Channel Input Select 1 */
#define CBIPSEL2_L          (0x0004u)  /* Comp. B Pos. Channel Input Select 2 */
#define CBIPSEL3_L          (0x0008u)  /* Comp. B Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010u)  /* Comp. B */
//#define RESERVED            (0x0020u)  /* Comp. B */
//#define RESERVED            (0x0040u)  /* Comp. B */
#define CBIPEN_L            (0x0080u)  /* Comp. B Pos. Channel Input Enable */
//#define RESERVED            (0x1000u)  /* Comp. B */
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */

/* CBCTL0 Control Bits */
//#define RESERVED            (0x0010u)  /* Comp. B */
//#define RESERVED            (0x0020u)  /* Comp. B */
//#define RESERVED            (0x0040u)  /* Comp. B */
#define CBIMSEL0_H          (0x0001u)  /* Comp. B Neg. Channel Input Select 0 */
#define CBIMSEL1_H          (0x0002u)  /* Comp. B Neg. Channel Input Select 1 */
#define CBIMSEL2_H          (0x0004u)  /* Comp. B Neg. Channel Input Select 2 */
#define CBIMSEL3_H          (0x0008u)  /* Comp. B Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000u)  /* Comp. B */
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */
#define CBIMEN_H            (0x0080u)  /* Comp. B Neg. Channel Input Enable */

#define CBIPSEL_0           (0x0000u)  /* Comp. B V+ terminal Input Select: Channel 0 */
#define CBIPSEL_1           (0x0001u)  /* Comp. B V+ terminal Input Select: Channel 1 */
#define CBIPSEL_2           (0x0002u)  /* Comp. B V+ terminal Input Select: Channel 2 */
#define CBIPSEL_3           (0x0003u)  /* Comp. B V+ terminal Input Select: Channel 3 */
#define CBIPSEL_4           (0x0004u)  /* Comp. B V+ terminal Input Select: Channel 4 */
#define CBIPSEL_5           (0x0005u)  /* Comp. B V+ terminal Input Select: Channel 5 */
#define CBIPSEL_6           (0x0006u)  /* Comp. B V+ terminal Input Select: Channel 6 */
#define CBIPSEL_7           (0x0007u)  /* Comp. B V+ terminal Input Select: Channel 7 */
#define CBIPSEL_8           (0x0008u)  /* Comp. B V+ terminal Input Select: Channel 8 */
#define CBIPSEL_9           (0x0009u)  /* Comp. B V+ terminal Input Select: Channel 9 */
#define CBIPSEL_10          (0x000Au)  /* Comp. B V+ terminal Input Select: Channel 10 */
#define CBIPSEL_11          (0x000Bu)  /* Comp. B V+ terminal Input Select: Channel 11 */
#define CBIPSEL_12          (0x000Cu)  /* Comp. B V+ terminal Input Select: Channel 12 */
#define CBIPSEL_13          (0x000Du)  /* Comp. B V+ terminal Input Select: Channel 13 */
#define CBIPSEL_14          (0x000Eu)  /* Comp. B V+ terminal Input Select: Channel 14 */
#define CBIPSEL_15          (0x000Fu)  /* Comp. B V+ terminal Input Select: Channel 15 */

#define CBIMSEL_0           (0x0000u)  /* Comp. B V- Terminal Input Select: Channel 0 */
#define CBIMSEL_1           (0x0100u)  /* Comp. B V- Terminal Input Select: Channel 1 */
#define CBIMSEL_2           (0x0200u)  /* Comp. B V- Terminal Input Select: Channel 2 */
#define CBIMSEL_3           (0x0300u)  /* Comp. B V- Terminal Input Select: Channel 3 */
#define CBIMSEL_4           (0x0400u)  /* Comp. B V- Terminal Input Select: Channel 4 */
#define CBIMSEL_5           (0x0500u)  /* Comp. B V- Terminal Input Select: Channel 5 */
#define CBIMSEL_6           (0x0600u)  /* Comp. B V- Terminal Input Select: Channel 6 */
#define CBIMSEL_7           (0x0700u)  /* Comp. B V- Terminal Input Select: Channel 7 */
#define CBIMSEL_8           (0x0800u)  /* Comp. B V- terminal Input Select: Channel 8 */
#define CBIMSEL_9           (0x0900u)  /* Comp. B V- terminal Input Select: Channel 9 */
#define CBIMSEL_10          (0x0A00u)  /* Comp. B V- terminal Input Select: Channel 10 */
#define CBIMSEL_11          (0x0B00u)  /* Comp. B V- terminal Input Select: Channel 11 */
#define CBIMSEL_12          (0x0C00u)  /* Comp. B V- terminal Input Select: Channel 12 */
#define CBIMSEL_13          (0x0D00u)  /* Comp. B V- terminal Input Select: Channel 13 */
#define CBIMSEL_14          (0x0E00u)  /* Comp. B V- terminal Input Select: Channel 14 */
#define CBIMSEL_15          (0x0F00u)  /* Comp. B V- terminal Input Select: Channel 15 */

/* CBCTL1 Control Bits */
#define CBOUT               (0x0001u)  /* Comp. B Output */
#define CBOUTPOL            (0x0002u)  /* Comp. B Output Polarity */
#define CBF                 (0x0004u)  /* Comp. B Enable Output Filter */
#define CBIES               (0x0008u)  /* Comp. B Interrupt Edge Select */
#define CBSHORT             (0x0010u)  /* Comp. B Input Short */
#define CBEX                (0x0020u)  /* Comp. B Exchange Inputs */
#define CBFDLY0             (0x0040u)  /* Comp. B Filter delay Bit 0 */
#define CBFDLY1             (0x0080u)  /* Comp. B Filter delay Bit 1 */
#define CBPWRMD0            (0x0100u)  /* Comp. B Power Mode Bit 0 */
#define CBPWRMD1            (0x0200u)  /* Comp. B Power Mode Bit 1 */
#define CBON                (0x0400u)  /* Comp. B enable */
#define CBMRVL              (0x0800u)  /* Comp. B CBMRV Level */
#define CBMRVS              (0x1000u)  /* Comp. B Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */
//#define RESERVED            (0x8000u)  /* Comp. B */

/* CBCTL1 Control Bits */
#define CBOUT_L             (0x0001u)  /* Comp. B Output */
#define CBOUTPOL_L          (0x0002u)  /* Comp. B Output Polarity */
#define CBF_L               (0x0004u)  /* Comp. B Enable Output Filter */
#define CBIES_L             (0x0008u)  /* Comp. B Interrupt Edge Select */
#define CBSHORT_L           (0x0010u)  /* Comp. B Input Short */
#define CBEX_L              (0x0020u)  /* Comp. B Exchange Inputs */
#define CBFDLY0_L           (0x0040u)  /* Comp. B Filter delay Bit 0 */
#define CBFDLY1_L           (0x0080u)  /* Comp. B Filter delay Bit 1 */
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */
//#define RESERVED            (0x8000u)  /* Comp. B */

/* CBCTL1 Control Bits */
#define CBPWRMD0_H          (0x0001u)  /* Comp. B Power Mode Bit 0 */
#define CBPWRMD1_H          (0x0002u)  /* Comp. B Power Mode Bit 1 */
#define CBON_H              (0x0004u)  /* Comp. B enable */
#define CBMRVL_H            (0x0008u)  /* Comp. B CBMRV Level */
#define CBMRVS_H            (0x0010u)  /* Comp. B Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000u)  /* Comp. B */
//#define RESERVED            (0x4000u)  /* Comp. B */
//#define RESERVED            (0x8000u)  /* Comp. B */

#define CBFDLY_0           (0x0000u)  /* Comp. B Filter delay 0 : 450ns */
#define CBFDLY_1           (0x0040u)  /* Comp. B Filter delay 1 : 900ns */
#define CBFDLY_2           (0x0080u)  /* Comp. B Filter delay 2 : 1800ns */
#define CBFDLY_3           (0x00C0u)  /* Comp. B Filter delay 3 : 3600ns */

#define CBPWRMD_0           (0x0000u)  /* Comp. B Power Mode 0 : High speed */
#define CBPWRMD_1           (0x0100u)  /* Comp. B Power Mode 1 : Normal */
#define CBPWRMD_2           (0x0200u)  /* Comp. B Power Mode 2 : Ultra-Low*/
#define CBPWRMD_3           (0x0300u)  /* Comp. B Power Mode 3 : Reserved */

/* CBCTL2 Control Bits */
#define CBREF00             (0x0001u)  /* Comp. B Reference 0 Resistor Select Bit : 0 */
#define CBREF01             (0x0002u)  /* Comp. B Reference 0 Resistor Select Bit : 1 */
#define CBREF02             (0x0004u)  /* Comp. B Reference 0 Resistor Select Bit : 2 */
#define CBREF03             (0x0008u)  /* Comp. B Reference 0 Resistor Select Bit : 3 */
#define CBREF04             (0x0010u)  /* Comp. B Reference 0 Resistor Select Bit : 4 */
#define CBRSEL              (0x0020u)  /* Comp. B Reference select */
#define CBRS0               (0x0040u)  /* Comp. B Reference Source Bit : 0 */
#define CBRS1               (0x0080u)  /* Comp. B Reference Source Bit : 1 */
#define CBREF10             (0x0100u)  /* Comp. B Reference 1 Resistor Select Bit : 0 */
#define CBREF11             (0x0200u)  /* Comp. B Reference 1 Resistor Select Bit : 1 */
#define CBREF12             (0x0400u)  /* Comp. B Reference 1 Resistor Select Bit : 2 */
#define CBREF13             (0x0800u)  /* Comp. B Reference 1 Resistor Select Bit : 3 */
#define CBREF14             (0x1000u)  /* Comp. B Reference 1 Resistor Select Bit : 4 */
#define CBREFL0             (0x2000u)  /* Comp. B Reference voltage level Bit : 0 */
#define CBREFL1             (0x4000u)  /* Comp. B Reference voltage level Bit : 1 */
#define CBREFACC            (0x8000u)  /* Comp. B Reference Accuracy */

/* CBCTL2 Control Bits */
#define CBREF00_L           (0x0001u)  /* Comp. B Reference 0 Resistor Select Bit : 0 */
#define CBREF01_L           (0x0002u)  /* Comp. B Reference 0 Resistor Select Bit : 1 */
#define CBREF02_L           (0x0004u)  /* Comp. B Reference 0 Resistor Select Bit : 2 */
#define CBREF03_L           (0x0008u)  /* Comp. B Reference 0 Resistor Select Bit : 3 */
#define CBREF04_L           (0x0010u)  /* Comp. B Reference 0 Resistor Select Bit : 4 */
#define CBRSEL_L            (0x0020u)  /* Comp. B Reference select */
#define CBRS0_L             (0x0040u)  /* Comp. B Reference Source Bit : 0 */
#define CBRS1_L             (0x0080u)  /* Comp. B Reference Source Bit : 1 */

/* CBCTL2 Control Bits */
#define CBREF10_H           (0x0001u)  /* Comp. B Reference 1 Resistor Select Bit : 0 */
#define CBREF11_H           (0x0002u)  /* Comp. B Reference 1 Resistor Select Bit : 1 */
#define CBREF12_H           (0x0004u)  /* Comp. B Reference 1 Resistor Select Bit : 2 */
#define CBREF13_H           (0x0008u)  /* Comp. B Reference 1 Resistor Select Bit : 3 */
#define CBREF14_H           (0x0010u)  /* Comp. B Reference 1 Resistor Select Bit : 4 */
#define CBREFL0_H           (0x0020u)  /* Comp. B Reference voltage level Bit : 0 */
#define CBREFL1_H           (0x0040u)  /* Comp. B Reference voltage level Bit : 1 */
#define CBREFACC_H          (0x0080u)  /* Comp. B Reference Accuracy */

#define CBREF0_0            (0x0000u)  /* Comp. B Int. Ref.0 Select 0 : 1/32 */
#define CBREF0_1            (0x0001u)  /* Comp. B Int. Ref.0 Select 1 : 2/32 */
#define CBREF0_2            (0x0002u)  /* Comp. B Int. Ref.0 Select 2 : 3/32 */
#define CBREF0_3            (0x0003u)  /* Comp. B Int. Ref.0 Select 3 : 4/32 */
#define CBREF0_4            (0x0004u)  /* Comp. B Int. Ref.0 Select 4 : 5/32 */
#define CBREF0_5            (0x0005u)  /* Comp. B Int. Ref.0 Select 5 : 6/32 */
#define CBREF0_6            (0x0006u)  /* Comp. B Int. Ref.0 Select 6 : 7/32 */
#define CBREF0_7            (0x0007u)  /* Comp. B Int. Ref.0 Select 7 : 8/32 */
#define CBREF0_8            (0x0008u)  /* Comp. B Int. Ref.0 Select 0 : 9/32 */
#define CBREF0_9            (0x0009u)  /* Comp. B Int. Ref.0 Select 1 : 10/32 */
#define CBREF0_10           (0x000Au)  /* Comp. B Int. Ref.0 Select 2 : 11/32 */
#define CBREF0_11           (0x000Bu)  /* Comp. B Int. Ref.0 Select 3 : 12/32 */
#define CBREF0_12           (0x000Cu)  /* Comp. B Int. Ref.0 Select 4 : 13/32 */
#define CBREF0_13           (0x000Du)  /* Comp. B Int. Ref.0 Select 5 : 14/32 */
#define CBREF0_14           (0x000Eu)  /* Comp. B Int. Ref.0 Select 6 : 15/32 */
#define CBREF0_15           (0x000Fu)  /* Comp. B Int. Ref.0 Select 7 : 16/32 */
#define CBREF0_16           (0x0010u)  /* Comp. B Int. Ref.0 Select 0 : 17/32 */
#define CBREF0_17           (0x0011u)  /* Comp. B Int. Ref.0 Select 1 : 18/32 */
#define CBREF0_18           (0x0012u)  /* Comp. B Int. Ref.0 Select 2 : 19/32 */
#define CBREF0_19           (0x0013u)  /* Comp. B Int. Ref.0 Select 3 : 20/32 */
#define CBREF0_20           (0x0014u)  /* Comp. B Int. Ref.0 Select 4 : 21/32 */
#define CBREF0_21           (0x0015u)  /* Comp. B Int. Ref.0 Select 5 : 22/32 */
#define CBREF0_22           (0x0016u)  /* Comp. B Int. Ref.0 Select 6 : 23/32 */
#define CBREF0_23           (0x0017u)  /* Comp. B Int. Ref.0 Select 7 : 24/32 */
#define CBREF0_24           (0x0018u)  /* Comp. B Int. Ref.0 Select 0 : 25/32 */
#define CBREF0_25           (0x0019u)  /* Comp. B Int. Ref.0 Select 1 : 26/32 */
#define CBREF0_26           (0x001Au)  /* Comp. B Int. Ref.0 Select 2 : 27/32 */
#define CBREF0_27           (0x001Bu)  /* Comp. B Int. Ref.0 Select 3 : 28/32 */
#define CBREF0_28           (0x001Cu)  /* Comp. B Int. Ref.0 Select 4 : 29/32 */
#define CBREF0_29           (0x001Du)  /* Comp. B Int. Ref.0 Select 5 : 30/32 */
#define CBREF0_30           (0x001Eu)  /* Comp. B Int. Ref.0 Select 6 : 31/32 */
#define CBREF0_31           (0x001Fu)  /* Comp. B Int. Ref.0 Select 7 : 32/32 */

#define CBRS_0              (0x0000u)  /* Comp. B Reference Source 0 : Off */
#define CBRS_1              (0x0040u)  /* Comp. B Reference Source 1 : Vcc */
#define CBRS_2              (0x0080u)  /* Comp. B Reference Source 2 : Shared Ref. */
#define CBRS_3              (0x00C0u)  /* Comp. B Reference Source 3 : Shared Ref. / Off */

#define CBREF1_0            (0x0000u)  /* Comp. B Int. Ref.1 Select 0 : 1/32 */
#define CBREF1_1            (0x0100u)  /* Comp. B Int. Ref.1 Select 1 : 2/32 */
#define CBREF1_2            (0x0200u)  /* Comp. B Int. Ref.1 Select 2 : 3/32 */
#define CBREF1_3            (0x0300u)  /* Comp. B Int. Ref.1 Select 3 : 4/32 */
#define CBREF1_4            (0x0400u)  /* Comp. B Int. Ref.1 Select 4 : 5/32 */
#define CBREF1_5            (0x0500u)  /* Comp. B Int. Ref.1 Select 5 : 6/32 */
#define CBREF1_6            (0x0600u)  /* Comp. B Int. Ref.1 Select 6 : 7/32 */
#define CBREF1_7            (0x0700u)  /* Comp. B Int. Ref.1 Select 7 : 8/32 */
#define CBREF1_8            (0x0800u)  /* Comp. B Int. Ref.1 Select 0 : 9/32 */
#define CBREF1_9            (0x0900u)  /* Comp. B Int. Ref.1 Select 1 : 10/32 */
#define CBREF1_10           (0x0A00u)  /* Comp. B Int. Ref.1 Select 2 : 11/32 */
#define CBREF1_11           (0x0B00u)  /* Comp. B Int. Ref.1 Select 3 : 12/32 */
#define CBREF1_12           (0x0C00u)  /* Comp. B Int. Ref.1 Select 4 : 13/32 */
#define CBREF1_13           (0x0D00u)  /* Comp. B Int. Ref.1 Select 5 : 14/32 */
#define CBREF1_14           (0x0E00u)  /* Comp. B Int. Ref.1 Select 6 : 15/32 */
#define CBREF1_15           (0x0F00u)  /* Comp. B Int. Ref.1 Select 7 : 16/32 */
#define CBREF1_16           (0x1000u)  /* Comp. B Int. Ref.1 Select 0 : 17/32 */
#define CBREF1_17           (0x1100u)  /* Comp. B Int. Ref.1 Select 1 : 18/32 */
#define CBREF1_18           (0x1200u)  /* Comp. B Int. Ref.1 Select 2 : 19/32 */
#define CBREF1_19           (0x1300u)  /* Comp. B Int. Ref.1 Select 3 : 20/32 */
#define CBREF1_20           (0x1400u)  /* Comp. B Int. Ref.1 Select 4 : 21/32 */
#define CBREF1_21           (0x1500u)  /* Comp. B Int. Ref.1 Select 5 : 22/32 */
#define CBREF1_22           (0x1600u)  /* Comp. B Int. Ref.1 Select 6 : 23/32 */
#define CBREF1_23           (0x1700u)  /* Comp. B Int. Ref.1 Select 7 : 24/32 */
#define CBREF1_24           (0x1800u)  /* Comp. B Int. Ref.1 Select 0 : 25/32 */
#define CBREF1_25           (0x1900u)  /* Comp. B Int. Ref.1 Select 1 : 26/32 */
#define CBREF1_26           (0x1A00u)  /* Comp. B Int. Ref.1 Select 2 : 27/32 */
#define CBREF1_27           (0x1B00u)  /* Comp. B Int. Ref.1 Select 3 : 28/32 */
#define CBREF1_28           (0x1C00u)  /* Comp. B Int. Ref.1 Select 4 : 29/32 */
#define CBREF1_29           (0x1D00u)  /* Comp. B Int. Ref.1 Select 5 : 30/32 */
#define CBREF1_30           (0x1E00u)  /* Comp. B Int. Ref.1 Select 6 : 31/32 */
#define CBREF1_31           (0x1F00u)  /* Comp. B Int. Ref.1 Select 7 : 32/32 */

#define CBREFL_0            (0x0000u)  /* Comp. B Reference voltage level 0 : None */
#define CBREFL_1            (0x2000u)  /* Comp. B Reference voltage level 1 : 1.5V */
#define CBREFL_2            (0x4000u)  /* Comp. B Reference voltage level 2 : 2.0V  */
#define CBREFL_3            (0x6000u)  /* Comp. B Reference voltage level 3 : 2.5V  */

#define CBPD0               (0x0001u)  /* Comp. B Disable Input Buffer of Port Register .0 */
#define CBPD1               (0x0002u)  /* Comp. B Disable Input Buffer of Port Register .1 */
#define CBPD2               (0x0004u)  /* Comp. B Disable Input Buffer of Port Register .2 */
#define CBPD3               (0x0008u)  /* Comp. B Disable Input Buffer of Port Register .3 */
#define CBPD4               (0x0010u)  /* Comp. B Disable Input Buffer of Port Register .4 */
#define CBPD5               (0x0020u)  /* Comp. B Disable Input Buffer of Port Register .5 */
#define CBPD6               (0x0040u)  /* Comp. B Disable Input Buffer of Port Register .6 */
#define CBPD7               (0x0080u)  /* Comp. B Disable Input Buffer of Port Register .7 */
#define CBPD8               (0x0100u)  /* Comp. B Disable Input Buffer of Port Register .8 */
#define CBPD9               (0x0200u)  /* Comp. B Disable Input Buffer of Port Register .9 */
#define CBPD10              (0x0400u)  /* Comp. B Disable Input Buffer of Port Register .10 */
#define CBPD11              (0x0800u)  /* Comp. B Disable Input Buffer of Port Register .11 */
#define CBPD12              (0x1000u)  /* Comp. B Disable Input Buffer of Port Register .12 */
#define CBPD13              (0x2000u)  /* Comp. B Disable Input Buffer of Port Register .13 */
#define CBPD14              (0x4000u)  /* Comp. B Disable Input Buffer of Port Register .14 */
#define CBPD15              (0x8000u)  /* Comp. B Disable Input Buffer of Port Register .15 */

#define CBPD0_L             (0x0001u)  /* Comp. B Disable Input Buffer of Port Register .0 */
#define CBPD1_L             (0x0002u)  /* Comp. B Disable Input Buffer of Port Register .1 */
#define CBPD2_L             (0x0004u)  /* Comp. B Disable Input Buffer of Port Register .2 */
#define CBPD3_L             (0x0008u)  /* Comp. B Disable Input Buffer of Port Register .3 */
#define CBPD4_L             (0x0010u)  /* Comp. B Disable Input Buffer of Port Register .4 */
#define CBPD5_L             (0x0020u)  /* Comp. B Disable Input Buffer of Port Register .5 */
#define CBPD6_L             (0x0040u)  /* Comp. B Disable Input Buffer of Port Register .6 */
#define CBPD7_L             (0x0080u)  /* Comp. B Disable Input Buffer of Port Register .7 */

#define CBPD8_H             (0x0001u)  /* Comp. B Disable Input Buffer of Port Register .8 */
#define CBPD9_H             (0x0002u)  /* Comp. B Disable Input Buffer of Port Register .9 */
#define CBPD10_H            (0x0004u)  /* Comp. B Disable Input Buffer of Port Register .10 */
#define CBPD11_H            (0x0008u)  /* Comp. B Disable Input Buffer of Port Register .11 */
#define CBPD12_H            (0x0010u)  /* Comp. B Disable Input Buffer of Port Register .12 */
#define CBPD13_H            (0x0020u)  /* Comp. B Disable Input Buffer of Port Register .13 */
#define CBPD14_H            (0x0040u)  /* Comp. B Disable Input Buffer of Port Register .14 */
#define CBPD15_H            (0x0080u)  /* Comp. B Disable Input Buffer of Port Register .15 */

/* CBINT Control Bits */
#define CBIFG                (0x0001u)  /* Comp. B Interrupt Flag */
#define CBIIFG               (0x0002u)  /* Comp. B Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004u)  /* Comp. B */
//#define RESERVED             (0x0008u)  /* Comp. B */
//#define RESERVED             (0x0010u)  /* Comp. B */
//#define RESERVED             (0x0020u)  /* Comp. B */
//#define RESERVED             (0x0040u)  /* Comp. B */
//#define RESERVED             (0x0080u)  /* Comp. B */
#define CBIE                 (0x0100u)  /* Comp. B Interrupt Enable */
#define CBIIE                (0x0200u)  /* Comp. B Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400u)  /* Comp. B */
//#define RESERVED             (0x0800u)  /* Comp. B */
//#define RESERVED             (0x1000u)  /* Comp. B */
//#define RESERVED             (0x2000u)  /* Comp. B */
//#define RESERVED             (0x4000u)  /* Comp. B */
//#define RESERVED             (0x8000u)  /* Comp. B */

/* CBINT Control Bits */
#define CBIFG_L             (0x0001u)  /* Comp. B Interrupt Flag */
#define CBIIFG_L            (0x0002u)  /* Comp. B Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004u)  /* Comp. B */
//#define RESERVED             (0x0008u)  /* Comp. B */
//#define RESERVED             (0x0010u)  /* Comp. B */
//#define RESERVED             (0x0020u)  /* Comp. B */
//#define RESERVED             (0x0040u)  /* Comp. B */
//#define RESERVED             (0x0080u)  /* Comp. B */
//#define RESERVED             (0x0400u)  /* Comp. B */
//#define RESERVED             (0x0800u)  /* Comp. B */
//#define RESERVED             (0x1000u)  /* Comp. B */
//#define RESERVED             (0x2000u)  /* Comp. B */
//#define RESERVED             (0x4000u)  /* Comp. B */
//#define RESERVED             (0x8000u)  /* Comp. B */

/* CBINT Control Bits */
//#define RESERVED             (0x0004u)  /* Comp. B */
//#define RESERVED             (0x0008u)  /* Comp. B */
//#define RESERVED             (0x0010u)  /* Comp. B */
//#define RESERVED             (0x0020u)  /* Comp. B */
//#define RESERVED             (0x0040u)  /* Comp. B */
//#define RESERVED             (0x0080u)  /* Comp. B */
#define CBIE_H              (0x0001u)  /* Comp. B Interrupt Enable */
#define CBIIE_H             (0x0002u)  /* Comp. B Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400u)  /* Comp. B */
//#define RESERVED             (0x0800u)  /* Comp. B */
//#define RESERVED             (0x1000u)  /* Comp. B */
//#define RESERVED             (0x2000u)  /* Comp. B */
//#define RESERVED             (0x4000u)  /* Comp. B */
//#define RESERVED             (0x8000u)  /* Comp. B */

/* CBIV Definitions */
#define CBIV_NONE           (0x0000u)    /* No Interrupt pending */
#define CBIV_CBIFG          (0x0002u)    /* CBIFG */
#define CBIV_CBIIFG         (0x0004u)    /* CBIIFG */

/************************************************************
* CC1101 Radio Interface
************************************************************/
#define __MSP430_HAS_CC1101__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CC1101__ 0x0F00

#define  RF1AIFCTL0_         (0x0F00u)  /* Radio interface control register 0 */
DEFCW(   RF1AIFCTL0        , RF1AIFCTL0_)
#define  RF1AIFCTL1_         (0x0F02u)  /* Radio interface control register 1 */
DEFCW(   RF1AIFCTL1        , RF1AIFCTL1_)
#define  RF1AIFIFG           RF1AIFCTL1_L  /* Radio interface interrupt flag register */
#define  RF1AIFIE            RF1AIFCTL1_H  /* Radio interface interrupt enable register */
#define  RF1AIFCTL2_         (0x0F04u)  /* (Radio interface control register 2) */
DEFCW(   RF1AIFCTL2        , RF1AIFCTL2_)
#define  RF1AIFERR_          (0x0F06u)  /* Radio interface error flag register */
DEFCW(   RF1AIFERR         , RF1AIFERR_)
#define  RF1AIFERRV_         (0x0F0Cu)  /* Radio interface error vector word register */
DEFCW(   RF1AIFERRV        , RF1AIFERRV_)
#define  RF1AIFIV_           (0x0F0Eu)  /* Radio interface interrupt vector word register */
DEFCW(   RF1AIFIV          , RF1AIFIV_)
#define  RF1AINSTRW_         (0x0F10u)  /* Radio instruction word register */
DEFCW(   RF1AINSTRW        , RF1AINSTRW_)
#define  RF1ADINB            RF1AINSTRW_L  /* Radio instruction byte register */
#define  RF1AINSTRB          RF1AINSTRW_H  /* Radio byte data in register */
#define  RF1AINSTR1W_        (0x0F12u)  /* Radio instruction 1-byte register with autoread */
DEFCW(   RF1AINSTR1W       , RF1AINSTR1W_)
#define  RF1AINSTR1B         RF1AINSTR1W_H /* Radio instruction 1-byte register with autoread */
#define  RF1AINSTR2W_        (0x0F14u)  /* Radio instruction 2-byte register with autoread */
DEFCW(   RF1AINSTR2W       , RF1AINSTR2W_)
#define  RF1AINSTR2B         RF1AINSTR1W_H /* Radio instruction 2-byte register with autoread */
#define  RF1ADINW_           (0x0F16u)  /* Radio word data in register */
DEFCW(   RF1ADINW          , RF1ADINW_)

#define  RF1ASTAT0W_         (0x0F20u)  /* Radio status word register without auto-read */
DEFCW(   RF1ASTAT0W        , RF1ASTAT0W_)
#define  RF1ADOUT0B          RF1ASTAT0W_L /* Radio byte data out register without auto-read */
#define  RF1ASTAT0B          RF1ASTAT0W_H /* Radio status byte register without auto-read */
#define  RF1ASTATW           RF1ASTAT0W   /* Radio status word register without auto-read */
#define  RF1ADOUTB           RF1ASTAT0W_L /* Radio byte data out register without auto-read */
#define  RF1ASTATB           RF1ASTAT0W_H /* Radio status byte register without auto-read */
#define  RF1ASTAT1W_         (0x0F22u)  /* Radio status word register with 1-byte auto-read */
DEFCW(   RF1ASTAT1W        , RF1ASTAT1W_)
#define  RF1ADOUT1B          RF1ASTAT1W_L /* Radio byte data out register with 1-byte auto-read */
#define  RF1ASTAT1B          RF1ASTAT1W_H /* Radio status byte register with 1-byte auto-read */
#define  RF1ASTAT2W_         (0x0F24u)  /* Radio status word register with 2-byte auto-read */
DEFCW(   RF1ASTAT2W        , RF1ASTAT2W_)
#define  RF1ADOUT2B          RF1ASTAT2W_L /* Radio byte data out register with 2-byte auto-read */
#define  RF1ASTAT2B          RF1ASTAT2W_H /* Radio status byte register with 2-byte auto-read */
#define  RF1ADOUT0W_         (0x0F28u)  /* Radio core word data out register without auto-read */
DEFCW(   RF1ADOUT0W        , RF1ADOUT0W_)
#define  RF1ADOUTW           RF1ADOUT0W   /* Radio core word data out register without auto-read */
#define  RF1ADOUTW_L         RF1ADOUT0W_L /* Radio core word data out register without auto-read */
#define  RF1ADOUTW_H         RF1ADOUT0W_H /* Radio core word data out register without auto-read */
#define  RF1ADOUT1W_         (0x0F2Au)  /* Radio core word data out register with 1-byte auto-read */
DEFCW(   RF1ADOUT1W        , RF1ADOUT1W_)
#define  RF1ADOUT2W_         (0x0F2Cu)  /* Radio core word data out register with 2-byte auto-read */
DEFCW(   RF1ADOUT2W        , RF1ADOUT2W_)
#define  RF1AIN_             (0x0F30u)  /* Radio core signal input register */
DEFCW(   RF1AIN            , RF1AIN_)
#define  RF1AIFG_            (0x0F32u)  /* Radio core interrupt flag register */
DEFCW(   RF1AIFG           , RF1AIFG_)
#define  RF1AIES_            (0x0F34u)  /* Radio core interrupt edge select register */
DEFCW(   RF1AIES           , RF1AIES_)
#define  RF1AIE_             (0x0F36u)  /* Radio core interrupt enable register */
DEFCW(   RF1AIE            , RF1AIE_)
#define  RF1AIV_             (0x0F38u)  /* Radio core interrupt vector word register */
DEFCW(   RF1AIV            , RF1AIV_)
#define  RF1ARXFIFO_         (0x0F3Cu)  /* Direct receive FIFO access register */
DEFCW(   RF1ARXFIFO        , RF1ARXFIFO_)
#define  RF1ATXFIFO_         (0x0F3Eu)  /* Direct transmit FIFO access register */
DEFCW(   RF1ATXFIFO        , RF1ATXFIFO_)

/* RF1AIFCTL0 Control Bits */
#define RFFIFOEN            (0x0001u)  /* CC1101 Direct FIFO access enable */
#define RFENDIAN            (0x0002u)  /* CC1101 Disable endianness conversion */

/* RF1AIFCTL0 Control Bits */
#define RFFIFOEN_L          (0x0001u)  /* CC1101 Direct FIFO access enable */
#define RFENDIAN_L          (0x0002u)  /* CC1101 Disable endianness conversion */

/* RF1AIFCTL0 Control Bits */

/* RF1AIFCTL1 Control Bits */
#define RFRXIFG             (0x0001u)  /* Radio interface direct FIFO access receive interrupt flag */
#define RFTXIFG             (0x0002u)  /* Radio interface direct FIFO access transmit interrupt flag */
#define RFERRIFG            (0x0004u)  /* Radio interface error interrupt flag */
#define RFINSTRIFG          (0x0010u)  /* Radio interface instruction interrupt flag */
#define RFDINIFG            (0x0020u)  /* Radio interface data in interrupt flag */
#define RFSTATIFG           (0x0040u)  /* Radio interface status interrupt flag */
#define RFDOUTIFG           (0x0080u)  /* Radio interface data out interrupt flag */
#define RFRXIE              (0x0100u)  /* Radio interface direct FIFO access receive interrupt enable */
#define RFTXIE              (0x0200u)  /* Radio interface direct FIFO access transmit interrupt enable */
#define RFERRIE             (0x0400u)  /* Radio interface error interrupt enable */
#define RFINSTRIE           (0x1000u)  /* Radio interface instruction interrupt enable */
#define RFDINIE             (0x2000u)  /* Radio interface data in interrupt enable */
#define RFSTATIE            (0x4000u)  /* Radio interface status interrupt enable */
#define RFDOUTIE            (0x8000u)  /* Radio interface data out interrupt enable */

/* RF1AIFCTL1 Control Bits */
#define RFRXIFG_L           (0x0001u)  /* Radio interface direct FIFO access receive interrupt flag */
#define RFTXIFG_L           (0x0002u)  /* Radio interface direct FIFO access transmit interrupt flag */
#define RFERRIFG_L          (0x0004u)  /* Radio interface error interrupt flag */
#define RFINSTRIFG_L        (0x0010u)  /* Radio interface instruction interrupt flag */
#define RFDINIFG_L          (0x0020u)  /* Radio interface data in interrupt flag */
#define RFSTATIFG_L         (0x0040u)  /* Radio interface status interrupt flag */
#define RFDOUTIFG_L         (0x0080u)  /* Radio interface data out interrupt flag */

/* RF1AIFCTL1 Control Bits */
#define RFRXIE_H            (0x0001u)  /* Radio interface direct FIFO access receive interrupt enable */
#define RFTXIE_H            (0x0002u)  /* Radio interface direct FIFO access transmit interrupt enable */
#define RFERRIE_H           (0x0004u)  /* Radio interface error interrupt enable */
#define RFINSTRIE_H         (0x0010u)  /* Radio interface instruction interrupt enable */
#define RFDINIE_H           (0x0020u)  /* Radio interface data in interrupt enable */
#define RFSTATIE_H          (0x0040u)  /* Radio interface status interrupt enable */
#define RFDOUTIE_H          (0x0080u)  /* Radio interface data out interrupt enable */

/* RF1AIFERR Control Bits */
#define LVERR               (0x0001u)  /* Low Core Voltage Error Flag */
#define OPERR               (0x0002u)  /* Operand Error Flag */
#define OUTERR              (0x0004u)  /* Output data not available Error Flag */
#define OPOVERR             (0x0008u)  /* Operand Overwrite Error Flag */

/* RF1AIFERR Control Bits */
#define LVERR_L             (0x0001u)  /* Low Core Voltage Error Flag */
#define OPERR_L             (0x0002u)  /* Operand Error Flag */
#define OUTERR_L            (0x0004u)  /* Output data not available Error Flag */
#define OPOVERR_L           (0x0008u)  /* Operand Overwrite Error Flag */

/* RF1AIFERR Control Bits */

/* RF1AIFERRV Definitions */
#define RF1AIFERRV_NONE     (0x0000u)  /* No Error pending */
#define RF1AIFERRV_LVERR    (0x0002u)  /* Low core voltage error */
#define RF1AIFERRV_OPERR    (0x0004u)  /* Operand Error */
#define RF1AIFERRV_OUTERR   (0x0006u)  /* Output data not available Error */
#define RF1AIFERRV_OPOVERR  (0x0008u)  /* Operand Overwrite Error */

/* RF1AIFIV Definitions */
#define RF1AIFIV_NONE       (0x0000u)  /* No Interrupt pending */
#define RF1AIFIV_RFERRIFG   (0x0002u)  /* Radio interface error */
#define RF1AIFIV_RFDOUTIFG  (0x0004u)  /* Radio i/f data out */
#define RF1AIFIV_RFSTATIFG  (0x0006u)  /* Radio i/f status out */
#define RF1AIFIV_RFDINIFG   (0x0008u)  /* Radio i/f data in */
#define RF1AIFIV_RFINSTRIFG (0x000Au)  /* Radio i/f instruction in */
#define RF1AIFIV_RFRXIFG    (0x000Cu)  /* Radio direct FIFO RX */
#define RF1AIFIV_RFTXIFG    (0x000Eu)  /* Radio direct FIFO TX */

/* RF1AIV Definitions */
#define RF1AIV_NONE         (0x0000u)  /* No Interrupt pending */
#define RF1AIV_RFIFG0       (0x0002u)  /* RFIFG0 */
#define RF1AIV_RFIFG1       (0x0004u)  /* RFIFG1 */
#define RF1AIV_RFIFG2       (0x0006u)  /* RFIFG2 */
#define RF1AIV_RFIFG3       (0x0008u)  /* RFIFG3 */
#define RF1AIV_RFIFG4       (0x000Au)  /* RFIFG4 */
#define RF1AIV_RFIFG5       (0x000Cu)  /* RFIFG5 */
#define RF1AIV_RFIFG6       (0x000Eu)  /* RFIFG6 */
#define RF1AIV_RFIFG7       (0x0010u)  /* RFIFG7 */
#define RF1AIV_RFIFG8       (0x0012u)  /* RFIFG8 */
#define RF1AIV_RFIFG9       (0x0014u)  /* RFIFG9 */
#define RF1AIV_RFIFG10      (0x0016u)  /* RFIFG10 */
#define RF1AIV_RFIFG11      (0x0018u)  /* RFIFG11 */
#define RF1AIV_RFIFG12      (0x001Au)  /* RFIFG12 */
#define RF1AIV_RFIFG13      (0x001Cu)  /* RFIFG13 */
#define RF1AIV_RFIFG14      (0x001Eu)  /* RFIFG14 */
#define RF1AIV_RFIFG15      (0x0020u)  /* RFIFG15 */

// Radio Core Registers
#define IOCFG2              0x00      /*  IOCFG2   - GDO2 output pin configuration  */
#define IOCFG1              0x01      /*  IOCFG1   - GDO1 output pin configuration  */
#define IOCFG0              0x02      /*  IOCFG1   - GDO0 output pin configuration  */
#define FIFOTHR             0x03      /*  FIFOTHR  - RX FIFO and TX FIFO thresholds */
#define SYNC1               0x04      /*  SYNC1    - Sync word, high byte */
#define SYNC0               0x05      /*  SYNC0    - Sync word, low byte */
#define PKTLEN              0x06      /*  PKTLEN   - Packet length */
#define PKTCTRL1            0x07      /*  PKTCTRL1 - Packet automation control */
#define PKTCTRL0            0x08      /*  PKTCTRL0 - Packet automation control */
#define ADDR                0x09      /*  ADDR     - Device address */
#define CHANNR              0x0A      /*  CHANNR   - Channel number */
#define FSCTRL1             0x0B      /*  FSCTRL1  - Frequency synthesizer control */
#define FSCTRL0             0x0C      /*  FSCTRL0  - Frequency synthesizer control */
#define FREQ2               0x0D      /*  FREQ2    - Frequency control word, high byte */
#define FREQ1               0x0E      /*  FREQ1    - Frequency control word, middle byte */
#define FREQ0               0x0F      /*  FREQ0    - Frequency control word, low byte */
#define MDMCFG4             0x10      /*  MDMCFG4  - Modem configuration */
#define MDMCFG3             0x11      /*  MDMCFG3  - Modem configuration */
#define MDMCFG2             0x12      /*  MDMCFG2  - Modem configuration */
#define MDMCFG1             0x13      /*  MDMCFG1  - Modem configuration */
#define MDMCFG0             0x14      /*  MDMCFG0  - Modem configuration */
#define DEVIATN             0x15      /*  DEVIATN  - Modem deviation setting */
#define MCSM2               0x16      /*  MCSM2    - Main Radio Control State Machine configuration */
#define MCSM1               0x17      /*  MCSM1    - Main Radio Control State Machine configuration */
#define MCSM0               0x18      /*  MCSM0    - Main Radio Control State Machine configuration */
#define FOCCFG              0x19      /*  FOCCFG   - Frequency Offset Compensation configuration */
#define BSCFG               0x1A      /*  BSCFG    - Bit Synchronization configuration */
#define AGCCTRL2            0x1B      /*  AGCCTRL2 - AGC control */
#define AGCCTRL1            0x1C      /*  AGCCTRL1 - AGC control */
#define AGCCTRL0            0x1D      /*  AGCCTRL0 - AGC control */
#define WOREVT1             0x1E      /*  WOREVT1  - High byte Event0 timeout */
#define WOREVT0             0x1F      /*  WOREVT0  - Low byte Event0 timeout */
#define WORCTRL             0x20      /*  WORCTRL  - Wake On Radio control */
#define FREND1              0x21      /*  FREND1   - Front end RX configuration */
#define FREND0              0x22      /*  FREDN0   - Front end TX configuration */
#define FSCAL3              0x23      /*  FSCAL3   - Frequency synthesizer calibration */
#define FSCAL2              0x24      /*  FSCAL2   - Frequency synthesizer calibration */
#define FSCAL1              0x25      /*  FSCAL1   - Frequency synthesizer calibration */
#define FSCAL0              0x26      /*  FSCAL0   - Frequency synthesizer calibration */
//#define RCCTRL1             0x27      /*  RCCTRL1  - RC oscillator configuration */
//#define RCCTRL0             0x28      /*  RCCTRL0  - RC oscillator configuration */
#define FSTEST              0x29      /*  FSTEST   - Frequency synthesizer calibration control */
#define PTEST               0x2A      /*  PTEST    - Production test */
#define AGCTEST             0x2B      /*  AGCTEST  - AGC test */
#define TEST2               0x2C      /*  TEST2    - Various test settings */
#define TEST1               0x2D      /*  TEST1    - Various test settings */
#define TEST0               0x2E      /*  TEST0    - Various test settings */

/* status registers */
#define PARTNUM             0x30      /*  PARTNUM    - Chip ID */
#define VERSION             0x31      /*  VERSION    - Chip ID */
#define FREQEST             0x32      /*  FREQEST    � Frequency Offset Estimate from demodulator */
#define LQI                 0x33      /*  LQI        � Demodulator estimate for Link Quality */
#define RSSI                0x34      /*  RSSI       � Received signal strength indication */
#define MARCSTATE           0x35      /*  MARCSTATE  � Main Radio Control State Machine state */
#define WORTIME1            0x36      /*  WORTIME1   � High byte of WOR time */
#define WORTIME0            0x37      /*  WORTIME0   � Low byte of WOR time */
#define PKTSTATUS           0x38      /*  PKTSTATUS  � Current GDOx status and packet status */
#define VCO_VC_DAC          0x39      /*  VCO_VC_DAC � Current setting from PLL calibration module */
#define TXBYTES             0x3A      /*  TXBYTES    � Underflow and number of bytes */
#define RXBYTES             0x3B      /*  RXBYTES    � Overflow and number of bytes */

/* burst write registers */
#define PATABLE             0x3E      /*  PATABLE - PA control settings table */
#define TXFIFO              0x3F      /*  TXFIFO  - Transmit FIFO */
#define RXFIFO              0x3F      /*  RXFIFO  - Receive FIFO */

/* Radio Core Instructions */
/* command strobes               */
#define RF_SRES             0x30      /*  SRES    - Reset chip. */
#define RF_SFSTXON          0x31      /*  SFSTXON - Enable and calibrate frequency synthesizer. */
#define RF_SXOFF            0x32      /*  SXOFF   - Turn off crystal oscillator. */
#define RF_SCAL             0x33      /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
#define RF_SRX              0x34      /*  SRX     - Enable RX. Perform calibration if enabled. */
#define RF_STX              0x35      /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
#define RF_SIDLE            0x36      /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
//#define RF_SRSVD            0x37      /*  SRVSD   - Reserved.  Do not use. */
#define RF_SWOR             0x38      /*  SWOR    - Start automatic RX polling sequence (Wake-on-Radio) */
#define RF_SPWD             0x39      /*  SPWD    - Enter power down mode when CSn goes high. */
#define RF_SFRX             0x3A      /*  SFRX    - Flush the RX FIFO buffer. */
#define RF_SFTX             0x3B      /*  SFTX    - Flush the TX FIFO buffer. */
#define RF_SWORRST          0x3C      /*  SWORRST - Reset real time clock. */
#define RF_SNOP             0x3D      /*  SNOP    - No operation. Returns status byte. */

#define RF_RXSTAT           0x80      /* Used in combination with strobe commands delivers number of availabe bytes in RX FIFO with return status */
#define RF_TXSTAT           0x00      /* Used in combination with strobe commands delivers number of availabe bytes in TX FIFO with return status */

/* other radio instr */
#define RF_SNGLREGRD        0x80
#define RF_SNGLREGWR        0x00
#define RF_REGRD            0xC0
#define RF_REGWR            0x40
#define RF_STATREGRD        0xC0      /* Read single radio core status register */
#define RF_SNGLPATABRD      (RF_SNGLREGRD+PATABLE)
#define RF_SNGLPATABWR      (RF_SNGLREGWR+PATABLE)
#define RF_PATABRD          (RF_REGRD+PATABLE)
#define RF_PATABWR          (RF_REGWR+PATABLE)
#define RF_SNGLRXRD         (RF_SNGLREGRD+RXFIFO)
#define RF_SNGLTXWR         (RF_SNGLREGWR+TXFIFO)
#define RF_RXFIFORD         (RF_REGRD+RXFIFO)
#define RF_TXFIFOWR         (RF_REGWR+TXFIFO)

/*************************************************************
* CRC Module
*************************************************************/
#define __MSP430_HAS_CRC__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x0150

#define  CRCDI_              (0x0150u)  /* CRC Data In Register */
DEFCW(   CRCDI             , CRCDI_)
#define  CRCDIRB_            (0x0152u)  /* CRC data in reverse byte Register */
DEFCW(   CRCDIRB           , CRCDIRB_)
#define  CRCINIRES_          (0x0154u)  /* CRC Initialisation Register and Result Register */
DEFCW(   CRCINIRES         , CRCINIRES_)
#define  CRCRESR_            (0x0156u)  /* CRC reverse result Register */
DEFCW(   CRCRESR           , CRCRESR_)

/************************************************************
* DMA_X
************************************************************/
#define __MSP430_HAS_DMAX_3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_DMAX_3__ 0x0500

#define  DMACTL0_            (0x0500u)    /* DMA Module Control 0 */
DEFCW(   DMACTL0           , DMACTL0_)
#define  DMACTL1_            (0x0502u)    /* DMA Module Control 1 */
DEFCW(   DMACTL1           , DMACTL1_)
#define  DMACTL2_            (0x0504u)    /* DMA Module Control 2 */
DEFCW(   DMACTL2           , DMACTL2_)
#define  DMACTL3_            (0x0506u)    /* DMA Module Control 3 */
DEFCW(   DMACTL3           , DMACTL3_)
#define  DMACTL4_            (0x0508u)    /* DMA Module Control 4 */
DEFCW(   DMACTL4           , DMACTL4_)
#define  DMAIV_              (0x050Eu)    /* DMA Interrupt Vector Word */
DEFCW(   DMAIV             , DMAIV_)

#define  DMA0CTL_            (0x0510u)    /* DMA Channel 0 Control */
DEFCW(   DMA0CTL           , DMA0CTL_)
#define  DMA0SA_             (0x0512u)    /* DMA Channel 0 Source Address */
DEFA(    DMA0SA            , DMA0SA_)
#define  DMA0DA_             (0x0516u)    /* DMA Channel 0 Destination Address */
DEFA(    DMA0DA            , DMA0DA_)
#define  DMA0SZ_             (0x051Au)    /* DMA Channel 0 Transfer Size */
DEFW(    DMA0SZ            , DMA0SZ_)

#define  DMA1CTL_            (0x0520u)    /* DMA Channel 1 Control */
DEFCW(   DMA1CTL           , DMA1CTL_)
#define  DMA1SA_             (0x0522u)    /* DMA Channel 1 Source Address */
DEFA(    DMA1SA            , DMA1SA_)
#define  DMA1DA_             (0x0526u)    /* DMA Channel 1 Destination Address */
DEFA(    DMA1DA            , DMA1DA_)
#define  DMA1SZ_             (0x052Au)    /* DMA Channel 1 Transfer Size */
DEFW(    DMA1SZ            , DMA1SZ_)

#define  DMA2CTL_            (0x0530u)    /* DMA Channel 2 Control */
DEFCW(   DMA2CTL           , DMA2CTL_)
#define  DMA2SA_             (0x0532u)    /* DMA Channel 2 Source Address */
DEFA(    DMA2SA            , DMA2SA_)
#define  DMA2DA_             (0x0536u)    /* DMA Channel 2 Destination Address */
DEFA(    DMA2DA            , DMA2DA_)
#define  DMA2SZ_             (0x053Au)    /* DMA Channel 2 Transfer Size */
DEFW(    DMA2SZ            , DMA2SZ_)

/* DMACTL0 Control Bits */
#define DMA0TSEL0           (0x0001u)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1           (0x0002u)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2           (0x0004u)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3           (0x0008u)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4           (0x0010u)    /* DMA channel 0 transfer select bit 4 */
#define DMA1TSEL0           (0x0100u)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1           (0x0200u)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2           (0x0400u)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3           (0x0800u)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4           (0x1000u)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA0TSEL0_L         (0x0001u)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L         (0x0002u)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L         (0x0004u)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L         (0x0008u)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L         (0x0010u)    /* DMA channel 0 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA1TSEL0_H         (0x0001u)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H         (0x0002u)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H         (0x0004u)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H         (0x0008u)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H         (0x0010u)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0           (0x0001u)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1           (0x0002u)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2           (0x0004u)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3           (0x0008u)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4           (0x0010u)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0_L         (0x0001u)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L         (0x0002u)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L         (0x0004u)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L         (0x0008u)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L         (0x0010u)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */

/* DMACTL4 Control Bits */
#define ENNMI               (0x0001u)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN          (0x0002u)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS           (0x0004u)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */
#define ENNMI_L             (0x0001u)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN_L        (0x0002u)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS_L         (0x0004u)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */

/* DMAxCTL Control Bits */
#define DMAREQ              (0x0001u)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT            (0x0002u)    /* DMA transfer aborted by NMI */
#define DMAIE               (0x0004u)    /* DMA interrupt enable */
#define DMAIFG              (0x0008u)    /* DMA interrupt flag */
#define DMAEN               (0x0010u)    /* DMA enable */
#define DMALEVEL            (0x0020u)    /* DMA level sensitive trigger select */
#define DMASRCBYTE          (0x0040u)    /* DMA source byte */
#define DMADSTBYTE          (0x0080u)    /* DMA destination byte */
#define DMASRCINCR0         (0x0100u)    /* DMA source increment bit 0 */
#define DMASRCINCR1         (0x0200u)    /* DMA source increment bit 1 */
#define DMADSTINCR0         (0x0400u)    /* DMA destination increment bit 0 */
#define DMADSTINCR1         (0x0800u)    /* DMA destination increment bit 1 */
#define DMADT0              (0x1000u)    /* DMA transfer mode bit 0 */
#define DMADT1              (0x2000u)    /* DMA transfer mode bit 1 */
#define DMADT2              (0x4000u)    /* DMA transfer mode bit 2 */

/* DMAxCTL Control Bits */
#define DMAREQ_L            (0x0001u)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT_L          (0x0002u)    /* DMA transfer aborted by NMI */
#define DMAIE_L             (0x0004u)    /* DMA interrupt enable */
#define DMAIFG_L            (0x0008u)    /* DMA interrupt flag */
#define DMAEN_L             (0x0010u)    /* DMA enable */
#define DMALEVEL_L          (0x0020u)    /* DMA level sensitive trigger select */
#define DMASRCBYTE_L        (0x0040u)    /* DMA source byte */
#define DMADSTBYTE_L        (0x0080u)    /* DMA destination byte */

/* DMAxCTL Control Bits */
#define DMASRCINCR0_H       (0x0001u)    /* DMA source increment bit 0 */
#define DMASRCINCR1_H       (0x0002u)    /* DMA source increment bit 1 */
#define DMADSTINCR0_H       (0x0004u)    /* DMA destination increment bit 0 */
#define DMADSTINCR1_H       (0x0008u)    /* DMA destination increment bit 1 */
#define DMADT0_H            (0x0010u)    /* DMA transfer mode bit 0 */
#define DMADT1_H            (0x0020u)    /* DMA transfer mode bit 1 */
#define DMADT2_H            (0x0040u)    /* DMA transfer mode bit 2 */

#define DMASWDW             (0*0x0040u)  /* DMA transfer: source word to destination word */
#define DMASBDW             (1*0x0040u)  /* DMA transfer: source byte to destination word */
#define DMASWDB             (2*0x0040u)  /* DMA transfer: source word to destination byte */
#define DMASBDB             (3*0x0040u)  /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0        (0*0x0100u)  /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1        (1*0x0100u)  /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2        (2*0x0100u)  /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3        (3*0x0100u)  /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0        (0*0x0400u)  /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1        (1*0x0400u)  /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2        (2*0x0400u)  /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3        (3*0x0400u)  /* DMA destination increment 3: destination address incremented */

#define DMADT_0             (0*0x1000u)  /* DMA transfer mode 0: Single transfer */
#define DMADT_1             (1*0x1000u)  /* DMA transfer mode 1: Block transfer */
#define DMADT_2             (2*0x1000u)  /* DMA transfer mode 2: Burst-Block transfer */
#define DMADT_3             (3*0x1000u)  /* DMA transfer mode 3: Burst-Block transfer */
#define DMADT_4             (4*0x1000u)  /* DMA transfer mode 4: Repeated Single transfer */
#define DMADT_5             (5*0x1000u)  /* DMA transfer mode 5: Repeated Block transfer */
#define DMADT_6             (6*0x1000u)  /* DMA transfer mode 6: Repeated Burst-Block transfer */
#define DMADT_7             (7*0x1000u)  /* DMA transfer mode 7: Repeated Burst-Block transfer */

/* DMAIV Definitions */
#define DMAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define DMAIV_DMA0IFG        (0x0002u)    /* DMA0IFG*/
#define DMAIV_DMA1IFG        (0x0004u)    /* DMA1IFG*/
#define DMAIV_DMA2IFG        (0x0006u)    /* DMA2IFG*/

#define DMA0TSEL_0          (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL_1          (1*0x0001u)  /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL_2          (2*0x0001u)  /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL_3          (3*0x0001u)  /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL_4          (4*0x0001u)  /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL_5          (5*0x0001u)  /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL_6          (6*0x0001u)  /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL_7          (7*0x0001u)  /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL_8          (8*0x0001u)  /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL_9          (9*0x0001u)  /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL_10         (10*0x0001u) /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL_11         (11*0x0001u) /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL_12         (12*0x0001u) /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL_13         (13*0x0001u) /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL_14         (14*0x0001u) /* DMA channel 0 transfer select 14: RFRXIFG */
#define DMA0TSEL_15         (15*0x0001u) /* DMA channel 0 transfer select 15: RFTXIFG */
#define DMA0TSEL_16         (16*0x0001u) /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL_17         (17*0x0001u) /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL_18         (18*0x0001u) /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL_19         (19*0x0001u) /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL_20         (20*0x0001u) /* DMA channel 0 transfer select 20: Reserved  */
#define DMA0TSEL_21         (21*0x0001u) /* DMA channel 0 transfer select 21: Reserved  */
#define DMA0TSEL_22         (22*0x0001u) /* DMA channel 0 transfer select 22: Reserved  */
#define DMA0TSEL_23         (23*0x0001u) /* DMA channel 0 transfer select 23: Reserved  */
#define DMA0TSEL_24         (24*0x0001u) /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL_25         (25*0x0001u) /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL_26         (26*0x0001u) /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL_27         (27*0x0001u) /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL_28         (28*0x0001u) /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL_29         (29*0x0001u) /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL_30         (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL_31         (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL_0          (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL_1          (1*0x0100u)  /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL_2          (2*0x0100u)  /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL_3          (3*0x0100u)  /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL_4          (4*0x0100u)  /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL_5          (5*0x0100u)  /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL_6          (6*0x0100u)  /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL_7          (7*0x0100u)  /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL_8          (8*0x0100u)  /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL_9          (9*0x0100u)  /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL_10         (10*0x0100u) /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL_11         (11*0x0100u) /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL_12         (12*0x0100u) /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL_13         (13*0x0100u) /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL_14         (14*0x0100u) /* DMA channel 1 transfer select 14: RFRXIFG */
#define DMA1TSEL_15         (15*0x0100u) /* DMA channel 1 transfer select 15: RFTXIFG */
#define DMA1TSEL_16         (16*0x0100u) /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL_17         (17*0x0100u) /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL_18         (18*0x0100u) /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL_19         (19*0x0100u) /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL_20         (20*0x0100u) /* DMA channel 1 transfer select 20: Reserved  */
#define DMA1TSEL_21         (21*0x0100u) /* DMA channel 1 transfer select 21: Reserved  */
#define DMA1TSEL_22         (22*0x0100u) /* DMA channel 1 transfer select 22: Reserved  */
#define DMA1TSEL_23         (23*0x0100u) /* DMA channel 1 transfer select 23: Reserved  */
#define DMA1TSEL_24         (24*0x0100u) /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL_25         (25*0x0100u) /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL_26         (26*0x0100u) /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL_27         (27*0x0100u) /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL_28         (28*0x0100u) /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL_29         (29*0x0100u) /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL_30         (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL_31         (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL_0          (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL_1          (1*0x0001u)  /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL_2          (2*0x0001u)  /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL_3          (3*0x0001u)  /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL_4          (4*0x0001u)  /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL_5          (5*0x0001u)  /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL_6          (6*0x0001u)  /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL_7          (7*0x0001u)  /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL_8          (8*0x0001u)  /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL_9          (9*0x0001u)  /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL_10         (10*0x0001u) /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL_11         (11*0x0001u) /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL_12         (12*0x0001u) /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL_13         (13*0x0001u) /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL_14         (14*0x0001u) /* DMA channel 2 transfer select 14: RFRXIFG */
#define DMA2TSEL_15         (15*0x0001u) /* DMA channel 2 transfer select 15: RFTXIFG */
#define DMA2TSEL_16         (16*0x0001u) /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL_17         (17*0x0001u) /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL_18         (18*0x0001u) /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL_19         (19*0x0001u) /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL_20         (20*0x0001u) /* DMA channel 2 transfer select 20: Reserved  */
#define DMA2TSEL_21         (21*0x0001u) /* DMA channel 2 transfer select 21: Reserved  */
#define DMA2TSEL_22         (22*0x0001u) /* DMA channel 2 transfer select 22: Reserved  */
#define DMA2TSEL_23         (23*0x0001u) /* DMA channel 2 transfer select 23: Reserved  */
#define DMA2TSEL_24         (24*0x0001u) /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL_25         (25*0x0001u) /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL_26         (26*0x0001u) /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL_27         (27*0x0001u) /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL_28         (28*0x0001u) /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL_29         (29*0x0001u) /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL_30         (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL_31         (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

#define DMA0TSEL__DMA_REQ   (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL__TA0CCR0   (1*0x0001u)  /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL__TA0CCR2   (2*0x0001u)  /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL__TA1CCR0   (3*0x0001u)  /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL__TA1CCR2   (4*0x0001u)  /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL__TB0CCR0   (5*0x0001u)  /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL__TB0CCR2   (6*0x0001u)  /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL__RES7      (7*0x0001u)  /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL__RES8      (8*0x0001u)  /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL__RES9      (9*0x0001u)  /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL__RES10     (10*0x0001u) /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL__RES11     (11*0x0001u) /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL__RES12     (12*0x0001u) /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL__RES13     (13*0x0001u) /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL__RFRXIFG   (14*0x0001u) /* DMA channel 0 transfer select 14: RFRXIFG */
#define DMA0TSEL__RFTXIFG   (15*0x0001u) /* DMA channel 0 transfer select 15: RFTXIFG */
#define DMA0TSEL__USCIA0RX  (16*0x0001u) /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL__USCIA0TX  (17*0x0001u) /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL__USCIB0RX  (18*0x0001u) /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL__USCIB0TX  (19*0x0001u) /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL__RES20     (20*0x0001u) /* DMA channel 0 transfer select 20: Reserved  */
#define DMA0TSEL__RES21     (21*0x0001u) /* DMA channel 0 transfer select 21: Reserved  */
#define DMA0TSEL__RES22     (22*0x0001u) /* DMA channel 0 transfer select 22: Reserved  */
#define DMA0TSEL__RES23     (23*0x0001u) /* DMA channel 0 transfer select 23: Reserved  */
#define DMA0TSEL__ADC12IFG  (24*0x0001u) /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL__RES25     (25*0x0001u) /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL__RES26     (26*0x0001u) /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL__RES27     (27*0x0001u) /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL__RES28     (28*0x0001u) /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL__MPY       (29*0x0001u) /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL__DMA2IFG   (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL__DMAE0     (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL__DMA_REQ   (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL__TA0CCR0   (1*0x0100u)  /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL__TA0CCR2   (2*0x0100u)  /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL__TA1CCR0   (3*0x0100u)  /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL__TA1CCR2   (4*0x0100u)  /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL__TB0CCR0   (5*0x0100u)  /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL__TB0CCR2   (6*0x0100u)  /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL__RES7      (7*0x0100u)  /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL__RES8      (8*0x0100u)  /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL__RES9      (9*0x0100u)  /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL__RES10     (10*0x0100u) /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL__RES11     (11*0x0100u) /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL__RES12     (12*0x0100u) /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL__RES13     (13*0x0100u) /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL__RFRXIFG   (14*0x0100u) /* DMA channel 1 transfer select 14: RFRXIFG */
#define DMA1TSEL__RFTXIFG   (15*0x0100u) /* DMA channel 1 transfer select 15: RFTXIFG */
#define DMA1TSEL__USCIA0RX  (16*0x0100u) /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL__USCIA0TX  (17*0x0100u) /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL__USCIB0RX  (18*0x0100u) /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL__USCIB0TX  (19*0x0100u) /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL__RES20     (20*0x0100u) /* DMA channel 1 transfer select 20: Reserved  */
#define DMA1TSEL__RES21     (21*0x0100u) /* DMA channel 1 transfer select 21: Reserved  */
#define DMA1TSEL__RES22     (22*0x0100u) /* DMA channel 1 transfer select 22: Reserved  */
#define DMA1TSEL__RES23     (23*0x0100u) /* DMA channel 1 transfer select 23: Reserved  */
#define DMA1TSEL__ADC12IFG  (24*0x0100u) /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL__RES25     (25*0x0100u) /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL__RES26     (26*0x0100u) /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL__RES27     (27*0x0100u) /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL__RES28     (28*0x0100u) /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL__MPY       (29*0x0100u) /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL__DMA0IFG   (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL__DMAE0     (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL__DMA_REQ   (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL__TA0CCR0   (1*0x0001u)  /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL__TA0CCR2   (2*0x0001u)  /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL__TA1CCR0   (3*0x0001u)  /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL__TA1CCR2   (4*0x0001u)  /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL__TB0CCR0   (5*0x0001u)  /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL__TB0CCR2   (6*0x0001u)  /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL__RES7      (7*0x0001u)  /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL__RES8      (8*0x0001u)  /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL__RES9      (9*0x0001u)  /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL__RES10     (10*0x0001u) /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL__RES11     (11*0x0001u) /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL__RES12     (12*0x0001u) /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL__RES13     (13*0x0001u) /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL__RFRXIFG   (14*0x0001u) /* DMA channel 2 transfer select 14: RFRXIFG */
#define DMA2TSEL__RFTXIFG   (15*0x0001u) /* DMA channel 2 transfer select 15: RFTXIFG */
#define DMA2TSEL__USCIA0RX  (16*0x0001u) /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL__USCIA0TX  (17*0x0001u) /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL__USCIB0RX  (18*0x0001u) /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL__USCIB0TX  (19*0x0001u) /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL__RES20     (20*0x0001u) /* DMA channel 2 transfer select 20: Reserved  */
#define DMA2TSEL__RES21     (21*0x0001u) /* DMA channel 2 transfer select 21: Reserved  */
#define DMA2TSEL__RES22     (22*0x0001u) /* DMA channel 2 transfer select 22: Reserved  */
#define DMA2TSEL__RES23     (23*0x0001u) /* DMA channel 2 transfer select 23: Reserved  */
#define DMA2TSEL__ADC12IFG  (24*0x0001u) /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL__RES25     (25*0x0001u) /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL__RES26     (26*0x0001u) /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL__RES27     (27*0x0001u) /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL__RES28     (28*0x0001u) /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL__MPY       (29*0x0001u) /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL__DMA1IFG   (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL__DMAE0     (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__         /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FLASH__ 0x0140

#define  FCTL1_              (0x0140u)  /* FLASH Control 1 */
DEFCW(   FCTL1             , FCTL1_)
//sfrbw    FCTL2               (0x0142)  /* FLASH Control 2 */
#define  FCTL3_              (0x0144u)  /* FLASH Control 3 */
DEFCW(   FCTL3             , FCTL3_)
#define  FCTL4_              (0x0146u)  /* FLASH Control 4 */
DEFCW(   FCTL4             , FCTL4_)

#define FRPW                (0x9600u)  /* Flash password returned by read */
#define FWPW                (0xA500u)  /* Flash password for write */
#define FXPW                (0x3300u)  /* for use with XOR instruction */
#define FRKEY               (0x9600u)  /* (legacy definition) Flash key returned by read */
#define FWKEY               (0xA500u)  /* (legacy definition) Flash key for write */
#define FXKEY               (0x3300u)  /* (legacy definition) for use with XOR instruction */

/* FCTL1 Control Bits */
//#define RESERVED            (0x0001u)  /* Reserved */
#define ERASE               (0x0002u)  /* Enable bit for Flash segment erase */
#define MERAS               (0x0004u)  /* Enable bit for Flash mass erase */
//#define RESERVED            (0x0008u)  /* Reserved */
//#define RESERVED            (0x0010u)  /* Reserved */
#define SWRT                (0x0020u)  /* Smart Write enable */
#define WRT                 (0x0040u)  /* Enable bit for Flash write */
#define BLKWRT              (0x0080u)  /* Enable bit for Flash segment write */

/* FCTL1 Control Bits */
//#define RESERVED            (0x0001u)  /* Reserved */
#define ERASE_L             (0x0002u)  /* Enable bit for Flash segment erase */
#define MERAS_L             (0x0004u)  /* Enable bit for Flash mass erase */
//#define RESERVED            (0x0008u)  /* Reserved */
//#define RESERVED            (0x0010u)  /* Reserved */
#define SWRT_L              (0x0020u)  /* Smart Write enable */
#define WRT_L               (0x0040u)  /* Enable bit for Flash write */
#define BLKWRT_L            (0x0080u)  /* Enable bit for Flash segment write */

/* FCTL1 Control Bits */
//#define RESERVED            (0x0001u)  /* Reserved */
//#define RESERVED            (0x0008u)  /* Reserved */
//#define RESERVED            (0x0010u)  /* Reserved */

/* FCTL3 Control Bits */
#define BUSY                (0x0001u)  /* Flash busy: 1 */
#define KEYV                (0x0002u)  /* Flash Key violation flag */
#define ACCVIFG             (0x0004u)  /* Flash Access violation flag */
#define WAIT                (0x0008u)  /* Wait flag for segment write */
#define LOCK                (0x0010u)  /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX                (0x0020u)  /* Flash Emergency Exit */
#define LOCKA               (0x0040u)  /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
//#define RESERVED            (0x0080u)  /* Reserved */

/* FCTL3 Control Bits */
#define BUSY_L              (0x0001u)  /* Flash busy: 1 */
#define KEYV_L              (0x0002u)  /* Flash Key violation flag */
#define ACCVIFG_L           (0x0004u)  /* Flash Access violation flag */
#define WAIT_L              (0x0008u)  /* Wait flag for segment write */
#define LOCK_L              (0x0010u)  /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX_L              (0x0020u)  /* Flash Emergency Exit */
#define LOCKA_L             (0x0040u)  /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
//#define RESERVED            (0x0080u)  /* Reserved */

/* FCTL3 Control Bits */
//#define RESERVED            (0x0080u)  /* Reserved */

/* FCTL4 Control Bits */
#define VPE                 (0x0001u)  /* Voltage Changed during Program Error Flag */
#define MGR0                (0x0010u)  /* Marginal read 0 mode. */
#define MGR1                (0x0020u)  /* Marginal read 1 mode. */
#define LOCKINFO            (0x0080u)  /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */

/* FCTL4 Control Bits */
#define VPE_L               (0x0001u)  /* Voltage Changed during Program Error Flag */
#define MGR0_L              (0x0010u)  /* Marginal read 0 mode. */
#define MGR1_L              (0x0020u)  /* Marginal read 1 mode. */
#define LOCKINFO_L          (0x0080u)  /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */

/* FCTL4 Control Bits */

/************************************************************
* LCD_B
************************************************************/
#define __MSP430_HAS_LCD_B__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_LCD_B__ 0x0A00

#define LCDBCTL0_           (0x0A00u)  /* LCD_B Control Register 0 */
DEFCW(  LCDBCTL0          , LCDBCTL0_)
#define LCDBCTL1_           (0x0A02u)  /* LCD_B Control Register 1 */
DEFCW(  LCDBCTL1          , LCDBCTL1_)
#define LCDBBLKCTL_         (0x0A04u)  /* LCD_B blinking control register */
DEFCW(  LCDBBLKCTL        , LCDBBLKCTL_)
#define LCDBMEMCTL_         (0x0A06u)  /* LCD_B memory control register */
DEFCW(  LCDBMEMCTL        , LCDBMEMCTL_)
#define LCDBVCTL_           (0x0A08u)  /* LCD_B Voltage Control Register */
DEFCW(  LCDBVCTL          , LCDBVCTL_)
#define LCDBPCTL0_          (0x0A0Au)  /* LCD_B Port Control Register 0 */
DEFCW(  LCDBPCTL0         , LCDBPCTL0_)
#define LCDBPCTL1_          (0x0A0Cu)  /* LCD_B Port Control Register 1 */
DEFCW(  LCDBPCTL1         , LCDBPCTL1_)
#define LCDBPCTL2_          (0x0A0Eu)  /* LCD_B Port Control Register 2 */
DEFCW(  LCDBPCTL2         , LCDBPCTL2_)
#define LCDBPCTL3_          (0x0A10u)  /* LCD_B Port Control Register 3 */
DEFCW(  LCDBPCTL3         , LCDBPCTL3_)
#define LCDBCPCTL_          (0x0A12u)  /* LCD_B Charge Pump Control Register 3 */
DEFCW(  LCDBCPCTL         , LCDBCPCTL_)
#define LCDBIV_             (0x0A1Eu)  /* LCD_B Interrupt Vector Register */
DEFW(   LCDBIV            , LCDBIV_)

// LCDBCTL0
#define LCDON               (0x0001u)  /* LCD_B LCD On */
#define LCDSON              (0x0004u)  /* LCD_B LCD Segments On */
#define LCDMX0              (0x0008u)  /* LCD_B Mux Rate Bit: 0 */
#define LCDMX1              (0x0010u)  /* LCD_B Mux Rate Bit: 1 */
//#define RESERVED            (0x0020u)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040u)  /* LCD_B RESERVED */
#define LCDSSEL             (0x0080u)  /* LCD_B Clock Select */
#define LCDPRE0             (0x0100u)  /* LCD_B LCD frequency pre-scaler Bit: 0 */
#define LCDPRE1             (0x0200u)  /* LCD_B LCD frequency pre-scaler Bit: 1 */
#define LCDPRE2             (0x0400u)  /* LCD_B LCD frequency pre-scaler Bit: 2 */
#define LCDDIV0             (0x0800u)  /* LCD_B LCD frequency divider Bit: 0 */
#define LCDDIV1             (0x1000u)  /* LCD_B LCD frequency divider Bit: 1 */
#define LCDDIV2             (0x2000u)  /* LCD_B LCD frequency divider Bit: 2 */
#define LCDDIV3             (0x4000u)  /* LCD_B LCD frequency divider Bit: 3 */
#define LCDDIV4             (0x8000u)  /* LCD_B LCD frequency divider Bit: 4 */

// LCDBCTL0
#define LCDON_L             (0x0001u)  /* LCD_B LCD On */
#define LCDSON_L            (0x0004u)  /* LCD_B LCD Segments On */
#define LCDMX0_L            (0x0008u)  /* LCD_B Mux Rate Bit: 0 */
#define LCDMX1_L            (0x0010u)  /* LCD_B Mux Rate Bit: 1 */
//#define RESERVED            (0x0020u)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040u)  /* LCD_B RESERVED */
#define LCDSSEL_L           (0x0080u)  /* LCD_B Clock Select */

// LCDBCTL0
//#define RESERVED            (0x0020u)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040u)  /* LCD_B RESERVED */
#define LCDPRE0_H           (0x0001u)  /* LCD_B LCD frequency pre-scaler Bit: 0 */
#define LCDPRE1_H           (0x0002u)  /* LCD_B LCD frequency pre-scaler Bit: 1 */
#define LCDPRE2_H           (0x0004u)  /* LCD_B LCD frequency pre-scaler Bit: 2 */
#define LCDDIV0_H           (0x0008u)  /* LCD_B LCD frequency divider Bit: 0 */
#define LCDDIV1_H           (0x0010u)  /* LCD_B LCD frequency divider Bit: 1 */
#define LCDDIV2_H           (0x0020u)  /* LCD_B LCD frequency divider Bit: 2 */
#define LCDDIV3_H           (0x0040u)  /* LCD_B LCD frequency divider Bit: 3 */
#define LCDDIV4_H           (0x0080u)  /* LCD_B LCD frequency divider Bit: 4 */

#define LCDPRE_0            (0x0000u)  /* LCD_B LCD frequency pre-scaler: /1 */
#define LCDPRE_1            (0x0100u)  /* LCD_B LCD frequency pre-scaler: /2 */
#define LCDPRE_2            (0x0200u)  /* LCD_B LCD frequency pre-scaler: /4 */
#define LCDPRE_3            (0x0300u)  /* LCD_B LCD frequency pre-scaler: /8 */
#define LCDPRE_4            (0x0400u)  /* LCD_B LCD frequency pre-scaler: /16 */
#define LCDPRE_5            (0x0500u)  /* LCD_B LCD frequency pre-scaler: /32 */
#define LCDPRE__1           (0x0000u)  /* LCD_B LCD frequency pre-scaler: /1 */
#define LCDPRE__2           (0x0100u)  /* LCD_B LCD frequency pre-scaler: /2 */
#define LCDPRE__4           (0x0200u)  /* LCD_B LCD frequency pre-scaler: /4 */
#define LCDPRE__8           (0x0300u)  /* LCD_B LCD frequency pre-scaler: /8 */
#define LCDPRE__16          (0x0400u)  /* LCD_B LCD frequency pre-scaler: /16 */
#define LCDPRE__32          (0x0500u)  /* LCD_B LCD frequency pre-scaler: /32 */

#define LCDDIV_0            (0x0000u)  /* LCD_B LCD frequency divider: /1 */
#define LCDDIV_1            (0x0800u)  /* LCD_B LCD frequency divider: /2 */
#define LCDDIV_2            (0x1000u)  /* LCD_B LCD frequency divider: /3 */
#define LCDDIV_3            (0x1800u)  /* LCD_B LCD frequency divider: /4 */
#define LCDDIV_4            (0x2000u)  /* LCD_B LCD frequency divider: /5 */
#define LCDDIV_5            (0x2800u)  /* LCD_B LCD frequency divider: /6 */
#define LCDDIV_6            (0x3000u)  /* LCD_B LCD frequency divider: /7 */
#define LCDDIV_7            (0x3800u)  /* LCD_B LCD frequency divider: /8 */
#define LCDDIV_8            (0x4000u)  /* LCD_B LCD frequency divider: /9 */
#define LCDDIV_9            (0x4800u)  /* LCD_B LCD frequency divider: /10 */
#define LCDDIV_10           (0x5000u)  /* LCD_B LCD frequency divider: /11 */
#define LCDDIV_11           (0x5800u)  /* LCD_B LCD frequency divider: /12 */
#define LCDDIV_12           (0x6000u)  /* LCD_B LCD frequency divider: /13 */
#define LCDDIV_13           (0x6800u)  /* LCD_B LCD frequency divider: /14 */
#define LCDDIV_14           (0x7000u)  /* LCD_B LCD frequency divider: /15 */
#define LCDDIV_15           (0x7800u)  /* LCD_B LCD frequency divider: /16 */
#define LCDDIV_16           (0x8000u)  /* LCD_B LCD frequency divider: /17 */
#define LCDDIV_17           (0x8800u)  /* LCD_B LCD frequency divider: /18 */
#define LCDDIV_18           (0x9000u)  /* LCD_B LCD frequency divider: /19 */
#define LCDDIV_19           (0x9800u)  /* LCD_B LCD frequency divider: /20 */
#define LCDDIV_20           (0xA000u)  /* LCD_B LCD frequency divider: /21 */
#define LCDDIV_21           (0xA800u)  /* LCD_B LCD frequency divider: /22 */
#define LCDDIV_22           (0xB000u)  /* LCD_B LCD frequency divider: /23 */
#define LCDDIV_23           (0xB800u)  /* LCD_B LCD frequency divider: /24 */
#define LCDDIV_24           (0xC000u)  /* LCD_B LCD frequency divider: /25 */
#define LCDDIV_25           (0xC800u)  /* LCD_B LCD frequency divider: /26 */
#define LCDDIV_26           (0xD000u)  /* LCD_B LCD frequency divider: /27 */
#define LCDDIV_27           (0xD800u)  /* LCD_B LCD frequency divider: /28 */
#define LCDDIV_28           (0xE000u)  /* LCD_B LCD frequency divider: /29 */
#define LCDDIV_29           (0xE800u)  /* LCD_B LCD frequency divider: /30 */
#define LCDDIV_30           (0xF000u)  /* LCD_B LCD frequency divider: /31 */
#define LCDDIV_31           (0xF800u)  /* LCD_B LCD frequency divider: /32 */
#define LCDDIV__1           (0x0000u)  /* LCD_B LCD frequency divider: /1 */
#define LCDDIV__2           (0x0800u)  /* LCD_B LCD frequency divider: /2 */
#define LCDDIV__3           (0x1000u)  /* LCD_B LCD frequency divider: /3 */
#define LCDDIV__4           (0x1800u)  /* LCD_B LCD frequency divider: /4 */
#define LCDDIV__5           (0x2000u)  /* LCD_B LCD frequency divider: /5 */
#define LCDDIV__6           (0x2800u)  /* LCD_B LCD frequency divider: /6 */
#define LCDDIV__7           (0x3000u)  /* LCD_B LCD frequency divider: /7 */
#define LCDDIV__8           (0x3800u)  /* LCD_B LCD frequency divider: /8 */
#define LCDDIV__9           (0x4000u)  /* LCD_B LCD frequency divider: /9 */
#define LCDDIV__10          (0x4800u)  /* LCD_B LCD frequency divider: /10 */
#define LCDDIV__11          (0x5000u)  /* LCD_B LCD frequency divider: /11 */
#define LCDDIV__12          (0x5800u)  /* LCD_B LCD frequency divider: /12 */
#define LCDDIV__13          (0x6000u)  /* LCD_B LCD frequency divider: /13 */
#define LCDDIV__14          (0x6800u)  /* LCD_B LCD frequency divider: /14 */
#define LCDDIV__15          (0x7000u)  /* LCD_B LCD frequency divider: /15 */
#define LCDDIV__16          (0x7800u)  /* LCD_B LCD frequency divider: /16 */
#define LCDDIV__17          (0x8000u)  /* LCD_B LCD frequency divider: /17 */
#define LCDDIV__18          (0x8800u)  /* LCD_B LCD frequency divider: /18 */
#define LCDDIV__19          (0x9000u)  /* LCD_B LCD frequency divider: /19 */
#define LCDDIV__20          (0x9800u)  /* LCD_B LCD frequency divider: /20 */
#define LCDDIV__21          (0xA000u)  /* LCD_B LCD frequency divider: /21 */
#define LCDDIV__22          (0xA800u)  /* LCD_B LCD frequency divider: /22 */
#define LCDDIV__23          (0xB000u)  /* LCD_B LCD frequency divider: /23 */
#define LCDDIV__24          (0xB800u)  /* LCD_B LCD frequency divider: /24 */
#define LCDDIV__25          (0xC000u)  /* LCD_B LCD frequency divider: /25 */
#define LCDDIV__26          (0xC800u)  /* LCD_B LCD frequency divider: /26 */
#define LCDDIV__27          (0xD000u)  /* LCD_B LCD frequency divider: /27 */
#define LCDDIV__28          (0xD800u)  /* LCD_B LCD frequency divider: /28 */
#define LCDDIV__29          (0xE000u)  /* LCD_B LCD frequency divider: /29 */
#define LCDDIV__30          (0xE800u)  /* LCD_B LCD frequency divider: /30 */
#define LCDDIV__31          (0xF000u)  /* LCD_B LCD frequency divider: /31 */
#define LCDDIV__32          (0xF800u)  /* LCD_B LCD frequency divider: /32 */

/* Display modes coded with Bits 2-4 */
#define LCDSTATIC           (LCDSON)
#define LCD2MUX             (LCDMX0+LCDSON)
#define LCD3MUX             (LCDMX1+LCDSON)
#define LCD4MUX             (LCDMX1+LCDMX0+LCDSON)

// LCDBCTL1
#define LCDFRMIFG           (0x0001u)  /* LCD_B LCD frame interrupt flag */
#define LCDBLKOFFIFG        (0x0002u)  /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIFG         (0x0004u)  /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIFG         (0x0008u)  /* LCD_B No cpacitance connected interrupt flag */
#define LCDFRMIE            (0x0100u)  /* LCD_B LCD frame interrupt enable */
#define LCDBLKOFFIE         (0x0200u)  /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIE          (0x0400u)  /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIE          (0x0800u)  /* LCD_B No cpacitance connected interrupt enable */

// LCDBCTL1
#define LCDFRMIFG_L         (0x0001u)  /* LCD_B LCD frame interrupt flag */
#define LCDBLKOFFIFG_L      (0x0002u)  /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIFG_L       (0x0004u)  /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIFG_L       (0x0008u)  /* LCD_B No cpacitance connected interrupt flag */

// LCDBCTL1
#define LCDFRMIE_H          (0x0001u)  /* LCD_B LCD frame interrupt enable */
#define LCDBLKOFFIE_H       (0x0002u)  /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIE_H        (0x0004u)  /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIE_H        (0x0008u)  /* LCD_B No cpacitance connected interrupt enable */

// LCDBBLKCTL
#define LCDBLKMOD0          (0x0001u)  /* LCD_B Blinking mode Bit: 0 */
#define LCDBLKMOD1          (0x0002u)  /* LCD_B Blinking mode Bit: 1 */
#define LCDBLKPRE0          (0x0004u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 0 */
#define LCDBLKPRE1          (0x0008u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 1 */
#define LCDBLKPRE2          (0x0010u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 2 */
#define LCDBLKDIV0          (0x0020u)  /* LCD_B Clock divider for blinking frequency Bit: 0 */
#define LCDBLKDIV1          (0x0040u)  /* LCD_B Clock divider for blinking frequency Bit: 1 */
#define LCDBLKDIV2          (0x0080u)  /* LCD_B Clock divider for blinking frequency Bit: 2 */

// LCDBBLKCTL
#define LCDBLKMOD0_L        (0x0001u)  /* LCD_B Blinking mode Bit: 0 */
#define LCDBLKMOD1_L        (0x0002u)  /* LCD_B Blinking mode Bit: 1 */
#define LCDBLKPRE0_L        (0x0004u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 0 */
#define LCDBLKPRE1_L        (0x0008u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 1 */
#define LCDBLKPRE2_L        (0x0010u)  /* LCD_B Clock pre-scaler for blinking frequency Bit: 2 */
#define LCDBLKDIV0_L        (0x0020u)  /* LCD_B Clock divider for blinking frequency Bit: 0 */
#define LCDBLKDIV1_L        (0x0040u)  /* LCD_B Clock divider for blinking frequency Bit: 1 */
#define LCDBLKDIV2_L        (0x0080u)  /* LCD_B Clock divider for blinking frequency Bit: 2 */

// LCDBBLKCTL

#define LCDBLKMOD_0         (0x0000u)  /* LCD_B Blinking mode: Off */
#define LCDBLKMOD_1         (0x0001u)  /* LCD_B Blinking mode: Individual */
#define LCDBLKMOD_2         (0x0002u)  /* LCD_B Blinking mode: All */
#define LCDBLKMOD_3         (0x0003u)  /* LCD_B Blinking mode: Switching */

// LCDBMEMCTL
#define LCDDISP             (0x0001u)  /* LCD_B LCD memory registers for display */
#define LCDCLRM             (0x0002u)  /* LCD_B Clear LCD memory */
#define LCDCLRBM            (0x0004u)  /* LCD_B Clear LCD blinking memory */

// LCDBMEMCTL
#define LCDDISP_L           (0x0001u)  /* LCD_B LCD memory registers for display */
#define LCDCLRM_L           (0x0002u)  /* LCD_B Clear LCD memory */
#define LCDCLRBM_L          (0x0004u)  /* LCD_B Clear LCD blinking memory */

// LCDBMEMCTL

// LCDBVCTL
#define LCD2B               (0x0001u)  /* Selects 1/2 bias. */
#define VLCDREF0            (0x0002u)  /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1            (0x0004u)  /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN             (0x0008u)  /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT             (0x0010u)  /* Select external source for VLCD. */
#define LCDEXTBIAS          (0x0020u)  /* V2 - V4 voltage select. */
#define R03EXT              (0x0040u)  /* Selects external connections for LCD mid voltages. */
#define LCDREXT             (0x0080u)  /* Selects external connection for lowest LCD voltage. */
#define VLCD0               (0x0200u)  /* VLCD select: 0 */
#define VLCD1               (0x0400u)  /* VLCD select: 1 */
#define VLCD2               (0x0800u)  /* VLCD select: 2 */
#define VLCD3               (0x1000u)  /* VLCD select: 3 */

// LCDBVCTL
#define LCD2B_L             (0x0001u)  /* Selects 1/2 bias. */
#define VLCDREF0_L          (0x0002u)  /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1_L          (0x0004u)  /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN_L           (0x0008u)  /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT_L           (0x0010u)  /* Select external source for VLCD. */
#define LCDEXTBIAS_L        (0x0020u)  /* V2 - V4 voltage select. */
#define R03EXT_L            (0x0040u)  /* Selects external connections for LCD mid voltages. */
#define LCDREXT_L           (0x0080u)  /* Selects external connection for lowest LCD voltage. */

// LCDBVCTL
#define VLCD0_H             (0x0002u)  /* VLCD select: 0 */
#define VLCD1_H             (0x0004u)  /* VLCD select: 1 */
#define VLCD2_H             (0x0008u)  /* VLCD select: 2 */
#define VLCD3_H             (0x0010u)  /* VLCD select: 3 */

/* Reference voltage source select for the regulated charge pump */
#define VLCDREF_0           (0<<1)    /* Internal */
#define VLCDREF_1           (1<<1)    /* External */
#define VLCDREF_2           (2<<1)    /* Reserved */
#define VLCDREF_3           (3<<1)    /* Reserved */

/* Charge pump voltage selections */
#define VLCD_0              (0<<9)    /* Charge pump disabled */
#define VLCD_1              (1<<9)    /* VLCD = 2.60V */
#define VLCD_2              (2<<9)    /* VLCD = 2.66V */
#define VLCD_3              (3<<9)    /* VLCD = 2.72V */
#define VLCD_4              (4<<9)    /* VLCD = 2.78V */
#define VLCD_5              (5<<9)    /* VLCD = 2.84V */
#define VLCD_6              (6<<9)    /* VLCD = 2.90V */
#define VLCD_7              (7<<9)    /* VLCD = 2.96V */
#define VLCD_8              (8<<9)    /* VLCD = 3.02V */
#define VLCD_9              (9<<9)    /* VLCD = 3.08V */
#define VLCD_10             (10<<9)   /* VLCD = 3.14V */
#define VLCD_11             (11<<9)   /* VLCD = 3.20V */
#define VLCD_12             (12<<9)   /* VLCD = 3.26V */
#define VLCD_13             (12<<9)   /* VLCD = 3.32V */
#define VLCD_14             (13<<9)   /* VLCD = 3.38V */
#define VLCD_15             (15<<9)   /* VLCD = 3.44V */

#define VLCD_DISABLED       (0<<9)    /* Charge pump disabled */
#define VLCD_2_60           (1<<9)    /* VLCD = 2.60V */
#define VLCD_2_66           (2<<9)    /* VLCD = 2.66V */
#define VLCD_2_72           (3<<9)    /* VLCD = 2.72V */
#define VLCD_2_78           (4<<9)    /* VLCD = 2.78V */
#define VLCD_2_84           (5<<9)    /* VLCD = 2.84V */
#define VLCD_2_90           (6<<9)    /* VLCD = 2.90V */
#define VLCD_2_96           (7<<9)    /* VLCD = 2.96V */
#define VLCD_3_02           (8<<9)    /* VLCD = 3.02V */
#define VLCD_3_08           (9<<9)    /* VLCD = 3.08V */
#define VLCD_3_14           (10<<9)   /* VLCD = 3.14V */
#define VLCD_3_20           (11<<9)   /* VLCD = 3.20V */
#define VLCD_3_26           (12<<9)   /* VLCD = 3.26V */
#define VLCD_3_32           (12<<9)   /* VLCD = 3.32V */
#define VLCD_3_38           (13<<9)   /* VLCD = 3.38V */
#define VLCD_3_44           (15<<9)   /* VLCD = 3.44V */

// LCDBPCTL0
#define LCDS0               (0x0001u)  /* LCD Segment  0 enable. */
#define LCDS1               (0x0002u)  /* LCD Segment  1 enable. */
#define LCDS2               (0x0004u)  /* LCD Segment  2 enable. */
#define LCDS3               (0x0008u)  /* LCD Segment  3 enable. */
#define LCDS4               (0x0010u)  /* LCD Segment  4 enable. */
#define LCDS5               (0x0020u)  /* LCD Segment  5 enable. */
#define LCDS6               (0x0040u)  /* LCD Segment  6 enable. */
#define LCDS7               (0x0080u)  /* LCD Segment  7 enable. */
#define LCDS8               (0x0100u)  /* LCD Segment  8 enable. */
#define LCDS9               (0x0200u)  /* LCD Segment  9 enable. */
#define LCDS10              (0x0400u)  /* LCD Segment 10 enable. */
#define LCDS11              (0x0800u)  /* LCD Segment 11 enable. */
#define LCDS12              (0x1000u)  /* LCD Segment 12 enable. */
#define LCDS13              (0x2000u)  /* LCD Segment 13 enable. */
#define LCDS14              (0x4000u)  /* LCD Segment 14 enable. */
#define LCDS15              (0x8000u)  /* LCD Segment 15 enable. */

// LCDBPCTL0
#define LCDS0_L             (0x0001u)  /* LCD Segment  0 enable. */
#define LCDS1_L             (0x0002u)  /* LCD Segment  1 enable. */
#define LCDS2_L             (0x0004u)  /* LCD Segment  2 enable. */
#define LCDS3_L             (0x0008u)  /* LCD Segment  3 enable. */
#define LCDS4_L             (0x0010u)  /* LCD Segment  4 enable. */
#define LCDS5_L             (0x0020u)  /* LCD Segment  5 enable. */
#define LCDS6_L             (0x0040u)  /* LCD Segment  6 enable. */
#define LCDS7_L             (0x0080u)  /* LCD Segment  7 enable. */

// LCDBPCTL0
#define LCDS8_H             (0x0001u)  /* LCD Segment  8 enable. */
#define LCDS9_H             (0x0002u)  /* LCD Segment  9 enable. */
#define LCDS10_H            (0x0004u)  /* LCD Segment 10 enable. */
#define LCDS11_H            (0x0008u)  /* LCD Segment 11 enable. */
#define LCDS12_H            (0x0010u)  /* LCD Segment 12 enable. */
#define LCDS13_H            (0x0020u)  /* LCD Segment 13 enable. */
#define LCDS14_H            (0x0040u)  /* LCD Segment 14 enable. */
#define LCDS15_H            (0x0080u)  /* LCD Segment 15 enable. */

// LCDBPCTL1
#define LCDS16              (0x0001u)  /* LCD Segment 16 enable. */
#define LCDS17              (0x0002u)  /* LCD Segment 17 enable. */
#define LCDS18              (0x0004u)  /* LCD Segment 18 enable. */
#define LCDS19              (0x0008u)  /* LCD Segment 19 enable. */
#define LCDS20              (0x0010u)  /* LCD Segment 20 enable. */
#define LCDS21              (0x0020u)  /* LCD Segment 21 enable. */
#define LCDS22              (0x0040u)  /* LCD Segment 22 enable. */
#define LCDS23              (0x0080u)  /* LCD Segment 23 enable. */
#define LCDS24              (0x0100u)  /* LCD Segment 24 enable. */
#define LCDS25              (0x0200u)  /* LCD Segment 25 enable. */
#define LCDS26              (0x0400u)  /* LCD Segment 26 enable. */
#define LCDS27              (0x0800u)  /* LCD Segment 27 enable. */
#define LCDS28              (0x1000u)  /* LCD Segment 28 enable. */
#define LCDS29              (0x2000u)  /* LCD Segment 29 enable. */
#define LCDS30              (0x4000u)  /* LCD Segment 30 enable. */
#define LCDS31              (0x8000u)  /* LCD Segment 31 enable. */

// LCDBPCTL1
#define LCDS16_L            (0x0001u)  /* LCD Segment 16 enable. */
#define LCDS17_L            (0x0002u)  /* LCD Segment 17 enable. */
#define LCDS18_L            (0x0004u)  /* LCD Segment 18 enable. */
#define LCDS19_L            (0x0008u)  /* LCD Segment 19 enable. */
#define LCDS20_L            (0x0010u)  /* LCD Segment 20 enable. */
#define LCDS21_L            (0x0020u)  /* LCD Segment 21 enable. */
#define LCDS22_L            (0x0040u)  /* LCD Segment 22 enable. */
#define LCDS23_L            (0x0080u)  /* LCD Segment 23 enable. */

// LCDBPCTL1
#define LCDS24_H            (0x0001u)  /* LCD Segment 24 enable. */
#define LCDS25_H            (0x0002u)  /* LCD Segment 25 enable. */
#define LCDS26_H            (0x0004u)  /* LCD Segment 26 enable. */
#define LCDS27_H            (0x0008u)  /* LCD Segment 27 enable. */
#define LCDS28_H            (0x0010u)  /* LCD Segment 28 enable. */
#define LCDS29_H            (0x0020u)  /* LCD Segment 29 enable. */
#define LCDS30_H            (0x0040u)  /* LCD Segment 30 enable. */
#define LCDS31_H            (0x0080u)  /* LCD Segment 31 enable. */

// LCDBPCTL2
#define LCDS32              (0x0001u)  /* LCD Segment 32 enable. */
#define LCDS33              (0x0002u)  /* LCD Segment 33 enable. */
#define LCDS34              (0x0004u)  /* LCD Segment 34 enable. */
#define LCDS35              (0x0008u)  /* LCD Segment 35 enable. */
#define LCDS36              (0x0010u)  /* LCD Segment 36 enable. */
#define LCDS37              (0x0020u)  /* LCD Segment 37 enable. */
#define LCDS38              (0x0040u)  /* LCD Segment 38 enable. */
#define LCDS39              (0x0080u)  /* LCD Segment 39 enable. */
#define LCDS40              (0x0100u)  /* LCD Segment 40 enable. */
#define LCDS41              (0x0200u)  /* LCD Segment 41 enable. */
#define LCDS42              (0x0400u)  /* LCD Segment 42 enable. */
#define LCDS43              (0x0800u)  /* LCD Segment 43 enable. */
#define LCDS44              (0x1000u)  /* LCD Segment 44 enable. */
#define LCDS45              (0x2000u)  /* LCD Segment 45 enable. */
#define LCDS46              (0x4000u)  /* LCD Segment 46 enable. */
#define LCDS47              (0x8000u)  /* LCD Segment 47 enable. */

// LCDBPCTL2
#define LCDS32_L            (0x0001u)  /* LCD Segment 32 enable. */
#define LCDS33_L            (0x0002u)  /* LCD Segment 33 enable. */
#define LCDS34_L            (0x0004u)  /* LCD Segment 34 enable. */
#define LCDS35_L            (0x0008u)  /* LCD Segment 35 enable. */
#define LCDS36_L            (0x0010u)  /* LCD Segment 36 enable. */
#define LCDS37_L            (0x0020u)  /* LCD Segment 37 enable. */
#define LCDS38_L            (0x0040u)  /* LCD Segment 38 enable. */
#define LCDS39_L            (0x0080u)  /* LCD Segment 39 enable. */

// LCDBPCTL2
#define LCDS40_H            (0x0001u)  /* LCD Segment 40 enable. */
#define LCDS41_H            (0x0002u)  /* LCD Segment 41 enable. */
#define LCDS42_H            (0x0004u)  /* LCD Segment 42 enable. */
#define LCDS43_H            (0x0008u)  /* LCD Segment 43 enable. */
#define LCDS44_H            (0x0010u)  /* LCD Segment 44 enable. */
#define LCDS45_H            (0x0020u)  /* LCD Segment 45 enable. */
#define LCDS46_H            (0x0040u)  /* LCD Segment 46 enable. */
#define LCDS47_H            (0x0080u)  /* LCD Segment 47 enable. */

// LCDBPCTL3
#define LCDS48              (0x0001u)  /* LCD Segment 48 enable. */
#define LCDS49              (0x0002u)  /* LCD Segment 49 enable. */
#define LCDS50              (0x0004u)  /* LCD Segment 50 enable. */

// LCDBPCTL3
#define LCDS48_L            (0x0001u)  /* LCD Segment 48 enable. */
#define LCDS49_L            (0x0002u)  /* LCD Segment 49 enable. */
#define LCDS50_L            (0x0004u)  /* LCD Segment 50 enable. */

// LCDBPCTL3

// LCDBCPCTL
#define LCDCPDIS0           (0x0001u)  /* LCD charge pump disable */
#define LCDCPDIS1           (0x0002u)  /* LCD charge pump disable */
#define LCDCPDIS2           (0x0004u)  /* LCD charge pump disable */
#define LCDCPDIS3           (0x0008u)  /* LCD charge pump disable */
#define LCDCPDIS4           (0x0010u)  /* LCD charge pump disable */
#define LCDCPDIS5           (0x0020u)  /* LCD charge pump disable */
#define LCDCPDIS6           (0x0040u)  /* LCD charge pump disable */
#define LCDCPDIS7           (0x0080u)  /* LCD charge pump disable */
#define LCDCPCLKSYNC        (0x8000u)  /* LCD charge pump clock synchronization */

// LCDBCPCTL
#define LCDCPDIS0_L         (0x0001u)  /* LCD charge pump disable */
#define LCDCPDIS1_L         (0x0002u)  /* LCD charge pump disable */
#define LCDCPDIS2_L         (0x0004u)  /* LCD charge pump disable */
#define LCDCPDIS3_L         (0x0008u)  /* LCD charge pump disable */
#define LCDCPDIS4_L         (0x0010u)  /* LCD charge pump disable */
#define LCDCPDIS5_L         (0x0020u)  /* LCD charge pump disable */
#define LCDCPDIS6_L         (0x0040u)  /* LCD charge pump disable */
#define LCDCPDIS7_L         (0x0080u)  /* LCD charge pump disable */

// LCDBCPCTL
#define LCDCPCLKSYNC_H      (0x0080u)  /* LCD charge pump clock synchronization */

#define LCDM1_              (0x0A20u)  /* LCD Memory 1 */
DEFC(   LCDM1             , LCDM1_)
#define LCDMEM_             LCDM1     /* LCD Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define LCDMEM              LCDM1     /* LCD Memory (for assembler) */
#else
#define LCDMEM              ((char*) &LCDM1) /* LCD Memory (for C) */
#endif
#define LCDM2_              (0x0A21u)  /* LCD Memory 2 */
DEFC(   LCDM2             , LCDM2_)
#define LCDM3_              (0x0A22u)  /* LCD Memory 3 */
DEFC(   LCDM3             , LCDM3_)
#define LCDM4_              (0x0A23u)  /* LCD Memory 4 */
DEFC(   LCDM4             , LCDM4_)
#define LCDM5_              (0x0A24u)  /* LCD Memory 5 */
DEFC(   LCDM5             , LCDM5_)
#define LCDM6_              (0x0A25u)  /* LCD Memory 6 */
DEFC(   LCDM6             , LCDM6_)
#define LCDM7_              (0x0A26u)  /* LCD Memory 7 */
DEFC(   LCDM7             , LCDM7_)
#define LCDM8_              (0x0A27u)  /* LCD Memory 8 */
DEFC(   LCDM8             , LCDM8_)
#define LCDM9_              (0x0A28u)  /* LCD Memory 9 */
DEFC(   LCDM9             , LCDM9_)
#define LCDM10_             (0x0A29u)  /* LCD Memory 10 */
DEFC(   LCDM10            , LCDM10_)
#define LCDM11_             (0x0A2Au)  /* LCD Memory 11 */
DEFC(   LCDM11            , LCDM11_)
#define LCDM12_             (0x0A2Bu)  /* LCD Memory 12 */
DEFC(   LCDM12            , LCDM12_)
#define LCDM13_             (0x0A2Cu)  /* LCD Memory 13 */
DEFC(   LCDM13            , LCDM13_)
#define LCDM14_             (0x0A2Du)  /* LCD Memory 14 */
DEFC(   LCDM14            , LCDM14_)
#define LCDM15_             (0x0A2Eu)  /* LCD Memory 15 */
DEFC(   LCDM15            , LCDM15_)
#define LCDM16_             (0x0A2Fu)  /* LCD Memory 16 */
DEFC(   LCDM16            , LCDM16_)
#define LCDM17_             (0x0A30u)  /* LCD Memory 17 */
DEFC(   LCDM17            , LCDM17_)
#define LCDM18_             (0x0A31u)  /* LCD Memory 18 */
DEFC(   LCDM18            , LCDM18_)
#define LCDM19_             (0x0A32u)  /* LCD Memory 19 */
DEFC(   LCDM19            , LCDM19_)
#define LCDM20_             (0x0A33u)  /* LCD Memory 20 */
DEFC(   LCDM20            , LCDM20_)
#define LCDM21_             (0x0A34u)  /* LCD Memory 21 */
DEFC(   LCDM21            , LCDM21_)
#define LCDM22_             (0x0A35u)  /* LCD Memory 22 */
DEFC(   LCDM22            , LCDM22_)
#define LCDM23_             (0x0A36u)  /* LCD Memory 23 */
DEFC(   LCDM23            , LCDM23_)
#define LCDM24_             (0x0A37u)  /* LCD Memory 24 */
DEFC(   LCDM24            , LCDM24_)

#define LCDBM1_             (0x0A40u)  /* LCD Blinking Memory 1 */
DEFC(   LCDBM1            , LCDBM1_)
#define LCDBMEM_            LCDBM1    /* LCD Blinking Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define LCDBMEM             (LCDBM1)  /* LCD Blinking Memory (for assembler) */
#else
#define LCDBMEM             ((char*) &LCDBM1) /* LCD Blinking Memory (for C) */
#endif
#define LCDBM2_             (0x0A41u)  /* LCD Blinking Memory 2 */
DEFC(   LCDBM2            , LCDBM2_)
#define LCDBM3_             (0x0A42u)  /* LCD Blinking Memory 3 */
DEFC(   LCDBM3            , LCDBM3_)
#define LCDBM4_             (0x0A43u)  /* LCD Blinking Memory 4 */
DEFC(   LCDBM4            , LCDBM4_)
#define LCDBM5_             (0x0A44u)  /* LCD Blinking Memory 5 */
DEFC(   LCDBM5            , LCDBM5_)
#define LCDBM6_             (0x0A45u)  /* LCD Blinking Memory 6 */
DEFC(   LCDBM6            , LCDBM6_)
#define LCDBM7_             (0x0A46u)  /* LCD Blinking Memory 7 */
DEFC(   LCDBM7            , LCDBM7_)
#define LCDBM8_             (0x0A47u)  /* LCD Blinking Memory 8 */
DEFC(   LCDBM8            , LCDBM8_)
#define LCDBM9_             (0x0A48u)  /* LCD Blinking Memory 9 */
DEFC(   LCDBM9            , LCDBM9_)
#define LCDBM10_            (0x0A49u)  /* LCD Blinking Memory 10 */
DEFC(   LCDBM10           , LCDBM10_)
#define LCDBM11_            (0x0A4Au)  /* LCD Blinking Memory 11 */
DEFC(   LCDBM11           , LCDBM11_)
#define LCDBM12_            (0x0A4Bu)  /* LCD Blinking Memory 12 */
DEFC(   LCDBM12           , LCDBM12_)
#define LCDBM13_            (0x0A4Cu)  /* LCD Blinking Memory 13 */
DEFC(   LCDBM13           , LCDBM13_)
#define LCDBM14_            (0x0A4Du)  /* LCD Blinking Memory 14 */
DEFC(   LCDBM14           , LCDBM14_)
#define LCDBM15_            (0x0A4Eu)  /* LCD Blinking Memory 15 */
DEFC(   LCDBM15           , LCDBM15_)
#define LCDBM16_            (0x0A4Fu)  /* LCD Blinking Memory 16 */
DEFC(   LCDBM16           , LCDBM16_)
#define LCDBM17_            (0x0A50u)  /* LCD Blinking Memory 17 */
DEFC(   LCDBM17           , LCDBM17_)
#define LCDBM18_            (0x0A51u)  /* LCD Blinking Memory 18 */
DEFC(   LCDBM18           , LCDBM18_)
#define LCDBM19_            (0x0A52u)  /* LCD Blinking Memory 19 */
DEFC(   LCDBM19           , LCDBM19_)
#define LCDBM20_            (0x0A53u)  /* LCD Blinking Memory 20 */
DEFC(   LCDBM20           , LCDBM20_)
#define LCDBM21_            (0x0A54u)  /* LCD Blinking Memory 21 */
DEFC(   LCDBM21           , LCDBM21_)
#define LCDBM22_            (0x0A55u)  /* LCD Blinking Memory 22 */
DEFC(   LCDBM22           , LCDBM22_)
#define LCDBM23_            (0x0A56u)  /* LCD Blinking Memory 23 */
DEFC(   LCDBM23           , LCDBM23_)
#define LCDBM24_            (0x0A57u)  /* LCD Blinking Memory 24 */
DEFC(   LCDBM24           , LCDBM24_)

/* LCDBIV Definitions */
#define LCDBIV_NONE         (0x0000u)    /* No Interrupt pending */
#define LCDBIV_LCDNOCAPIFG  (0x0002u)    /* No capacitor connected */
#define LCDBIV_LCDBLKOFFIFG (0x0004u)    /* Blink, segments off */
#define LCDBIV_LCDBLKONIFG  (0x0006u)    /* Blink, segments on */
#define LCDBIV_LCDFRMIFG    (0x0008u)    /* Frame interrupt */

/************************************************************
* HARDWARE MULTIPLIER 32Bit
************************************************************/
#define __MSP430_HAS_MPY32__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPY32__ 0x04C0

#define  MPY_                (0x04C0u)  /* Multiply Unsigned/Operand 1 */
DEFCW(   MPY               , MPY_)
#define  MPYS_               (0x04C2u)  /* Multiply Signed/Operand 1 */
DEFCW(   MPYS              , MPYS_)
#define  MAC_                (0x04C4u)  /* Multiply Unsigned and Accumulate/Operand 1 */
DEFCW(   MAC               , MAC_)
#define  MACS_               (0x04C6u)  /* Multiply Signed and Accumulate/Operand 1 */
DEFCW(   MACS              , MACS_)
#define  OP2_                (0x04C8u)  /* Operand 2 */
DEFCW(   OP2               , OP2_)
#define  RESLO_              (0x04CAu)  /* Result Low Word */
DEFCW(   RESLO             , RESLO_)
#define  RESHI_              (0x04CCu)  /* Result High Word */
DEFCW(   RESHI             , RESHI_)
#define SUMEXT_             (0x04CEu)  /* Sum Extend */
READ_ONLY_DEFCW( SUMEXT         , SUMEXT_)

#define  MPY32L_             (0x04D0u)  /* 32-bit operand 1 - multiply - low word */
DEFCW(   MPY32L            , MPY32L_)
#define  MPY32H_             (0x04D2u)  /* 32-bit operand 1 - multiply - high word */
DEFCW(   MPY32H            , MPY32H_)
#define  MPYS32L_            (0x04D4u)  /* 32-bit operand 1 - signed multiply - low word */
DEFCW(   MPYS32L           , MPYS32L_)
#define  MPYS32H_            (0x04D6u)  /* 32-bit operand 1 - signed multiply - high word */
DEFCW(   MPYS32H           , MPYS32H_)
#define  MAC32L_             (0x04D8u)  /* 32-bit operand 1 - multiply accumulate - low word */
DEFCW(   MAC32L            , MAC32L_)
#define  MAC32H_             (0x04DAu)  /* 32-bit operand 1 - multiply accumulate - high word */
DEFCW(   MAC32H            , MAC32H_)
#define  MACS32L_            (0x04DCu)  /* 32-bit operand 1 - signed multiply accumulate - low word */
DEFCW(   MACS32L           , MACS32L_)
#define  MACS32H_            (0x04DEu)  /* 32-bit operand 1 - signed multiply accumulate - high word */
DEFCW(   MACS32H           , MACS32H_)
#define  OP2L_               (0x04E0u)  /* 32-bit operand 2 - low word */
DEFCW(   OP2L              , OP2L_)
#define  OP2H_               (0x04E2u)  /* 32-bit operand 2 - high word */
DEFCW(   OP2H              , OP2H_)
#define  RES0_               (0x04E4u)  /* 32x32-bit result 0 - least significant word */
DEFCW(   RES0              , RES0_)
#define  RES1_               (0x04E6u)  /* 32x32-bit result 1 */
DEFCW(   RES1              , RES1_)
#define  RES2_               (0x04E8u)  /* 32x32-bit result 2 */
DEFCW(   RES2              , RES2_)
#define  RES3_               (0x04EAu)  /* 32x32-bit result 3 - most significant word */
DEFCW(   RES3              , RES3_)
#define  MPY32CTL0_          (0x04ECu)  /* MPY32 Control Register 0 */
DEFCW(   MPY32CTL0         , MPY32CTL0_)

#define MPY_B               MPY_L      /* Multiply Unsigned/Operand 1 (Byte Access) */
#define MPYS_B              MPYS_L     /* Multiply Signed/Operand 1 (Byte Access) */
#define MAC_B               MAC_L      /* Multiply Unsigned and Accumulate/Operand 1 (Byte Access) */
#define MACS_B              MACS_L     /* Multiply Signed and Accumulate/Operand 1 (Byte Access) */
#define OP2_B               OP2_L      /* Operand 2 (Byte Access) */
#define MPY32L_B            MPY32L_L   /* 32-bit operand 1 - multiply - low word (Byte Access) */
#define MPY32H_B            MPY32H_L   /* 32-bit operand 1 - multiply - high word (Byte Access) */
#define MPYS32L_B           MPYS32L_L  /* 32-bit operand 1 - signed multiply - low word (Byte Access) */
#define MPYS32H_B           MPYS32H_L  /* 32-bit operand 1 - signed multiply - high word (Byte Access) */
#define MAC32L_B            MAC32L_L   /* 32-bit operand 1 - multiply accumulate - low word (Byte Access) */
#define MAC32H_B            MAC32H_L   /* 32-bit operand 1 - multiply accumulate - high word (Byte Access) */
#define MACS32L_B           MACS32L_L  /* 32-bit operand 1 - signed multiply accumulate - low word (Byte Access) */
#define MACS32H_B           MACS32H_L  /* 32-bit operand 1 - signed multiply accumulate - high word (Byte Access) */
#define OP2L_B              OP2L_L     /* 32-bit operand 2 - low word (Byte Access) */
#define OP2H_B              OP2H_L     /* 32-bit operand 2 - high word (Byte Access) */

/* MPY32CTL0 Control Bits */
#define MPYC                (0x0001u)  /* Carry of the multiplier */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYFRAC             (0x0004u)  /* Fractional mode */
#define MPYSAT              (0x0008u)  /* Saturation mode */
#define MPYM0               (0x0010u)  /* Multiplier mode Bit:0 */
#define MPYM1               (0x0020u)  /* Multiplier mode Bit:1 */
#define OP1_32              (0x0040u)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32              (0x0080u)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */
#define MPYDLYWRTEN         (0x0100u)  /* Delayed write enable */
#define MPYDLY32            (0x0200u)  /* Delayed write mode */

/* MPY32CTL0 Control Bits */
#define MPYC_L              (0x0001u)  /* Carry of the multiplier */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYFRAC_L           (0x0004u)  /* Fractional mode */
#define MPYSAT_L            (0x0008u)  /* Saturation mode */
#define MPYM0_L             (0x0010u)  /* Multiplier mode Bit:0 */
#define MPYM1_L             (0x0020u)  /* Multiplier mode Bit:1 */
#define OP1_32_L            (0x0040u)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32_L            (0x0080u)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */

/* MPY32CTL0 Control Bits */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYDLYWRTEN_H       (0x0001u)  /* Delayed write enable */
#define MPYDLY32_H          (0x0002u)  /* Delayed write mode */

#define MPYM_0              (0x0000u)  /* Multiplier mode: MPY */
#define MPYM_1              (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM_2              (0x0020u)  /* Multiplier mode: MAC */
#define MPYM_3              (0x0030u)  /* Multiplier mode: MACS */
#define MPYM__MPY           (0x0000u)  /* Multiplier mode: MPY */
#define MPYM__MPYS          (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM__MAC           (0x0020u)  /* Multiplier mode: MAC */
#define MPYM__MACS          (0x0030u)  /* Multiplier mode: MACS */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200

#define PAIN_               (0x0200u)  /* Port A Input */
READ_ONLY_DEFCW( PAIN           , PAIN_)
#define  PAOUT_              (0x0202u)  /* Port A Output */
DEFCW(   PAOUT             , PAOUT_)
#define  PADIR_              (0x0204u)  /* Port A Direction */
DEFCW(   PADIR             , PADIR_)
#define  PAREN_              (0x0206u)  /* Port A Resistor Enable */
DEFCW(   PAREN             , PAREN_)
#define  PADS_               (0x0208u)  /* Port A Resistor Drive Strenght */
DEFCW(   PADS              , PADS_)
#define  PASEL_              (0x020Au)  /* Port A Selection */
DEFCW(   PASEL             , PASEL_)
#define  PAIES_              (0x0218u)  /* Port A Interrupt Edge Select */
DEFCW(   PAIES             , PAIES_)
#define  PAIE_               (0x021Au)  /* Port A Interrupt Enable */
DEFCW(   PAIE              , PAIE_)
#define  PAIFG_              (0x021Cu)  /* Port A Interrupt Flag */
DEFCW(   PAIFG             , PAIFG_)


#define P1IV_               (0x020Eu)  /* Port 1 Interrupt Vector Word */
DEFW(   P1IV              , P1IV_)
#define P2IV_               (0x021Eu)  /* Port 2 Interrupt Vector Word */
DEFW(   P2IV              , P2IV_)
#define P1IN                (PAIN_L)  /* Port 1 Input */
#define P1OUT               (PAOUT_L) /* Port 1 Output */
#define P1DIR               (PADIR_L) /* Port 1 Direction */
#define P1REN               (PAREN_L) /* Port 1 Resistor Enable */
#define P1DS                (PADS_L)  /* Port 1 Resistor Drive Strenght */
#define P1SEL               (PASEL_L) /* Port 1 Selection */
#define P1IES               (PAIES_L) /* Port 1 Interrupt Edge Select */
#define P1IE                (PAIE_L)  /* Port 1 Interrupt Enable */
#define P1IFG               (PAIFG_L) /* Port 1 Interrupt Flag */

//Definitions for P1IV
#define P1IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P1IV_P1IFG0          (0x0002u)    /* P1IV P1IFG.0 */
#define P1IV_P1IFG1          (0x0004u)    /* P1IV P1IFG.1 */
#define P1IV_P1IFG2          (0x0006u)    /* P1IV P1IFG.2 */
#define P1IV_P1IFG3          (0x0008u)    /* P1IV P1IFG.3 */
#define P1IV_P1IFG4          (0x000Au)    /* P1IV P1IFG.4 */
#define P1IV_P1IFG5          (0x000Cu)    /* P1IV P1IFG.5 */
#define P1IV_P1IFG6          (0x000Eu)    /* P1IV P1IFG.6 */
#define P1IV_P1IFG7          (0x0010u)    /* P1IV P1IFG.7 */

#define P2IN                (PAIN_H)  /* Port 2 Input */
#define P2OUT               (PAOUT_H) /* Port 2 Output */
#define P2DIR               (PADIR_H) /* Port 2 Direction */
#define P2REN               (PAREN_H) /* Port 2 Resistor Enable */
#define P2DS                (PADS_H)  /* Port 2 Resistor Drive Strenght */
#define P2SEL               (PASEL_H) /* Port 2 Selection */
#define P2IES               (PAIES_H) /* Port 2 Interrupt Edge Select */
#define P2IE                (PAIE_H)  /* Port 2 Interrupt Enable */
#define P2IFG               (PAIFG_H) /* Port 2 Interrupt Flag */

//Definitions for P2IV
#define P2IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P2IV_P2IFG0          (0x0002u)    /* P2IV P2IFG.0 */
#define P2IV_P2IFG1          (0x0004u)    /* P2IV P2IFG.1 */
#define P2IV_P2IFG2          (0x0006u)    /* P2IV P2IFG.2 */
#define P2IV_P2IFG3          (0x0008u)    /* P2IV P2IFG.3 */
#define P2IV_P2IFG4          (0x000Au)    /* P2IV P2IFG.4 */
#define P2IV_P2IFG5          (0x000Cu)    /* P2IV P2IFG.5 */
#define P2IV_P2IFG6          (0x000Eu)    /* P2IV P2IFG.6 */
#define P2IV_P2IFG7          (0x0010u)    /* P2IV P2IFG.7 */


/************************************************************
* DIGITAL I/O Port3/4 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT3_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_R__ 0x0220
#define __MSP430_HAS_PORT4_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT4_R__ 0x0220
#define __MSP430_HAS_PORTB_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTB_R__ 0x0220

#define PBIN_               (0x0220u)  /* Port B Input */
READ_ONLY_DEFCW( PBIN           , PBIN_)
#define  PBOUT_              (0x0222u)  /* Port B Output */
DEFCW(   PBOUT             , PBOUT_)
#define  PBDIR_              (0x0224u)  /* Port B Direction */
DEFCW(   PBDIR             , PBDIR_)
#define  PBREN_              (0x0226u)  /* Port B Resistor Enable */
DEFCW(   PBREN             , PBREN_)
#define  PBDS_               (0x0228u)  /* Port B Resistor Drive Strenght */
DEFCW(   PBDS              , PBDS_)
#define  PBSEL_              (0x022Au)  /* Port B Selection */
DEFCW(   PBSEL             , PBSEL_)


#define P3IN                (PBIN_L)  /* Port 3 Input */
#define P3OUT               (PBOUT_L) /* Port 3 Output */
#define P3DIR               (PBDIR_L) /* Port 3 Direction */
#define P3REN               (PBREN_L) /* Port 3 Resistor Enable */
#define P3DS                (PBDS_L)  /* Port 3 Resistor Drive Strenght */
#define P3SEL               (PBSEL_L) /* Port 3 Selection */

#define P4IN                (PBIN_H)  /* Port 4 Input */
#define P4OUT               (PBOUT_H) /* Port 4 Output */
#define P4DIR               (PBDIR_H) /* Port 4 Direction */
#define P4REN               (PBREN_H) /* Port 4 Resistor Enable */
#define P4DS                (PBDS_H)  /* Port 4 Resistor Drive Strenght */
#define P4SEL               (PBSEL_H) /* Port 4 Selection */


/************************************************************
* DIGITAL I/O Port5 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT5_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT5_R__ 0x0240
#define __MSP430_HAS_PORTC_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTC_R__ 0x0240

#define PCIN_               (0x0240u)  /* Port C Input */
READ_ONLY_DEFCW( PCIN           , PCIN_)
#define  PCOUT_              (0x0242u)  /* Port C Output */
DEFCW(   PCOUT             , PCOUT_)
#define  PCDIR_              (0x0244u)  /* Port C Direction */
DEFCW(   PCDIR             , PCDIR_)
#define  PCREN_              (0x0246u)  /* Port C Resistor Enable */
DEFCW(   PCREN             , PCREN_)
#define  PCDS_               (0x0248u)  /* Port C Resistor Drive Strenght */
DEFCW(   PCDS              , PCDS_)
#define  PCSEL_              (0x024Au)  /* Port C Selection */
DEFCW(   PCSEL             , PCSEL_)


#define P5IN                (PCIN_L)  /* Port 5 Input */
#define P5OUT               (PCOUT_L) /* Port 5 Output */
#define P5DIR               (PCDIR_L) /* Port 5 Direction */
#define P5REN               (PCREN_L) /* Port 5 Resistor Enable */
#define P5DS                (PCDS_L)  /* Port 5 Resistor Drive Strenght */
#define P5SEL               (PCSEL_L) /* Port 5 Selection */


/************************************************************
* DIGITAL I/O PortJ Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORTJ_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTJ_R__ 0x0320

#define PJIN_               (0x0320u)  /* Port J Input */
READ_ONLY_DEFCW( PJIN           , PJIN_)
#define  PJOUT_              (0x0322u)  /* Port J Output */
DEFCW(   PJOUT             , PJOUT_)
#define  PJDIR_              (0x0324u)  /* Port J Direction */
DEFCW(   PJDIR             , PJDIR_)
#define  PJREN_              (0x0326u)  /* Port J Resistor Enable */
DEFCW(   PJREN             , PJREN_)
#define  PJDS_               (0x0328u)  /* Port J Resistor Drive Strenght */
DEFCW(   PJDS              , PJDS_)

/************************************************************
* PORT MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT_MAPPING__   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT_MAPPING__ 0x01C0

#define  PMAPKEYID_          (0x01C0u)  /* Port Mapping Key register */
DEFCW(   PMAPKEYID         , PMAPKEYID_)
#define  PMAPCTL_            (0x01C2u)  /* Port Mapping control register */
DEFCW(   PMAPCTL           , PMAPCTL_)

#define  PMAPKEY             (0x2D52u)  /* Port Mapping Key */
#define  PMAPPWD             PMAPKEYID /* Legacy Definition: Mapping Key register */
#define  PMAPPW              (0x2D52u)  /* Legacy Definition: Port Mapping Password */

/* PMAPCTL Control Bits */
#define PMAPLOCKED          (0x0001u)  /* Port Mapping Lock bit. Read only */
#define PMAPRECFG           (0x0002u)  /* Port Mapping re-configuration control bit */

/* PMAPCTL Control Bits */
#define PMAPLOCKED_L        (0x0001u)  /* Port Mapping Lock bit. Read only */
#define PMAPRECFG_L         (0x0002u)  /* Port Mapping re-configuration control bit */

/* PMAPCTL Control Bits */

/************************************************************
* PORT 1 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT1_MAPPING__   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_MAPPING__ 0x01C8

#define  P1MAP01_            (0x01C8u)  /* Port P1.0/1 mapping register */
DEFCW(   P1MAP01           , P1MAP01_)
#define  P1MAP23_            (0x01CAu)  /* Port P1.2/3 mapping register */
DEFCW(   P1MAP23           , P1MAP23_)
#define  P1MAP45_            (0x01CCu)  /* Port P1.4/5 mapping register */
DEFCW(   P1MAP45           , P1MAP45_)
#define  P1MAP67_            (0x01CEu)  /* Port P1.6/7 mapping register */
DEFCW(   P1MAP67           , P1MAP67_)
#define  P1MAP0              P1MAP01_L /* Port P1.0 mapping register */
#define  P1MAP1              P1MAP01_H /* Port P1.1 mapping register */
#define  P1MAP2              P1MAP23_L /* Port P1.2 mapping register */
#define  P1MAP3              P1MAP23_H /* Port P1.3 mapping register */
#define  P1MAP4              P1MAP45_L /* Port P1.4 mapping register */
#define  P1MAP5              P1MAP45_H /* Port P1.5 mapping register */
#define  P1MAP6              P1MAP67_L /* Port P1.6 mapping register */
#define  P1MAP7              P1MAP67_H /* Port P1.7 mapping register */

/************************************************************
* PORT 2 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT2_MAPPING__   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_MAPPING__ 0x01D0

#define  P2MAP01_            (0x01D0u)  /* Port P2.0/1 mapping register */
DEFCW(   P2MAP01           , P2MAP01_)
#define  P2MAP23_            (0x01D2u)  /* Port P2.2/3 mapping register */
DEFCW(   P2MAP23           , P2MAP23_)
#define  P2MAP45_            (0x01D4u)  /* Port P2.4/5 mapping register */
DEFCW(   P2MAP45           , P2MAP45_)
#define  P2MAP67_            (0x01D6u)  /* Port P2.6/7 mapping register */
DEFCW(   P2MAP67           , P2MAP67_)
#define  P2MAP0              P2MAP01_L /* Port P2.0 mapping register */
#define  P2MAP1              P2MAP01_H /* Port P2.1 mapping register */
#define  P2MAP2              P2MAP23_L /* Port P2.2 mapping register */
#define  P2MAP3              P2MAP23_H /* Port P2.3 mapping register */
#define  P2MAP4              P2MAP45_L /* Port P2.4 mapping register */
#define  P2MAP5              P2MAP45_H /* Port P2.5 mapping register */
#define  P2MAP6              P2MAP67_L /* Port P2.6 mapping register */
#define  P2MAP7              P2MAP67_H /* Port P2.7 mapping register */

/************************************************************
* PORT 3 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT3_MAPPING__   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_MAPPING__ 0x01D8

#define  P3MAP01_            (0x01D8u)  /* Port P3.0/1 mapping register */
DEFCW(   P3MAP01           , P3MAP01_)
#define  P3MAP23_            (0x01DAu)  /* Port P3.2/3 mapping register */
DEFCW(   P3MAP23           , P3MAP23_)
#define  P3MAP45_            (0x01DCu)  /* Port P3.4/5 mapping register */
DEFCW(   P3MAP45           , P3MAP45_)
#define  P3MAP67_            (0x01DEu)  /* Port P3.6/7 mapping register */
DEFCW(   P3MAP67           , P3MAP67_)
#define  P3MAP0              P3MAP01_L /* Port P3.0 mapping register */
#define  P3MAP1              P3MAP01_H /* Port P3.1 mapping register */
#define  P3MAP2              P3MAP23_L /* Port P3.2 mapping register */
#define  P3MAP3              P3MAP23_H /* Port P3.3 mapping register */
#define  P3MAP4              P3MAP45_L /* Port P3.4 mapping register */
#define  P3MAP5              P3MAP45_H /* Port P3.5 mapping register */
#define  P3MAP6              P3MAP67_L /* Port P3.6 mapping register */
#define  P3MAP7              P3MAP67_H /* Port P3.7 mapping register */

#define PM_NONE       0
#define PM_CBOUT0     1
#define PM_TA0CLK     1
#define PM_CBOUT1     2
#define PM_TA1CLK     2
#define PM_ACLK       3
#define PM_MCLK       4
#define PM_SMCLK      5
#define PM_RTCCLK     6
#define PM_MODCLK     7
#define PM_DMAE0      7
#define PM_SVMOUT     8
#define PM_TA0CCR0A   9
#define PM_TA0CCR1A   10
#define PM_TA0CCR2A   11
#define PM_TA0CCR3A   12
#define PM_TA0CCR4A   13
#define PM_TA1CCR0A   14
#define PM_TA1CCR1A   15
#define PM_TA1CCR2A   16
#define PM_UCA0RXD    17
#define PM_UCA0SOMI   17
#define PM_UCA0TXD    18
#define PM_UCA0SIMO   18
#define PM_UCA0CLK    19
#define PM_UCB0STE    19
#define PM_UCB0SOMI   20
#define PM_UCB0SCL    20
#define PM_UCB0SIMO   21
#define PM_UCB0SDA    21
#define PM_UCB0CLK    22
#define PM_UCA0STE    22
#define PM_RFGDO0     23
#define PM_RFGDO1     24
#define PM_RFGDO2     25
#define PM_ANALOG     31

/************************************************************
* PMM - Power Management System
************************************************************/
#define __MSP430_HAS_PMM__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM__ 0x0120

#define  PMMCTL0_           (0x0120u)  /* PMM Control 0 */
DEFCW(   PMMCTL0          , PMMCTL0_)
#define  PMMCTL1_           (0x0122u)  /* PMM Control 1 */
DEFCW(   PMMCTL1          , PMMCTL1_)
#define  SVSMHCTL_          (0x0124u)  /* SVS and SVM high side control register */
DEFCW(   SVSMHCTL         , SVSMHCTL_)
#define  SVSMLCTL_          (0x0126u)  /* SVS and SVM low side control register */
DEFCW(   SVSMLCTL         , SVSMLCTL_)
#define  SVSMIO_            (0x0128u)  /* SVSIN and SVSOUT control register */
DEFCW(   SVSMIO           , SVSMIO_)
#define  PMMIFG_            (0x012Cu)  /* PMM Interrupt Flag */
DEFCW(   PMMIFG           , PMMIFG_)
#define  PMMRIE_            (0x012Eu)  /* PMM and RESET Interrupt Enable */
DEFCW(   PMMRIE           , PMMRIE_)
#define  PM5CTL0_           (0x0130u)  /* PMM Power Mode 5 Control Register 0 */
DEFCW(   PM5CTL0          , PM5CTL0_)

#define PMMPW               (0xA500u)  /* PMM Register Write Password */
#define PMMPW_H             (0xA5)    /* PMM Register Write Password for high word access */

/* PMMCTL0 Control Bits */
#define PMMCOREV0           (0x0001u)  /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1           (0x0002u)  /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR            (0x0004u)  /* PMM Software BOR */
#define PMMSWPOR            (0x0008u)  /* PMM Software POR */
#define PMMREGOFF           (0x0010u)  /* PMM Turn Regulator off */
#define PMMHPMRE            (0x0080u)  /* PMM Global High Power Module Request Enable */

/* PMMCTL0 Control Bits */
#define PMMCOREV0_L         (0x0001u)  /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1_L         (0x0002u)  /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR_L          (0x0004u)  /* PMM Software BOR */
#define PMMSWPOR_L          (0x0008u)  /* PMM Software POR */
#define PMMREGOFF_L         (0x0010u)  /* PMM Turn Regulator off */
#define PMMHPMRE_L          (0x0080u)  /* PMM Global High Power Module Request Enable */

/* PMMCTL0 Control Bits */

#define PMMCOREV_0          (0x0000u)  /* PMM Core Voltage 0 (1.35V) */
#define PMMCOREV_1          (0x0001u)  /* PMM Core Voltage 1 (1.55V) */
#define PMMCOREV_2          (0x0002u)  /* PMM Core Voltage 2 (1.75V) */
#define PMMCOREV_3          (0x0003u)  /* PMM Core Voltage 3 (1.85V) */

/* PMMCTL1 Control Bits */
#define PMMREFMD            (0x0001u)  /* PMM Reference Mode */
#define PMMCMD0             (0x0010u)  /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1             (0x0020u)  /* PMM Voltage Regulator Current Mode Bit: 1 */

/* PMMCTL1 Control Bits */
#define PMMREFMD_L          (0x0001u)  /* PMM Reference Mode */
#define PMMCMD0_L           (0x0010u)  /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1_L           (0x0020u)  /* PMM Voltage Regulator Current Mode Bit: 1 */

/* PMMCTL1 Control Bits */

/* SVSMHCTL Control Bits */
#define SVSMHRRL0           (0x0001u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1           (0x0002u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2           (0x0004u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST          (0x0008u)  /* SVS and SVM high side delay status */
#define SVSHMD              (0x0010u)  /* SVS high side mode */
#define SVSMHEVM            (0x0040u)  /* SVS and SVM high side event mask */
#define SVSMHACE            (0x0080u)  /* SVS and SVM high side auto control enable */
#define SVSHRVL0            (0x0100u)  /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1            (0x0200u)  /* SVS high side reset voltage level Bit: 1 */
#define SVSHE               (0x0400u)  /* SVS high side enable */
#define SVSHFP              (0x0800u)  /* SVS high side full performace mode */
#define SVMHOVPE            (0x1000u)  /* SVM high side over-voltage enable */
#define SVMHE               (0x4000u)  /* SVM high side enable */
#define SVMHFP              (0x8000u)  /* SVM high side full performace mode */

/* SVSMHCTL Control Bits */
#define SVSMHRRL0_L         (0x0001u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1_L         (0x0002u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2_L         (0x0004u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST_L        (0x0008u)  /* SVS and SVM high side delay status */
#define SVSHMD_L            (0x0010u)  /* SVS high side mode */
#define SVSMHEVM_L          (0x0040u)  /* SVS and SVM high side event mask */
#define SVSMHACE_L          (0x0080u)  /* SVS and SVM high side auto control enable */

/* SVSMHCTL Control Bits */
#define SVSHRVL0_H          (0x0001u)  /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1_H          (0x0002u)  /* SVS high side reset voltage level Bit: 1 */
#define SVSHE_H             (0x0004u)  /* SVS high side enable */
#define SVSHFP_H            (0x0008u)  /* SVS high side full performace mode */
#define SVMHOVPE_H          (0x0010u)  /* SVM high side over-voltage enable */
#define SVMHE_H             (0x0040u)  /* SVM high side enable */
#define SVMHFP_H            (0x0080u)  /* SVM high side full performace mode */

#define SVSMHRRL_0          (0x0000u)  /* SVS and SVM high side Reset Release Voltage Level 0 */
#define SVSMHRRL_1          (0x0001u)  /* SVS and SVM high side Reset Release Voltage Level 1 */
#define SVSMHRRL_2          (0x0002u)  /* SVS and SVM high side Reset Release Voltage Level 2 */
#define SVSMHRRL_3          (0x0003u)  /* SVS and SVM high side Reset Release Voltage Level 3 */
#define SVSMHRRL_4          (0x0004u)  /* SVS and SVM high side Reset Release Voltage Level 4 */
#define SVSMHRRL_5          (0x0005u)  /* SVS and SVM high side Reset Release Voltage Level 5 */
#define SVSMHRRL_6          (0x0006u)  /* SVS and SVM high side Reset Release Voltage Level 6 */
#define SVSMHRRL_7          (0x0007u)  /* SVS and SVM high side Reset Release Voltage Level 7 */

#define SVSHRVL_0           (0x0000u)  /* SVS high side Reset Release Voltage Level 0 */
#define SVSHRVL_1           (0x0100u)  /* SVS high side Reset Release Voltage Level 1 */
#define SVSHRVL_2           (0x0200u)  /* SVS high side Reset Release Voltage Level 2 */
#define SVSHRVL_3           (0x0300u)  /* SVS high side Reset Release Voltage Level 3 */

/* SVSMLCTL Control Bits */
#define SVSMLRRL0           (0x0001u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1           (0x0002u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2           (0x0004u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST          (0x0008u)  /* SVS and SVM low side delay status */
#define SVSLMD              (0x0010u)  /* SVS low side mode */
#define SVSMLEVM            (0x0040u)  /* SVS and SVM low side event mask */
#define SVSMLACE            (0x0080u)  /* SVS and SVM low side auto control enable */
#define SVSLRVL0            (0x0100u)  /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1            (0x0200u)  /* SVS low side reset voltage level Bit: 1 */
#define SVSLE               (0x0400u)  /* SVS low side enable */
#define SVSLFP              (0x0800u)  /* SVS low side full performace mode */
#define SVMLOVPE            (0x1000u)  /* SVM low side over-voltage enable */
#define SVMLE               (0x4000u)  /* SVM low side enable */
#define SVMLFP              (0x8000u)  /* SVM low side full performace mode */

/* SVSMLCTL Control Bits */
#define SVSMLRRL0_L         (0x0001u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1_L         (0x0002u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2_L         (0x0004u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST_L        (0x0008u)  /* SVS and SVM low side delay status */
#define SVSLMD_L            (0x0010u)  /* SVS low side mode */
#define SVSMLEVM_L          (0x0040u)  /* SVS and SVM low side event mask */
#define SVSMLACE_L          (0x0080u)  /* SVS and SVM low side auto control enable */

/* SVSMLCTL Control Bits */
#define SVSLRVL0_H          (0x0001u)  /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1_H          (0x0002u)  /* SVS low side reset voltage level Bit: 1 */
#define SVSLE_H             (0x0004u)  /* SVS low side enable */
#define SVSLFP_H            (0x0008u)  /* SVS low side full performace mode */
#define SVMLOVPE_H          (0x0010u)  /* SVM low side over-voltage enable */
#define SVMLE_H             (0x0040u)  /* SVM low side enable */
#define SVMLFP_H            (0x0080u)  /* SVM low side full performace mode */

#define SVSMLRRL_0          (0x0000u)  /* SVS and SVM low side Reset Release Voltage Level 0 */
#define SVSMLRRL_1          (0x0001u)  /* SVS and SVM low side Reset Release Voltage Level 1 */
#define SVSMLRRL_2          (0x0002u)  /* SVS and SVM low side Reset Release Voltage Level 2 */
#define SVSMLRRL_3          (0x0003u)  /* SVS and SVM low side Reset Release Voltage Level 3 */
#define SVSMLRRL_4          (0x0004u)  /* SVS and SVM low side Reset Release Voltage Level 4 */
#define SVSMLRRL_5          (0x0005u)  /* SVS and SVM low side Reset Release Voltage Level 5 */
#define SVSMLRRL_6          (0x0006u)  /* SVS and SVM low side Reset Release Voltage Level 6 */
#define SVSMLRRL_7          (0x0007u)  /* SVS and SVM low side Reset Release Voltage Level 7 */

#define SVSLRVL_0           (0x0000u)  /* SVS low side Reset Release Voltage Level 0 */
#define SVSLRVL_1           (0x0100u)  /* SVS low side Reset Release Voltage Level 1 */
#define SVSLRVL_2           (0x0200u)  /* SVS low side Reset Release Voltage Level 2 */
#define SVSLRVL_3           (0x0300u)  /* SVS low side Reset Release Voltage Level 3 */

/* SVSMIO Control Bits */
#define SVMLOE              (0x0008u)  /* SVM low side output enable */
#define SVMLVLROE           (0x0010u)  /* SVM low side voltage level reached output enable */
#define SVMOUTPOL           (0x0020u)  /* SVMOUT pin polarity */
#define SVMHOE              (0x0800u)  /* SVM high side output enable */
#define SVMHVLROE           (0x1000u)  /* SVM high side voltage level reached output enable */

/* SVSMIO Control Bits */
#define SVMLOE_L            (0x0008u)  /* SVM low side output enable */
#define SVMLVLROE_L         (0x0010u)  /* SVM low side voltage level reached output enable */
#define SVMOUTPOL_L         (0x0020u)  /* SVMOUT pin polarity */

/* SVSMIO Control Bits */
#define SVMHOE_H            (0x0008u)  /* SVM high side output enable */
#define SVMHVLROE_H         (0x0010u)  /* SVM high side voltage level reached output enable */

/* PMMIFG Control Bits */
#define SVSMLDLYIFG         (0x0001u)  /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG             (0x0002u)  /* SVM low side interrupt flag */
#define SVMLVLRIFG          (0x0004u)  /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG         (0x0010u)  /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG             (0x0020u)  /* SVM high side interrupt flag */
#define SVMHVLRIFG          (0x0040u)  /* SVM high side Voltage Level Reached interrupt flag */
#define PMMBORIFG           (0x0100u)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG           (0x0200u)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG           (0x0400u)  /* PMM Software POR interrupt flag */
#define SVSHIFG             (0x1000u)  /* SVS low side interrupt flag */
#define SVSLIFG             (0x2000u)  /* SVS high side interrupt flag */
#define PMMLPM5IFG          (0x8000u)  /* LPM5 indication Flag */

/* PMMIFG Control Bits */
#define SVSMLDLYIFG_L       (0x0001u)  /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG_L           (0x0002u)  /* SVM low side interrupt flag */
#define SVMLVLRIFG_L        (0x0004u)  /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG_L       (0x0010u)  /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG_L           (0x0020u)  /* SVM high side interrupt flag */
#define SVMHVLRIFG_L        (0x0040u)  /* SVM high side Voltage Level Reached interrupt flag */

/* PMMIFG Control Bits */
#define PMMBORIFG_H         (0x0001u)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H         (0x0002u)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H         (0x0004u)  /* PMM Software POR interrupt flag */
#define SVSHIFG_H           (0x0010u)  /* SVS low side interrupt flag */
#define SVSLIFG_H           (0x0020u)  /* SVS high side interrupt flag */
#define PMMLPM5IFG_H        (0x0080u)  /* LPM5 indication Flag */

#define PMMRSTLPM5IFG       PMMLPM5IFG /* LPM5 indication Flag */

/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE          (0x0001u)  /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE              (0x0002u)  /* SVM low side interrupt enable */
#define SVMLVLRIE           (0x0004u)  /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE          (0x0010u)  /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE              (0x0020u)  /* SVM high side interrupt enable */
#define SVMHVLRIE           (0x0040u)  /* SVM high side Voltage Level Reached interrupt enable */
#define SVSLPE              (0x0100u)  /* SVS low side POR enable */
#define SVMLVLRPE           (0x0200u)  /* SVM low side Voltage Level reached POR enable */
#define SVSHPE              (0x1000u)  /* SVS high side POR enable */
#define SVMHVLRPE           (0x2000u)  /* SVM high side Voltage Level reached POR enable */

/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE_L        (0x0001u)  /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE_L            (0x0002u)  /* SVM low side interrupt enable */
#define SVMLVLRIE_L         (0x0004u)  /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE_L        (0x0010u)  /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE_L            (0x0020u)  /* SVM high side interrupt enable */
#define SVMHVLRIE_L         (0x0040u)  /* SVM high side Voltage Level Reached interrupt enable */

/* PMMIE and RESET Control Bits */
#define SVSLPE_H            (0x0001u)  /* SVS low side POR enable */
#define SVMLVLRPE_H         (0x0002u)  /* SVM low side Voltage Level reached POR enable */
#define SVSHPE_H            (0x0010u)  /* SVS high side POR enable */
#define SVMHVLRPE_H         (0x0020u)  /* SVM high side Voltage Level reached POR enable */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5            (0x0001u)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5_L          (0x0001u)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKIO              LOCKLPM5  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/*************************************************************
* RAM Control Module
*************************************************************/
#define __MSP430_HAS_RC__             /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RC__ 0x0158

#define  RCCTL0_             (0x0158u)  /* Ram Controller Control Register */
DEFCW(   RCCTL0            , RCCTL0_)

/* RCCTL0 Control Bits */
#define RCRS0OFF            (0x0001u)  /* RAM Controller RAM Sector 0 Off */
#define RCRS1OFF            (0x0002u)  /* RAM Controller RAM Sector 1 Off */
#define RCRS2OFF            (0x0004u)  /* RAM Controller RAM Sector 2 Off */
#define RCRS3OFF            (0x0008u)  /* RAM Controller RAM Sector 3 Off */

/* RCCTL0 Control Bits */
#define RCRS0OFF_L          (0x0001u)  /* RAM Controller RAM Sector 0 Off */
#define RCRS1OFF_L          (0x0002u)  /* RAM Controller RAM Sector 1 Off */
#define RCRS2OFF_L          (0x0004u)  /* RAM Controller RAM Sector 2 Off */
#define RCRS3OFF_L          (0x0008u)  /* RAM Controller RAM Sector 3 Off */

/* RCCTL0 Control Bits */

#define RCKEY               (0x5A00u)

/************************************************************
* Shared Reference
************************************************************/
#define __MSP430_HAS_REF__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_REF__ 0x01B0

#define  REFCTL0_            (0x01B0u)  /* REF Shared Reference control register 0 */
DEFCW(   REFCTL0           , REFCTL0_)

/* REFCTL0 Control Bits */
#define REFON               (0x0001u)  /* REF Reference On */
#define REFOUT              (0x0002u)  /* REF Reference output Buffer On */
//#define RESERVED            (0x0004u)  /* Reserved */
#define REFTCOFF            (0x0008u)  /* REF Temp.Sensor off */
#define REFVSEL0            (0x0010u)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1            (0x0020u)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040u)  /* Reserved */
#define REFMSTR             (0x0080u)  /* REF Master Control */
#define REFGENACT           (0x0100u)  /* REF Reference generator active */
#define REFBGACT            (0x0200u)  /* REF Reference bandgap active */
#define REFGENBUSY          (0x0400u)  /* REF Reference generator busy */
#define BGMODE              (0x0800u)  /* REF Bandgap mode */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

/* REFCTL0 Control Bits */
#define REFON_L             (0x0001u)  /* REF Reference On */
#define REFOUT_L            (0x0002u)  /* REF Reference output Buffer On */
//#define RESERVED            (0x0004u)  /* Reserved */
#define REFTCOFF_L          (0x0008u)  /* REF Temp.Sensor off */
#define REFVSEL0_L          (0x0010u)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1_L          (0x0020u)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040u)  /* Reserved */
#define REFMSTR_L           (0x0080u)  /* REF Master Control */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

/* REFCTL0 Control Bits */
//#define RESERVED            (0x0004u)  /* Reserved */
//#define RESERVED            (0x0040u)  /* Reserved */
#define REFGENACT_H         (0x0001u)  /* REF Reference generator active */
#define REFBGACT_H          (0x0002u)  /* REF Reference bandgap active */
#define REFGENBUSY_H        (0x0004u)  /* REF Reference generator busy */
#define BGMODE_H            (0x0008u)  /* REF Bandgap mode */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

#define REFVSEL_0           (0x0000u)  /* REF Reference Voltage Level Select 1.5V */
#define REFVSEL_1           (0x0010u)  /* REF Reference Voltage Level Select 2.0V */
#define REFVSEL_2           (0x0020u)  /* REF Reference Voltage Level Select 2.5V */
#define REFVSEL_3           (0x0030u)  /* REF Reference Voltage Level Select 2.5V */

/************************************************************
* Real Time Clock
************************************************************/
#define __MSP430_HAS_RTC_D__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC_D__ 0x04A0

#define RTCCTL01_           (0x04A0u)  /* Real Timer Control 0/1 */
DEFCW(  RTCCTL01          , RTCCTL01_)
#define RTCCTL23_           (0x04A2u)  /* Real Timer Control 2/3 */
DEFCW(  RTCCTL23          , RTCCTL23_)
#define RTCPS0CTL_          (0x04A8u)  /* Real Timer Prescale Timer 0 Control */
DEFCW(  RTCPS0CTL         , RTCPS0CTL_)
#define RTCPS1CTL_          (0x04AAu)  /* Real Timer Prescale Timer 1 Control */
DEFCW(  RTCPS1CTL         , RTCPS1CTL_)
#define RTCPS_              (0x04ACu)  /* Real Timer Prescale Timer Control */
DEFCW(  RTCPS             , RTCPS_)
#define RTCIV_              (0x04AEu)  /* Real Time Clock Interrupt Vector */
DEFW(   RTCIV             , RTCIV_)
#define RTCTIM0_            (0x04B0u)  /* Real Time Clock Time 0 */
DEFCW(  RTCTIM0           , RTCTIM0_)
#define RTCTIM1_            (0x04B2u)  /* Real Time Clock Time 1 */
DEFCW(  RTCTIM1           , RTCTIM1_)
#define RTCDATE_            (0x04B4u)  /* Real Time Clock Date */
DEFCW(  RTCDATE           , RTCDATE_)
#define RTCYEAR_            (0x04B6u)  /* Real Time Clock Year */
DEFCW(  RTCYEAR           , RTCYEAR_)
#define RTCAMINHR_          (0x04B8u)  /* Real Time Clock Alarm Min/Hour */
DEFCW(  RTCAMINHR         , RTCAMINHR_)
#define RTCADOWDAY_         (0x04BAu)  /* Real Time Clock Alarm day of week/day */
DEFCW(  RTCADOWDAY        , RTCADOWDAY_)
#define BIN2BCD_            (0x04BCu)  /* Real Time Binary-to-BCD conversion register */
DEFW(   BIN2BCD           , BIN2BCD_)
#define BCD2BIN_            (0x04BEu)  /* Real Time BCD-to-binary conversion register */
DEFW(   BCD2BIN           , BCD2BIN_)

#define RTCCTL0             RTCCTL01_L  /* Real Time Clock Control 0 */
#define RTCCTL1             RTCCTL01_H  /* Real Time Clock Control 1 */
#define RTCCTL2             RTCCTL23_L  /* Real Time Clock Control 2 */
#define RTCCTL3             RTCCTL23_H  /* Real Time Clock Control 3 */
#define RTCNT12             RTCTIM0
#define RTCNT34             RTCTIM1
#define RTCNT1              RTCTIM0_L
#define RTCNT2              RTCTIM0_H
#define RTCNT3              RTCTIM1_L
#define RTCNT4              RTCTIM1_H
#define RTCSEC              RTCTIM0_L
#define RTCMIN              RTCTIM0_H
#define RTCHOUR             RTCTIM1_L
#define RTCDOW              RTCTIM1_H
#define RTCDAY              RTCDATE_L
#define RTCMON              RTCDATE_H
#define RTCYEARL            RTCYEAR_L
#define RTCYEARH            RTCYEAR_H
#define RT0PS               RTCPS_L
#define RT1PS               RTCPS_H
#define RTCAMIN             RTCAMINHR_L  /* Real Time Clock Alarm Min */
#define RTCAHOUR            RTCAMINHR_H  /* Real Time Clock Alarm Hour */
#define RTCADOW             RTCADOWDAY_L /* Real Time Clock Alarm day of week */
#define RTCADAY             RTCADOWDAY_H /* Real Time Clock Alarm day */

/* RTCCTL01 Control Bits */
#define RTCBCD              (0x8000u)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD             (0x4000u)     /* RTC Hold */
#define RTCMODE             (0x2000u)     /* RTC Mode 0:Counter / 1: Calendar */
#define RTCRDY              (0x1000u)     /* RTC Ready */
#define RTCSSEL1            (0x0800u)     /* RTC Source Select 1 */
#define RTCSSEL0            (0x0400u)     /* RTC Source Select 0 */
#define RTCTEV1             (0x0200u)     /* RTC Time Event 1 */
#define RTCTEV0             (0x0100u)     /* RTC Time Event 0 */
#define RTCOFIE             (0x0080u)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE            (0x0040u)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE              (0x0020u)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE            (0x0010u)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG            (0x0008u)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG           (0x0004u)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG             (0x0002u)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG           (0x0001u)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
#define RTCOFIE_L           (0x0080u)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE_L          (0x0040u)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE_L            (0x0020u)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE_L          (0x0010u)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG_L          (0x0008u)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG_L         (0x0004u)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG_L           (0x0002u)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG_L         (0x0001u)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
#define RTCBCD_H            (0x0080u)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD_H           (0x0040u)     /* RTC Hold */
#define RTCMODE_H           (0x0020u)     /* RTC Mode 0:Counter / 1: Calendar */
#define RTCRDY_H            (0x0010u)     /* RTC Ready */
#define RTCSSEL1_H          (0x0008u)     /* RTC Source Select 1 */
#define RTCSSEL0_H          (0x0004u)     /* RTC Source Select 0 */
#define RTCTEV1_H           (0x0002u)     /* RTC Time Event 1 */
#define RTCTEV0_H           (0x0001u)     /* RTC Time Event 0 */

#define RTCSSEL_0           (0x0000u)     /* RTC Source Select ACLK */
#define RTCSSEL_1           (0x0400u)     /* RTC Source Select SMCLK */
#define RTCSSEL_2           (0x0800u)     /* RTC Source Select RT1PS */
#define RTCSSEL_3           (0x0C00u)     /* RTC Source Select RT1PS */
#define RTCSSEL__ACLK       (0x0000u)     /* RTC Source Select ACLK */
#define RTCSSEL__SMCLK      (0x0400u)     /* RTC Source Select SMCLK */
#define RTCSSEL__RT1PS      (0x0800u)     /* RTC Source Select RT1PS */
#define RTCTEV_0            (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200u)     /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300u)     /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__0000        (0x0200u)     /* RTC Time Event: 2 (00:00 changed) */
#define RTCTEV__1200        (0x0300u)     /* RTC Time Event: 3 (12:00 changed) */

/* RTCCTL23 Control Bits */
#define RTCCALF1            (0x0200u)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0            (0x0100u)     /* RTC Calibration Frequency Bit 0 */
#define RTCCALS             (0x0080u)     /* RTC Calibration Sign */
//#define Reserved          (0x0040u)
#define RTCCAL5             (0x0020u)     /* RTC Calibration Bit 5 */
#define RTCCAL4             (0x0010u)     /* RTC Calibration Bit 4 */
#define RTCCAL3             (0x0008u)     /* RTC Calibration Bit 3 */
#define RTCCAL2             (0x0004u)     /* RTC Calibration Bit 2 */
#define RTCCAL1             (0x0002u)     /* RTC Calibration Bit 1 */
#define RTCCAL0             (0x0001u)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALS_L           (0x0080u)     /* RTC Calibration Sign */
//#define Reserved          (0x0040u)
#define RTCCAL5_L           (0x0020u)     /* RTC Calibration Bit 5 */
#define RTCCAL4_L           (0x0010u)     /* RTC Calibration Bit 4 */
#define RTCCAL3_L           (0x0008u)     /* RTC Calibration Bit 3 */
#define RTCCAL2_L           (0x0004u)     /* RTC Calibration Bit 2 */
#define RTCCAL1_L           (0x0002u)     /* RTC Calibration Bit 1 */
#define RTCCAL0_L           (0x0001u)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALF1_H          (0x0002u)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0_H          (0x0001u)     /* RTC Calibration Frequency Bit 0 */
//#define Reserved          (0x0040u)

#define RTCCALF_0           (0x0000u)     /* RTC Calibration Frequency: No Output */
#define RTCCALF_1           (0x0100u)     /* RTC Calibration Frequency: 512 Hz */
#define RTCCALF_2           (0x0200u)     /* RTC Calibration Frequency: 256 Hz */
#define RTCCALF_3           (0x0300u)     /* RTC Calibration Frequency: 1 Hz */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000u)
//#define Reserved          (0x4000u)
#define RT0PSDIV2           (0x2000u)     /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
#define RT0PSDIV1           (0x1000u)     /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
#define RT0PSDIV0           (0x0800u)     /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
#define RT0PSHOLD           (0x0100u)     /* RTC Prescale Timer 0 Hold */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT0IP2              (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1              (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0              (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE             (0x0002u)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG            (0x0001u)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000u)
//#define Reserved          (0x4000u)
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT0IP2_L            (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1_L            (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0_L            (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE_L           (0x0002u)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG_L          (0x0001u)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000u)
//#define Reserved          (0x4000u)
#define RT0PSDIV2_H         (0x0020u)     /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
#define RT0PSDIV1_H         (0x0010u)     /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
#define RT0PSDIV0_H         (0x0008u)     /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
#define RT0PSHOLD_H         (0x0001u)     /* RTC Prescale Timer 0 Hold */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)

#define RT0IP_0             (0x0000u)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000Cu)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014u)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018u)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001Cu)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0PSDIV_0          (0x0000u)     /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1          (0x0800u)     /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2          (0x1000u)     /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3          (0x1800u)     /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4          (0x2000u)     /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5          (0x2800u)     /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6          (0x3000u)     /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7          (0x3800u)     /* RTC Prescale Timer 0 Clock Divide /256 */

/* RTCPS1CTL Control Bits */
#define RT1SSEL1            (0x8000u)     /* RTC Prescale Timer 1 Source Select Bit 1 */
#define RT1SSEL0            (0x4000u)     /* RTC Prescale Timer 1 Source Select Bit 0 */
#define RT1PSDIV2           (0x2000u)     /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
#define RT1PSDIV1           (0x1000u)     /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
#define RT1PSDIV0           (0x0800u)     /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
#define RT1PSHOLD           (0x0100u)     /* RTC Prescale Timer 1 Hold */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT1IP2              (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1              (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0              (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE             (0x0002u)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG            (0x0001u)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT1IP2_L            (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1_L            (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0_L            (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE_L           (0x0002u)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG_L          (0x0001u)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
#define RT1SSEL1_H          (0x0080u)     /* RTC Prescale Timer 1 Source Select Bit 1 */
#define RT1SSEL0_H          (0x0040u)     /* RTC Prescale Timer 1 Source Select Bit 0 */
#define RT1PSDIV2_H         (0x0020u)     /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
#define RT1PSDIV1_H         (0x0010u)     /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
#define RT1PSDIV0_H         (0x0008u)     /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
//#define Reserved          (0x0400u)
//#define Reserved          (0x0200u)
#define RT1PSHOLD_H         (0x0001u)     /* RTC Prescale Timer 1 Hold */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)

#define RT1IP_0             (0x0000u)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000Cu)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014u)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018u)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001Cu)     /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1PSDIV_0          (0x0000u)     /* RTC Prescale Timer 1 Clock Divide /2 */
#define RT1PSDIV_1          (0x0800u)     /* RTC Prescale Timer 1 Clock Divide /4 */
#define RT1PSDIV_2          (0x1000u)     /* RTC Prescale Timer 1 Clock Divide /8 */
#define RT1PSDIV_3          (0x1800u)     /* RTC Prescale Timer 1 Clock Divide /16 */
#define RT1PSDIV_4          (0x2000u)     /* RTC Prescale Timer 1 Clock Divide /32 */
#define RT1PSDIV_5          (0x2800u)     /* RTC Prescale Timer 1 Clock Divide /64 */
#define RT1PSDIV_6          (0x3000u)     /* RTC Prescale Timer 1 Clock Divide /128 */
#define RT1PSDIV_7          (0x3800u)     /* RTC Prescale Timer 1 Clock Divide /256 */

#define RT1SSEL_0           (0x0000u)     /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL_1           (0x4000u)     /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL_2           (0x8000u)     /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL_3           (0xC000u)     /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL__ACLK       (0x0000u)     /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL__SMCLK      (0x4000u)     /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL__RT0PS      (0x8000u)     /* RTC Prescale Timer Source Select RT0PS */

/* RTC Definitions */
#define RTCIV_NONE           (0x0000u)    /* No Interrupt pending */
#define RTCIV_RTCRDYIFG      (0x0002u)    /* RTC ready: RTCRDYIFG */
#define RTCIV_RTCTEVIFG      (0x0004u)    /* RTC interval timer: RTCTEVIFG */
#define RTCIV_RTCAIFG        (0x0006u)    /* RTC user alarm: RTCAIFG */
#define RTCIV_RT0PSIFG       (0x0008u)    /* RTC prescaler 0: RT0PSIFG */
#define RTCIV_RT1PSIFG       (0x000Au)    /* RTC prescaler 1: RT1PSIFG */
#define RTCIV_RTCOFIFG       (0x000Cu)    /* RTC Oscillator fault */

/* Legacy Definitions */
#define RTC_NONE           (0x0000u)      /* No Interrupt pending */
#define RTC_RTCRDYIFG      (0x0002u)      /* RTC ready: RTCRDYIFG */
#define RTC_RTCTEVIFG      (0x0004u)      /* RTC interval timer: RTCTEVIFG */
#define RTC_RTCAIFG        (0x0006u)      /* RTC user alarm: RTCAIFG */
#define RTC_RT0PSIFG       (0x0008u)      /* RTC prescaler 0: RT0PSIFG */
#define RTC_RT1PSIFG       (0x000Au)      /* RTC prescaler 1: RT1PSIFG */
#define RTC_RTCOFIFG       (0x000Cu)      /* RTC Oscillator fault */


/************************************************************
* SFR - Special Function Register Module
************************************************************/
#define __MSP430_HAS_SFR__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100

#define  SFRIE1_             (0x0100u)  /* Interrupt Enable 1 */
DEFCW(   SFRIE1            , SFRIE1_)

/* SFRIE1 Control Bits */
#define WDTIE               (0x0001u)  /* WDT Interrupt Enable */
#define OFIE                (0x0002u)  /* Osc Fault Enable */
//#define Reserved          (0x0004u)
#define VMAIE               (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE               (0x0010u)  /* NMI Interrupt Enable */
#define ACCVIE              (0x0020u)  /* Flash Access Violation Interrupt Enable */
#define JMBINIE             (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE            (0x0080u)  /* JTAG Mail Box output Interrupt Enable */

#define WDTIE_L             (0x0001u)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002u)  /* Osc Fault Enable */
//#define Reserved          (0x0004u)
#define VMAIE_L             (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010u)  /* NMI Interrupt Enable */
#define ACCVIE_L            (0x0020u)  /* Flash Access Violation Interrupt Enable */
#define JMBINIE_L           (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080u)  /* JTAG Mail Box output Interrupt Enable */

//#define Reserved          (0x0004u)

#define  SFRIFG1_            (0x0102u)  /* Interrupt Flag 1 */
DEFCW(   SFRIFG1           , SFRIFG1_)
/* SFRIFG1 Control Bits */
#define WDTIFG              (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG               (0x0002u)  /* Osc Fault Flag */
//#define Reserved          (0x0004u)
#define VMAIFG              (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG              (0x0010u)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020u)
#define JMBINIFG            (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG           (0x0080u)  /* JTAG Mail Box output Interrupt Flag */

#define WDTIFG_L            (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG_L             (0x0002u)  /* Osc Fault Flag */
//#define Reserved          (0x0004u)
#define VMAIFG_L            (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG_L            (0x0010u)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020u)
#define JMBINIFG_L          (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L         (0x0080u)  /* JTAG Mail Box output Interrupt Flag */

//#define Reserved          (0x0004u)
//#define Reserved          (0x0020u)

#define  SFRRPCR_            (0x0104u)  /* RESET Pin Control Register */
DEFCW(   SFRRPCR           , SFRRPCR_)
/* SFRRPCR Control Bits */
#define SYSNMI              (0x0001u)  /* NMI select */
#define SYSNMIIES           (0x0002u)  /* NMI edge select */
#define SYSRSTUP            (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE            (0x0008u)  /* RESET Pin Resistor enable */

#define SYSNMI_L            (0x0001u)  /* NMI select */
#define SYSNMIIES_L         (0x0002u)  /* NMI edge select */
#define SYSRSTUP_L          (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE_L          (0x0008u)  /* RESET Pin Resistor enable */

/************************************************************
* SYS - System Module
************************************************************/
#define __MSP430_HAS_SYS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0180

#define  SYSCTL_             (0x0180u)  /* System control */
DEFCW(   SYSCTL            , SYSCTL_)
#define  SYSBSLC_            (0x0182u)  /* Boot strap configuration area */
DEFCW(   SYSBSLC           , SYSBSLC_)
#define  SYSJMBC_            (0x0186u)  /* JTAG mailbox control */
DEFCW(   SYSJMBC           , SYSJMBC_)
#define  SYSJMBI0_           (0x0188u)  /* JTAG mailbox input 0 */
DEFCW(   SYSJMBI0          , SYSJMBI0_)
#define  SYSJMBI1_           (0x018Au)  /* JTAG mailbox input 1 */
DEFCW(   SYSJMBI1          , SYSJMBI1_)
#define  SYSJMBO0_           (0x018Cu)  /* JTAG mailbox output 0 */
DEFCW(   SYSJMBO0          , SYSJMBO0_)
#define  SYSJMBO1_           (0x018Eu)  /* JTAG mailbox output 1 */
DEFCW(   SYSJMBO1          , SYSJMBO1_)

#define  SYSBERRIV_          (0x0198u)  /* Bus Error vector generator */
DEFCW(   SYSBERRIV         , SYSBERRIV_)
#define  SYSUNIV_            (0x019Au)  /* User NMI vector generator */
DEFCW(   SYSUNIV           , SYSUNIV_)
#define  SYSSNIV_            (0x019Cu)  /* System NMI vector generator */
DEFCW(   SYSSNIV           , SYSSNIV_)
#define  SYSRSTIV_           (0x019Eu)  /* Reset vector generator */
DEFCW(   SYSRSTIV          , SYSRSTIV_)

/* SYSCTL Control Bits */
#define SYSRIVECT           (0x0001u)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SYSPMMPE            (0x0004u)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
#define SYSBSLIND           (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN          (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCTL Control Bits */
#define SYSRIVECT_L         (0x0001u)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SYSPMMPE_L          (0x0004u)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
#define SYSBSLIND_L         (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L        (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCTL Control Bits */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0         (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1         (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR             (0x0004u)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
#define SYSBSLOFF           (0x4000u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE            (0x8000u)  /* SYS - BSL Memory protection enabled */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L       (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L       (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L           (0x0004u)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
#define SYSBSLOFF_H         (0x0040u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE_H          (0x0080u)  /* SYS - BSL Memory protection enabled */

/* SYSJMBC Control Bits */
#define JMBIN0FG            (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG            (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG           (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG           (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE             (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
#define JMBCLR0OFF          (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF          (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
#define JMBIN0FG_L          (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L          (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L         (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L         (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L           (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
#define JMBCLR0OFF_L        (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L        (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002u)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004u)    /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_ACCVIFG    (0x0006u)    /* SYSUNIV : Access Violation - ACCVIFG */
#define SYSUNIV_SYSBERRIV  (0x0008u)    /* SYSUNIV : Bus Error - SYSBERRIV */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSSNIV_SVMLIFG    (0x0002u)    /* SYSSNIV : SVMLIFG */
#define SYSSNIV_SVMHIFG    (0x0004u)    /* SYSSNIV : SVMHIFG */
#define SYSSNIV_DLYLIFG    (0x0006u)    /* SYSSNIV : DLYLIFG */
#define SYSSNIV_DLYHIFG    (0x0008u)    /* SYSSNIV : DLYHIFG */
#define SYSSNIV_VMAIFG     (0x000Au)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x000Cu)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x000Eu)    /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_VLRLIFG    (0x0010u)    /* SYSSNIV : VLRLIFG */
#define SYSSNIV_VLRHIFG    (0x0012u)    /* SYSSNIV : VLRHIFG */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000u)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002u)    /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI    (0x0004u)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0006u)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU    (0x0008u)    /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV     (0x000Au)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSL      (0x000Cu)    /* SYSRSTIV : SVSL */
#define SYSRSTIV_SVSH      (0x000Eu)    /* SYSRSTIV : SVSH */
#define SYSRSTIV_SVML_OVP  (0x0010u)    /* SYSRSTIV : SVML_OVP */
#define SYSRSTIV_SVMH_OVP  (0x0012u)    /* SYSRSTIV : SVMH_OVP */
#define SYSRSTIV_DOPOR     (0x0014u)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x0016u)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0018u)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_KEYV      (0x001Au)    /* SYSRSTIV : Flash Key violation */
#define SYSRSTIV_PLLUL     (0x001Cu)    /* SYSRSTIV : PLL unlock */
#define SYSRSTIV_PERF      (0x001Eu)    /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMKEY    (0x0020u)    /* SYSRSTIV : PMMKEY violation */

#define SYSRSTIV_PSSKEY    (0x0020u)    /* SYSRSTIV : Legacy: PMMKEY violation */

/************************************************************
* Timer0_A5
************************************************************/
#define __MSP430_HAS_T0A5__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A5__ 0x0340

#define  TA0CTL_             (0x0340u)  /* Timer0_A5 Control */
DEFW(    TA0CTL            , TA0CTL_)
#define  TA0CCTL0_           (0x0342u)  /* Timer0_A5 Capture/Compare Control 0 */
DEFW(    TA0CCTL0          , TA0CCTL0_)
#define  TA0CCTL1_           (0x0344u)  /* Timer0_A5 Capture/Compare Control 1 */
DEFW(    TA0CCTL1          , TA0CCTL1_)
#define  TA0CCTL2_           (0x0346u)  /* Timer0_A5 Capture/Compare Control 2 */
DEFW(    TA0CCTL2          , TA0CCTL2_)
#define  TA0CCTL3_           (0x0348u)  /* Timer0_A5 Capture/Compare Control 3 */
DEFW(    TA0CCTL3          , TA0CCTL3_)
#define  TA0CCTL4_           (0x034Au)  /* Timer0_A5 Capture/Compare Control 4 */
DEFW(    TA0CCTL4          , TA0CCTL4_)
#define  TA0R_               (0x0350u)  /* Timer0_A5 */
DEFW(    TA0R              , TA0R_)
#define  TA0CCR0_            (0x0352u)  /* Timer0_A5 Capture/Compare 0 */
DEFW(    TA0CCR0           , TA0CCR0_)
#define  TA0CCR1_            (0x0354u)  /* Timer0_A5 Capture/Compare 1 */
DEFW(    TA0CCR1           , TA0CCR1_)
#define  TA0CCR2_            (0x0356u)  /* Timer0_A5 Capture/Compare 2 */
DEFW(    TA0CCR2           , TA0CCR2_)
#define  TA0CCR3_            (0x0358u)  /* Timer0_A5 Capture/Compare 3 */
DEFW(    TA0CCR3           , TA0CCR3_)
#define  TA0CCR4_            (0x035Au)  /* Timer0_A5 Capture/Compare 4 */
DEFW(    TA0CCR4           , TA0CCR4_)
#define  TA0IV_              (0x036Eu)  /* Timer0_A5 Interrupt Vector Word */
DEFW(    TA0IV             , TA0IV_)
#define  TA0EX0_             (0x0360u)  /* Timer0_A5 Expansion Register 0 */
DEFW(    TA0EX0            , TA0EX0_)

/* TAxCTL Control Bits */
#define TASSEL1             (0x0200u)  /* Timer A clock source select 1 */
#define TASSEL0             (0x0100u)  /* Timer A clock source select 0 */
#define ID1                 (0x0080u)  /* Timer A clock input divider 1 */
#define ID0                 (0x0040u)  /* Timer A clock input divider 0 */
#define MC1                 (0x0020u)  /* Timer A mode control 1 */
#define MC0                 (0x0010u)  /* Timer A mode control 0 */
#define TACLR               (0x0004u)  /* Timer A counter clear */
#define TAIE                (0x0002u)  /* Timer A counter interrupt enable */
#define TAIFG               (0x0001u)  /* Timer A counter interrupt flag */

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */
#define MC__STOP            (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC__UP              (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINOUS       (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC__UPDOWN          (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID__1               (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID__2               (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID__4               (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID__8               (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK       (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK        (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK       (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK       (3*0x100u) /* Timer A clock source select: 3 - INCLK */

/* TAxCCTLx Control Bits */
#define CM1                 (0x8000u)  /* Capture mode 1 */
#define CM0                 (0x4000u)  /* Capture mode 0 */
#define CCIS1               (0x2000u)  /* Capture input select 1 */
#define CCIS0               (0x1000u)  /* Capture input select 0 */
#define SCS                 (0x0800u)  /* Capture sychronize */
#define SCCI                (0x0400u)  /* Latched capture signal (read) */
#define CAP                 (0x0100u)  /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2             (0x0080u)  /* Output mode 2 */
#define OUTMOD1             (0x0040u)  /* Output mode 1 */
#define OUTMOD0             (0x0020u)  /* Output mode 0 */
#define CCIE                (0x0010u)  /* Capture/compare interrupt enable */
#define CCI                 (0x0008u)  /* Capture input signal (read) */
#define OUT                 (0x0004u)  /* PWM Output signal if output mode 0 */
#define COV                 (0x0002u)  /* Capture/compare overflow flag */
#define CCIFG               (0x0001u)  /* Capture/compare interrupt flag */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */

/* TAxEX0 Control Bits */
#define TAIDEX0             (0x0001u)  /* Timer A Input divider expansion Bit: 0 */
#define TAIDEX1             (0x0002u)  /* Timer A Input divider expansion Bit: 1 */
#define TAIDEX2             (0x0004u)  /* Timer A Input divider expansion Bit: 2 */

#define TAIDEX_0            (0*0x0001u) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (1*0x0001u) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (2*0x0001u) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (3*0x0001u) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (4*0x0001u) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (5*0x0001u) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (6*0x0001u) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (7*0x0001u) /* Timer A Input divider expansion : /8 */

/* T0A5IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TA0CCR1       (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2       (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_TA0CCR3       (0x0006u)    /* TA0CCR3_CCIFG */
#define TA0IV_TA0CCR4       (0x0008u)    /* TA0CCR4_CCIFG */
#define TA0IV_5             (0x000Au)    /* Reserved */
#define TA0IV_6             (0x000Cu)    /* Reserved */
#define TA0IV_TA0IFG        (0x000Eu)    /* TA0IFG */

/************************************************************
* Timer1_A3
************************************************************/
#define __MSP430_HAS_T1A3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0380

#define  TA1CTL_             (0x0380u)  /* Timer1_A3 Control */
DEFW(    TA1CTL            , TA1CTL_)
#define  TA1CCTL0_           (0x0382u)  /* Timer1_A3 Capture/Compare Control 0 */
DEFW(    TA1CCTL0          , TA1CCTL0_)
#define  TA1CCTL1_           (0x0384u)  /* Timer1_A3 Capture/Compare Control 1 */
DEFW(    TA1CCTL1          , TA1CCTL1_)
#define  TA1CCTL2_           (0x0386u)  /* Timer1_A3 Capture/Compare Control 2 */
DEFW(    TA1CCTL2          , TA1CCTL2_)
#define  TA1R_               (0x0390u)  /* Timer1_A3 */
DEFW(    TA1R              , TA1R_)
#define  TA1CCR0_            (0x0392u)  /* Timer1_A3 Capture/Compare 0 */
DEFW(    TA1CCR0           , TA1CCR0_)
#define  TA1CCR1_            (0x0394u)  /* Timer1_A3 Capture/Compare 1 */
DEFW(    TA1CCR1           , TA1CCR1_)
#define  TA1CCR2_            (0x0396u)  /* Timer1_A3 Capture/Compare 2 */
DEFW(    TA1CCR2           , TA1CCR2_)
#define  TA1IV_              (0x03AEu)  /* Timer1_A3 Interrupt Vector Word */
DEFW(    TA1IV             , TA1IV_)
#define  TA1EX0_             (0x03A0u)  /* Timer1_A3 Expansion Register 0 */
DEFW(    TA1EX0            , TA1EX0_)

/* Bits are already defined within the Timer0_Ax */

/* TA1IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TA1CCR1       (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2       (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_3             (0x0006u)    /* Reserved */
#define TA1IV_4             (0x0008u)    /* Reserved */
#define TA1IV_5             (0x000Au)    /* Reserved */
#define TA1IV_6             (0x000Cu)    /* Reserved */
#define TA1IV_TA1IFG        (0x000Eu)    /* TA1IFG */

/************************************************************
* UNIFIED CLOCK SYSTEM FOR Radio Devices
************************************************************/
#define __MSP430_HAS_UCS_RF__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_UCS_RF__ 0x0160

#define  UCSCTL0_            (0x0160u)  /* UCS Control Register 0 */
DEFCW(   UCSCTL0           , UCSCTL0_)
#define  UCSCTL1_            (0x0162u)  /* UCS Control Register 1 */
DEFCW(   UCSCTL1           , UCSCTL1_)
#define  UCSCTL2_            (0x0164u)  /* UCS Control Register 2 */
DEFCW(   UCSCTL2           , UCSCTL2_)
#define  UCSCTL3_            (0x0166u)  /* UCS Control Register 3 */
DEFCW(   UCSCTL3           , UCSCTL3_)
#define  UCSCTL4_            (0x0168u)  /* UCS Control Register 4 */
DEFCW(   UCSCTL4           , UCSCTL4_)
#define  UCSCTL5_            (0x016Au)  /* UCS Control Register 5 */
DEFCW(   UCSCTL5           , UCSCTL5_)
#define  UCSCTL6_            (0x016Cu)  /* UCS Control Register 6 */
DEFCW(   UCSCTL6           , UCSCTL6_)
#define  UCSCTL7_            (0x016Eu)  /* UCS Control Register 7 */
DEFCW(   UCSCTL7           , UCSCTL7_)
#define  UCSCTL8_            (0x0170u)  /* UCS Control Register 8 */
DEFCW(   UCSCTL8           , UCSCTL8_)

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001u)    /* RESERVED */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
#define MOD0                (0x0008u)    /* Modulation Bit Counter Bit : 0 */
#define MOD1                (0x0010u)    /* Modulation Bit Counter Bit : 1 */
#define MOD2                (0x0020u)    /* Modulation Bit Counter Bit : 2 */
#define MOD3                (0x0040u)    /* Modulation Bit Counter Bit : 3 */
#define MOD4                (0x0080u)    /* Modulation Bit Counter Bit : 4 */
#define DCO0                (0x0100u)    /* DCO TAP Bit : 0 */
#define DCO1                (0x0200u)    /* DCO TAP Bit : 1 */
#define DCO2                (0x0400u)    /* DCO TAP Bit : 2 */
#define DCO3                (0x0800u)    /* DCO TAP Bit : 3 */
#define DCO4                (0x1000u)    /* DCO TAP Bit : 4 */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001u)    /* RESERVED */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
#define MOD0_L              (0x0008u)    /* Modulation Bit Counter Bit : 0 */
#define MOD1_L              (0x0010u)    /* Modulation Bit Counter Bit : 1 */
#define MOD2_L              (0x0020u)    /* Modulation Bit Counter Bit : 2 */
#define MOD3_L              (0x0040u)    /* Modulation Bit Counter Bit : 3 */
#define MOD4_L              (0x0080u)    /* Modulation Bit Counter Bit : 4 */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001u)    /* RESERVED */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
#define DCO0_H              (0x0001u)    /* DCO TAP Bit : 0 */
#define DCO1_H              (0x0002u)    /* DCO TAP Bit : 1 */
#define DCO2_H              (0x0004u)    /* DCO TAP Bit : 2 */
#define DCO3_H              (0x0008u)    /* DCO TAP Bit : 3 */
#define DCO4_H              (0x0010u)    /* DCO TAP Bit : 4 */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL1 Control Bits */
#define DISMOD              (0x0001u)    /* Disable Modulation */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DCORSEL0            (0x0010u)    /* DCO Freq. Range Select Bit : 0 */
#define DCORSEL1            (0x0020u)    /* DCO Freq. Range Select Bit : 1 */
#define DCORSEL2            (0x0040u)    /* DCO Freq. Range Select Bit : 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL1 Control Bits */
#define DISMOD_L            (0x0001u)    /* Disable Modulation */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DCORSEL0_L          (0x0010u)    /* DCO Freq. Range Select Bit : 0 */
#define DCORSEL1_L          (0x0020u)    /* DCO Freq. Range Select Bit : 1 */
#define DCORSEL2_L          (0x0040u)    /* DCO Freq. Range Select Bit : 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL1 Control Bits */
//#define RESERVED            (0x0002u)    /* RESERVED */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define DCORSEL_0           (0x0000u)    /* DCO RSEL 0 */
#define DCORSEL_1           (0x0010u)    /* DCO RSEL 1 */
#define DCORSEL_2           (0x0020u)    /* DCO RSEL 2 */
#define DCORSEL_3           (0x0030u)    /* DCO RSEL 3 */
#define DCORSEL_4           (0x0040u)    /* DCO RSEL 4 */
#define DCORSEL_5           (0x0050u)    /* DCO RSEL 5 */
#define DCORSEL_6           (0x0060u)    /* DCO RSEL 6 */
#define DCORSEL_7           (0x0070u)    /* DCO RSEL 7 */

/* UCSCTL2 Control Bits */
#define FLLN0               (0x0001u)    /* FLL Multipier Bit : 0 */
#define FLLN1               (0x0002u)    /* FLL Multipier Bit : 1 */
#define FLLN2               (0x0004u)    /* FLL Multipier Bit : 2 */
#define FLLN3               (0x0008u)    /* FLL Multipier Bit : 3 */
#define FLLN4               (0x0010u)    /* FLL Multipier Bit : 4 */
#define FLLN5               (0x0020u)    /* FLL Multipier Bit : 5 */
#define FLLN6               (0x0040u)    /* FLL Multipier Bit : 6 */
#define FLLN7               (0x0080u)    /* FLL Multipier Bit : 7 */
#define FLLN8               (0x0100u)    /* FLL Multipier Bit : 8 */
#define FLLN9               (0x0200u)    /* FLL Multipier Bit : 9 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
#define FLLD0               (0x1000u)    /* Loop Divider Bit : 0 */
#define FLLD1               (0x2000u)    /* Loop Divider Bit : 1 */
#define FLLD2               (0x4000u)    /* Loop Divider Bit : 1 */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL2 Control Bits */
#define FLLN0_L             (0x0001u)    /* FLL Multipier Bit : 0 */
#define FLLN1_L             (0x0002u)    /* FLL Multipier Bit : 1 */
#define FLLN2_L             (0x0004u)    /* FLL Multipier Bit : 2 */
#define FLLN3_L             (0x0008u)    /* FLL Multipier Bit : 3 */
#define FLLN4_L             (0x0010u)    /* FLL Multipier Bit : 4 */
#define FLLN5_L             (0x0020u)    /* FLL Multipier Bit : 5 */
#define FLLN6_L             (0x0040u)    /* FLL Multipier Bit : 6 */
#define FLLN7_L             (0x0080u)    /* FLL Multipier Bit : 7 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL2 Control Bits */
#define FLLN8_H             (0x0001u)    /* FLL Multipier Bit : 8 */
#define FLLN9_H             (0x0002u)    /* FLL Multipier Bit : 9 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
#define FLLD0_H             (0x0010u)    /* Loop Divider Bit : 0 */
#define FLLD1_H             (0x0020u)    /* Loop Divider Bit : 1 */
#define FLLD2_H             (0x0040u)    /* Loop Divider Bit : 1 */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define FLLD_0             (0x0000u)    /* Multiply Selected Loop Freq. 1 */
#define FLLD_1             (0x1000u)    /* Multiply Selected Loop Freq. 2 */
#define FLLD_2             (0x2000u)    /* Multiply Selected Loop Freq. 4 */
#define FLLD_3             (0x3000u)    /* Multiply Selected Loop Freq. 8 */
#define FLLD_4             (0x4000u)    /* Multiply Selected Loop Freq. 16 */
#define FLLD_5             (0x5000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_6             (0x6000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_7             (0x7000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD__1            (0x0000u)    /* Multiply Selected Loop Freq. By 1 */
#define FLLD__2            (0x1000u)    /* Multiply Selected Loop Freq. By 2 */
#define FLLD__4            (0x2000u)    /* Multiply Selected Loop Freq. By 4 */
#define FLLD__8            (0x3000u)    /* Multiply Selected Loop Freq. By 8 */
#define FLLD__16           (0x4000u)    /* Multiply Selected Loop Freq. By 16 */
#define FLLD__32           (0x5000u)    /* Multiply Selected Loop Freq. By 32 */

/* UCSCTL3 Control Bits */
#define FLLREFDIV0          (0x0001u)    /* Reference Divider Bit : 0 */
#define FLLREFDIV1          (0x0002u)    /* Reference Divider Bit : 1 */
#define FLLREFDIV2          (0x0004u)    /* Reference Divider Bit : 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELREF0             (0x0010u)    /* FLL Reference Clock Select Bit : 0 */
#define SELREF1             (0x0020u)    /* FLL Reference Clock Select Bit : 1 */
#define SELREF2             (0x0040u)    /* FLL Reference Clock Select Bit : 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL3 Control Bits */
#define FLLREFDIV0_L        (0x0001u)    /* Reference Divider Bit : 0 */
#define FLLREFDIV1_L        (0x0002u)    /* Reference Divider Bit : 1 */
#define FLLREFDIV2_L        (0x0004u)    /* Reference Divider Bit : 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELREF0_L           (0x0010u)    /* FLL Reference Clock Select Bit : 0 */
#define SELREF1_L           (0x0020u)    /* FLL Reference Clock Select Bit : 1 */
#define SELREF2_L           (0x0040u)    /* FLL Reference Clock Select Bit : 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL3 Control Bits */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define FLLREFDIV_0         (0x0000u)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV_1         (0x0001u)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV_2         (0x0002u)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV_3         (0x0003u)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV_4         (0x0004u)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV_5         (0x0005u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_6         (0x0006u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_7         (0x0007u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV__1        (0x0000u)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV__2        (0x0001u)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV__4        (0x0002u)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV__8        (0x0003u)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV__12       (0x0004u)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV__16       (0x0005u)    /* Reference Divider: f(LFCLK)/16 */
#define SELREF_0            (0x0000u)    /* FLL Reference Clock Select 0 */
#define SELREF_1            (0x0010u)    /* FLL Reference Clock Select 1 */
#define SELREF_2            (0x0020u)    /* FLL Reference Clock Select 2 */
#define SELREF_3            (0x0030u)    /* FLL Reference Clock Select 3 */
#define SELREF_4            (0x0040u)    /* FLL Reference Clock Select 4 */
#define SELREF_5            (0x0050u)    /* FLL Reference Clock Select 5 */
#define SELREF_6            (0x0060u)    /* FLL Reference Clock Select 6 */
#define SELREF_7            (0x0070u)    /* FLL Reference Clock Select 7 */
#define SELREF__XT1CLK      (0x0000u)    /* Multiply Selected Loop Freq. By XT1CLK */
#define SELREF__REFOCLK     (0x0020u)    /* Multiply Selected Loop Freq. By REFOCLK */
#define SELREF__XT2CLK      (0x0050u)    /* Multiply Selected Loop Freq. By XT2CLK */

/* UCSCTL4 Control Bits */
#define SELM0               (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1               (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELM2               (0x0004u)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0               (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1               (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELS2               (0x0040u)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0               (0x0100u)   /* ACLK Source Select Bit: 0 */
#define SELA1               (0x0200u)   /* ACLK Source Select Bit: 1 */
#define SELA2               (0x0400u)   /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL4 Control Bits */
#define SELM0_L             (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELM2_L             (0x0004u)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0_L             (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELS2_L             (0x0040u)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL4 Control Bits */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0_H             (0x0001u)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002u)   /* ACLK Source Select Bit: 1 */
#define SELA2_H             (0x0004u)   /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define SELM_0              (0x0000u)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001u)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002u)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003u)   /* MCLK Source Select 3 */
#define SELM_4              (0x0004u)   /* MCLK Source Select 4 */
#define SELM_5              (0x0005u)   /* MCLK Source Select 5 */
#define SELM_6              (0x0006u)   /* MCLK Source Select 6 */
#define SELM_7              (0x0007u)   /* MCLK Source Select 7 */
#define SELM__XT1CLK        (0x0000u)   /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK        (0x0001u)   /* MCLK Source Select VLOCLK */
#define SELM__REFOCLK       (0x0002u)   /* MCLK Source Select REFOCLK */
#define SELM__DCOCLK        (0x0003u)   /* MCLK Source Select DCOCLK */
#define SELM__DCOCLKDIV     (0x0004u)   /* MCLK Source Select DCOCLKDIV */
#define SELM__XT2CLK        (0x0005u)   /* MCLK Source Select XT2CLK */

#define SELS_0              (0x0000u)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010u)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020u)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030u)   /* SMCLK Source Select 3 */
#define SELS_4              (0x0040u)   /* SMCLK Source Select 4 */
#define SELS_5              (0x0050u)   /* SMCLK Source Select 5 */
#define SELS_6              (0x0060u)   /* SMCLK Source Select 6 */
#define SELS_7              (0x0070u)   /* SMCLK Source Select 7 */
#define SELS__XT1CLK        (0x0000u)   /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK        (0x0010u)   /* SMCLK Source Select VLOCLK */
#define SELS__REFOCLK       (0x0020u)   /* SMCLK Source Select REFOCLK */
#define SELS__DCOCLK        (0x0030u)   /* SMCLK Source Select DCOCLK */
#define SELS__DCOCLKDIV     (0x0040u)   /* SMCLK Source Select DCOCLKDIV */
#define SELS__XT2CLK        (0x0050u)   /* SMCLK Source Select XT2CLK */

#define SELA_0              (0x0000u)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100u)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200u)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300u)   /* ACLK Source Select 3 */
#define SELA_4              (0x0400u)   /* ACLK Source Select 4 */
#define SELA_5              (0x0500u)   /* ACLK Source Select 5 */
#define SELA_6              (0x0600u)   /* ACLK Source Select 6 */
#define SELA_7              (0x0700u)   /* ACLK Source Select 7 */
#define SELA__XT1CLK        (0x0000u)   /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK        (0x0100u)   /* ACLK Source Select VLOCLK */
#define SELA__REFOCLK       (0x0200u)   /* ACLK Source Select REFOCLK */
#define SELA__DCOCLK        (0x0300u)   /* ACLK Source Select DCOCLK */
#define SELA__DCOCLKDIV     (0x0400u)   /* ACLK Source Select DCOCLKDIV */
#define SELA__XT2CLK        (0x0500u)   /* ACLK Source Select XT2CLK */

/* UCSCTL5 Control Bits */
#define DIVM0               (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1               (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2               (0x0004u)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DIVS0               (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1               (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2               (0x0040u)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define DIVA0               (0x0100u)   /* ACLK Divider Bit: 0 */
#define DIVA1               (0x0200u)   /* ACLK Divider Bit: 1 */
#define DIVA2               (0x0400u)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0800u)    /* RESERVED */
#define DIVPA0              (0x1000u)   /* ACLK from Pin Divider Bit: 0 */
#define DIVPA1              (0x2000u)   /* ACLK from Pin Divider Bit: 1 */
#define DIVPA2              (0x4000u)   /* ACLK from Pin Divider Bit: 2 */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL5 Control Bits */
#define DIVM0_L             (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1_L             (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2_L             (0x0004u)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DIVS0_L             (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1_L             (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2_L             (0x0040u)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL5 Control Bits */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define DIVA0_H             (0x0001u)   /* ACLK Divider Bit: 0 */
#define DIVA1_H             (0x0002u)   /* ACLK Divider Bit: 1 */
#define DIVA2_H             (0x0004u)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0800u)    /* RESERVED */
#define DIVPA0_H            (0x0010u)   /* ACLK from Pin Divider Bit: 0 */
#define DIVPA1_H            (0x0020u)   /* ACLK from Pin Divider Bit: 1 */
#define DIVPA2_H            (0x0040u)   /* ACLK from Pin Divider Bit: 2 */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define DIVM_0              (0x0000u)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001u)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002u)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003u)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004u)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005u)    /* MCLK Source Divider 5 */
#define DIVM_6              (0x0006u)    /* MCLK Source Divider 6 */
#define DIVM_7              (0x0007u)    /* MCLK Source Divider 7 */
#define DIVM__1             (0x0000u)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001u)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002u)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003u)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004u)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005u)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000u)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010u)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020u)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030u)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040u)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050u)    /* SMCLK Source Divider 5 */
#define DIVS_6              (0x0060u)    /* SMCLK Source Divider 6 */
#define DIVS_7              (0x0070u)    /* SMCLK Source Divider 7 */
#define DIVS__1             (0x0000u)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010u)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020u)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030u)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040u)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050u)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000u)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100u)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200u)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300u)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400u)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500u)    /* ACLK Source Divider 5 */
#define DIVA_6              (0x0600u)    /* ACLK Source Divider 6 */
#define DIVA_7              (0x0700u)    /* ACLK Source Divider 7 */
#define DIVA__1             (0x0000u)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100u)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200u)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300u)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400u)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500u)    /* ACLK Source Divider f(ACLK)/32 */

#define DIVPA_0             (0x0000u)    /* ACLK from Pin Source Divider 0 */
#define DIVPA_1             (0x1000u)    /* ACLK from Pin Source Divider 1 */
#define DIVPA_2             (0x2000u)    /* ACLK from Pin Source Divider 2 */
#define DIVPA_3             (0x3000u)    /* ACLK from Pin Source Divider 3 */
#define DIVPA_4             (0x4000u)    /* ACLK from Pin Source Divider 4 */
#define DIVPA_5             (0x5000u)    /* ACLK from Pin Source Divider 5 */
#define DIVPA_6             (0x6000u)    /* ACLK from Pin Source Divider 6 */
#define DIVPA_7             (0x7000u)    /* ACLK from Pin Source Divider 7 */
#define DIVPA__1            (0x0000u)    /* ACLK from Pin Source Divider f(ACLK)/1 */
#define DIVPA__2            (0x1000u)    /* ACLK from Pin Source Divider f(ACLK)/2 */
#define DIVPA__4            (0x2000u)    /* ACLK from Pin Source Divider f(ACLK)/4 */
#define DIVPA__8            (0x3000u)    /* ACLK from Pin Source Divider f(ACLK)/8 */
#define DIVPA__16           (0x4000u)    /* ACLK from Pin Source Divider f(ACLK)/16 */
#define DIVPA__32           (0x5000u)    /* ACLK from Pin Source Divider f(ACLK)/32 */

/* UCSCTL6 Control Bits */
#define XT1OFF              (0x0001u)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF            (0x0002u)    /* SMCLK Off */
#define XCAP0               (0x0004u)    /* XIN/XOUT Cap Bit: 0 */
#define XCAP1               (0x0008u)    /* XIN/XOUT Cap Bit: 1 */
#define XT1BYPASS           (0x0010u)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS                 (0x0020u)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0           (0x0040u)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1           (0x0080u)    /* XT1 Drive Level mode Bit 1 */
#define XT2OFF              (0x0100u)    /* High Frequency Oscillator 2 (XT2) disable */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL6 Control Bits */
#define XT1OFF_L            (0x0001u)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF_L          (0x0002u)    /* SMCLK Off */
#define XCAP0_L             (0x0004u)    /* XIN/XOUT Cap Bit: 0 */
#define XCAP1_L             (0x0008u)    /* XIN/XOUT Cap Bit: 1 */
#define XT1BYPASS_L         (0x0010u)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L               (0x0020u)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L         (0x0040u)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L         (0x0080u)    /* XT1 Drive Level mode Bit 1 */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL6 Control Bits */
#define XT2OFF_H            (0x0001u)    /* High Frequency Oscillator 2 (XT2) disable */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define XCAP_0              (0x0000u)    /* XIN/XOUT Cap 0 */
#define XCAP_1              (0x0004u)    /* XIN/XOUT Cap 1 */
#define XCAP_2              (0x0008u)    /* XIN/XOUT Cap 2 */
#define XCAP_3              (0x000Cu)    /* XIN/XOUT Cap 3 */
#define XT1DRIVE_0          (0x0000u)    /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1          (0x0040u)    /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2          (0x0080u)    /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3          (0x00C0u)    /* XT1 Drive Level mode: 3 */

/* UCSCTL7 Control Bits */
#define DCOFFG              (0x0001u)    /* DCO Fault Flag */
#define XT1LFOFFG           (0x0002u)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT1HFOFFG           (0x0004u)    /* XT1 High Frequency Oscillator 1 Fault Flag */
#define XT2OFFG             (0x0008u)    /* High Frequency Oscillator 2 Fault Flag */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL7 Control Bits */
#define DCOFFG_L            (0x0001u)    /* DCO Fault Flag */
#define XT1LFOFFG_L         (0x0002u)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT1HFOFFG_L         (0x0004u)    /* XT1 High Frequency Oscillator 1 Fault Flag */
#define XT2OFFG_L           (0x0008u)    /* High Frequency Oscillator 2 Fault Flag */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL7 Control Bits */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL8 Control Bits */
#define ACLKREQEN           (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN           (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN          (0x0004u)    /* SMCLK Clock Request Enable */
#define MODOSCREQEN         (0x0008u)    /* MODOSC Clock Request Enable */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL8 Control Bits */
#define ACLKREQEN_L         (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004u)    /* SMCLK Clock Request Enable */
#define MODOSCREQEN_L       (0x0008u)    /* MODOSC Clock Request Enable */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* UCSCTL8 Control Bits */
//#define RESERVED            (0x0010u)    /* RESERVED */
//#define RESERVED            (0x0020u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0100u)    /* RESERVED */
//#define RESERVED            (0x0200u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/************************************************************
* USCI A0
************************************************************/
#define __MSP430_HAS_USCI_A0__       /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_A0__ 0x05C0

#define UCA0CTLW0_          (0x05C0u)  /* USCI A0 Control Word Register 0 */
DEFCW(  UCA0CTLW0         , UCA0CTLW0_)
#define UCA0CTL1            UCA0CTLW0_L  /* USCI A0 Control Register 1 */
#define UCA0CTL0            UCA0CTLW0_H  /* USCI A0 Control Register 0 */
#define UCA0BRW_            (0x05C6u)  /* USCI A0 Baud Word Rate 0 */
DEFCW(  UCA0BRW           , UCA0BRW_)
#define UCA0BR0             UCA0BRW_L /* USCI A0 Baud Rate 0 */
#define UCA0BR1             UCA0BRW_H /* USCI A0 Baud Rate 1 */
#define UCA0MCTL_           (0x05C8u)  /* USCI A0 Modulation Control */
DEFC(   UCA0MCTL          , UCA0MCTL_)
#define UCA0STAT_           (0x05CAu)  /* USCI A0 Status Register */
DEFC(   UCA0STAT          , UCA0STAT_)
#define UCA0RXBUF_          (0x05CCu)  /* USCI A0 Receive Buffer */
READ_ONLY DEFC( UCA0RXBUF      , UCA0RXBUF_)
#define UCA0TXBUF_          (0x05CEu)  /* USCI A0 Transmit Buffer */
DEFC(   UCA0TXBUF         , UCA0TXBUF_)
#define UCA0ABCTL_          (0x05D0u)  /* USCI A0 LIN Control */
DEFC(   UCA0ABCTL         , UCA0ABCTL_)
#define UCA0IRCTL_          (0x05D2u)  /* USCI A0 IrDA Transmit Control */
DEFCW(  UCA0IRCTL         , UCA0IRCTL_)
#define UCA0IRTCTL          UCA0IRCTL_L  /* USCI A0 IrDA Transmit Control */
#define UCA0IRRCTL          UCA0IRCTL_H  /* USCI A0 IrDA Receive Control */
#define UCA0ICTL_           (0x05DCu)  /* USCI A0 Interrupt Enable Register */
DEFCW(  UCA0ICTL          , UCA0ICTL_)
#define UCA0IE              UCA0ICTL_L  /* USCI A0 Interrupt Enable Register */
#define UCA0IFG             UCA0ICTL_H  /* USCI A0 Interrupt Flags Register */
#define UCA0IV_             (0x05DEu)  /* USCI A0 Interrupt Vector Register */
DEFW(   UCA0IV            , UCA0IV_)


/************************************************************
* USCI B0
************************************************************/
#define __MSP430_HAS_USCI_B0__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_B0__ 0x05E0


#define UCB0CTLW0_          (0x05E0u)  /* USCI B0 Control Word Register 0 */
DEFCW(  UCB0CTLW0         , UCB0CTLW0_)
#define UCB0CTL1            UCB0CTLW0_L  /* USCI B0 Control Register 1 */
#define UCB0CTL0            UCB0CTLW0_H  /* USCI B0 Control Register 0 */
#define UCB0BRW_            (0x05E6u)  /* USCI B0 Baud Word Rate 0 */
DEFCW(  UCB0BRW           , UCB0BRW_)
#define UCB0BR0             UCB0BRW_L /* USCI B0 Baud Rate 0 */
#define UCB0BR1             UCB0BRW_H /* USCI B0 Baud Rate 1 */
#define UCB0STAT_           (0x05EAu)  /* USCI B0 Status Register */
DEFC(   UCB0STAT          , UCB0STAT_)
#define UCB0RXBUF_          (0x05ECu)  /* USCI B0 Receive Buffer */
READ_ONLY DEFC( UCB0RXBUF      , UCB0RXBUF_)
#define UCB0TXBUF_          (0x05EEu)  /* USCI B0 Transmit Buffer */
DEFC(   UCB0TXBUF         , UCB0TXBUF_)
#define UCB0I2COA_          (0x05F0u)  /* USCI B0 I2C Own Address */
DEFCW(  UCB0I2COA         , UCB0I2COA_)
#define UCB0I2CSA_          (0x05F2u)  /* USCI B0 I2C Slave Address */
DEFCW(  UCB0I2CSA         , UCB0I2CSA_)
#define UCB0ICTL_           (0x05FCu)  /* USCI B0 Interrupt Enable Register */
DEFCW(  UCB0ICTL          , UCB0ICTL_)
#define UCB0IE              UCB0ICTL_L  /* USCI B0 Interrupt Enable Register */
#define UCB0IFG             UCB0ICTL_H  /* USCI B0 Interrupt Flags Register */
#define UCB0IV_             (0x05FEu)  /* USCI B0 Interrupt Vector Register */
DEFW(   UCB0IV            , UCB0IV_)

// UCAxCTL0 UART-Mode Control Bits
#define UCPEN               (0x80)    /* Async. Mode: Parity enable */
#define UCPAR               (0x40)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB               (0x20)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT              (0x10)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB               (0x08)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1             (0x04)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0             (0x02)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC              (0x01)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// UCxxCTL0 SPI-Mode Control Bits
#define UCCKPH              (0x80)    /* Sync. Mode: Clock Phase */
#define UCCKPL              (0x40)    /* Sync. Mode: Clock Polarity */
#define UCMST               (0x08)    /* Sync. Mode: Master Select */

// UCBxCTL0 I2C-Mode Control Bits
#define UCA10               (0x80)    /* 10-bit Address Mode */
#define UCSLA10             (0x40)    /* 10-bit Slave Address Mode */
#define UCMM                (0x20)    /* Multi-Master Environment */
//#define res               (0x10)    /* reserved */
#define UCMODE_0            (0x00)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x02)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x04)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x06)    /* Sync. Mode: USCI Mode: 3 */

// UCAxCTL1 UART-Mode Control Bits
#define UCSSEL1             (0x80)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0             (0x40)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE             (0x20)    /* RX Error interrupt enable */
#define UCBRKIE             (0x10)    /* Break interrupt enable */
#define UCDORM              (0x08)    /* Dormant (Sleep) Mode */
#define UCTXADDR            (0x04)    /* Send next Data as Address */
#define UCTXBRK             (0x02)    /* Send next Data as Break */
#define UCSWRST             (0x01)    /* USCI Software Reset */

// UCxxCTL1 SPI-Mode Control Bits
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
//#define res               (0x08)    /* reserved */
//#define res               (0x04)    /* reserved */
//#define res               (0x02)    /* reserved */

// UCBxCTL1 I2C-Mode Control Bits
//#define res               (0x20)    /* reserved */
#define UCTR                (0x10)    /* Transmit/Receive Select/Flag */
#define UCTXNACK            (0x08)    /* Transmit NACK */
#define UCTXSTP             (0x04)    /* Transmit STOP */
#define UCTXSTT             (0x02)    /* Transmit START */
#define UCSSEL_0            (0x00)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x40)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x80)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0xC0)    /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK        (0x00)    /* USCI 0 Clock Source: UCLK */
#define UCSSEL__ACLK        (0x40)    /* USCI 0 Clock Source: ACLK */
#define UCSSEL__SMCLK       (0x80)    /* USCI 0 Clock Source: SMCLK */

/* UCAxMCTL Control Bits */
#define UCBRF3              (0x80)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2              (0x40)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1              (0x20)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0              (0x10)    /* USCI First Stage Modulation Select 0 */
#define UCBRS2              (0x08)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1              (0x04)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0              (0x02)    /* USCI Second Stage Modulation Select 0 */
#define UCOS16              (0x01)    /* USCI 16-times Oversampling enable */

#define UCBRF_0             (0x00)    /* USCI First Stage Modulation: 0 */
#define UCBRF_1             (0x10)    /* USCI First Stage Modulation: 1 */
#define UCBRF_2             (0x20)    /* USCI First Stage Modulation: 2 */
#define UCBRF_3             (0x30)    /* USCI First Stage Modulation: 3 */
#define UCBRF_4             (0x40)    /* USCI First Stage Modulation: 4 */
#define UCBRF_5             (0x50)    /* USCI First Stage Modulation: 5 */
#define UCBRF_6             (0x60)    /* USCI First Stage Modulation: 6 */
#define UCBRF_7             (0x70)    /* USCI First Stage Modulation: 7 */
#define UCBRF_8             (0x80)    /* USCI First Stage Modulation: 8 */
#define UCBRF_9             (0x90)    /* USCI First Stage Modulation: 9 */
#define UCBRF_10            (0xA0)    /* USCI First Stage Modulation: A */
#define UCBRF_11            (0xB0)    /* USCI First Stage Modulation: B */
#define UCBRF_12            (0xC0)    /* USCI First Stage Modulation: C */
#define UCBRF_13            (0xD0)    /* USCI First Stage Modulation: D */
#define UCBRF_14            (0xE0)    /* USCI First Stage Modulation: E */
#define UCBRF_15            (0xF0)    /* USCI First Stage Modulation: F */

#define UCBRS_0             (0x00)    /* USCI Second Stage Modulation: 0 */
#define UCBRS_1             (0x02)    /* USCI Second Stage Modulation: 1 */
#define UCBRS_2             (0x04)    /* USCI Second Stage Modulation: 2 */
#define UCBRS_3             (0x06)    /* USCI Second Stage Modulation: 3 */
#define UCBRS_4             (0x08)    /* USCI Second Stage Modulation: 4 */
#define UCBRS_5             (0x0A)    /* USCI Second Stage Modulation: 5 */
#define UCBRS_6             (0x0C)    /* USCI Second Stage Modulation: 6 */
#define UCBRS_7             (0x0E)    /* USCI Second Stage Modulation: 7 */

/* UCAxSTAT Control Bits */
#define UCLISTEN            (0x80)    /* USCI Listen mode */
#define UCFE                (0x40)    /* USCI Frame Error Flag */
#define UCOE                (0x20)    /* USCI Overrun Error Flag */
#define UCPE                (0x10)    /* USCI Parity Error Flag */
#define UCBRK               (0x08)    /* USCI Break received */
#define UCRXERR             (0x04)    /* USCI RX Error Flag */
#define UCADDR              (0x02)    /* USCI Address received Flag */
#define UCBUSY              (0x01)    /* USCI Busy Flag */
#define UCIDLE              (0x02)    /* USCI Idle line detected Flag */

/* UCBxSTAT Control Bits */
#define UCSCLLOW            (0x40)    /* SCL low */
#define UCGC                (0x20)    /* General Call address received Flag */
#define UCBBUSY             (0x10)    /* Bus Busy Flag */

/* UCAxIRTCTL Control Bits */
#define UCIRTXPL5           (0x80)    /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4           (0x40)    /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3           (0x20)    /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2           (0x10)    /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1           (0x08)    /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0           (0x04)    /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK           (0x02)    /* IRDA Transmit Pulse Clock Select */
#define UCIREN              (0x01)    /* IRDA Encoder/Decoder enable */

/* UCAxIRRCTL Control Bits */
#define UCIRRXFL5           (0x80)    /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4           (0x40)    /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3           (0x20)    /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2           (0x10)    /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1           (0x08)    /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0           (0x04)    /* IRDA Receive Filter Length 0 */
#define UCIRRXPL            (0x02)    /* IRDA Receive Input Polarity */
#define UCIRRXFE            (0x01)    /* IRDA Receive Filter enable */

/* UCAxABCTL Control Bits */
//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1            (0x20)    /* Break Sync Delimiter 1 */
#define UCDELIM0            (0x10)    /* Break Sync Delimiter 0 */
#define UCSTOE              (0x08)    /* Sync-Field Timeout error */
#define UCBTOE              (0x04)    /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN             (0x01)    /* Auto Baud Rate detect enable */

/* UCBxI2COA Control Bits */
#define UCGCEN              (0x8000u)  /* I2C General Call enable */
#define UCOA9               (0x0200u)  /* I2C Own Address 9 */
#define UCOA8               (0x0100u)  /* I2C Own Address 8 */
#define UCOA7               (0x0080u)  /* I2C Own Address 7 */
#define UCOA6               (0x0040u)  /* I2C Own Address 6 */
#define UCOA5               (0x0020u)  /* I2C Own Address 5 */
#define UCOA4               (0x0010u)  /* I2C Own Address 4 */
#define UCOA3               (0x0008u)  /* I2C Own Address 3 */
#define UCOA2               (0x0004u)  /* I2C Own Address 2 */
#define UCOA1               (0x0002u)  /* I2C Own Address 1 */
#define UCOA0               (0x0001u)  /* I2C Own Address 0 */

/* UCBxI2COA Control Bits */
#define UCOA7_L             (0x0080u)  /* I2C Own Address 7 */
#define UCOA6_L             (0x0040u)  /* I2C Own Address 6 */
#define UCOA5_L             (0x0020u)  /* I2C Own Address 5 */
#define UCOA4_L             (0x0010u)  /* I2C Own Address 4 */
#define UCOA3_L             (0x0008u)  /* I2C Own Address 3 */
#define UCOA2_L             (0x0004u)  /* I2C Own Address 2 */
#define UCOA1_L             (0x0002u)  /* I2C Own Address 1 */
#define UCOA0_L             (0x0001u)  /* I2C Own Address 0 */

/* UCBxI2COA Control Bits */
#define UCGCEN_H            (0x0080u)  /* I2C General Call enable */
#define UCOA9_H             (0x0002u)  /* I2C Own Address 9 */
#define UCOA8_H             (0x0001u)  /* I2C Own Address 8 */

/* UCBxI2CSA Control Bits */
#define UCSA9               (0x0200u)  /* I2C Slave Address 9 */
#define UCSA8               (0x0100u)  /* I2C Slave Address 8 */
#define UCSA7               (0x0080u)  /* I2C Slave Address 7 */
#define UCSA6               (0x0040u)  /* I2C Slave Address 6 */
#define UCSA5               (0x0020u)  /* I2C Slave Address 5 */
#define UCSA4               (0x0010u)  /* I2C Slave Address 4 */
#define UCSA3               (0x0008u)  /* I2C Slave Address 3 */
#define UCSA2               (0x0004u)  /* I2C Slave Address 2 */
#define UCSA1               (0x0002u)  /* I2C Slave Address 1 */
#define UCSA0               (0x0001u)  /* I2C Slave Address 0 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L             (0x0080u)  /* I2C Slave Address 7 */
#define UCSA6_L             (0x0040u)  /* I2C Slave Address 6 */
#define UCSA5_L             (0x0020u)  /* I2C Slave Address 5 */
#define UCSA4_L             (0x0010u)  /* I2C Slave Address 4 */
#define UCSA3_L             (0x0008u)  /* I2C Slave Address 3 */
#define UCSA2_L             (0x0004u)  /* I2C Slave Address 2 */
#define UCSA1_L             (0x0002u)  /* I2C Slave Address 1 */
#define UCSA0_L             (0x0001u)  /* I2C Slave Address 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H             (0x0002u)  /* I2C Slave Address 9 */
#define UCSA8_H             (0x0001u)  /* I2C Slave Address 8 */

/* UCAxIE Control Bits */
#define UCTXIE              (0x0002u)  /* USCI Transmit Interrupt Enable */
#define UCRXIE              (0x0001u)  /* USCI Receive Interrupt Enable */

/* UCBxIE Control Bits */
#define UCNACKIE            (0x0020u)  /* NACK Condition interrupt enable */
#define UCALIE              (0x0010u)  /* Arbitration Lost interrupt enable */
#define UCSTPIE             (0x0008u)  /* STOP Condition interrupt enable */
#define UCSTTIE             (0x0004u)  /* START Condition interrupt enable */
#define UCTXIE              (0x0002u)  /* USCI Transmit Interrupt Enable */
#define UCRXIE              (0x0001u)  /* USCI Receive Interrupt Enable */

/* UCAxIFG Control Bits */
#define UCTXIFG             (0x0002u)  /* USCI Transmit Interrupt Flag */
#define UCRXIFG             (0x0001u)  /* USCI Receive Interrupt Flag */

/* UCBxIFG Control Bits */
#define UCNACKIFG           (0x0020u)  /* NAK Condition interrupt Flag */
#define UCALIFG             (0x0010u)  /* Arbitration Lost interrupt Flag */
#define UCSTPIFG            (0x0008u)  /* STOP Condition interrupt Flag */
#define UCSTTIFG            (0x0004u)  /* START Condition interrupt Flag */
#define UCTXIFG             (0x0002u)  /* USCI Transmit Interrupt Flag */
#define UCRXIFG             (0x0001u)  /* USCI Receive Interrupt Flag */

/* USCI Definitions */
#define USCI_NONE           (0x0000u)    /* No Interrupt pending */
#define USCI_UCRXIFG        (0x0002u)    /* USCI UCRXIFG */
#define USCI_UCTXIFG        (0x0004u)    /* USCI UCTXIFG */
#define USCI_I2C_UCALIFG    (0x0002u)    /* USCI I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG  (0x0004u)    /* USCI I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG   (0x0006u)    /* USCI I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG   (0x0008u)    /* USCI I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG    (0x000Au)    /* USCI I2C Mode: UCRXIFG */
#define USCI_I2C_UCTXIFG    (0x000Cu)    /* USCI I2C Mode: UCTXIFG */

/************************************************************
* WATCHDOG TIMER A
************************************************************/
#define __MSP430_HAS_WDT_A__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x0150

#define  WDTCTL_             (0x015Cu)  /* Watchdog Timer Control */
DEFCW(   WDTCTL            , WDTCTL_)
/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0              (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1              (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2              (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL            (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL            (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0            (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1            (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD             (0x0080u)  /* WDT - Timer hold */

/* WDTCTL Control Bits */
#define WDTIS0_L            (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1_L            (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2_L            (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L          (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL_L          (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0_L          (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L          (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L           (0x0080u)  /* WDT - Timer hold */

/* WDTCTL Control Bits */

#define WDTPW               (0x5A00u)

#define WDTIS_0           (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS_1           (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS_2           (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3           (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS_4           (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS_5           (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6           (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS_7           (7*0x0001u)  /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G         (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M       (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K      (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K       (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K        (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192       (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512        (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS__64         (7*0x0001u)  /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0         (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1         (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2         (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3         (3*0x0020u)  /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK    (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK     (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO      (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */


/************************************************************
* TLV Descriptors
************************************************************/
#define __MSP430_HAS_TLV__              /* Definition to show that Module is available */

#define TLV_START             (0x1A08u)    /* Start Address of the TLV structure */
#define TLV_END               (0x1AFFu)    /* End Address of the TLV structure */

#define TLV_LDTAG             (0x01)      /*  Legacy descriptor (1xx, 2xx, 4xx families) */
#define TLV_PDTAG             (0x02)      /*  Peripheral discovery descriptor */
#define TLV_Reserved3         (0x03)      /*  Future usage */
#define TLV_Reserved4         (0x04)      /*  Future usage */
#define TLV_BLANK             (0x05)      /*  Blank descriptor */
#define TLV_Reserved6         (0x06)      /*  Future usage */
#define TLV_Reserved7         (0x07)      /*  Serial Number */
#define TLV_DIERECORD         (0x08)      /*  Die Record  */
#define TLV_ADCCAL            (0x11)      /*  ADC12 calibration */
#define TLV_ADC12CAL          (0x11)      /*  ADC12 calibration */
#define TLV_ADC10CAL          (0x13)      /*  ADC10 calibration */
#define TLV_REFCAL            (0x12)      /*  REF calibration */
#define TLV_TAGEXT            (0xFE)      /*  Tag extender */
#define TLV_TAGEND            (0xFF)      //  Tag End of Table

/************************************************************
* Interrupt Vectors (offset from 0xFF80)
************************************************************/


#define AES_VECTOR          (45 * 2u) /* 0xFFDA AES */
#define RTC_VECTOR          (46 * 2u) /* 0xFFDC RTC */
#define LCD_B_VECTOR        (47 * 2u) /* 0xFFDE LCD B */
#define PORT2_VECTOR        (48 * 2u) /* 0xFFE0 Port 2 */
#define PORT1_VECTOR        (49 * 2u) /* 0xFFE2 Port 1 */
#define TIMER1_A1_VECTOR    (50 * 2u) /* 0xFFE4 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR    (51 * 2u) /* 0xFFE6 Timer1_A3 CC0 */
#define DMA_VECTOR          (52 * 2u) /* 0xFFE8 DMA */
#define CC1101_VECTOR       (53 * 2u) /* 0xFFEA CC1101 Radio Interface */
#define TIMER0_A1_VECTOR    (54 * 2u) /* 0xFFEC Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR    (55 * 2u) /* 0xFFEE Timer0_A5 CC0 */
#define ADC10_VECTOR        (56 * 2u) /* 0xFFF0 ADC */
#define USCI_B0_VECTOR      (57 * 2u) /* 0xFFF2 USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR      (58 * 2u) /* 0xFFF4 USCI A0 Receive/Transmit */
#define WDT_VECTOR          (59 * 2u) /* 0xFFF6 Watchdog Timer */
#define COMP_B_VECTOR       (60 * 2u) /* 0xFFF8 Comparator B */
#define UNMI_VECTOR         (61 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (62 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (63 * 2u) /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __CC430F5147 */

