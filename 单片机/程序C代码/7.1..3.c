#include "reg52.h"
#define uchar unsigned char    
#define uint unsigned int

sbit buzz=P2^2;//蜂鸣器
sbit key1=P2^7;//按键
bit start;    //报警触发的变量
uchar num;    //21个音的计数
uint timer;   //定时器初值
//频率表
code uint pinlv[]={466,523,587,659,698,784,880,//低音
	                932,1047,1175,1319,1397,1568,1760,//中音
                  1865,2094,2351,2633,2792,3134,3517};//高音

void delayms(uint ms);
void delay(uchar t);									
void play();
void main()
{
	buzz=1;
	TMOD=0x01;
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
			play();
			start=0;
		}
	}
}
void timer0() interrupt 1
{	
	TH0=timer/256;
	TL0=timer%256;	
	buzz=~buzz;	
}
void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=114;j>0;j--);
}
void delay(uchar t)
{
	uint i,j;
	for(i=t;i>0;i--)
		for(j=29000;j>0;j--);
}
void play()
{
	for(num=0;num<21;num++)
	{
		TR0=1;
		timer=65536-(11059200/12)/(pinlv[num]*2);
		TH0=timer/256;
		TL0=timer%256;	
		delay(1);
	}	
	TR0=0;
}

