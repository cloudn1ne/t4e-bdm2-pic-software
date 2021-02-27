/*
 *  BDM2USB
 *  Version 1.0
 *  (c) 2016, Georg Swoboda <cn@warp.at>
 * 
 *  BDM code based on http://www.erwinrol.com/mpc8xx-bdm-debugging-library/
 * 
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
#include <string.h>         /* memset */
#include <stdio.h>         /* for printf via putch */
#include "system.h"
#include "mpc_bdm.h"


void bdm_save_regs(void)
{
    save_regs[0] = bdm_get_gpr( 0 ); /*save r0*/
	save_regs[1] = bdm_get_gpr( 1 ); /*save r1*/    
}

void bdm_restore_regs(void)
{    
    bdm_set_gpr( 0, save_regs[0] ); /*restore data*/
	bdm_set_gpr( 1, save_regs[1] ); /*restore data*/
}

void bdm_reset(void)
{    
  /*
  * set DSCK and /DSDI, implicite wait in Write
  * assert /HRESET and /SRESET, hold DSCK and /DSDI
  * Debug Mode enable
  */  
  __delay_ms(50); 
  DSCK=HIGH;  
  DSDI=LOW;
  __delay_ms(1);  
  SRESET=LOW; 
  HRESET=LOW;  
  __delay_ms(1);  
  HRESET=HIGH;  
  SRESET=HIGH;
  __delay_ms(1);  
  DSCK=LOW; 
  bdm_wait_ready(100);
}

static int bdm_clk_bit( unsigned long b )
{
  int res = 0;  
  if( DSDO )
	res = 1;

  if (b)
  {
      DSDI=HIGH;
      //printf("1",b);
  }
  else 
  {
      DSDI=LOW;
      //printf("0",b);
  }
 //  __delay_us(BDM_CLK_DELAY); 
  DSCK=HIGH;    
 //  __delay_us(BDM_CLK_DELAY); 
  DSCK=LOW;  
  return res;
}

/* keep DSDI low and toggle DSCK until DSDO goes low */

int bdm_wait_ready( int timeout )
{        
    //printf("bdm_wait_ready");
  //  DSDI=LOW;   
	while( DSDO )
	{                       
                // __delay_us(BDM_CLK_DELAY);  
                DSCK=HIGH;                
                // __delay_us(BDM_CLK_DELAY);  
                DSCK=LOW;  
             //   t++;
	
	}
    //printf(">done\n");
	return 0;
}

long bdm_clk_serial(struct bdm_in_s* in, struct bdm_out_s* out)
{
  int res = 0;
  int n;
  int reslen = 0;
  int len; // , nResult;
  unsigned long mask,word,x;

  
  // __delay_us(100);
  /* clear out */
  memset( out, 0 , sizeof(bdm_out_t) );
 
  bdm_wait_ready(2);
  
  if( in->prefix & 2  )
  {
   len = 7;
   mask = 0x40;
  }
  else
  {
   len = 32;
   mask = 0x80000000;
  }
  
  
  /* clock start bit get ready bit */
  out->ready = bdm_clk_bit( 1 );
  /* clock mode get first status bit */
  out->status = bdm_clk_bit( in->prefix & 2 );
  out->status <<= 1;
  /* clock control bit get second status bit */
  out->status |= bdm_clk_bit( in->prefix & 1 );
  
 // printf("out->status: %x\n", out->status);
  switch( out->status ){
  	case MPC8XX_BDM_STAT_CORE_DATA:                                         /* 00b +32 bits */
  		reslen = 32;
		break;

	    /* debug command while target not in debug mode */
    case MPC8XX_BDM_STAT_SEQ_ERROR:                                         /* 01b +2 bits + xx */
        //printf("MPC8XX_BDM_STAT_SEQ_ERROR\n");
		res = -3;
		reslen = 7;
		break;

		/* interrupt occurred, have to read ICR to clear */
	case MPC8XX_BDM_STAT_CORE_INTERRUPT:                                    /* 10b +2 bits + xx */
        //printf("MPC8XX_BDM_STAT_CORE_INTERRUPT\n");
		res = -4;
		reslen = 7;
		break;

	case MPC8XX_BDM_STAT_NULL:                                              /* 11b +2 bits + xx */
		reslen = 7;
		break;

	default:
        //printf("MPC_UNKNOWN\n");
		return -5;
		break;
  }  
  
  //printf("|M_start: %lx|",mask);
  word = (unsigned long)in->data;
 // printf("|TX:%lx|",word);
  out->data = 0;
  for(n = 0; n < len; n++ )
  {
	out->data <<= 1;
    x= (unsigned long)(word&mask);
    out->data |= bdm_clk_bit( x );
	mask >>= 1;
    //printf(" |M:%lx|",mask);
  }
  for(;n < reslen; n++ ) /* clock rest of data in with writing zeros*/
  {
	out->data <<= 1;
    out->data |= bdm_clk_bit( 0 );
  }
 // printf(" |RX: %lx|\n",out->data);
  DSDI=LOW;     /* reset data bit on DSDI */  
  return res;
}

