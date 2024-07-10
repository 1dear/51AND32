#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_it.h"
#include "aliyun.h"
#include "esp8266.h"
#include "key.h"
#include "timer.h"


/*
 * Copyright (c) 2020-2021 AIThinker.yangbin All rights reserved.
 *
 * ������ֻ��STM32�Խ�ESP8266������demo�������ο�������֤�����ȶ���,
 * �����̲ο������߽�����ֲ������Ϊhttps://blog.csdn.net/it_boy__/article/details/71975797
 * ���ս���Ȩ�������а��ſɿƼ����޹�˾���С�
 *
 * 
 */

int main(void)
{
	delay_init();
	LED_Init();
	uart3_Init(115200);
	ESP8266_Init(115200);
	KEY_Init();
	TIM3_PWM_Init(800-1,0);
	TIM_SetCompare2(TIM3,0);
	while(1)
	{
		ESP8266_aliyun_Test();//�����׼ҹ̼�
	}
}
