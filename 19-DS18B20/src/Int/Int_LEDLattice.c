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

void Int_LEDLattice_Refresh_ByTimer0()
{
    u8 i;
    ROW = ~0x00;
    for (i = 0;i < 8;++i)
    {
        //������ʾ����
        if (i == 0)
            SER = 1;
        else
            SER = 0;
        //������λ�Ĵ���
        SCK = ~SCK;
        SCK = ~SCK;
        //RCK ����洢�Ĵ��������
        RCK = ~RCK;
        RCK = ~RCK;

        //���õ�ǰ������
        ROW = ~(s_buffer[i]);
        Com_Util_Delay1ms(1);

    }


}

void Int_LEDLattice_Refresh()
{
    u8 i;
    ROW = ~0x00;
    for (i = 0;i < 8;++i)
    {
        //������ʾ����
        if (i == 0)
            SER = 1;
        else
            SER = 0;
        //������λ�Ĵ���
        SCK = ~SCK;
        SCK = ~SCK;
        //RCK ����洢�Ĵ��������
        RCK = ~RCK;
        RCK = ~RCK;

        //���õ�ǰ������
        ROW = ~(s_buffer[i]);
        Com_Util_Delay1ms(1);

    }


}

