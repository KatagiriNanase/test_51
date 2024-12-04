#include "Com_Util.h"
#include <INTRINS.H>
void Com_Util_Delay1ms(u16 count)	//@11.0592MHz
{
    unsigned char data i, j;

    while (count--)
    {
        _nop_();
        i = 2;
        j = 199;
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