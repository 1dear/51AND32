/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_timer.c
 * 摘要：
 *  
 * 修改历史     版本号       Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/
#include "main.h"
#include "driver_timer.h"

/*
 * 定义全局变量
*/
TIM_HandleTypeDef htim;

/*
 *  函数名：void TimerInit(void)
 *  输入参数：
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化定时器，使其时钟频率为4MHz
*/
void TimerInit(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
  
    htim.Instance               = TIM2;
    htim.Init.Prescaler         = 72-1;                             // HCLK = 72MHz, 72MHz/72 = 1MHz
    htim.Init.Period            = 0;                                // 即每1us会计数满一次
    htim.Init.CounterMode       = TIM_COUNTERMODE_UP;               // 向上计数，按上面两行的配置：
                                                                    // 每1MHz即1us会向上计数1次，当计数4次会引发定时器中断或产生溢出事件
    htim.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           // 定时器时钟不从HCLK分频
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   // 不重新装载或与装载
    
    // 初始化上面的参数
    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;       // 选用内部时钟作为定时器时钟源
    if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;               // 计数器复位不产生更新事件
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;  // 主从模式不使能
    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

#if 0
/*
 *  函数名：void us_timer_delay(uint16_t t)
 *  输入参数：t-延时时间us
 *  输出参数：无
 *  返回值：无
 *  函数作用：定时器实现的延时函数，延时时间为t us，为了缩短时间，函数体使用寄存器操作，用户可对照手册查看每个寄存器每一位的意义
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
 *  函数名：void us_timer_delay(uint16_t t)
 *  输入参数：t-延时时间us
 *  输出参数：无
 *  返回值：无
 *  函数作用：延时粗略实现的延时函数，延时时间为t us
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

