#include "esp8266.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include <stdarg.h>

struct STRUCT_USART_Fram ESP8266_Fram_Record_Struct = { 0 };  //定义了一个数据帧结构体
void ESP8266_Init(u32 bound)
{
    uart2_Init(bound); 
}

static int process_data(char *p)
{
  int data = 0;
	
	char * tmp = strstr(p,":");
	
	if(tmp == NULL) return -1;
	
	p = tmp + 1;
	
	tmp = strstr(p,"}");
	if(tmp == NULL) return -1;
  
  int len = tmp - p;
	
  while(len --)
  {
    data = data * 10 + *p - '0';
    p++;
  }
  
  return data;
}


//对ESP8266模块发送相关指令
// cmd 待发送的指令
void ESP8266_Send_AT_Cmd(char *cmd,u32 time)
{
		
    ESP8266_Fram_Record_Struct .InfBit .FramLength = 0; //重新接收新的数据包
	  memset(ESP8266_Fram_Record_Struct .Data_RX_BUF,0,sizeof(ESP8266_Fram_Record_Struct .Data_RX_BUF));
    ESP8266_USART("%s\r\n", cmd);
    delay_ms(time);   //延时
}



bool ESP8266_Scan(void)
{
	  if(strstr(ESP8266_Fram_Record_Struct.Data_RX_BUF,"CLOUD CONNECTED"))
		{
			ESP8266_LED_OFF();
			return false;
		}
		return true;
}

bool ESP8266_Scan1(void)
{
	int i;
	if(strstr(ESP8266_Fram_Record_Struct.Data_RX_BUF,"{\"LightSwitch\":1}"))
	{
			TIM_SetCompare2(TIM3,700);
			return true;
	}
	else if(strstr(ESP8266_Fram_Record_Struct.Data_RX_BUF,"{\"LightSwitch\":0}"))
	{
			TIM_SetCompare2(TIM3,0);
			return true;			
	}
	else
	{
			i = process_data(ESP8266_Fram_Record_Struct.Data_RX_BUF);
			if( i==-1)
			{
				return true;	
			}
	    //printf("%d\r\n",i);
			TIM_SetCompare2(TIM3,i);
			return true;			
	}
}

void ESP8266_AT(void)//发送该指令测试AT返回是否OK
{ 
    ESP8266_Send_AT_Cmd("AT+RESTORE",1000);
}


void ESP8266_get_mac(void)//查询模块的MAC地址
{
    char cStr [20];
	sprintf ( cStr, "AT+GETMAC");
	ESP8266_Send_AT_Cmd( cStr,1000);  
}

void ESP8266_get_version(void)//查询模块的MAC地址
{
    char cStr [20];
	sprintf ( cStr, "AT+VERSION");
	ESP8266_Send_AT_Cmd( cStr,1000);  
}
   
void ESP8266_net(void)//
{
  char cStr [20];
	sprintf ( cStr, "AT+ALISMARTCONFIG");
  ESP8266_Send_AT_Cmd( cStr,1000);
}

void ESP8266_RECVJSON(void)
{
  char cStr [20];
	sprintf ( cStr, "AT+RECVJSON");
  ESP8266_Send_AT_Cmd( cStr,100);
}

static char *itoa( int value, char *string, int radix )
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;

    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */


void USART_printf ( USART_TypeDef * USARTx, char * Data, ... )
{
    const char *s;
    int d;   
    char buf[16];


    va_list ap;
    va_start(ap, Data);

    while ( * Data != 0 )     // 判断数据是否到达结束符
    {                                         
        if ( * Data == 0x5c )  //'\'
        {                                     
            switch ( *++Data )
            {
                case 'r':                                     //回车符
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;

                case 'n':                                     //换行符
                USART_SendData(USARTx, 0x0a);   
                Data ++;
                break;

                default:
                Data ++;
                break;
            }            
        }

        else if ( * Data == '%')
        {                                     
            switch ( *++Data )
            {               
                case 's':                                         //字符串
                s = va_arg(ap, const char *);
                for ( ; *s; s++) 
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                }
                Data++;
                break;

                case 'd':           
                    //十进制
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++) 
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                }
                     Data++;
                     break;
                default:
                     Data++;
                     break;
            }        
        }
        else USART_SendData(USARTx, *Data++);
        while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );

    }
}
