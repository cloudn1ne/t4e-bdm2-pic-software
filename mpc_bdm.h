/*
 *  BDM2USB
 *  Version 1.0
 *  (c) 2016, Georg Swoboda <cn@warp.at>
 */

#ifndef MPC_BDM_H
#define	MPC_BDM_H

#ifdef	__cplusplus
extern "C" {
#endif

    
// BDM Output Pins
#define DSDI LATCbits.LATC5
#define DSCK LATCbits.LATC4
#define SRESET LATCbits.LATC3
#define HRESET LATCbits.LATC6
#define LED LATBbits.LATB6

// BDM Input Pins
#define DSDO PORTAbits.RA5

// Hi/Lo
#define HIGH 1
#define LOW 0
    
    
#define     BDM_CLK_DELAY       1

#define PPC_BITS        32
#define PPC_BIT(x)      ( 1 << (PPC_BITS-1-(x)) )
    
// flag if we should poll for freeze status via bdm_nop()'s
// this is used to detect if we should TRAP back to the debugger
unsigned char check_freeze=0;


/* Commands of Development Port Shift Register */

#define MPC8XX_BDM_PREFIX_CORE_INSTRUCTION	0x0	/* 00b +32 bits */
#define MPC8XX_BDM_PREFIX_CORE_DATA		0x1	/* 01b +32 bits */
#define MPC8XX_BDM_PREFIX_TECR			0x2	/* 10b +7 bits */
#define MPC8XX_BDM_PREFIX_DPC			0x3	/* 11b +7 bits */
#define MPC8XX_BDM_DPC_NOP 			0x00
#define MPC8XX_BDM_DPC_HRESET			0x01
#define MPC8XX_BDM_DPC_SRESET			0x02
#define MPC8XX_BDM_DPC_END_DOWNLOAD		0x43
#define MPC8XX_BDM_DPC_START_DOWNLOAD		0x63
#define MPC8XX_BDM_DPC_NEGATE_MASK_BREAK	0x1f
#define MPC8XX_BDM_DPC_ASSERT_MASK_BREAK	0x3f
#define MPC8XX_BDM_DPC_NEGATE_NMASK_BREAK	0x1f
#define MPC8XX_BDM_DPC_ASSERT_NMASK_BREAK	0x7f
#define MPC8XX_BDM_STAT_CORE_DATA		0x0	/* 00b +32 bits */
#define MPC8XX_BDM_STAT_SEQ_ERROR		0x1	/* 01b +2 bits + xx */
#define MPC8XX_BDM_STAT_CORE_INTERRUPT  0x2	/* 10b +2 bits + xx */
#define MPC8XX_BDM_STAT_NULL			0x3	/* 11b +2 bits + xx */
#define MPC8XX_COM_NOP		0x60000000
#define MPC8XX_COM_RFI		0x4C000064
#define MPC8XX_COM_ICR		0x7C1422A6
#define MPC8XX_COM_DER		0x7C1522A6
#define MPC8XX_COM_MFMSR	0x7C0000A6
#define MPC8XX_COM_MTSPR	0x7C169BA6
#define MPC8XX_COM_ISYNC    0x4c00012c
#define PPC_I_R0R1   0x90010000	/* stw 0,0(1) # mov r0,@r1 */
#define PPC_I_R0R1hw 0xB0010000	/* stw 0,0(1) # movh r0,@r1 */
#define PPC_I_R1R0   0x80010000	/* lwz 0,0(1) # mov @r1,r0 */
#define MAX_HWBRK	4 /*number of hardware breakpoint registers to use*/
#define MAX_HWWPT	2 /*number of hardware watchpoint registers to use*/
#define BDM_BREAKPOINT {0x0,0x0,0x0,0x0} /* For ppc 8xx */
#define MPC8XX_GPR_REG_MASK	0x2000
#define MPC8XX_SPR_XER		1
#define MPC8XX_SPR_LR		8
#define MPC8XX_SPR_CTR		9
#define MPC8XX_SPR_TBLR		268
#define MPC8XX_SPR_TBUR		269
#define MPC8XX_SPR_DSISR	18
#define MPC8XX_SPR_DAR		19
#define MPC8XX_SPR_DEC		22
#define MPC8XX_SPR_SRR0		26
#define MPC8XX_SPR_SRR1		27
#define MPC8XX_SPR_SPRG0	272
#define MPC8XX_SPR_SPRG1	273
#define MPC8XX_SPR_SPRG2	274
#define MPC8XX_SPR_SPRG3	275
#define MPC8XX_SPR_TBLW		284
#define MPC8XX_SPR_TBUW		285
#define MPC8XX_SPR_PVR		287
#define MPC8XX_SPR_EIE		80
#define MPC8XX_SPR_EID		81
#define MPC8XX_SPR_NRI		82
#define MPC8XX_SPR_DPIR		631
#define MPC8XX_SPR_IMMR		638
#define MPC8XX_SPR_IC_CST	560
#define MPC8XX_SPR_IC_ADR	561
#define MPC8XX_SPR_IC_DAT	562
#define MPC8XX_SPR_DC_CST	568
#define MPC8XX_SPR_DC_ADR	569
#define MPC8XX_SPR_DC_DAT	570
#define MPC8XX_SPR_MI_CTR	784
#define MPC8XX_SPR_MI_AP	786
#define MPC8XX_SPR_MI_EPN	787
#define MPC8XX_SPR_MI_TWC	789
#define MPC8XX_SPR_MI_RPN	790
#define MPC8XX_SPR_MI_CAM	816
#define MPC8XX_SPR_MI_RAM0	817
#define MPC8XX_SPR_MI_RAM1	818
#define MPC8XX_SPR_MD_CTR	792
#define MPC8XX_SPR_M_CASID	793
#define MPC8XX_SPR_MD_AP	794
#define MPC8XX_SPR_MD_EPN	795
#define MPC8XX_SPR_M_TWB	796
#define MPC8XX_SPR_MD_TWC	797
#define MPC8XX_SPR_MD_RPN	798
#define MPC8XX_SPR_M_TW		799
#define MPC8XX_SPR_MD_CAM	824
#define MPC8XX_SPR_MD_RAM0	825
#define MPC8XX_SPR_MD_RAM1	826
#define MPC8XX_SPR_CMPA		144
#define MPC8XX_SPR_CMPB		145
#define MPC8XX_SPR_CMPC		146
#define MPC8XX_SPR_CMPD		147
#define MPC8XX_SPR_ICR		148
#define MPC8XX_SPR_DER		149
#define MPC8XX_SPR_COUNTA	150
#define MPC8XX_SPR_COUNTB	151
#define MPC8XX_SPR_CMPE		152
#define MPC8XX_SPR_CMPF		153
#define MPC8XX_SPR_CMPG		154
#define MPC8XX_SPR_CMPH		155
#define MPC8XX_SPR_LCTRL1	156
#define MPC8XX_SPR_LCTRL2	157
#define MPC8XX_SPR_ICTRL	158
#define MPC8XX_SPR_BAR		159
#define MPC8XX_SPR_DPDR		630

#define MPC8XX_SPRI_REV_NUM 	0x3cb0

#define MPC8XX_SPRI_MASK	0x10000
#define MPC8XX_SPRI_SIUMCR	(MPC8XX_SPRI_MASK | 0x000)
#define MPC8XX_SPRI_SYPCR	(MPC8XX_SPRI_MASK | 0x004)
#define MPC8XX_SPRI_SWSR	(MPC8XX_SPRI_MASK | 0x00E)  /* 16 bit 556C AA39 */
#define MPC8XX_SPRI_SIPEND	(MPC8XX_SPRI_MASK | 0x010)
#define MPC8XX_SPRI_SIMASK	(MPC8XX_SPRI_MASK | 0x014)
#define MPC8XX_SPRI_SIEL	(MPC8XX_SPRI_MASK | 0x018)
#define MPC8XX_SPRI_SIVEC	(MPC8XX_SPRI_MASK | 0x01c)
#define MPC8XX_SPRI_TESR	(MPC8XX_SPRI_MASK | 0x020)
#define MPC8XX_SPRI_SDCR	(MPC8XX_SPRI_MASK | 0x032)
#define MPC8XX_SPRI_PBR(x)	(MPC8XX_SPRI_MASK | ( 0x080 + (x)*8))
#define MPC8XX_SPRI_POR(x)	(MPC8XX_SPRI_MASK | ( 0x084 + (x)*8))
#define MPC8XX_SPRI_PGCRA	(MPC8XX_SPRI_MASK | 0x0E0)
#define MPC8XX_SPRI_PGCRB	(MPC8XX_SPRI_MASK | 0x0E4)
#define MPC8XX_SPRI_PSCR	(MPC8XX_SPRI_MASK | 0x0E8)
#define MPC8XX_SPRI_PIPR	(MPC8XX_SPRI_MASK | 0x0F0)
#define MPC8XX_SPRI_PER		(MPC8XX_SPRI_MASK | 0x0F8)
#define MPC8XX_SPRI_BR(x)	(MPC8XX_SPRI_MASK | (0x100 + (x)*8))
#define MPC8XX_SPRI_OR(x)	(MPC8XX_SPRI_MASK | (0x104 + (x)*8))
#define MPC8XX_SPRI_MAR		(MPC8XX_SPRI_MASK | 0x164)
#define MPC8XX_SPRI_MCR		(MPC8XX_SPRI_MASK | 0x168)
#define MPC8XX_SPRI_MAMR	(MPC8XX_SPRI_MASK | 0x170)
#define MPC8XX_SPRI_MBMR	(MPC8XX_SPRI_MASK | 0x174)
#define MPC8XX_SPRI_MSTAT	(MPC8XX_SPRI_MASK | 0x178)    /* MSTAT MPTPR */
#define MPC8XX_SPRI_MDR		(MPC8XX_SPRI_MASK | 0x17C)
#define MPC8XX_SPRI_TBSCR	(MPC8XX_SPRI_MASK | 0x200)
#define MPC8XX_SPRI_TBREFA	(MPC8XX_SPRI_MASK | 0x204)
#define MPC8XX_SPRI_TBREFB	(MPC8XX_SPRI_MASK | 0x208)
#define MPC8XX_SPRI_RTCSC	(MPC8XX_SPRI_MASK | 0x220)
#define MPC8XX_SPRI_RTC		(MPC8XX_SPRI_MASK | 0x224)
#define MPC8XX_SPRI_RTSEC	(MPC8XX_SPRI_MASK | 0x228)
#define MPC8XX_SPRI_RTCAL	(MPC8XX_SPRI_MASK | 0x22C)
#define MPC8XX_SPRI_PISCR	(MPC8XX_SPRI_MASK | 0x240)
#define MPC8XX_SPRI_PITC	(MPC8XX_SPRI_MASK | 0x244)
#define MPC8XX_SPRI_PITR	(MPC8XX_SPRI_MASK | 0x248)
#define MPC8XX_SPRI_SCCR	(MPC8XX_SPRI_MASK | 0x280)
#define MPC8XX_SPRI_PLPRCR	(MPC8XX_SPRI_MASK | 0x284)
#define MPC8XX_SPRI_RSR		(MPC8XX_SPRI_MASK | 0x288)
#define MPC8XX_SPRI_TBSCRK	(MPC8XX_SPRI_MASK | 0x300)
#define MPC8XX_SPRI_CIVR	(MPC8XX_SPRI_MASK | 0x930)
#define MPC8XX_SPRI_CICR	(MPC8XX_SPRI_MASK | 0x940)
#define MPC8XX_SPRI_CIPR	(MPC8XX_SPRI_MASK | 0x944)
#define MPC8XX_SPRI_CIMR	(MPC8XX_SPRI_MASK | 0x948)
#define MPC8XX_SPRI_CISR	(MPC8XX_SPRI_MASK | 0x94C)
#define MPC8XX_SPRI_PADIR	(MPC8XX_SPRI_MASK | 0x950)
#define MPC8XX_SPRI_PAODR	(MPC8XX_SPRI_MASK | 0x954)
#define MPC8XX_SPRI_PCDIR	(MPC8XX_SPRI_MASK | 0x960)
#define MPC8XX_SPRI_PCSO	(MPC8XX_SPRI_MASK | 0x964)
#define MPC8XX_SPRI_PCINT	(MPC8XX_SPRI_MASK | 0x968)
#define MPC8XX_SPRI_PDDIR	(MPC8XX_SPRI_MASK | 0x970)
#define MPC8XX_SPRI_PDDAT	(MPC8XX_SPRI_MASK | 0x976)
#define MPC8XX_SPRI_PBDIR	(MPC8XX_SPRI_MASK | 0xAB8)
#define MPC8XX_SPRI_PBPAR	(MPC8XX_SPRI_MASK | 0xABC)
#define MPC8XX_SPRI_PBODR	(MPC8XX_SPRI_MASK | 0xAC0)
#define MPC8XX_SPRI_PBDAT	(MPC8XX_SPRI_MASK | 0xAC4)
#define MPC8XX_SPRI_SIMODE	(MPC8XX_SPRI_MASK | 0xAE0)
#define MPC8XX_SPRI_SIGMR	(MPC8XX_SPRI_MASK | 0xAE4)
#define MPC8XX_SPRI_SICR	(MPC8XX_SPRI_MASK | 0xAEC)
#define MPC8XX_SPRI_SIRP	(MPC8XX_SPRI_MASK | 0xAF0)
#define MPC8XX_SPR_MASK		0x20000
#define MPC8XX_SPR_MSR		(MPC8XX_SPR_MASK | 0x1)
#define MPC8XX_SPR_CR		(MPC8XX_SPR_MASK | 0x2)
#define MPC8XX_ICR_RST		PPC_BIT( 1 )
#define MPC8XX_ICR_CHSTP	PPC_BIT( 2 )
#define MPC8XX_ICR_MCI		PPC_BIT( 3 )
#define MPC8XX_ICR_EXTI		PPC_BIT( 6 )
#define MPC8XX_ICR_ALI		PPC_BIT( 7 )
#define MPC8XX_ICR_PRI		PPC_BIT( 8 )
#define MPC8XX_ICR_FPUVI	PPC_BIT( 9 )
#define MPC8XX_ICR_DECI		PPC_BIT( 10 )
#define MPC8XX_ICR_SYSI		PPC_BIT( 13 )
#define MPC8XX_ICR_TR		PPC_BIT( 14 )
#define MPC8XX_ICR_SEI		PPC_BIT( 17 )
#define MPC8XX_ICR_ITLBM	PPC_BIT( 18 )
#define MPC8XX_ICR_DTLBM	PPC_BIT( 19 )
#define MPC8XX_ICR_ITLBER	PPC_BIT( 20 )
#define MPC8XX_ICR_DTLBER	PPC_BIT( 21 )
#define MPC8XX_ICR_LBRK		PPC_BIT( 28 )
#define MPC8XX_ICR_IBRK		PPC_BIT( 29 )
#define MPC8XX_ICR_EBRK		PPC_BIT( 30 )
#define MPC8XX_ICR_DPI		PPC_BIT( 31 )
#define MPC8XX_DER_RST		PPC_BIT( 1 )
#define MPC8XX_DER_CHSTP	PPC_BIT( 2 )
#define MPC8XX_DER_MCI		PPC_BIT( 3 )
#define MPC8XX_DER_EXTI		PPC_BIT( 6 )
#define MPC8XX_DER_ALI		PPC_BIT( 7 )
#define MPC8XX_DER_PRI		PPC_BIT( 8 )
#define MPC8XX_DER_FPUVI	PPC_BIT( 9 )
#define MPC8XX_DER_DECI		PPC_BIT( 10 )
#define MPC8XX_DER_SYSI		PPC_BIT( 13 )
#define MPC8XX_DER_TR		PPC_BIT( 14 )
#define MPC8XX_DER_SEI		PPC_BIT( 17 )
#define MPC8XX_DER_ITLBM	PPC_BIT( 18 )
#define MPC8XX_DER_DTLBM	PPC_BIT( 19 )
#define MPC8XX_DER_ITLBER	PPC_BIT( 20 )
#define MPC8XX_DER_DTLBER	PPC_BIT( 21 )
#define MPC8XX_DER_LBRK		PPC_BIT( 28 )
#define MPC8XX_DER_IBRK		PPC_BIT( 29 )
#define MPC8XX_DER_EBRK		PPC_BIT( 30 )
#define MPC8XX_DER_DPI		PPC_BIT( 31 )

struct bdm_in_s {
	unsigned int prefix	: 2;	/**< 2 bit prefix */
	unsigned long data;		/**< 32 bit data */
};
typedef struct bdm_in_s bdm_in_t;
struct bdm_out_s {
	unsigned int ready 	: 1;	/**< target ready status */
	unsigned int status 	: 2;	/**< target status */
	unsigned long data;		/**< target data */
};
typedef struct bdm_out_s bdm_out_t;

static unsigned long save_regs[2];     // used to save r0,r1 messages

unsigned long break_points[MAX_HWBRK] = BDM_BREAKPOINT;

struct wp {
    unsigned long addr;
    unsigned char rw;       //0= read, 1= write, 2=read or write
} watch_points[MAX_HWWPT];

/* BDM Functions */

unsigned long bdm_get_spri(   unsigned int reg );
unsigned long bdm_get_spr(   unsigned long reg );
unsigned long bdm_get_spr2(  unsigned long reg );
long bdm_get_gpr(unsigned long reg_nr);
int bdm_set_gpr( unsigned long reg_nr, unsigned long value );
int bdm_continue_single_step(void);
void bdm_reset(void);
int bdm_set_spr(   unsigned long reg, unsigned long value );
int bdm_set_spri(   unsigned int reg, unsigned long value );
int bdm_wait_ready( int timeout );
void bdm_init(void);
unsigned long bdm_nop(void);
int bdm_resume(void);
int bdm_continue(void);
void bdm_update_breakpoints(void);
int bdm_interrupt( void );
void bdm_save_regs(void);
void bdm_restore_regs(void);
unsigned long bdm_get_data( unsigned long addr, unsigned char size);
void bdm_set_data( unsigned long addr, unsigned long val, unsigned char size);

#ifdef	__cplusplus
}
#endif

#endif	/* MPC_BDM_H */