unsigned long bdm_nop(void)
{
  bdm_in_t in;
  bdm_out_t out;

  in.prefix = MPC8XX_BDM_PREFIX_DPC;
  in.data = MPC8XX_BDM_DPC_NOP;

  /*get data*/
  if( bdm_clk_serial( &in, &out ) <  0 ){
		return 0x0;
  }  
  return out.data;
}

long bdm_get_gpr(unsigned long reg_nr)
{
  bdm_in_t in;
  bdm_out_t out;

  reg_nr &= ~MPC8XX_GPR_REG_MASK;  
  /* mtspr DPDR,rreg */
  in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
  in.data = 0;
  /// in.data =  ( 31 << 26 ) | ( reg_nr << 21 ) | ( 723 << 11 ) | ( 467 << 1 );
  in.data = 0x7c169ba6 + ( reg_nr << 21 );
  if( bdm_clk_serial( &in, &out ) < 0 ){
		return 0xDEADBEEF;
  }

  in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
  in.data = MPC8XX_COM_NOP;

  /*get data*/
  if( bdm_clk_serial( &in, &out ) <  0 ){
		return 0xDEADBEEF;
  }  
  return out.data;
}

int bdm_set_gpr( unsigned long reg_nr, unsigned long value )
{
	bdm_in_t in;
	bdm_out_t out;

	reg_nr &= ~MPC8XX_GPR_REG_MASK;
    
	/* mtspr DPDR,rreg */
	in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION; 	
    // in.data = (31 << 26) | (reg_nr << 21) | (723 << 11) | (339 << 1);
    in.data = 0x7c169aa6 + (reg_nr << 21);    
	if( bdm_clk_serial( &in, &out ) <  0){
		return -1;
	}

	in.prefix = MPC8XX_BDM_PREFIX_CORE_DATA;
	in.data = value;
	/* set data */
	if( bdm_clk_serial( &in, &out ) < 0 ){        
		return -1;
	}
	return 0;
}

unsigned long bdm_get_spr(  unsigned long reg )
{
	//unsigned long r0;
	unsigned long spr;
	bdm_in_t in;
	bdm_out_t out;
    
    //printf("bdm_get_spr(%x)\n", reg);
	/* special for msr */
//	if(reg == MPC8XX_SPR_MSR)
//		return bdm_get_msr( ); 

	/* special for cr */
//	if(reg == MPC8XX_SPR_CR)
//	return bdm_get_cr( );

	/* memory mapped sprs */
	//if(reg & MPC8XX_SPRI_MASK)
	//	return bdm_get_spri(  reg & ~MPC8XX_SPRI_MASK );
     
	//r0 = bdm_get_gpr(  0 ); /*save r0*/
    bdm_save_regs();
	/* mfspr r0, SPRreg */
	in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;	
    in.data = ((((reg&0x1f) << 5) | ((reg >> 5)&0x1f)) << 11);    
    in.data= in.data + 0x7c0002a6;
	if( bdm_clk_serial( &in, &out ) < 0 ){
		return 0xDEADBEEF;
	}
	spr = bdm_get_gpr(  0 ); /*read r0*/
	//bdm_set_gpr(  0, r0 ); /*restore r0*/
    bdm_restore_regs();
	return spr;
}

