#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__
typedef void (*Timer0_Callback)(void);

void Dri_Timer0_Init();

/**
* @brief ע��ص�����
*
* @param callback ����ָ��
* @return bit 1:�ɹ� 0:ʧ��
*/
bit Dir_Timer0_RegisterCallBack(Timer0_Callback callback);

/**
* @brief ȡ��ע��ص�����
*
* @param callback ����ָ��
* @return bit 1:�ɹ� 0:ʧ��
*/
bit Dir_Timer0_DeregisterCallBack(Timer0_Callback callback);



#endif /* __DRI_TIMER0_H__ */