#include <STC89C5xRC.H>


void Delay100ms(void)	//@11.0592MHz
{
    unsigned char data i, j;

    i = 180;
    j = 73;
    do
    {
        while (--j);
    } while (--i);
}

void main()//³äµçµÆ
{
    unsigned char tmp = 0xFF; //1111 1111

    while (1)
    {
        P0 = tmp; //1111 1111 /0111 1111 /0011 1111/0000 0000
        Delay100ms();
        tmp <<= 1;

        if (tmp == 0x00)
        {
            P0 = 0x00;
            tmp = 0xFF;
            Delay100ms();
        }
    }
}