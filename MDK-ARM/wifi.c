#include "wifi.h"

const u8* ip="192.168.31.161";	
const u8* portnum="8000";	

//WIFI STA模式,设置要去连接的路由器无线参数,请根据你自己的路由器设置,自行修改.
const u8* wifista_ssid="wsn";			//路由器SSID号
const u8* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes加密方式
const u8* wifista_password="wsn123456"; 	//连接密码

//串口发送缓存区 	
__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节  	  
//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
		while((USART3->SR&0X40)==0);			//循环发送,直到发送完毕   
		USART3->DR=USART3_TX_BUF[j];  
	} 
}

//将收到的AT指令应答数据返回给电脑串口
//mode:0,不清零USART3_RX_STA;
//     1,清零USART3_RX_STA;
void atk_8266_at_response(u8 mode)
{
	
}
//向ATK-ESP8266发送命令
//cmd:发送的命令字符串
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u3_printf("%s\r\n",cmd);	//发送命令
	if(waittime)
	{
		while(--waittime)
		{
			HAL_Delay(10);
		}
	}
	return 0;
}

u8 cmd[32];
void init_wifi_STA()
{
	u8 *p=cmd;
	HAL_Delay(10);
	atk_8266_at_response(1);
	atk_8266_send_cmd("AT+CWMODE=1","OK",20);		//设置WIFI STA模式
	atk_8266_send_cmd("AT+RST","OK",500);		//DHCP服务器关闭 3s的等待启动是必要的！！
	atk_8266_send_cmd("AT+CWJAP=\"wsn\",\"wsn123456\"","WIFI GOT IP",800);//5s的等待WIFI是必要的！！
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);  //单链接模式
	atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"192.168.31.161\",8000","OK",20);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",20);//传输模式为：透传	
	atk_8266_send_cmd("AT+CIPSEND","OK",20);//开始透传   
	
	//连接成功校验与LED指示
	//TODO
	printf("config ok\n");
	//u3_printf("test client\n");
	
}

