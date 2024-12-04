#include "Int_Buzzer.h"
#include "Com_Util.h"
#include "Int_DigitalTube.h"
void main()
{
    u8 key = 0;
    Int_DigitalTube_Init();
    while (1)
    {
        key = Int_KeyMatrix_CheckSW();

        if (key)
        {
            Int_DigitalTube_DisplayNum(key);
            Int_Buzzer_Buzz();
        }
        Int_DigitalTube_Refresh();
    }
}