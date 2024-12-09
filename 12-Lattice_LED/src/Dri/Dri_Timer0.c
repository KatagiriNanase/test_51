/*
    ���˾���ע�ắ����ɾ������Ӧ���������Ա�Ĳ����ȽϺã�
    �����ܱ�ִ֤���жϷ�������ʱ��˳�򲻻ᱻ����
*/
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#include <STDIO.H>
#define MAX_CALLBACK_COUNT 4
static Timer0_Callback s_callbacks[MAX_CALLBACK_COUNT];

void Dri_Timer0_Init()
{
    u8 i;
    //�ж�����Ĵ���
    EA = 1;
    ET0 = 1;
    //TMOD�Ĵ���������λѰַ����ʱ16λ����ģʽ��Gate�رգ������ⲿ���ſ���
    TMOD &= 0xF0;
    TMOD |= 0x01;

    //���������������ʼֵ1ms
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //������������TCON�Ĵ�����
    TR0 = 1;

    //��ʼ������ָ������
    for (i = 0;i < MAX_CALLBACK_COUNT;++i)
        s_callbacks[i] = NULL;


}

bit Dir_Timer0_RegisterCallBack(Timer0_Callback callback)
{
    u8 i;
    //�жϺ�������ע��
    for (i = 0;i < MAX_CALLBACK_COUNT;++i)
    {
        if (s_callbacks[i] == callback)
            return 1;
    }

    for (i = 0;i < MAX_CALLBACK_COUNT;++i)
    {
        if (s_callbacks[i] == NULL)
        {
            s_callbacks[i] = callback;
            return 1;
        }
    }

    return 0;

}

bit Dir_Timer0_DeregisterCallBack(Timer0_Callback callback)
{
    u8 i;
    for (i = 0;i < MAX_CALLBACK_COUNT;++i)
    {
        if (s_callbacks[i] == callback)
        {
            s_callbacks[i] = NULL;
            return 1;
        }
    }

    return 0;
}


void Dri_Timer0_Handler() interrupt 1
{
    u8 i;
    //����װ��
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //��ѯ����ָ������
    for (i = 0;i < MAX_CALLBACK_COUNT;i++)
    {
        if (s_callbacks[i])
            s_callbacks[i]();
    }

}