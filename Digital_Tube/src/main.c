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

//����ܵ�����ʾ
void DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    //���������
    SMG_EN = 0;

    //�ر�LED��
    LED_EN = 0;

    //λѡ
    position <<= 3;//00 xxx 000
    P1 &= 0xC7;//1100 0111 ������ ��P15 P14 P13����
    P1 |= position;//������ ���м�����ֵ��ֵ

    //��ѡ
    P0 = digital_num[num_code];

}



void main()
{
    while (1)
    {
        u8 tmp;//1111 1111
        //��ˮ������
        tmp = 0xFF;
        while (tmp)
        {
            P0 = tmp;
            tmp <<= 1;
            Delay1ms(10);
        }
        P0 = 0;
        Delay1ms(10);

        //��ˮ����ʧ
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