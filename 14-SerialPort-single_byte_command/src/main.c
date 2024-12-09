#include "Dri_UART.h"
#include "Com_Util.h"
#include <STC89C5xRC.H>
void main()
{
    u8 receive_char = 0;
    Dri_UART_Init();
    while (1)
    {
        
        if (Dri_UART_ReceiveChar(&receive_char))
        {
            if (receive_char == 'A')
            {
                P0 = 0x00;
                Dri_UART_SendStr("LED is on! ");
            }

            else if (receive_char == 'B')
            {
                P0 = 0xFF;
                Dri_UART_SendStr("LED is off! ");
            }

            else
                Dri_UART_SendStr("What can I say? ");


        }
    }
}