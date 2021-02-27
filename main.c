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

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>         /* for printf via putch */
#include <stdlib.h> 
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "usb/include/usb.h"
#include "usb_config.h"
#include "usb/include/usb_ch9.h"
#include "usb/include/usb_cdc.h"
#include "gdb_stub.h"
#include "mpc_bdm.h"


 // #define    DBG_SERIAL       1

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{    
    unsigned char i,k,s,e;    
    unsigned char checksum;
    unsigned long msg_checksum;
    unsigned char msg[GDB_MSG_SIZE]="";
    unsigned char msg_len;
    unsigned char buf_start=0;
    unsigned char buf_end=0;
    unsigned char buf_start_found=0;
    unsigned char buf_end_found=0;
    //unsigned char buf_checksum_ok=0;        
    unsigned long c;
    
//    unsigned long t;
  //  unsigned long r0,r1,r2,r3,c,icr,msr;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
     /* Initialize I/O and Peripherals for application */
    InitApp();
    /* Initialize USB Stack */
    usb_init();
    /* show that we are ready */
    led_flash(3);
    /* init BDM */
    bdm_init();    
    c=0;
    // while(1) {}
        
  
            //  Application Loop
    while (1) 
    {                                
                if (check_freeze > 0)       // are we single stepping, or continuing ?
                {
                    c=bdm_nop();   
                    __delay_ms(10);
                    if ((c&0x40) == 0x40)   // scan for freeze bit set in reply from target   
                    {
                        //bdm_get_spr(MPC8XX_SPR_ICR);
                        //bdm_set_word( 0x2FC004, 0xFF80 );    // kill watchdog 
                        if (check_freeze == 1)
                            gdb_send('+',"T05");
                        if (check_freeze == 2)
                            gdb_send('+',"S05");                        
                        check_freeze=0;     // disable check until next time
                    }                      
                }
                // process input via USB
                if (usb_is_configured() && !usb_out_endpoint_halted(2) && usb_out_endpoint_has_data(2)) 
                {
                    const unsigned char *out_buf;
                    size_t out_buf_len;                   
                   // LED=HIGH;
                    out_buf_len = usb_get_out_buffer(2, &out_buf);
                    if (out_buf_len > 0)                        
                    {                           
                        for (i=0;i<out_buf_len;i++)
                        {                           
                            if (gdb_buf_idx < GDB_BUF_SIZE-1)
                            {
                                if (out_buf[i]=='\x03') {  bdm_interrupt(); }
                                gdb_buf[gdb_buf_idx++] = out_buf[i];
                            }
                            else
                            {                                 
                                gdb_buf_idx=0;  
#ifdef DBG_SERIAL                                 
                                printf("**** error buffer overrun\r\n");
#endif
                                goto no_msg;                           
                            }                        
                        }                                
                    }                    
                    //LED=LOW;                    
                    gdb_buf[gdb_buf_idx]=0;
                    
#ifdef DBG_SERIAL                
                    
                    printf("\r\ncopied %d bytes to gdb_buf, gdb_buf_idx=%d\r\n", i, gdb_buf_idx);
                    printf("gdb_buf = '%s'\r\n", gdb_buf);
#endif                                       
                    
                    /*
                     *  now iterate over gdb_buf[] and extract any messages
                     */
                    i=0;
                    buf_end_found=0;
                    buf_start_found=0;
                    buf_start=0; 
                    buf_end=0;
                    while (i < gdb_buf_idx)
                    {   
#ifdef DBG_SERIAL                            
                        printf("buf_start=%d buf_end=%d\r\n",buf_start,buf_end);
#endif                                                
                        // find start '$'                              
                        for (s=i;s<gdb_buf_idx;s++)
                        {
                            if (gdb_buf[s]=='$') { buf_start=s; buf_start_found=1; break; }
                        }
                    
                        // find end '\n'                       
                        for (e=i+1;e<gdb_buf_idx;e++)
                        {
                            if (gdb_buf[e]=='#') { buf_end=e; buf_end_found=1; break; }
                        }       
                                          
                        if (buf_start_found && buf_end_found && (buf_end-buf_start) > 0)
                        {
                                // parse checksum bytes                    
                                checksum=gdb_ahex2bin (gdb_buf[buf_end+1], gdb_buf[buf_end+2]);                 
#ifdef DBG_SERIAL                                    
                                printf("gdb_buf_checksum bytes #%c%c ", gdb_buf[buf_end+1], gdb_buf[buf_end+2]);                                 
#endif                                
                                // verify checksum                    
                                msg_len=buf_end-buf_start-1;    
                                msg_checksum=0;
                                for (k=0;k<msg_len;k++)
                                {
                                    msg[k]=gdb_buf[buf_start+k+1];
                                    msg_checksum+=msg[k];
                                }
                                msg[k]=0;  
                                msg_checksum=msg_checksum%0x100;                                
                                if (msg_checksum==checksum)                                    
                                {   
#ifdef DBG_SERIAL                                    
                                    printf(" -> msg is '%s' (%d)\r\n", msg, msg_len); 
#endif                                    
                                    LED=HIGH;
                                    gdb_process_command(&msg, msg_len);
                                    LED=LOW;
                                }                                                                 
                                buf_end_found=0;                                
                                buf_start_found=0;                                                  
                                i=buf_end;
                        }
                        i++;                                             
                    
#ifdef DBG_SERIAL                           
                        printf("i=%d\r\n", i);                                                
#endif                        
                    }                    
#ifdef DBG_SERIAL    
                    printf("-----------------------------------------------------------------\r\n");
                    printf("processing finished gdb_buf_idx = %d, last found end was: %d\r\n", gdb_buf_idx, e);
#endif                    
                    if (!buf_end_found)
                    {
                        for (i=0;i<gdb_buf_idx-buf_start;i++)
                            gdb_buf[i]=gdb_buf[i+buf_start];
                        
                        gdb_buf_idx=gdb_buf_idx-buf_start;
                    //    printf("no end found\r\n");
                    }
                    
                 
                    if (!buf_start_found && !buf_end_found)                    
                        gdb_buf_idx=0;                                                           

#ifdef DBG_SERIAL               
                   printf("\r\nfinal buf_idx=%d\r\n", gdb_buf_idx);
                   printf("gdb_buf = '%s'\r\n", gdb_buf);
                   printf("\r\n"); 
#endif     
               
                    
no_msg:
                    usb_arm_out_endpoint(2);
                }                                                                                                                                         
     }
}



