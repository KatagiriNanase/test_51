#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define LED1 P00

void Int_LED1_Flash()
{
    static u16 count = 0;
    count++;
    if (count >= 500)
    {
        LED1 = ~LED1;
        count = 0;
    }

}
void main()
{
    Dri_Timer0_Init();
    Dir_Timer0_RegisterCallBack(Int_LED1_Flash);
    while (1)
    {

    }
}