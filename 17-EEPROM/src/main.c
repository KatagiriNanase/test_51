#include "Int_EEPROM.h"
#include "Int_LEDLattice.h"
#include "Dri_Timer0.h"
#include "Int_Key.h"
#define MAX_ROW 8
u8 buffer1[MAX_ROW], buffer2[MAX_ROW];

void Change_Pic();

void main()
{
    //  u8 bilibli1[8] = { 0x42,0x24,0xFF,0x81,0xA5,0x81,0x99,0xFF };
    //  u8 bilibli2[8] = { 0x00,0x66,0xFF,0x81,0xE7,0x81,0x99,0xFF };
    // u8 heart_full[MAX_ROW] = { 0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,0x00 };
    // u8 heart_break[MAX_ROW] = { 0x00,0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18 };

    // u8 i;
    Dri_Timer0_Init();
    Int_LEDLattice_Init();
    // Int_EEPROM_WriteBytes(16, heart_full, MAX_ROW);
    // Int_EEPROM_WriteBytes(16 + MAX_ROW, heart_break, MAX_ROW);
    Dir_Timer0_RegisterCallBack(Change_Pic);

    while (1)
    {
        Int_LEDLattice_SetPic(buffer1);
        Com_Util_Delay1ms(500);
        Int_LEDLattice_SetPic(buffer2);
        Com_Util_Delay1ms(500);
    }
}

void Change_Pic()
{
    if (Int_Key_IsSw3Pressed())
    {
        Int_EEPROM_ReadBytes(16, buffer1, MAX_ROW);
        Int_EEPROM_ReadBytes(16 + MAX_ROW, buffer2, MAX_ROW);
    }

    if (Int_Key_IsSw4Pressed())
    {
        Int_EEPROM_ReadBytes(0, buffer1, MAX_ROW);
        Int_EEPROM_ReadBytes(0 + 8, buffer2, MAX_ROW);
    }
}
