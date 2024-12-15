#include "Dri_1Wire.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#define BUS P44 // 1wire ����


bit Dri_1Wire_Init()
{
    bit exist = 0;
    BUS = 0;
    //��ʱ480us
    Com_Util_Delay480us();
    //�ͷ�����
    BUS = 1;
    //��ʱ�ȴ���������
    Com_Util_Delay60us();
    exist = ~BUS;
    Com_Util_Delay420us();
    return exist;
}

void Dri_1Wire_WriteByte(u8 byte)
{
    u8 i;
    for (i = 0;i < 8;++i)
    {
            BUS = 0;
            //��ʱһ��
            BUS = byte & 0x01;
            byte >>= 1;
            //��ʱ60us����һ��дʱ��
            Com_Util_Delay60us();
            //�ͷ����ߣ�׼��������һʱ��
            BUS = 1;
    }
}

u8 Dri_1Wire_ReadByte()
{
    u8 i;
    u8 byte = 0;
    for (i = 0;i < 8;++i)
    {
        BUS = 0;
        //��ʱһ��
        //�ͷ�����
        BUS = 1;
        Com_Util_Delay10us();
        byte >>= 1;
        if (BUS == 1)
            byte |= 0x80;
        //��֤ʱ������60us
        Com_Util_Delay50us();
    }
    return byte;
}
