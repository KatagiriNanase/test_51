#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define LED1 P00

void Dri_Timer0_Init()
{
    //中断允许寄存器
    EA = 1;
    ET0 = 1;
    //TMOD寄存器（不可位寻址）定时16位工作模式，Gate关闭，不收外部引脚控制
    TMOD &= 0xF0;
    TMOD |= 0x01;

    //设置脉冲计数器初始值
    TL0 = 64614;
    TH0 = 64614 >> 8;

    //启动计数器（TCON寄存器）
    TR0 = 1;

}

void INT_Timer0_Handler() interrupt 1
{
    static u16 count = 0;//局部静态变量 只有此函数能用 且生命周期和整个程序相同
    //中断服务程序激活，对脉冲计数器进行重载
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