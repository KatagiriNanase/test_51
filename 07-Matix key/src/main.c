#include "Int_KeyMatrix.h"
#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

void main()
{
    u8 key=0;
    Int_DigitalTube_Init();
    while (1)
    {
        key = Int_KeyMatrix_CheckSW();

        if (key)
        {
            Int_DigitalTube_DisplayNum(key);
        }
        Int_DigitalTube_Refresh();
    }
}