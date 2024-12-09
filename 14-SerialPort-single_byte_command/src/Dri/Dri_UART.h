#ifndef __DRI_UART_H__
#define __DRI_UART_H__
#include "Com_Util.h"
void Dri_UART_Init();

void Dri_UART_SendChar(char c);

void Dri_UART_SendStr(char* str);

bit Dri_UART_ReceiveChar(u8* pc);


#endif /* __DRI_UART_H__ */