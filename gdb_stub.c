/*
 *  BDM2USB
 *  Version 1.1
 *  (c) 2018, Georg Swoboda <cn@warp.at>
 *
 * v1.1 - support for IDA Pro added - better memory read function (up to 256 bytes in one go)
 */

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>         /* for printf via putch */
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "gdb_stub.h"
#include "usb/include/usb.h"
#include "usb_config.h"
#include "usb/include/usb_ch9.h"
#include "usb/include/usb_cdc.h"
#include "mpc_bdm.h"

//static char byteMap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
//static int  byteMapLen = sizeof(byteMap);

static   char qchksum;

/*
 * GDB command processor
 * deterimines RSP query, calls BDM functions 
 */
void gdb_process_command(unsigned char *msg, unsigned char msg_len)
{
    unsigned char reg_num;
//    unsigned int  reg_val_h,reg_val_l;
    unsigned long reg_val;
    unsigned char msg_out[GDB_MSG_SIZE]="";
    unsigned char long_str[24];
    unsigned char i,j,k,s,u;
//    unsigned long t;
    unsigned long x=0;
    unsigned long y=0;
    
             
    if (msg[0]=='q' && msg[1]=='S')                         // qSupported  
    {           
        bdm_init();
        bdm_reset();       
        bdm_nop();         
        // t=bdm_get_spr(MPC8XX_SPR_IMMR);
        // bdm_set_spr(MPC8XX_SPR_IMMR, t | (1<<11));        // flash enable
        // bdm_set_spr(MPC8XX_SPR_DER, 0x7FE7540F);
        bdm_set_spr(MPC8XX_SPR_DER, 0x4002000F);        
        bdm_set_spr(MPC8XX_SPR_MSR, 0x000003002);    
        bdm_set_spr(MPC8XX_SPR_SRR1, 0x000003002);
        bdm_get_spr(MPC8XX_SPR_ICR);
        bdm_set_data( 0x2FC004, 0xFF80, 4 );    // kill watchdog needs to be a 32bit write !
        // reset any watchpoints
        for (i=0;i<MAX_HWWPT;i++)
            watch_points[i].addr=0x0;
        // reset any breakpoints
        for (i=0;i<MAX_HWBRK;i++)
         break_points[i]=0x0;
        bdm_update_breakpoints();
        check_freeze=0;
        gdb_send('+', "PackeSize=64;multiprocess-;swbreak+;hwbreak+;qRelocInsn-;vContSupported-");                                  
    }                                                  
    else if (msg[0]=='?')                                    // why stopped
    {
        // bdm_reset();
        gdb_send('+',"S05");
    }
    else if (msg[0]=='g')                                    // dump ALL registers
    {            
        gdb_send_start('+', &qchksum);        
        for (x=0;x<=0x1F;x++)
        {
          gdb_hexstr(&msg_out, bdm_get_gpr(x), 4, 0);
          gdb_send_data(msg_out, &qchksum);         
        }
        gdb_send_end(&qchksum);      
    }
    else if (msg[0]=='p')                                    // read register XX via bdm_get_gpr(regno)
    {        
        x=0;
        j=0;
        x=gdb_extract_bytes(msg_len-1, 0, msg);   
        reg_val=x;        
        if (x<=0x1f) 
        {
            reg_val=bdm_get_gpr(x);     
        }
        else
        {
            switch (x)
            {
              case 0x46: reg_val= bdm_get_spr(MPC8XX_SPR_DER); break;
              case 0x45: reg_val=bdm_get_spr(MPC8XX_SPR_ICR); break;              
              case 0x43: reg_val=bdm_get_spr(MPC8XX_SPR_LR); break;
              case 0x42: reg_val=bdm_get_spr(MPC8XX_SPR_SRR1); break;
              case 0x41: reg_val=bdm_get_spr(MPC8XX_SPR_MSR); break;
              case 0x40: reg_val=bdm_get_spr(MPC8XX_SPR_SRR0); break;
            }
        }                    
        gdb_hexstr(&msg_out, reg_val, 4, 0);
        gdb_send('+',msg_out);
    }
    else if (msg[0]=='P')                                    // write register XX via bdm_set_gpr(regno, val)
    {                
        // find = seperator
        for (i=msg_len;i>=1;i--)
        {
            if (msg[i]=='=') break;
        }  
        reg_val=gdb_extract_bytes(msg_len-1, i, msg);  
        reg_num=gdb_extract_bytes(i-1, 0, msg);       
        if (reg_num <= 0x1f)             
            bdm_set_gpr(reg_num, reg_val);
        if (reg_num == 0x41)        // MSR register
            bdm_set_spr(MPC8XX_SPR_MSR, reg_val);
        if (reg_num == 0x42)        // SSR1 register
            bdm_set_spr(MPC8XX_SPR_SRR1, reg_val);
        if (reg_num == 0x40)        // PC register
            bdm_set_spr(MPC8XX_SPR_SRR0, reg_val);                         
        if (reg_num == 0x43)        // LR register
            bdm_set_spr(MPC8XX_SPR_LR, reg_val);   
        if (reg_num == 0x45)        // XER=ICR=ECR register
            bdm_set_spr(MPC8XX_SPR_ICR, reg_val);      
        if (reg_num == 0x46)        // MQ=DER register
            bdm_set_spr(MPC8XX_SPR_DER, reg_val);      
        gdb_send('+',"OK");
    }
    else if (msg[0]=='m')                                    // read memory XX
    {        
        x=0;
        j=0;
        for (j=msg_len-1;j>0;j--)
        {
        	if (msg[j]==',') break;
        }               
        k=gdb_extract_bytes(msg_len-1, j, msg);   // bytes len
        x=gdb_extract_bytes(j-1, 0, msg);         // address       
        
        gdb_send_start('+', &qchksum);          
        if (k>0x400) k=0x400;       // cap at 0x400 bytes read max
        
        for (j=0;j<(k/4);j++)   // send 4 byte chunks
        {
            gdb_hexstr(&msg_out, bdm_get_data(x+(j*4), 4), 4, 0);
            gdb_send_data(msg_out, &qchksum); 
        }
        i=j*4;              // send remainder in single bytes
        for (j=0;j<(k%4);j++)
        {
            gdb_hexstr(&msg_out, bdm_get_data(x+j+i, 1), 1, 0);
            gdb_send_data(msg_out, &qchksum); 
        }      
        gdb_send_end(&qchksum);   
    }
    else if (msg[0]=='M')                                    // write memory XX
    {        
        x=0;                
        // find , seperator
        for (i=msg_len-3;i>=1;i--)
        {
            if (msg[i]==',') break;
        }                 
        // write size        
        s=msg[i+1];        
        i--;                    
        // extract the address part (x)
        j=0;
        while (i>=1)
        {
            k=msg[i];            
            if (k > '9') k -= 7;
            (unsigned long)x=(unsigned long)x + (unsigned long)((unsigned long)(k&0xf) << j);
            j=j+4;
            i--;        
        }                            
        // find : seperator
        for (i=msg_len-3;i>=1;i--)
        {
            if (msg[i]==':') break;
        }       
        u=i;                      
        // extract the data to write (y)        
        y=gdb_extract_bytes(msg_len-1, u, msg);       
        if (s=='3')            
            bdm_set_data(x,(y<<8), 4);
        if (s=='2')            
            bdm_set_data(x,(y&0xffff), 2);       
        if (s=='1')
            bdm_set_data(x,(y&0xff), 1);
        
        gdb_send('+',"OK");     
    }
    else if (msg[0]=='Z')                                    // insert breakpoint/watchpoint (Z0,Z1 = bkp, Z2= write watchpoint, Z3 = read watchpoint, Z4 = read/write watchpoint) 
    {
        k=msg[1];       // type
        x=gdb_extract_bytes(msg_len-3, 2, msg);
        // check if that kbp is already set        
        j=0;
        if (k=='2' || k=='3' || k=='4')
        {
           for (i=0;i<MAX_HWWPT;i++)
            {
                if (watch_points[i].addr==x) { j=1; break; }
            }
            if (j==0) // not currently set
            {
                for (i=0;i<MAX_HWWPT;i++)
                {
                    if (watch_points[i].addr==0) 
                    { 
                        watch_points[i].addr=x; 
                        if (k=='2') watch_points[i].rw=1;
                        if (k=='3') watch_points[i].rw=0;
                        if (k=='4') watch_points[i].rw=2;
                        break; 
                    }
                }
            }
        }
        else
        {
            for (i=0;i<MAX_HWBRK;i++)
            {
                if (break_points[i]==x) { j=1; break; }
            }
            if (j==0) // not currently set
            {
                for (i=0;i<MAX_HWBRK;i++)
                {
                    if (break_points[i]==0) { break_points[i]=x; break; }
                }
            }
        }
        bdm_update_breakpoints();        
        gdb_send('+',"OK");                 
    }
    else if (msg[0]=='z')                                    // remove breakpoint (we only do hard bkps)
    {
        k=msg[1];       // type
        x=gdb_extract_bytes(msg_len-3, 2, msg);
        // check if that kbp is already set
        j=0;
        if (k=='2' || k=='3' || k=='4')
        {        
            for (i=0;i<MAX_HWWPT;i++)
            {
                if ( watch_points[i].addr==x) { watch_points[i].addr=0; break; }
            }        
        }
        else
        {
            for (i=0;i<MAX_HWBRK;i++)
            {
                if (break_points[i]==x) { break_points[i]=0; break; }
            }        
        }
        bdm_update_breakpoints();        
        gdb_send('+',"OK");                 
    }
    else if (msg[0]=='s')                                    // single step        
    {
        bdm_continue_single_step();
        check_freeze=2;       
    }
    else if (msg[0]=='c')                                    // continue
    {                
        bdm_continue();   
        check_freeze=1;                     
    } 
    else if (msg[0]=='H' && msg[1]=='c')                         // HcX
    {   
       gdb_send('+',"OK");
    }   
    else 
      gdb_send('+',"");                                    // unknown/unsupported
}

