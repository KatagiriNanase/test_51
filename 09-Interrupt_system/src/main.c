#include <STC89C5xRC.H>
#include "Com_Util.h"
#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03

void Dri_INT0_Init()
{
    //启用中断
    EA = 1;
    EX0 = 1;

    //选择中断模式（下沿）
    IT0 = 1;

    //设置中断优先级（可选）

}

void Dri_INT1_Init()
{
    EA = 1;
    EX1 = 1;

    IT1 = 1;
}

void Dri_INT2_Init()
{
    EA = 1;
    EX2 = 1;

    IT2 = 1;
}
void Dri_INT3_Init()
{
    EA = 1;
    EX3 = 1;

    IT3 = 1;
}

void main()
{
    Dri_INT0_Init();
    Dri_INT1_Init();
    Dri_INT2_Init();
    Dri_INT3_Init();

    while (1)
    {

    }
}


void INT0_Handle() interrupt 0
{
    Com_Util_Delay1ms(10);
    if (INT0 == 0)
        LED3 = ~LED3;
}

void INT1_Handle() interrupt 2
{
    Com_Util_Delay1ms(10);
    if (INT1 == 0)
        LED4 = ~LED4;
}

void INT2_Handle() interrupt 6
{
    Com_Util_Delay1ms(10);
    if (P43 == 0)
        LED2 = ~LED2;
}

void INT3_Handle() interrupt 7
{
    Com_Util_Delay1ms(10);
    if (P42 == 0)
        LED1 = ~LED1;
}