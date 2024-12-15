#include "Int_DS1302.h"
#include "Int_DS18B20.h"
#include "Int_OLED.h"
#include "STDIO.H"
char* WEEK_NAME[] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun" };

void main()
{
    Struct_Date st_date;
    char str1[17] = { 0 };
    char str2[17] = { 0 };
    char temp = 0;
    st_date.year = 24;
    st_date.month = 12;
    st_date.day = 15;
    st_date.hour = 22;
    st_date.minute = 31;
    st_date.second = 0;
    st_date.week = 7;
    Int_OLED_Init();
    Int_OLED_Clear();
    Int_DS1302_Init();
    Int_DS1302_SetDate(&st_date);
    Int_OLED_ShowStr(0, 2, "Stay in the past");
    while (1)
    {
        Int_DS1302_GetDate(&st_date);
        temp = Int_DS18B20_GetTemperature();
        sprintf(str1, "20%02d/%02d/%02d %s", (int)st_date.year, (int)st_date.month, (int)st_date.day, WEEK_NAME[st_date.week - 1]);
        sprintf(str2, "%02d:%02d:%02d Tmp:%02d", (int)st_date.hour, (int)st_date.minute, (int)st_date.second, (int)temp);
        Int_OLED_ShowStr(0, 0, str1);
        Int_OLED_ShowStr(0, 1, str2);
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

        Com_Util_Delay1ms(200);
    }
}