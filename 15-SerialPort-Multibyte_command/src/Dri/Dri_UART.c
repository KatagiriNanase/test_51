#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#include "Dri_Timer0.h"
static bit s_is_sending = 0;//0:δ�ڷ������� 1:���ڷ�������
static char s_buffer[16] = { 0 };//��ȡ���ջ����������ݵ���ʱ����

static u8 s_buffer_index = 0;
static u8 s_idle_count = 0;

static bit s_IsComplete = 0;

//��ʱ��ÿһ���봥���ж� ��s_idle_count+1
void Dri_UART_Timer0CallBack()
{
    s_idle_count++;
    if (s_buffer_index > 0 && s_idle_count >= 10)//���ֱ���жϴ���ʮ�� ���������Զ��û��д������ ���ǻ��if
    {
        s_IsComplete = 1;
    }
}

void Dri_UART_Init()
{
    //1.Timer1��ʼ��

    TMOD &= 0x0F;
    TMOD |= 0x20;

    //���ò�����
    PCON &= 0x7F;
    TH1 = 0xFD;
    TL1 = 0xFD;

    //������ʱ��
    TR1 = 1;

    //2.����ͨ�ų�ʼ��
    //����ģʽ
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;
    //����ʹ��
    REN = 1;

    //3.���������ж�
    EA = 1;
    ES = 1;

    //��־λ����
    RI = 0;
    TI = 0;

    //4.ע����м�⺯��
    Dir_Timer0_RegisterCallBack(Dri_UART_Timer0CallBack);
}




void Dri_UART_SendChar(char c)
{
    while (s_is_sending == 1);
    s_is_sending = 1;
    SBUF = c;
}

void Dri_UART_SendStr(char* str)
{
    u8 i = 0;
    while (str[i] != '\0')
    {
        Dri_UART_SendChar(str[i]);
        ++i;
    }
}

bit Dri_UART_ReceiveStr(u8* ps)
{

    if (s_IsComplete)
    {
        u8 i;
        for (i = 0;i < s_buffer_index;i++)
            ps[i] = s_buffer[i];
        ps[i] = '\0';

        s_IsComplete = 0;
        s_buffer_index = 0;
        return 1;

    }

    return 0;
}


void Dri_UART_Handler() interrupt 4
{

    if (RI)
    {
        s_idle_count = 0;
        s_buffer[s_buffer_index] = SBUF;
        s_buffer_index++;
        RI = 0;
    }

    if (TI)
    {
        s_is_sending = 0;
        TI = 0;
    }
}