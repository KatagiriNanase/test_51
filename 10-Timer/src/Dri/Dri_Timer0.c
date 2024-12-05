#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define LED1 P00

void Dri_Timer0_Init()
{
    //�ж�����Ĵ���
    EA = 1;
    ET0 = 1;
    //TMOD�Ĵ���������λѰַ����ʱ16λ����ģʽ��Gate�رգ������ⲿ���ſ���
    TMOD &= 0xF0;
    TMOD |= 0x01;

    //���������������ʼֵ
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //������������TCON�Ĵ�����
    TR0 = 1;

}

void INT_Timer0_Handler() interrupt 1
{
    static u16 count = 0;//�ֲ���̬���� ֻ�д˺������� ���������ں�����������ͬ
    //�жϷ�����򼤻�������������������
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //LED
    count++;
    if (count >= 500)
    {
        LED1 = ~LED1;
        count = 0;
    }
}