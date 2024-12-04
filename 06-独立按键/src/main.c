#include "Int_Key.h"
#include <STC89C5xRC.H>

#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03

void main()
{
    while (1)
    {
        if (Int_Key_IsSw3Pressed())
            LED1 = ~LED1;
        if (Int_Key_IsSw4Pressed())
            LED2 = ~LED2;
        if (Int_Key_IsSw5Pressed())
            LED3 = ~LED3;
        if (Int_Key_IsSw6Pressed())
            LED4 = ~LED4;
    }
}