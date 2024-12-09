#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
static bit s_is_sending = 0;//0:δ�ڷ������� 1:���ڷ�������
static char s_buffer = 0;//��ȡ���ջ����������ݵ���ʱ����
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


}

bit Dri_UART_ReceiveChar(u8* pc)
{
    if (!s_buffer)
        return 0;
    if (s_buffer)
    {
        *pc = s_buffer;
        s_buffer = 0;
        return 1;
    }

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



void Dri_UART_Handler() interrupt 4
{
    if (RI)
    {
        s_buffer = SBUF;
        RI = 0;
    }

    if (TI)
    {
        s_is_sending = 0;
        TI = 0;
    }
}