#include "Int_OLED.h"
void main()
{
    Int_OLED_Init();
    Int_OLED_Clear();
    Int_OLED_ShowStr(0, 0, " You woke me up");
    Int_OLED_ShowStr(4, 2, "\"Master\"");
    Int_OLED_ShowStr(4, 3, "-1368843");
    while (1)
    {

    }
}