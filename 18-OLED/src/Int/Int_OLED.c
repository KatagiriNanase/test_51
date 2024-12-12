#include "Int_OLED.h"
#include "Dri_IIC.h"
#define OLED_ADDR 0x78
#define DATA_MODE_CON 0x40
#define CMD_MODE_CON 0x00
void Int_OLED_WriteDate(u8* bytes, u8 len)
{
    u8 i;

    Dri_IIC_Start();
    //���ʹ��豸��ַ
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();
    //��������ģʽ������д��
    Dri_IIC_SendByte(DATA_MODE_CON);
    Dri_IIC_ReceiveAck();
    //����д������
    for (i = 0;i < len;++i)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();



}

void Int_OLED_WriteCmd(u8* bytes, u8 len)
{
    u8 i;

    Dri_IIC_Start();
    //���ʹ��豸��ַ
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();
    //��������ģʽ������д��
    Dri_IIC_SendByte(CMD_MODE_CON);
    Dri_IIC_ReceiveAck();
    //����д���������
    for (i = 0;i < len;++i)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();
}

void Int_OLED_Init()
{
    u8 cmd[6];
    //�ر���Ļ
    cmd[0] = 0xAE;
    //����ӳ��
    cmd[1] = 0xC8;
    //����ӳ��
    cmd[2] = 0xA1;
    //������ɱ�
    cmd[3] = 0x8D;
    cmd[4] = 0x14;
    //������Ļ
    cmd[5] = 0xAF;

    //��������
    Int_OLED_WriteCmd(cmd, 6);
}

void Int_OLED_Clear()
{
    u16 i;
    u8 addr_mode[2];
    u8 cmd[2] = { 0xAE,0xAF };
    //�ر���Ļ
    Int_OLED_WriteCmd(cmd, 1);
    addr_mode[0] = 0x20;
    addr_mode[1] = 0x00;
    //����ˮƽѰַ
    Int_OLED_WriteCmd(addr_mode, 2);

    Dri_IIC_Start();
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(DATA_MODE_CON);
    Dri_IIC_ReceiveAck();
    for (i = 0;i < 128 * 8;++i)
    {
        Dri_IIC_SendByte(0x00);
        Dri_IIC_ReceiveAck();
    }
    //������Ļ
    Int_OLED_WriteCmd(cmd + 1, 1);
}
