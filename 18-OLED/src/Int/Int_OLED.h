#ifndef __INT_OLED_H__
#define __INT_OLED_H__
#include "Com_Util.h"

void Int_OLED_WriteDate(u8* bytes, u8 len);

void Int_OLED_WriteCmd(u8* bytes, u8 len);

void Int_OLED_Init();

void Int_OLED_Clear();
#endif /* __INT_OLED_H__ */