/*
 * create up to 8 char (32bit) hexstrings in one go
 */
void gdb_hexstr(char *buf, unsigned long val, unsigned char len, unsigned char offset)
{
    unsigned char i,j,a;
    unsigned long m=0xf;

    j=len*2;            // number of chars needed
    buf[offset+j]=0;    // mark end of string
    for (i=0;i<j;i++)
    {
     a=(val&(m<<(i*4)))>>(i*4);
     buf[offset+j-i-1] = (a<10)?'0'+a:'a'+(a-10);
    }
}

void gdb_send_start(char reply_type, char *chksum)
{
    unsigned char *qbuf = usb_get_in_buffer(2);
    
    while (usb_in_endpoint_busy(2) || usb_in_endpoint_halted(2)) {} 
        
    *chksum = 0;
    qbuf[0]=reply_type;
    qbuf[1]='$';   
    if (usb_is_configured() && !usb_in_endpoint_halted(2) && !usb_in_endpoint_busy(2))    
      usb_send_in_buffer(2, 2);       
}

void gdb_send_data(unsigned char *reply, char *chksum)
{
    unsigned char *qbuf = usb_get_in_buffer(2);
    unsigned char k = 0;     
    
    while (usb_in_endpoint_busy(2) || usb_in_endpoint_halted(2)) {}     
    
    while (reply[k]!=0)             
      *chksum+=reply[k++];         
    memcpy(qbuf, reply, k);        
    // send via usb
    if (usb_is_configured() && !usb_in_endpoint_halted(2) && !usb_in_endpoint_busy(2))    
      usb_send_in_buffer(2, k);                            
}

