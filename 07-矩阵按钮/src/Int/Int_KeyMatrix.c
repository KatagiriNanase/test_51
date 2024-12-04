#include "Int_KeyMatrix.h"
#include <STC89C5xRC.H>


u8 Int_KeyMatrix_CheckSW()
{
    u8  i;
    //检测第一行
    P2 = 0xFE;

    if (P24 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P24 == 0)
        {
            while (P24 == 0);
            return 7;
        }
    }
    if (P25 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P25 == 0)
        {
            while (P25 == 0);
            return 8;
        }
    }
    if (P26 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P26 == 0)
        {
            while (P26 == 0);
            return 9;
        }
    }
    if (P27 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P27 == 0)
        {
            while (P27 == 0);
            return 10;
        }
    }

    //检测第二行
    P2 = 0xFD;
    if (P24 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P24 == 0)
        {
            while (P24 == 0);
            return 11;
        }
    }
    if (P25 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P25 == 0)
        {
            while (P25 == 0);
            return 12;
        }
    }
    if (P26 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P26 == 0)
        {
            while (P26 == 0);
            return 13;
        }
    }
    if (P27 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P27 == 0)
        {
            while (P27 == 0);
            return 14;
        }
    }
    //检测第三行
    P2 = 0xFB;
    if (P24 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P24 == 0)
        {
            while (P24 == 0);
            return 15;
        }
    }
    if (P25 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P25 == 0)
        {
            while (P25 == 0);
            return 16;
        }
    }
    if (P26 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P26 == 0)
        {
            while (P26 == 0);
            return 17;
        }
    }
    if (P27 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P27 == 0)
        {
            while (P27 == 0);
            return 18;
        }
    }

    //检测第四行
    P2 = 0xF7;
    if (P24 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P24 == 0)
        {
            while (P24 == 0);
            return 19;
        }
    }
    if (P25 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P25 == 0)
        {
            while (P25 == 0);
            return 20;
        }
    }
    if (P26 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P26 == 0)
        {
            while (P26 == 0);
            return 21;
        }
    }
    if (P27 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P27 == 0)
        {
            while (P27 == 0);
            return 22;
        }
    }
    return 0;
}