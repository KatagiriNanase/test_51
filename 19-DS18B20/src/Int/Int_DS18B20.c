#include "Int_DS18B20.h"
#include "Com_Util.h"
#include "Dri_1Wire.h"
#define ROM_SKIP 0xCC
#define TEMP_CONV 0x44
#define READ_REG 0xBE
void Int_DS18B20_TemperatureConversion()
{
    Dri_1Wire_Init();
    Dri_1Wire_WriteByte(ROM_SKIP);
    Dri_1Wire_WriteByte(TEMP_CONV);

}

void Int_DS18B20_ReadRegister()
{
    Dri_1Wire_Init();
    Dri_1Wire_WriteByte(ROM_SKIP);
    Dri_1Wire_WriteByte(READ_REG);

}


char Int_DS18B20_GetTemperature()
{
    u8 ls_byte;
    u8 ms_byte;
    //³õÊ¼»¯
    //ROMÃüÁî
    //ÎÂ¶È×ª»»
    Int_DS18B20_TemperatureConversion();
    //³õÊ¼»¯
    //ROMÃüÁî
    //¶ÁÈ¡Ôİ´æ¼Ä´æÆ÷
    Int_DS18B20_ReadRegister();
    ls_byte = Dri_1Wire_ReadByte();
    ms_byte = Dri_1Wire_ReadByte();

    //´¦ÀíÎÂ¶È
    return (ls_byte >> 4) | (ms_byte << 4);

}