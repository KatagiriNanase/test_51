#include "Int_Buzzer.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define BUZZER P46

//蜂鸣器以500hz响0.1s
void Int_Buzzer_Buzz()
{
    u8 count = 100;
    while (count--)
    {
        BUZZER = ~BUZZER;
        Com_Util_Delay1ms(1);//一个周期2ms 频率500hz
    }
}