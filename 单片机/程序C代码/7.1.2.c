#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int
sbit buzz=P2^2;//蜂鸣器
sbit key1=P2^7;//按键
bit start;   //报警触发的变量
uchar num=10;  //响停的循环次数
uint timer;   //定时器初值
uint pinlv=500;//方波的频率
void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}
void baojing()
{
	for(num=10;num>0;num--)
	{
		TR0=~TR0;
		delayms(500);
	}	
}
void timer0() interrupt 1
{	
	TH0=timer/256;
	TL0=timer%256;	
	buzz=~buzz;	
}
void main()
{
	buzz=1;
	TMOD=0x01;
	timer=65536-(11059200/12)/(pinlv*2);
	TH0=timer/256;
	TL0=timer%256;	
	EA=1;
	ET0=1;
	while(1)
	{
		if(!key1)
		{
			delayms(10);
			if(key1==0)
				start=1;
		}
		if(start)
		{
			baojing();
			start=0;
		}
	}
}


