#ifndef __COM__UTIL__H__
#define __COM__UTIL__H__
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

void Com_Util_Delay1ms(u16 count);	//@11.0592MHz
void Com_Util_Delay200us(void);
void Com_Util_Delay10us();
void Com_Util_Delay60us(void);
void Com_Util_Delay480us(void);
void Com_Util_Delay420us(void);
void Com_Util_Delay50us(void);
#endif