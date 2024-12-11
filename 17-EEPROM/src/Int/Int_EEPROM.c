#include "Int_EEPROM.h"
#include "Dri_IIC.h"
#include "Com_Util.h"
#define EEPROM_ADDR_W 0xA0 //1010 0000
#define EEPROM_ADDR_R 0xA1 //1010 0001
#define PAGE_SIZE 16
void Int_EEPROM_WritePage(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    //���Ϳ�ʼ�ź�
    Dri_IIC_Start();
    //�����豸��ַ
    Dri_IIC_SendByte(EEPROM_ADDR_W);
    Dri_IIC_ReceiveAck();
    //����д���ַ
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();
    //ҳд����
    for (i = 0;i < len;++i)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }
    //����ֹͣ����
    Dri_IIC_Stop();
    //�ȴ�tWR����
    Com_Util_Delay1ms(5);
}

//�ݹ�
// void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
// {
//     u8 page_remain = PAGE_SIZE - addr % PAGE_SIZE;
//     //�жϵ�ǰҳ�Ƿ�
//     if (len > page_remain)
//     {
//         //��������д����һҳ
//         Int_EEPROM_WritePage(addr, bytes, page_remain);
//         //Ȼ����д��һ�У��ݹ飩
//         Int_EEPROM_WriteBytes(addr + page_remain, bytes + page_remain, len - page_remain);
//     }
//     else
//         //��ҳ���˾�ֱ��д
//         Int_EEPROM_WritePage(addr, bytes, len);

// }

//����
void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
{
    while (1)
    {
        u8 page_remain = PAGE_SIZE - addr % PAGE_SIZE;
        if (len > page_remain)
        {
            //д����ǰҳ
            Int_EEPROM_WritePage(addr, bytes, page_remain);
            //�ı�д���ַ����ʼλ�á�ʣ��ҳ��
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
