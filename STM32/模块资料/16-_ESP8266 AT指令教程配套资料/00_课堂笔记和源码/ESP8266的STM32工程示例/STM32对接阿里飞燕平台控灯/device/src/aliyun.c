#include "aliyun.h"
#include "usart.h"
#include "esp8266.h"
#include "delay.h"
#include "key.h"

void ESP8266_aliyun_Test(void)
{
	vu8 key=0;
	ESP8266_get_mac();
	ESP8266_get_version();
	while(ESP8266_Scan())
	{
 		key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//进入配网模式
					ESP8266_LED_ON();
					ESP8266_net();
				  
					break;
				case KEY1_PRES:
					ESP8266_AT();
					break;
			}
		}
		else			
		delay_ms(10);
	};
	while(ESP8266_Scan1())
	{
		ESP8266_RECVJSON();
	}
}
