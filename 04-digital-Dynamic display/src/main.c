#include <STC89C5xRC.H>
#include <INTRINS.H>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

#define SMG_EN P36
#define LED_EN P34

static u8 code_num[10] = {
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

//存放每位段选编码
static u8 buffer[8];

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

void Delay200us(void)	//@11.0592MHz
{
    unsigned char data i, j;

    i = 3;
    j = 35;
    do
    {
        while (--j);
    } while (--i);
}


//数码管单个显示
void DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    //置零 防止重影
    P0 = 0x00;

    //位选
    position <<= 3;//00 xxx 000
    P1 &= 0xC7;//1100 0111 与运算 将P15 P14 P13置零
    P1 |= position;//或运算 将中间三个值赋值

    //段选
    P0 = num_code;


}

//设置显存数组
void DigitalTube_DisplayNum(u32 num)//0-99999999 所以选择
{
    u8 i;
    //清零显存数组
    for (i = 0;i < 8;++i)
        buffer[i] = 0x00;//全部给低电平



    if (num == 0)
    {
        buffer[7] = code_num[0];
        return;
    }
    //设置显存数组
    i = 7;
    while (num > 0)
    {
        buffer[i] = code_num[num % 10];
        num /= 10;
        --i;
    }

}

//动态扫描
void DigitalTube_Refresh()
{
    u8 i;
    for (i = 0;i < 8;++i)
    {
        DigitalTube_DisplaySingle(i, buffer[i]);
        Delay200us();
    }
}

void main()
{
    LED_EN = 0;
    SMG_EN = 0;
    DigitalTube_DisplayNum(114514);
    while (1)
        DigitalTube_Refresh();
}