#include "Int_OLED.h"
#include "Dri_IIC.h"
#define OLED_ADDR 0x78
#define DATA_MODE_CON 0x40
#define CMD_MODE_CON 0x00
void Int_OLED_WriteDate(u8* bytes, u8 len)
{
    u8 i;

    Dri_IIC_Start();
    //发送从设备地址
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();
    //设置数据模式：连续写入
    Dri_IIC_SendByte(DATA_MODE_CON);
    Dri_IIC_ReceiveAck();
    //连续写入数据
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
    //发送从设备地址
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();
    //设置命令模式：连续写入
    Dri_IIC_SendByte(CMD_MODE_CON);
    Dri_IIC_ReceiveAck();
    //连续写入控制命令
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
    //关闭屏幕
    cmd[0] = 0xAE;
    //行重映射
    cmd[1] = 0xC8;
    //列重映射
    cmd[2] = 0xA1;
    //开启电荷泵
    cmd[3] = 0x8D;
    cmd[4] = 0x14;
    //开启屏幕
    cmd[5] = 0xAF;

    //发送命令
    Int_OLED_WriteCmd(cmd, 6);
}

void Int_OLED_Clear()
{
    u16 i;
    u8 addr_mode[2];
    u8 cmd[2] = { 0xAE,0xAF };
    //关闭屏幕
    Int_OLED_WriteCmd(cmd, 1);
    addr_mode[0] = 0x20;
    addr_mode[1] = 0x00;
    //设置水平寻址
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
    //开启屏幕
    Int_OLED_WriteCmd(cmd + 1, 1);
}