unsigned long bdm_get_spr2(  unsigned long reg )
{
	//unsigned long r0;
	unsigned int spr;
	bdm_in_t in;
	bdm_out_t out;
     
    
	// r0 = bdm_get_gpr(  0 ); /*save r0*/
    bdm_save_regs();
    
	/* mfspr r0, SPRreg */
	in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
    in.data = ((((reg&0x1f) << 5) | ((reg >> 5)&0x1f)) << 11);    
    in.data= in.data + 0x7c0002a6;

	if( bdm_clk_serial( &in, &out ) < 0 ){
		return 0xDEADBEEF;
	}

	spr = bdm_get_gpr(  0 ); /*read r0*/
	//bdm_set_gpr(  0, r0 ); /*restore r0*/
    bdm_restore_regs();
	return spr;
}


int bdm_set_spr( unsigned long reg, unsigned long value )
{
	//unsigned long r0;
	bdm_in_t in;
	bdm_out_t out;

	/* special for msr */
//	if(reg == MPC8XX_SPR_MSR){
//		return bdm_set_msr(  value );
//	}

	/* special for cr */
	// if(reg == MPC8XX_SPR_CR){
	//	return bdm_set_cr(  value ); 
	//}
	/* memory mapped sprs */
	//if(reg & MPC8XX_SPRI_MASK){
	//	return bdm_set_spri(  reg & ~MPC8XX_SPRI_MASK, value );
	//}

    //r0 = bdm_get_gpr(  0 ); /*save r0*/
    bdm_save_regs();
    
	bdm_set_gpr(  0, value );

	/*mtspr SPRreg,r0*/
	in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
	// in.data = (31 << 26) | ((((reg&0x1f) << 5) | ((reg >> 5)&0x1f)) << 11) | (467 << 1);
    in.data = ((((reg&0x1f) << 5) | ((reg >> 5)&0x1f)) << 11);
    in.data = in.data + 0x7c0003a6;
	if( bdm_clk_serial( &in, &out ) < 0 ){
		return -1;
	}

	//bdm_set_gpr(  0, r0 ); /*restore r0*/
    bdm_restore_regs();
	return 0;
}

unsigned long bdm_get_data( unsigned long addr, unsigned char size)
{
    unsigned long val;
	bdm_in_t in;
	bdm_out_t out;
    
    bdm_save_regs();
	bdm_set_gpr(  1, addr ); /*set addr to r1*/
    
    in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
    switch(size)
    {
        case 4: in.data = 0x80010000; break;  /* lwz r0,0(r1) */
        case 2: in.data = 0xA0010000; break;  /* lhz r0,0(r1) */
        case 1: in.data = 0x88010000; break;  /* lbz r0,0(r1) */
        default: break;
    }
    if( bdm_clk_serial( &in, &out ) < 0 ){
		return 0xDEADBEEF;
	}
	val = bdm_get_gpr(  0 ); /*get data from r0*/
	
    bdm_restore_regs();
	return val;
}

void bdm_set_data( unsigned long addr, unsigned long val, unsigned char size)
{    
	bdm_in_t in;
	bdm_out_t out;
    
    bdm_save_regs();
	bdm_set_gpr(  1, addr ); /*put addr in r1*/
	bdm_set_gpr(  0, val ); /*put data in r0*/
    
    in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
    switch(size)
    {
        case 4: in.data = 0x90010000; break;  /* stw r0,0(r1) */
        case 2: in.data = 0xB0010000; break;  /* sth r0,0(r1) */
        case 1: in.data = 0x98010000; break;  /* stb r0,0(r1) */
        default: break;
    }
    if( bdm_clk_serial( &in, &out ) < 0 ){
		return;
	}
		
    bdm_restore_regs();
	return;
}

int bdm_continue(void)
{
    unsigned long der;
	unsigned long srr1;
    
    der = bdm_get_spr(  MPC8XX_SPR_DER ); /*save previous Debug Enable Register value*/
	der &= ~PPC_BIT(14);
	bdm_set_spr(  MPC8XX_SPR_DER, der );

	/* clear single step trace enable in next MSR */
	srr1 = bdm_get_spr(  MPC8XX_SPR_SRR1 );
	srr1 &= ~ ( PPC_BIT(21) | PPC_BIT(22) );

	bdm_set_spr(  MPC8XX_SPR_SRR1, srr1 );
    
    return bdm_resume( );
}

