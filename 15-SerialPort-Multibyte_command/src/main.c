#include "Dri_UART.h"
#include "Com_Util.h"
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include <STRING.H>


void main()
{

    u8 receive_str[16] = { 0 };
    Dri_Timer0_Init();
    Dri_UART_Init();

    while (1)
    {
        u8 i = 0;

        if (Dri_UART_ReceiveStr(receive_str))
        {
            if (!strcmp(receive_str, "bili"))
            {
                P0 = 0x00;
                Dri_UART_SendStr("bilibili~ cheer");
            }

            else if (!strcmp(receive_str, "heart"))
            {
                P0 = 0xFF;
                Dri_UART_SendStr("heart is broken TAT");
            }

            else
                Dri_UART_SendStr("What can I say? ");
        }
    }
}