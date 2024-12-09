#include "Int_LEDLattice.h"
#include "Dri_Timer0.h"
void main()
{
    u8 pic[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };
    Dri_Timer0_Init();
    Int_LEDLattice_Init();
    Int_LEDLattice_SetPic(pic);

    while (1)
    {

    }
}