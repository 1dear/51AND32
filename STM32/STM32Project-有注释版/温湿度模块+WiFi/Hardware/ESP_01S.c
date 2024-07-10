#include "stm32f10x.h" // Device header
#include "ESP_01S.h"
#include"Delay.h"
#include "OLED.h"
#include<stdio.h>
#include<stdlib.h>
uint8_t ESP01S_RxData[100];//接收数据
uint8_t ESP01S_RxFlag;//接收标志位
static uint8_t cur_pos;//当前传输到数据位置

typedef struct RecvData
{
    uint8_t ESP01S_RxData[100];
    uint8_t ESP01S_RxFlag;//接收标志位
    uint8_t cur_pos;//当前传输到数据位置
}RecvData;


RecvData rxData;
// 1.	A2 	2tx  ,A3 2rx
void ESP_01S_Init()
{ 
    // 打开APB1的外设，串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 设置GPIO2，3 复用推挽输出
    GPIO_InitTypeDef GPIO_InitStruture;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruture.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruture);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;         // 不需要校验
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 字长
    USART_Init(USART2, &USART_InitStructure);

    // //开启哪一个中断
    // USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    // //配置NVIC为分组2-----------怎么分？？？？？？？？？？？？
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // NVIC_InitTypeDef NVIC_InitTypeStructure;
    // NVIC_InitTypeStructure.NVIC_IRQChannel=USART1_IRQn;
    // NVIC_InitTypeStructure.NVIC_IRQChannelCmd=ENABLE;
    // NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority=NVIC_PriorityGroup_0;
    // NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority=NVIC_PriorityGroup_0;
    // NVIC_Init(&NVIC_InitTypeStructure);

    //启动串口
    USART_Cmd(USART2,ENABLE);
}


static void Send_Byte(uint8_t byte)
{
    USART_SendData(USART2,byte);
    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//等待发送完毕
}


void ESP_01S_SendString(char * str)
{
    uint16_t i=0;
    while(str[i])
    {

        Send_Byte(str[i]);
        ++i;
    }
}


//////////////////////////////////////ESP-01S指令

//测试是否有用
void AT()
{
     ESP_01S_SendString("AT\r\n");
     
}
/// @brief 设置WIFI应用模式
void AT_CWMODE()
{
     ESP_01S_SendString("AT+CWMODE=1\r\n");
}
/// @brief 连接WiFi
void AT_CWJAP()
{
    char str[100];
	//设置WIFI连接
	sprintf(str,"AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_SSID,WIFI_PASSWORD);
	ESP_01S_SendString(str);
	
}

/// @brief 与服务器建立TCP连接
void AT_CIPSTART()
{
     char str[100];
	//设置WIFI连接
	sprintf(str,"AT+CIPSTART=\"TCP\",\"192.168.98.143\",5000\r\n");
	ESP_01S_SendString(str);
}
/// @brief 设置透传模式
void AT_CIPMODE()
{
    ESP_01S_SendString("AT+CIPMODE=1\r\n");
}
/// @brief 开始透传
void AT_CIPSEND()
{
    ESP_01S_SendString("AT+CIPSEND\r\n");
}
/// @brief 退出透传模式
void AT_EXIT_CIPSEND()
{
    ESP_01S_SendString("+++");
}
//////////////////////////////////////ESP-01S指令


///////////////////////////////////Tcp处理部分-----透传模式

/// @brief TCP连接
void TCP_Connect()
{
    static time_update =0;
    AT();
    Delay_s(1);
    //设置为station模式
    AT_CWMODE();
    Delay_s(1+time_update*0.5);
    //加入接入点
    AT_CWJAP();
    Delay_s(10+time_update);
    //与TCP相连接
    AT_CIPSTART();
    Delay_s(10+time_update);
    ++time_update;
}
/// @brief 关闭服务器
void TCP_Close()
{
    ESP_01S_SendString("AT+CIPCLOSE\r\n");
   
}
/// @brief TCP发送
void TCP_CIP_SEND()
{
    //设置为透传模式
    AT_CIPMODE();
    Delay_ms(500);
    //开始透传
    AT_CIPSEND();
    Delay_s(1);
    
}

/// @brief 接收中断
/// @param  
// void USART2_IRQHandler(void)
// {
//     //单片机空间不够怎么搞？？？？？
// 	//串口接收，可以使用查询（在主函数里不断判断RXNE标志位）和中断两种方法
// 	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
// 	{
// 		ESP01S_RxData[cur_pos++] = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
// 		ESP01S_RxFlag = 1;										//置接收标志位变量为1
// 		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
// 																//读取数据寄存器会自动清除此标志位
// 																//如果已经读取了数据寄存器，也可以不执行此代码
// 	}
// }
///////////////////////////////////Tcp处理部分-----透传模式




//////////////////////////////////////////////////////////HTTTP

/// @brief 制作请求行
/// @param line 请求行，
/// @param method 请求方法
/// @param url 请求路由
void make_requestLine(char* line, char* method, char* url)
{
    sprintf(line, "%s %s HTTP/1.1\r\n", method, url);
}

/// @brief 制作请求头部
/// @param header 请求头部
/// @param content_Type 请求类型
/// @param value 请求值
void make_requestHeader(char* header, char* content_Type, char* value)
{
    sprintf(header, "%s:%s\r\n", content_Type, value);
    //注意最后的请求头部有一个\r\n
}

uint16_t strlenGet(char* str)
{
    uint16_t length = 0;
    char* ptr = str;
    while (*ptr++)
    {
        length++;

    }
    return length;
}
/// @brief 温度和湿度的json制作
/// @param data 需要封装成json的数据
/// @param Hvalue 温度值
/// @param Tvalue 湿度值
void json_DHT11(char* data, uint8_t Hvalue,uint8_t Tvalue)
{
    sprintf(data, "{\"temperature\":%d,\"humidity\":%d}", Tvalue, Hvalue);
}
void make_request(char* request,char *data)
{
    /*
    问题：当传过来的字符数组长度小于处理的长度时会这么办
    */
    uint16_t data_length = 0;
    char line[100];
    char header[100];
    // char data[100];
    //请求数据
    //sprintf(data, "{\"temperature\":25,\"humidity\":50}");
    data_length = strlenGet(data);
    //请求行
    make_requestLine(line, "POST", "/");
    sprintf(header, "Host: 192.168.98.143:5000\r\nContent-Type: application/json\r\nContent-Length: %d\r\n", data_length);
    //请求头部最后有一个\r\n
    sprintf(request, "%s%s\r\n%s", line, header, data);

}

//////////////////////////////////////////////////////////HTTTP