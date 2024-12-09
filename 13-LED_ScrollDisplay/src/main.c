#include "Int_LEDLattice.h"
#include "Dri_Timer0.h"
#define MAX_ROW 8
void main()
{
    u8 i;
    u8 pic1[MAX_ROW] = {
    0x66,
    0xFF,
    0xFF,
    0xFF,
    0x7E,
    0x3C,
    0x18,
    0x00
    };


    
    u8 pic2[MAX_ROW] = {
0x00,
0x66,
0x99,
0x91,
0x89,
0x52,
0x2C,
0x18




    };
    Dri_Timer0_Init();
    Int_LEDLattice_Init();

    while (1)
    {
        Int_LEDLattice_SetPic(pic1);
        Com_Util_Delay1ms(500);
        Int_LEDLattice_SetPic(pic2);
        Com_Util_Delay1ms(500);
    }
}