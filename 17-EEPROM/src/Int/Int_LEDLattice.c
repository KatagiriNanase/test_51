#include "Int_LEDLattice.h"
#include <STC89C5xRC.H>
#include "Dri_Timer0.h"
#define LED_LATTICE_EN P35
#define LED_EN P34
#define SER P10
#define SCK P12
#define RCK P11
#define ROW P0
//�������Դ����� ȫ�ֱ���Ĭ��Ϊ0
static u8 s_buffer[8];
void Int_LEDLattice_Refresh_ByTimer0();

void Int_LEDLattice_Init()
{
    //�ر�LED��ˮ��
    LED_EN = 0;
    //����ʹ�ܿ���
    LED_LATTICE_EN = 0;


    //
    Dir_Timer0_RegisterCallBack(Int_LEDLattice_Refresh_ByTimer0);
}

void Int_LEDLattice_SetPic(u8 pic[])
{
    u8 i;

    //������ʾ����
    for (i = 0;i < 8;++i)
        s_buffer[i] = pic[i];

}

void Int_LEDLattice_Shift(u8 row_pic)
{
    u8 i;
    //�ƶ�ԭ��buffer������ǰ��λ������
    for (i = 7;i > 0;--i)
        s_buffer[i] = s_buffer[i - 1];

    s_buffer[0] = row_pic;
}



void Int_LEDLattice_Refresh_ByTimer0()
{
    static u8 i = 0;
    ROW = ~0x00;
    if (i == 0)
        SER = 1;
    else
        SER = 0;

    //������ʾ��
    SCK = 0;
    SCK = 1;
    RCK = 0;
    RCK = 1;

    //���õ�ǰ����ʾ����
    ROW = ~(s_buffer[i]);


    ++i;
    if (i == 8)
        i = 0;

}
