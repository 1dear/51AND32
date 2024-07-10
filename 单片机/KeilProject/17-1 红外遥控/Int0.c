#include <REGX52.H>

/**
  * @brief  外部中断0初始化
  * @param  无
  * @retval 无
  */
void Int0_Init(void)
{
	IT0=1;
	IE0=0;
	EX0=1;
	EA=1;
	PX0=1;//高优先级更为合适，要打断其他优先级的中断，进行中断嵌套，防止解码错误
}

/*外部中断0中断函数模板
void Int0_Routine(void) interrupt 0
{
	
}
*/
