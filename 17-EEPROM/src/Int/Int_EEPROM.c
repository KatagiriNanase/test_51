#include "Int_EEPROM.h"
#include "Dri_IIC.h"
#include "Com_Util.h"
#define EEPROM_ADDR_W 0xA0 //1010 0000
#define EEPROM_ADDR_R 0xA1 //1010 0001
#define PAGE_SIZE 16
void Int_EEPROM_WritePage(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    //发送开始信号
    Dri_IIC_Start();
    //发送设备地址
    Dri_IIC_SendByte(EEPROM_ADDR_W);
    Dri_IIC_ReceiveAck();
    //发送写入地址
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();
    //页写数据
    for (i = 0;i < len;++i)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }
    //发送停止数据
    Dri_IIC_Stop();
    //等待tWR周期
    Com_Util_Delay1ms(5);
}

//递归
// void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
// {
//     u8 page_remain = PAGE_SIZE - addr % PAGE_SIZE;
//     //判断当前页是否够
//     if (len > page_remain)
//     {
//         //不够，先写满这一页
//         Int_EEPROM_WritePage(addr, bytes, page_remain);
//         //然后再写下一行（递归）
//         Int_EEPROM_WriteBytes(addr + page_remain, bytes + page_remain, len - page_remain);
//     }
//     else
//         //这页够了就直接写
//         Int_EEPROM_WritePage(addr, bytes, len);

// }

//迭代
void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
{
    while (1)
    {
        u8 page_remain = PAGE_SIZE - addr % PAGE_SIZE;
        if (len > page_remain)
        {
            //写满当前页
            Int_EEPROM_WritePage(addr, bytes, page_remain);
            //改变写入地址、起始位置、剩余页数
            addr += page_remain;
            bytes += page_remain;
            len -= page_remain;
        }
        else
        {
            Int_EEPROM_WriteBytes(addr, bytes, len);
            break;
        }
    }
}

void Int_EEPROM_ReadBytes(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR_W);
    Dri_IIC_ReceiveAck();

    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();

    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR_R);
    Dri_IIC_ReceiveAck();

    for (i = 0;i < len;++i)
    {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_IIC_SendAck(i == len - 1 ? 1 : 0);
    }

    Dri_IIC_Stop();
}
