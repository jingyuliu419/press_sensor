#ifndef __WIFI_H__
#define __WIFI_H__	
#include "sys.h"
#include "stdio.h"
#include "sys.h"
#include "stdarg.h"	 
#include "string.h"	

//串口3相关宏定义
#define USART3_MAX_RECV_LEN		800					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		800					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.





void init_wifi_STA(void);
void u3_printf(char* fmt,...);





#endif
