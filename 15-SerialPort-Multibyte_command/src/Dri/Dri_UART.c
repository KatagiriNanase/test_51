#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#include "Dri_Timer0.h"
static bit s_is_sending = 0;//0:未在发送数据 1:正在发送数据
static char s_buffer[16] = { 0 };//读取接收缓冲区的数据的临时变量

static u8 s_buffer_index = 0;
static u8 s_idle_count = 0;

static bit s_IsComplete = 0;

//定时器每一毫秒触发中断 让s_idle_count+1
void Dri_UART_Timer0CallBack()
{
    s_idle_count++;
    if (s_buffer_index > 0 && s_idle_count >= 10)//如果直接判断大于十秒 那我如果永远都没有写过数据 还是会进if
    {
        s_IsComplete = 1;
    }
}

void Dri_UART_Init()
{
    //1.Timer1初始化

    TMOD &= 0x0F;
    TMOD |= 0x20;

    //设置波特率
    PCON &= 0x7F;
    TH1 = 0xFD;
    TL1 = 0xFD;

    //启动定时器
    TR1 = 1;

    //2.串口通信初始化
    //工作模式
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;
    //接收使能
    REN = 1;

    //3.开启串口中断
    EA = 1;
    ES = 1;

    //标志位置零
    RI = 0;
    TI = 0;

    //4.注册空闲检测函数
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