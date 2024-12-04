#include "Com_Util.h"
#include <INTRINS.H>
void Com_Util_Delay1ms(u8 count)	//@11.0592MHz
{
    unsigned char data i, j;

    while (count--)
    {
        _nop_();
        _nop_();
        _nop_();
        i = 11;
        j = 190;
        do
        {
            while (--j);
        } while (--i);
    }

}

void Com_Util_Delay200us(void)	//@11.0592MHz
{
    unsigned char data i, j;

    i = 3;
    j = 35;
    do
    {
        while (--j);
    } while (--i);
}