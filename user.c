/*
 *  BDM2USB
 *  Version 1.0
 *  (c) 2016, Georg Swoboda <cn@warp.at>
 */

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "system.h"
#include "mpc_bdm.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    TRISA=1;
    TRISBbits.TRISB6=0;     // LED
    TRISC=0;
    
    OSCCONbits.IRCF = 0b1111; /* 0b1111 = 16MHz HFINTOSC postscalar */

    /* Enable Active clock-tuning from the USB */
    ACTCONbits.ACTSRC = 1; /* 1=USB */
    ACTCONbits.ACTEN = 1;    
    
    /* Enable Peripherial Interrupt (for USB) */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void led_flash(int c)
{
    int i,j;

    for (j=0;j<c;j++)
    {
        LED=0;
        for (i=0;i<20;i++)
            __delay_ms(10);
        LED=1;
        for (i=0;i<20;i++)
            __delay_ms(10);
    }
    LED=0;
}
