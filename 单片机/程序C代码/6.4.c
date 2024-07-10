#include <reg52.h>         // 导入头文件
#define uchar unsigned char// 预定义变量类型uchar   
#define uint unsigned int  // 预定义变量类型uint

////计数器T0中断服务程序
void timer0 () interrupt 1 // 计数器T0中断服务程序
{
	P0=~P0;                  //  LED灯状态取反               
}
void main()                //  主函数             
{
	P0=0x00;                 //  LED灯状态初始化，全亮             
	TMOD=0x06;               //  设置T0的工作方式               
	TH0=0xfd;                //  设置T0的初值寄存器
	TL0=0xfd;                //  设置T0的初值寄存器
	EA=1;                    //  打开中断允许总开关
	ET0=1;                   //  打开计数器中断允许开关
	TR0=1;                   //  启动计数器
	while(1);                //  等待
}