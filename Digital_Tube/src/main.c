#include <STC89C5xRC.H>
#include<INTRINS.H>
typedef unsigned char u8;
#define SMG_EN P36
#define LED_EN P34


void Delay500us(void)	//@11.0592MHz
{
    unsigned char data i, j;

    _nop_();
    _nop_();
    i = 6;
    j = 93;
    do
    {
        while (--j);
    } while (--i);
}

void Delay1ms(u8 count)	//@11.0592MHz
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



static u8 digital_num[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

//数码管单个显示
void DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    //开启数码管
    SMG_EN = 0;

    //关闭LED灯
    LED_EN = 0;

    //位选
    position <<= 3;//00 xxx 000
    P1 &= 0xC7;//1100 0111 与运算 将P15 P14 P13置零
    P1 |= position;//或运算 将中间三个值赋值

    //段选
    P0 = digital_num[num_code];

}



void main()
{
    while (1)
    {
        u8 tmp;//1111 1111
        //流水灯右移
        tmp = 0xFF;
        while (tmp)
        {
            P0 = tmp;
            tmp <<= 1;
            Delay1ms(10);
        }
        P0 = 0;
        Delay1ms(10);

        //流水灯消失
        tmp = 0xFF;
        while (tmp)
        {
            P0 = ~tmp;
            tmp <<= 1;
            Delay1ms(10);
        }

        P0 = 0xFF;
        Delay1ms(10);

    }
}