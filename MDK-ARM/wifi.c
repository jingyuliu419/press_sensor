#include "wifi.h"

const u8* ip="192.168.31.161";	
const u8* portnum="8000";	

//WIFI STAģʽ,����Ҫȥ���ӵ�·�������߲���,��������Լ���·��������,�����޸�.
const u8* wifista_ssid="wsn";
const u8* wifista_encryption="wpawpa2_aes";
const u8* wifista_password="wsn123456";

__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	  
 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
		while((USART3->SR&0X40)==0);			//ѭ������,ֱ���������   
		USART3->DR=USART3_TX_BUF[j];  
	} 
}

int atk_8266_at_response_dump()
{
	char *resp;
	/* TODO: get u3 */

	printf("resp:%s\r\n", resp);
}

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u3_printf("%s\r\n",cmd);
	printf("%s\r\n",cmd);
	if(waittime)
	{
		while(--waittime)
		{
			HAL_Delay(10);
		}
	}

	atk_8266_at_response_dump();
	return 0;
}

u8 cmd[32];
void init_wifi_STA()
{
	u8 *p=cmd;
	HAL_Delay(10);
	atk_8266_send_cmd("AT+CWMODE=1","OK",20);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","OK",500);		//DHCP�������ر� 3s�ĵȴ������Ǳ�Ҫ�ģ���
	atk_8266_send_cmd("AT+CWJAP=\"wsn\",\"wsn123456\"","WIFI GOT IP",800);//5s�ĵȴ�WIFI�Ǳ�Ҫ�ģ���
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);  //������ģʽ
	atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"192.168.31.101\",8000","OK",20);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",20);//����ģʽΪ��͸��	
	atk_8266_send_cmd("AT+CIPSEND","OK",20);//��ʼ͸��   
	
	//���ӳɹ�У����LEDָʾ
	//TODO
	printf("config ok\n");
	u3_printf("test client\n");
	
}

