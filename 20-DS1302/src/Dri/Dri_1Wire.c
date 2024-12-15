#include "Dri_1Wire.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define BUS P44 // 1wire 总线


bit Dri_1Wire_Init()
{
    bit exist = 0;
    BUS = 0;
    //延时480us
    Com_Util_Delay480us();
    //释放总线
    BUS = 1;
    //延时等待存在脉冲
    Com_Util_Delay60us();
    exist = ~BUS;
    Com_Util_Delay420us();
    return exist;
}

void Dri_1Wire_WriteByte(u8 byte)
{
    u8 i;
    for (i = 0;i < 8;++i)
    {
            BUS = 0;
            //延时一秒
            BUS = byte & 0x01;
            byte >>= 1;
            //延时60us满足一个写时段
            Com_Util_Delay60us();
            //释放总线，准备进行下一时段
            BUS = 1;
    }
}

u8 Dri_1Wire_ReadByte()
{
    u8 i;
    u8 byte = 0;
    for (i = 0;i < 8;++i)
    {
        BUS = 0;
        //延时一秒
        //释放总线
        BUS = 1;
        Com_Util_Delay10us();
        byte >>= 1;
        if (BUS == 1)
            byte |= 0x80;
        //保证时段满足60us
        Com_Util_Delay50us();
    }
    return byte;
}
