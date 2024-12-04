#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

#define SMG_EN P36
#define LED_EN P34

static u8 s_code_num[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

//存放每位段选编码
static u8 s_buffer[8];

void Int_DigitalTube_Init()
{
    SMG_EN = 0;
    LED_EN = 0;
}

//数码管单个显示（内部函数，不需要暴露接口）
static void Int_DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    //置零 防止重影
    P0 = 0x00;

    //位选
    position <<= 3;//00 xxx 000
    P1 &= 0xC7;//1100 0111 与运算 将P15 P14 P13置零
    P1 |= position;//或运算 将中间三个值赋值

    //段选
    P0 = num_code;


}



//设置显存数组
void Int_DigitalTube_DisplayNum(u32 num)//0-99999999 所以选择
{
    u8 i;
    //清零显存数组
    for (i = 0;i < 8;++i)
        s_buffer[i] = 0x00;//全部给低电平



    if (num == 0)
    {
        s_buffer[7] = s_code_num[0];
        return;
    }
    //设置显存数组
    i = 7;
    while (num > 0)
    {
        s_buffer[i] = s_code_num[num % 10];
        num /= 10;
        --i;
    }

}

//单次动态扫描
void Int_DigitalTube_Refresh()
{
    u8 i;
    for (i = 0;i < 8;++i)
    {
        Int_DigitalTube_DisplaySingle(i, s_buffer[i]);
        Com_Util_Delay200us();
        //Com_Util_Delay1ms(1);
    }
}