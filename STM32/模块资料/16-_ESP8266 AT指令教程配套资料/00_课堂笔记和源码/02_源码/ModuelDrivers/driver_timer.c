/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 * 
 * �ļ����ƣ�driver_timer.c
 * ժҪ��
 *  
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
#include "main.h"
#include "driver_timer.h"

/*
 * ����ȫ�ֱ���
*/
TIM_HandleTypeDef htim;

/*
 *  ��������void TimerInit(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ����ʱ����ʹ��ʱ��Ƶ��Ϊ4MHz
*/
void TimerInit(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
  
    htim.Instance               = TIM2;
    htim.Init.Prescaler         = 72-1;                             // HCLK = 72MHz, 72MHz/72 = 1MHz
    htim.Init.Period            = 0;                                // ��ÿ1us�������һ��
    htim.Init.CounterMode       = TIM_COUNTERMODE_UP;               // ���ϼ��������������е����ã�
                                                                    // ÿ1MHz��1us�����ϼ���1�Σ�������4�λ�������ʱ���жϻ��������¼�
    htim.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           // ��ʱ��ʱ�Ӳ���HCLK��Ƶ
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   // ������װ�ػ���װ��
    
    // ��ʼ������Ĳ���
    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;       // ѡ���ڲ�ʱ����Ϊ��ʱ��ʱ��Դ
    if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;               // ��������λ�����������¼�
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;  // ����ģʽ��ʹ��
    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

#if 0
/*
 *  ��������void us_timer_delay(uint16_t t)
 *  ���������t-��ʱʱ��us
 *  �����������
 *  ����ֵ����
 *  �������ã���ʱ��ʵ�ֵ���ʱ��������ʱʱ��Ϊt us��Ϊ������ʱ�䣬������ʹ�üĴ����������û��ɶ����ֲ�鿴ÿ���Ĵ���ÿһλ������
*/
void us_timer_delay(uint16_t t)
{
    uint16_t counter = 0;
	__HAL_TIM_SET_AUTORELOAD(&htim, t);		
	__HAL_TIM_SET_COUNTER(&htim, counter);
	HAL_TIM_Base_Start(&htim);
	while(counter != t)
	{
		counter = __HAL_TIM_GET_COUNTER(&htim);
	}
	HAL_TIM_Base_Stop(&htim);
}
#else
/*
 *  ��������void us_timer_delay(uint16_t t)
 *  ���������t-��ʱʱ��us
 *  �����������
 *  ����ֵ����
 *  �������ã���ʱ����ʵ�ֵ���ʱ��������ʱʱ��Ϊt us
*/
void us_timer_delay(uint16_t t)
{
    uint16_t counter = 0;
	
	while(t--)
	{
		counter=10; 
		
		while(counter--) ;    
	}
}
#endif


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    __HAL_RCC_TIM2_CLK_ENABLE();
}

