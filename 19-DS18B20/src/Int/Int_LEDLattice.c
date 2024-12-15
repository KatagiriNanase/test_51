#include "Int_LEDLattice.h"
#include <STC89C5xRC.H>
#include "Dri_Timer0.h"
#define LED_LATTICE_EN P35
#define LED_EN P34
#define SER P10
#define SCK P12
#define RCK P11
#define ROW P0
//点阵屏显存数组 全局变量默认为0
static u8 s_buffer[8];
void Int_LEDLattice_Refresh_ByTimer0();

void Int_LEDLattice_Init()
{
    //关闭LED流水灯
    LED_EN = 0;
    //开启使能开关
    LED_LATTICE_EN = 0;


    //
    Dir_Timer0_RegisterCallBack(Int_LEDLattice_Refresh_ByTimer0);
}

void Int_LEDLattice_SetPic(u8 pic[])
{
    u8 i;

    //放置显示内容
    for (i = 0;i < 8;++i)
        s_buffer[i] = pic[i];

}

void Int_LEDLattice_Refresh_ByTimer0()
{
    u8 i;
    ROW = ~0x00;
    for (i = 0;i < 8;++i)
    {
        //设置显示哪行
        if (i == 0)
            SER = 1;
        else
            SER = 0;
        //载入移位寄存器
        SCK = ~SCK;
        SCK = ~SCK;
        //RCK 存入存储寄存器并输出
        RCK = ~RCK;
        RCK = ~RCK;

        //设置当前行内容
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
        //设置显示哪行
        if (i == 0)
            SER = 1;
        else
            SER = 0;
        //载入移位寄存器
        SCK = ~SCK;
        SCK = ~SCK;
        //RCK 存入存储寄存器并输出
        RCK = ~RCK;
        RCK = ~RCK;

        //设置当前行内容
        ROW = ~(s_buffer[i]);
        Com_Util_Delay1ms(1);

    }


}

