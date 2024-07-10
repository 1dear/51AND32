#include "stm32f10x.h" // Device header
#include <stdio.h>
#include <stdarg.h>

#include"Delay.h"
#include "serial.h"

void Serial_Init()
{
    // 打开APB2的外设，串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // 设置GPIO9，10 复用推挽输出
    GPIO_InitTypeDef GPIO_InitStruture;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruture.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruture);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;        // 不需要校验
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 字长
    USART_Init(USART1, &USART_InitStructure);



    //开启哪一个中断
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    //配置NVIC为分组2-----------怎么分？？？？？？？？？？？？
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitTypeStructure;
    NVIC_InitTypeStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitTypeStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority=NVIC_PriorityGroup_0;
    NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority=NVIC_PriorityGroup_0;
    NVIC_Init(&NVIC_InitTypeStructure);
    //启动串口
    USART_Cmd(USART1,ENABLE);
}

static void Send_Byte(uint8_t byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待发送完毕
}

static void Receive_Byte(uint8_t byte)
{
    USART_ReceiveData(USART1);
}
void Serial_SendString(char * str)
{
    uint16_t i=0;
    while(str[i])
    {

        Send_Byte(str[i]);
        ++i;
    }
}
//怎么找？？？？？？？？？？？？？？？？
void USART1_IRQHandler(void)
{

}