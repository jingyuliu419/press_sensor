#ifndef __WIFI_H__
#define __WIFI_H__	
#include "sys.h"
#include "stdio.h"
#include "sys.h"
#include "stdarg.h"	 
#include "string.h"	

//����3��غ궨��
#define USART3_MAX_RECV_LEN		800					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		800					//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.





void init_wifi_STA(void);
void u3_printf(char* fmt,...);





#endif