void gdb_send_end(char *chksum)
{     
    unsigned char *qbuf = usb_get_in_buffer(2);
    *chksum = *chksum % 0x100;
            
    while (usb_in_endpoint_busy(2) || usb_in_endpoint_halted(2)) {} 
    
    qbuf[0]='#';
    gdb_hexstr(qbuf, *chksum, 1, 1);
        
    if (usb_is_configured() && !usb_in_endpoint_halted(2) && !usb_in_endpoint_busy(2))    
      usb_send_in_buffer(2, 3);       
}

/*
 * send message back to GDB
 * reply_type is "-", "+"
 * reply is the message, checksum will be added automatically
 */
void gdb_send(char reply_type, unsigned char *reply)
{
    unsigned char *qbuf = usb_get_in_buffer(2);
    unsigned char checksum,k; 
                   
    checksum=0;    
    k=0;
    while (reply[k]!=0)             
      checksum+=reply[k++];         
    checksum=checksum%0x100;   
    
    while (usb_in_endpoint_busy(2) || usb_in_endpoint_halted(2)) {} 
    
    // prepare send buffer (usb))    
    if (reply_type != 0)
    {
        qbuf[0]=reply_type;
        qbuf[1]='$';
        if (k!=0)
          memcpy(qbuf+2, reply, k);
        k++;                            
    }
    else
    {
        qbuf[0]='$';
        if (k!=0)
          memcpy(qbuf+1, reply, k);                                
    }         
    qbuf[k+1]='#';
    gdb_hexstr(qbuf, checksum, 1, k+2);
        
    k=0;
    // count size
    while (qbuf[k++]!=0) {}                                   
    // send via usb
    if (usb_is_configured() && !usb_in_endpoint_halted(2) && !usb_in_endpoint_busy(2))    
      usb_send_in_buffer(2, k-1);                                                            
}

//
// right (s) to left (e) extraction of hex fmt bytes
//
unsigned long gdb_extract_bytes(unsigned char s, unsigned char e, unsigned char *msg)
{
    unsigned char i,j,k;
    unsigned long x;
    
    j=0;
    x=0;
    for (i=s;i>e;i--)
    {
            k=msg[i];            
            if (k > '9') k -= 7;
            (unsigned long)x=(unsigned long)x + (unsigned long)((unsigned long)(k&0xf) << j);
            j=j+4;            
    }          
    return(x);
}

unsigned char gdb_ahex2bin (unsigned char MSB, unsigned char LSB)
{  
 if (MSB > '9') MSB -= 7;   
 if (LSB > '9') LSB -= 7;   //
 return (MSB <<4) | (LSB & 0x0F);   
}  
