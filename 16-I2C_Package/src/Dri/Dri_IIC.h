#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__
#include <STC89C5xRC.H>
#include "Com_Util.h"
void Dri_IIC_Start();

void Dri_IIC_SendByte(u8 byte);

bit Dri_IIC_ReceiveAck();

void Dri_IIC_ReceiveByte();

void Dri_IIC_SendAck(bit ack);

void Dri_IIC_Stop();


#endif /* __DRI_IIC_H__ */