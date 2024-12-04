#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

#define SMG_EN P36
#define LED_EN P34

static u8 s_code_num[10] = {
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
static u8 s_buffer[8];

void Int_DigitalTube_Init()
{
    SMG_EN = 0;
    LED_EN = 0;
}

//����ܵ�����ʾ���ڲ�����������Ҫ��¶�ӿڣ�
static void Int_DigitalTube_DisplaySingle(u8 position, u8 num_code)
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
void Int_DigitalTube_DisplayNum(u32 num)//0-99999999 ����ѡ��
{
    u8 i;
    //�����Դ�����
    for (i = 0;i < 8;++i)
        s_buffer[i] = 0x00;//ȫ�����͵�ƽ



    if (num == 0)
    {
        s_buffer[7] = s_code_num[0];
        return;
    }
    //�����Դ�����
    i = 7;
    while (num > 0)
    {
        s_buffer[i] = s_code_num[num % 10];
        num /= 10;
        --i;
    }

}

//���ζ�̬ɨ��
void Int_DigitalTube_Refresh()
{
    u8 i;
    for (i = 0;i < 8;++i)
    {
        Int_DigitalTube_DisplaySingle(i, s_buffer[i]);
        Com_Util_Delay200us();
        //Com_Util_Delay1ms(1);
    }
}