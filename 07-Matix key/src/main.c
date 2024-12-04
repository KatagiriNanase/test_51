#include "Int_KeyMatrix.h"
#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>
#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03

void main()
{
    u8 key;
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