/******************************************************************************/
/* USB CALLBACKS                                                              */
/******************************************************************************/
/* These function names are set in usb_config.h. */
void app_set_configuration_callback(uint8_t configuration)
{

}

uint16_t app_get_device_status_callback()
{
        return 0x0000;
}

void app_endpoint_halt_callback(uint8_t endpoint, bool halted)
{

}

int8_t app_set_interface_callback(uint8_t interface, uint8_t alt_setting)
{
        return 0;
}

int8_t app_get_interface_callback(uint8_t interface)
{
        return 0;
}

void app_out_transaction_callback(uint8_t endpoint)
{

}

void app_in_transaction_complete_callback(uint8_t endpoint)
{

}

int8_t app_unknown_setup_request_callback(const struct setup_packet *setup)
{
        /* To use the CDC device class, have a handler for unknown setup
         * requests and call process_cdc_setup_request() (as shown here),
         * which will check if the setup request is CDC-related, and will
         * call the CDC application callbacks defined in usb_cdc.h. For
         * composite devices containing other device classes, make sure
         * MULTI_CLASS_DEVICE is defined in usb_config.h and call all
         * appropriate device class setup request functions here.
         */
        return process_cdc_setup_request(setup);
}

int16_t app_unknown_get_descriptor_callback(const struct setup_packet *pkt, const void **descriptor)
{
        return -1;
}

void app_start_of_frame_callback(void)
{

}

void app_usb_reset_callback(void)
{

}

/* CDC Callbacks. See usb_cdc.h for documentation. */

int8_t app_send_encapsulated_command(uint8_t interface, uint16_t length)
{
        return -1;
}

int16_t app_get_encapsulated_response(uint8_t interface,
                                      uint16_t length, const void **report,
                                      usb_ep0_data_stage_callback *callback,
                                      void **context)
{
        return -1;
}

void app_set_comm_feature_callback(uint8_t interface,
                                     bool idle_setting,
                                     bool data_multiplexed_state)
{

}

void app_clear_comm_feature_callback(uint8_t interface,
                                       bool idle_setting,
                                       bool data_multiplexed_state)
{

}

int8_t app_get_comm_feature_callback(uint8_t interface,
                                     bool *idle_setting,
                                     bool *data_multiplexed_state)
{
        return -1;
}

void app_set_line_coding_callback(uint8_t interface,
                                    const struct cdc_line_coding *coding)
{

}

int8_t app_get_line_coding_callback(uint8_t interface,
                                    struct cdc_line_coding *coding)
{
        /* This is where baud rate, data, stop, and parity bits are set. */
        return -1;
}

int8_t app_set_control_line_state_callback(uint8_t interface,
                                           bool dtr, bool dts)
{
        return 0;
}

int8_t app_send_break_callback(uint8_t interface, uint16_t duration)
{
        return 0;
}


/*
 *  printf output function - called char by char
 */
void putch(unsigned char byte)
{   
   // usb send buffer ptr
   static unsigned char usb_send_buf_ptr=0;
   unsigned char *buf = usb_get_in_buffer(2);
   
   if (usb_is_configured() && !usb_in_endpoint_halted(2))
   {
        if ( !usb_in_endpoint_busy(2) ) 
        {                
           buf[usb_send_buf_ptr++]=byte;   
           if (byte=='\n' || usb_send_buf_ptr == EP_2_IN_LEN-1)
           {
            usb_send_in_buffer(2, usb_send_buf_ptr);
            usb_send_buf_ptr=0;
           }      
           while (usb_in_endpoint_busy(2)) {  }           
           return;
        }
        if ( usb_in_endpoint_busy(2) )
        {
            // endpoint is busy - so we queue the data
            if (usb_send_buf_ptr < EP_2_IN_LEN-5)
                buf[usb_send_buf_ptr++]=byte;
            // else - we have to drop it !           
        }
   }
}

