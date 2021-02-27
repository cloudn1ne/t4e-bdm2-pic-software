/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
// #define SYS_FREQ        500000L
#define SYS_FREQ        48000000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ      SYS_FREQ


// #define DBG_SERIAL      
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