int bdm_continue_single_step(void)
{
	unsigned long der;
	unsigned long srr1;
    
    
    der = bdm_get_spr( MPC8XX_SPR_DER ); /*save previous Debug Enable Register value*/
	bdm_set_spr( MPC8XX_SPR_DER, der | PPC_BIT(14) ); /* force TRE for single step*/

	/* set single step trace enable in next MSR */
	srr1 = bdm_get_spr( MPC8XX_SPR_SRR1 );
	srr1 &= ~ ( PPC_BIT(21) | PPC_BIT(22) );
	srr1 |= PPC_BIT(21);
	bdm_set_spr( MPC8XX_SPR_SRR1, srr1 );    
	
	return bdm_resume( );
}

int bdm_resume(void)
{
//	unsigned long icr;
	bdm_in_t in;
	bdm_out_t out;
    // unsigned long der;

    //bdm_set_word( 0x2FC004, 0xFF80 );    // kill watchdog 
    
	// bdm_set_spr( MPC8XX_SPR_IC_CST, 0x0C000000); /*invalidate instruction cache*/
	bdm_get_spr( MPC8XX_SPR_ICR); /*read ICR to clear pending interrupts*/	     
    
    in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
    in.data = MPC8XX_COM_ISYNC;    
	if( bdm_clk_serial( &in, &out ) < 0 )
	{
		return -1;
	}
    
	/* tell PPC to exit from Debug Port Interrupt */
	in.prefix = MPC8XX_BDM_PREFIX_CORE_INSTRUCTION;
	in.data = MPC8XX_COM_RFI;
	if( bdm_clk_serial( &in, &out ) < 0 )
	{
		return -1;
	}
	return 0;
}


void bdm_init(void)
{
    HRESET=LOW; 
    SRESET=LOW; 
    __delay_ms(20);    
    HRESET=HIGH; 
    SRESET=HIGH; 
    __delay_ms(20);    
}

/*
 *  write all 4 hardware breakpoints to CMPA-CMPD
 *  and the 2 load and store address watchpoints to CMPE-CMPF
 *  we enable all of them per default
 */
void bdm_update_breakpoints(void)
{
    unsigned char i,j;
    unsigned long reg;
    unsigned long reg_l1;
    unsigned long wc=0x0;
    
    for (i=0;i<MAX_HWBRK;i++)
    {        
        bdm_set_spr(MPC8XX_SPR_CMPA+i, break_points[i]);          
    }
    
    reg_l1=0x90000000;      // enable CMPE-F - equal matching
    for (i=0;i<MAX_HWWPT;i++)
    {        
        bdm_set_spr(MPC8XX_SPR_CMPE+i, watch_points[i].addr);    
                
        switch (watch_points[i].rw + i*10)
        {
            case 0: wc=0x80000; break;     // read wp0
            case 1: wc=0xC0000; break;     // write wp0                 
            case 10: wc=0x20000; break;    // read wp1
            case 11: wc=0x30000; break;    // write wp1         
            default: wc=0x0;
        }
        reg_l1 = reg_l1 | wc;
    }
    bdm_set_spr(MPC8XX_SPR_LCTRL1, reg_l1);  
     
    reg=bdm_get_spr(MPC8XX_SPR_ICTRL);
    reg = reg | 0x924AAF00; // enable CMPA-CMPD exact match
    bdm_set_spr(MPC8XX_SPR_ICTRL, reg);                
    
    reg=bdm_get_spr(MPC8XX_SPR_LCTRL2);
    reg = reg | 0x82208002;     // 0x82000002; 
    bdm_set_spr(MPC8XX_SPR_LCTRL2, reg);      
}

int bdm_interrupt( void )
{
	bdm_in_t in;
	bdm_out_t out;
    int c;
    unsigned long x;
    
	in.prefix = MPC8XX_BDM_PREFIX_DPC;
	in.data = MPC8XX_BDM_DPC_ASSERT_NMASK_BREAK;

	if( bdm_clk_serial( &in, &out ) < 0 )
	{
		return -1;
	}

    // wait for freeze
    c=0;     
    x=0;
    while (((c&0x40) != 0x40) && (x<1000)) { c= bdm_nop(); x++; }        
                    
	in.prefix = MPC8XX_BDM_PREFIX_DPC;
	in.data = MPC8XX_BDM_DPC_NEGATE_NMASK_BREAK;

	if( bdm_clk_serial( &in, &out ) < 0 )
	{
		return -1;
	}

	return 0;
}
