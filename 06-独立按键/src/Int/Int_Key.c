#include "Int_Key.h"
#include "Com_Util.h"
#define SW3 P42
#define SW4 P43
#define SW5 P32
#define SW6 P33



bit Int_Key_IsSW3Pressed()
{
    if (P42 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P42 == 0)
        {
            while (P42 == 0);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSW4Pressed()
{
    if (P43 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P43 == 0)
        {
            while (P43 == 0);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSW5Pressed()
{
    if (P32 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P32 == 0)
        {
            while (P32 == 0);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSW6Pressed()
{
    if (P33 == 0)
    {
        Com_Util_Delay1ms(10);
        if (P33 == 0)
        {
            while (P33 == 0);
            return 1;
        }
    }
    return 0;
}
