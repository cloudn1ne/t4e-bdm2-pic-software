/*
 *  BDM2USB
 *  Version 1.0
 *  (c) 2016, Georg Swoboda <cn@warp.at>
 */

#ifndef GDB_STUB_H
#define	GDB_STUB_H

#ifdef	__cplusplus
extern "C" {
#endif

// GDB Serial buffer
#define GDB_BUF_SIZE            96 // 96
#define GDB_MSG_SIZE            64 // 64
unsigned char gdb_buf[GDB_BUF_SIZE];
unsigned char gdb_buf_idx=0;
// unsigned char gdb_buf_len=0;

/*
 * GDB Stub Functions
 */
void            gdb_process_command(unsigned char *msg, unsigned char msg_len);
void            gdb_send(char reply_type, unsigned char *reply);
unsigned char   gdb_ahex2bin(unsigned char MSB, unsigned char LSB);
unsigned long   gdb_extract_bytes(unsigned char s, unsigned char e, unsigned char *msg);
void            gdb_hexstr(char *buf, unsigned long val, unsigned char len, unsigned char offset);
void            gdb_send_start(char reply_type, char *chksum);
void            gdb_send_data(unsigned char *reply, char *chksum);
void            gdb_send_end(char *chksum);


#ifdef	__cplusplus
}
#endif

#endif	/* GDB_STUB_H */

