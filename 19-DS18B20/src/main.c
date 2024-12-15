#include "Int_DS18B20.h"
#include "Int_OLED.h"
// #include "Int_LEDLattice.h"
// #include <STRING.H>
// #include <STC89C5xRC.H>
// #include "Dri_Timer0.h"
// u8 buffer1[8];
// u8 buffer2[8];

// code const u8 warm[16] = { 0x00,0x00,0x42,0xA5,0x00,0x24,0x18,0x00,0x00,
//                             0x00,0xE7,0x00,0x00,0x00,0x24,0x18 };

// code const u8 cold[16] = { 0x00,0x55,0x22,0x00,0x00,0x00,0x3C,0x00,
//                             0x00,0x00,0xE7,0x00,0x00,0x00,0x18,0x24 };
// code const u8 hot[16] = { 0x00,0x00,0x42,0x24,0x00,0x3C,0x24,0x3C,
//                             0x81,0x42,0x24,0x00,0x7E,0x42,0x42,0x7E };

void main()
{
    char temp = 0;
    // u8 i = 0;
    // u8 j = 0;
    Int_OLED_Init();
    Int_OLED_Clear();
    //Int_LEDLattice_Init();

    while (1)
    {
        Int_OLED_ShowStr(0, 0, "Now Temperature:");
        temp = Int_DS18B20_GetTemperature();
        Int_OLED_ShowNum(7, 1, temp);
        if (temp < 10)
        {
            Int_OLED_ShowStr(5, 3, "Cold! TAT");
        }

        if (temp >= 10 && temp < 20)
        {
            Int_OLED_ShowStr(2, 3, "just so so= = ");
        }

        if (temp >= 20 && temp < 30)
        {

            // memcpy(buffer1, warm, 8);
            Int_OLED_ShowStr(2, 3, "Warm (` v `) ");
        }
        if (temp >= 30)
        {
            Int_OLED_ShowStr(2, 3, "Hot! ");
        }

        // P0 = ~(0x01 << i);
        // ++i;
        // Com_Util_Delay1ms(50);
        // if (i == 9)
        //     i = 0;
        Com_Util_Delay1ms(500);

    }
}



// void Change_Pic()
// {
//     static u16 count = 0;
//     count++;

//     if (count >= 500)
//     {

// }