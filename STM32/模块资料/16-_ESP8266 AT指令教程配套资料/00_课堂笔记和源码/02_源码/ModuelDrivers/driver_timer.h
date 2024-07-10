/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_timer.h
 * ժҪ��
 *  
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
#ifndef __DRIVER_TIMER_H
#define __DRIVER_TIMER_H

#include "stm32f1xx_hal.h"

/*
 *  ��������void TimerInit(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ����ʱ����ʹ��ʱ��Ƶ��Ϊ4MHz
*/
extern void TimerInit(void);

/*
 *  ��������void us_timer_delay(uint16_t t)
 *  ���������t-��ʱʱ��us
 *  �����������
 *  ����ֵ����
 *  �������ã���ʱ��ʵ�ֵ���ʱ��������ʱʱ��Ϊt us��Ϊ������ʱ�䣬������ʹ�üĴ����������û��ɶ����ֲ�鿴ÿ���Ĵ���ÿһλ������
*/
extern void us_timer_delay(uint16_t t);

#endif
