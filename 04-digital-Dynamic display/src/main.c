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

//���ÿλ��ѡ����
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


//����ܵ�����ʾ
void DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    //���� ��ֹ��Ӱ
    P0 = 0x00;

    //λѡ
    position <<= 3;//00 xxx 000
    P1 &= 0xC7;//1100 0111 ������ ��P15 P14 P13����
    P1 |= position;//������ ���м�����ֵ��ֵ

    //��ѡ
    P0 = num_code;


}

//�����Դ�����
void DigitalTube_DisplayNum(u32 num)//0-99999999 ����ѡ��
{
    u8 i;
    //�����Դ�����
    for (i = 0;i < 8;++i)
        buffer[i] = 0x00;//ȫ�����͵�ƽ



    if (num == 0)
    {
        buffer[7] = code_num[0];
        return;
    }
    //�����Դ�����
    i = 7;
    while (num > 0)
    {
        buffer[i] = code_num[num % 10];
        num /= 10;
        --i;
    }

}

//��̬ɨ��
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