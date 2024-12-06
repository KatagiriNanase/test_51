/*
    个人觉得注册函数和删除函数应该引入线性表的操作比较好，
    这样能保证执行中断服务程序的时候顺序不会被打乱
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
    //中断允许寄存器
    EA = 1;
    ET0 = 1;
    //TMOD寄存器（不可位寻址）定时16位工作模式，Gate关闭，不收外部引脚控制
    TMOD &= 0xF0;
    TMOD |= 0x01;

    //设置脉冲计数器初始值1ms
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //启动计数器（TCON寄存器）
    TR0 = 1;

    //初始化函数指针数组
    for (i = 0;i < MAX_CALLBACK_COUNT;++i)
        s_callbacks[i] = NULL;


}

bit Dir_Timer0_RegisterCallBack(Timer0_Callback callback)
{
    u8 i;
    //判断函数有无注册
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
    //重新装载
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //轮询函数指针数组
    for (i = 0;i < MAX_CALLBACK_COUNT;i++)
    {
        if (s_callbacks[i])
            s_callbacks[i]();
    }

}