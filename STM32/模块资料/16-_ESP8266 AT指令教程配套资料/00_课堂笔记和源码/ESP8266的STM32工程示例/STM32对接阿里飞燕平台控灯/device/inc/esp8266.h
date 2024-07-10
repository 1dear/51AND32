#ifndef __ESP8266_H
#define __ESP8266_H 			   
#include "stm32f10x.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

#define ESP8266_USART(fmt, ...)  USART_printf (USART2, fmt, ##__VA_ARGS__)    
#define PC_USART(fmt, ...)       printf(fmt, ##__VA_ARGS__)       //这是串口打印函数，串口1，执行printf后会自动执行fput函数，重定向了printf。



#define RX_BUF_MAX_LEN 1024       //最大字节数
extern struct STRUCT_USART_Fram   //数据帧结构体
{
    char Data_RX_BUF[RX_BUF_MAX_LEN];
    union 
    {
        __IO u16 InfAll;
        struct 
        {
            __IO u16 FramLength       :15;                               // 14:0 
            __IO u16 FramFinishFlag   :1;                                // 15 
        }InfBit;
    }; 
	
}ESP8266_Fram_Record_Struct;


//初始化和TCP功能函数
void ESP8266_Init(u32 bound);
void ESP8266_AT(void);
void ESP8266_Send_AT_Cmd(char *cmd,u32 time);
void ESP8266_set_model(char *temp);
void ESP8266_get_mac(void);
void ESP8266_get_version(void);
void ESP8266_net(void);
bool ESP8266_Scan(void);
bool ESP8266_Scan1(void);
void ESP8266_RECVJSON(void);
void ESP8266_LED_ON(void);
void ESP8266_LED_OFF(void);
void USART_printf( USART_TypeDef * USARTx, char * Data, ... );

#endif
